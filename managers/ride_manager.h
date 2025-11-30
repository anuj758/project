#ifndef RIDE_MANAGER_H
#define RIDE_MANAGER_H

#include "../rides/ride.h"
#include "../users/rider.h"
#include "../users/driver.h"
#include "../strategies/matching_strategy.h"
#include "../observers/notification_observer.h"
#include "../pricing/fare_calculator.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

class RideManager {
private:
    static RideManager* instance;
    vector<shared_ptr<Rider>> riders;
    vector<shared_ptr<Driver>> drivers;
    unordered_map<string, shared_ptr<Ride>> rides;
    vector<shared_ptr<NotificationObserver>> observers;
    unique_ptr<MatchingStrategy> matchingStrategy;
    unique_ptr<FareCalculator> fareCalculator;
    int rideCounter;

    RideManager() : rideCounter(1) {
        matchingStrategy = make_unique<NearestDriverStrategy>();
        fareCalculator = make_unique<BaseFareCalculator>();
    }

public:
    static RideManager* getInstance() {
        if (instance == nullptr) {
            instance = new RideManager();
        }
        return instance;
    }
    
    // User Management
    void addRider(shared_ptr<Rider> rider) {
        riders.push_back(rider);
    }
    
    void addDriver(shared_ptr<Driver> driver) {
        drivers.push_back(driver);
    }
    
    // Observer Management
    void addObserver(shared_ptr<NotificationObserver> observer) {
        observers.push_back(observer);
    }
    
    void removeObserver(shared_ptr<NotificationObserver> observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }
    
    // Strategy Management
    void setMatchingStrategy(unique_ptr<MatchingStrategy> strategy) {
        matchingStrategy = move(strategy);
    }
    
    void setFareCalculator(unique_ptr<FareCalculator> calculator) {
        fareCalculator = move(calculator);
    }
    
    // Core Ride Operations
    shared_ptr<Ride> requestRide(const string& riderId, 
                               const Location& pickup,
                               const Location& dropoff,
                               VehicleType vehicleType,
                               RideType rideType = RideType::NORMAL) {
        
        // Find rider
        auto riderIt = find_if(riders.begin(), riders.end(),
            [&riderId](const shared_ptr<Rider>& r) {
                return r->getUserId() == riderId;
            });
        
        if (riderIt == riders.end()) {
            cout << "Rider not found!" << endl;
            return nullptr;
        }
        
        // Create ride
        string rideId = "RIDE_" + to_string(rideCounter++);
        auto ride = make_shared<Ride>(rideId, *riderIt, pickup, dropoff, vehicleType, rideType);
        
        // Find available driver
        vector<shared_ptr<Driver>> availableDrivers;
        for (const auto& driver : drivers) {
            if (driver->isAvailable()) {
                availableDrivers.push_back(driver);
            }
        }
        
        auto assignedDriver = matchingStrategy->findBestDriver(availableDrivers, *ride);
        
        if (assignedDriver) {
            ride->setDriver(assignedDriver);
            ride->setStatus(RideStatus::DRIVER_ASSIGNED);
            assignedDriver->setStatus(DriverStatus::ON_TRIP);
            
            rides[rideId] = ride;
            
            // Notify observers
            notifyDriverAssigned(ride);
            notifyRideStatusChanged(ride);
            
            cout << "Ride " << rideId << " created and driver " 
                 << assignedDriver->getName() << " assigned using " 
                 << matchingStrategy->getStrategyName() << endl;
        } else {
            cout << "No available drivers found for the requested vehicle type!" << endl;
            return nullptr;
        }
        
        return ride;
    }
    
    void startRide(const string& rideId) {
        auto it = rides.find(rideId);
        if (it != rides.end()) {
            auto ride = it->second;
            ride->setStatus(RideStatus::DRIVER_EN_ROUTE);
            notifyRideStatusChanged(ride);
            
            // Simulate driver reaching pickup
            cout << "Driver is en route to pickup location..." << endl;
            ride->startRide();
            notifyRideStatusChanged(ride);
        }
    }
    
    void completeRide(const string& rideId) {
        auto it = rides.find(rideId);
        if (it != rides.end()) {
            auto ride = it->second;
            ride->completeRide();
            
            // Calculate fare
            double fare = fareCalculator->calculateFare(*ride);
            ride->setFare(fare);
            
            // Update driver status
            if (ride->getDriver()) {
                ride->getDriver()->setStatus(DriverStatus::AVAILABLE);
                ride->getDriver()->addRideToHistory(rideId);
            }
            
            // Update rider history
            ride->getRider()->addRideToHistory(rideId);
            
            notifyRideStatusChanged(ride);
            notifyPaymentCompleted(ride);
            
            cout << "Ride " << rideId << " completed. Fare: $" << fare 
                 << " (calculated using " << fareCalculator->getDescription() << ")" << endl;
        }
    }
    
    // Notification methods
    void notifyRideStatusChanged(shared_ptr<Ride> ride) {
        for (auto& observer : observers) {
            observer->onRideStatusChanged(ride);
        }
    }
    
    void notifyDriverAssigned(shared_ptr<Ride> ride) {
        for (auto& observer : observers) {
            observer->onDriverAssigned(ride);
        }
    }
    
    void notifyPaymentCompleted(shared_ptr<Ride> ride) {
        for (auto& observer : observers) {
            observer->onPaymentCompleted(ride);
        }
    }
    
    // Utility methods
    shared_ptr<Ride> getRide(const string& rideId) {
        auto it = rides.find(rideId);
        return (it != rides.end()) ? it->second : nullptr;
    }
    
    void printSystemStatus() {
        cout << "\n=== SYSTEM STATUS ===" << endl;
        cout << "Total Riders: " << riders.size() << endl;
        cout << "Total Drivers: " << drivers.size() << endl;
        cout << "Active Rides: " << rides.size() << endl;
        
        int availableDrivers = 0;
        for (const auto& driver : drivers) {
            if (driver->isAvailable()) availableDrivers++;
        }
        cout << "Available Drivers: " << availableDrivers << endl;
        cout << "Current Matching Strategy: " << matchingStrategy->getStrategyName() << endl;
        cout << "Current Fare Calculator: " << fareCalculator->getDescription() << endl;
        cout << "===================" << endl;
    }
};

// Static member definition
RideManager* RideManager::instance = nullptr;

#endif
