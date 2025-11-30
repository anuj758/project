#ifndef RIDE_H
#define RIDE_H

#include "../common/types.h"
#include "../users/rider.h"
#include "../users/driver.h"
#include <chrono>
#include <limits>

class Ride {
private:
    string rideId;
    shared_ptr<Rider> rider;
    shared_ptr<Driver> driver;
    Location pickupLocation;
    Location dropoffLocation;
    RideStatus status;
    RideType rideType;
    VehicleType requestedVehicleType;
    double fare;
    chrono::system_clock::time_point requestTime;
    chrono::system_clock::time_point startTime;
    chrono::system_clock::time_point endTime;

public:
    Ride(const string& id, shared_ptr<Rider> r, const Location& pickup,
         const Location& dropoff, VehicleType vehicleType, RideType type = RideType::NORMAL)
        : rideId(id), rider(r), pickupLocation(pickup), dropoffLocation(dropoff),
          status(RideStatus::REQUESTED), rideType(type), requestedVehicleType(vehicleType),
          fare(0.0), requestTime(chrono::system_clock::now()) {}
    
    // Getters
    const string& getRideId() const { return rideId; }
    shared_ptr<Rider> getRider() const { return rider; }
    shared_ptr<Driver> getDriver() const { return driver; }
    const Location& getPickupLocation() const { return pickupLocation; }
    const Location& getDropoffLocation() const { return dropoffLocation; }
    RideStatus getStatus() const { return status; }
    RideType getRideType() const { return rideType; }
    VehicleType getRequestedVehicleType() const { return requestedVehicleType; }
    double getFare() const { return fare; }
    
    // Setters
    void setDriver(shared_ptr<Driver> d) { driver = d; }
    void setStatus(RideStatus s) { status = s; }
    void setFare(double f) { fare = f; }
    
    void startRide() {
        startTime = chrono::system_clock::now();
        status = RideStatus::IN_PROGRESS;
    }
    
    void completeRide() {
        endTime = chrono::system_clock::now();
        status = RideStatus::COMPLETED;
    }
    
    double getDistance() const {
        return pickupLocation.distanceTo(dropoffLocation);
    }
    
    string getStatusString() const {
        switch (status) {
            case RideStatus::REQUESTED: return "Requested";
            case RideStatus::DRIVER_ASSIGNED: return "Driver Assigned";
            case RideStatus::DRIVER_EN_ROUTE: return "Driver En Route";
            case RideStatus::IN_PROGRESS: return "In Progress";
            case RideStatus::COMPLETED: return "Completed";
            case RideStatus::CANCELLED: return "Cancelled";
            default: return "Unknown";
        }
    }
};

#endif
