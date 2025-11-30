#ifndef MATCHING_STRATEGY_H
#define MATCHING_STRATEGY_H

#include "../users/driver.h"
#include "../rides/ride.h"
#include <vector>
#include <algorithm>

class MatchingStrategy {
public:
    virtual ~MatchingStrategy() = default;
    virtual shared_ptr<Driver> findBestDriver(
        const vector<shared_ptr<Driver>>& availableDrivers,
        const Ride& ride) = 0;
    virtual string getStrategyName() const = 0;
};

class NearestDriverStrategy : public MatchingStrategy {
public:
    shared_ptr<Driver> findBestDriver(
        const vector<shared_ptr<Driver>>& availableDrivers,
        const Ride& ride) override {
        
        if (availableDrivers.empty()) return nullptr;
        
        shared_ptr<Driver> bestDriver = nullptr;
        double minDistance = numeric_limits<double>::max();
        
        for (const auto& driver : availableDrivers) {
            if (!driver->isAvailable()) continue;
            
            // Check if vehicle type matches
            if (driver->getVehicle()->getType() != ride.getRequestedVehicleType()) continue;
            
            double distance = driver->getCurrentLocation().distanceTo(ride.getPickupLocation());
            if (distance < minDistance) {
                minDistance = distance;
                bestDriver = driver;
            }
        }
        
        return bestDriver;
    }
    
    string getStrategyName() const override {
        return "Nearest Driver Strategy";
    }
};

class HighestRatedDriverStrategy : public MatchingStrategy {
public:
    shared_ptr<Driver> findBestDriver(
        const vector<shared_ptr<Driver>>& availableDrivers,
        const Ride& ride) override {
        
        if (availableDrivers.empty()) return nullptr;
        
        shared_ptr<Driver> bestDriver = nullptr;
        double highestRating = 0.0;
        
        for (const auto& driver : availableDrivers) {
            if (!driver->isAvailable()) continue;
            
            // Check if vehicle type matches
            if (driver->getVehicle()->getType() != ride.getRequestedVehicleType()) continue;
            
            if (driver->getRating() > highestRating) {
                highestRating = driver->getRating();
                bestDriver = driver;
            }
        }
        
        return bestDriver;
    }
    
    string getStrategyName() const override {
        return "Highest Rated Driver Strategy";
    }
};

#endif
