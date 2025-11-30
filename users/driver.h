#ifndef DRIVER_H
#define DRIVER_H

#include "user.h"
#include "../vehicles/vehicle.h"

class Driver : public User {
private:
    double rating;
    DriverStatus status;
    unique_ptr<Vehicle> vehicle;
    vector<string> rideHistory;

public:
    Driver(const string& id, const string& name, const string& phone,
           const Location& loc, unique_ptr<Vehicle> v, double r = 5.0)
        : User(id, name, phone, loc), rating(r), status(DriverStatus::AVAILABLE), 
          vehicle(move(v)) {}
    
    double getRating() const { return rating; }
    void setRating(double r) { rating = r; }
    
    DriverStatus getStatus() const { return status; }
    void setStatus(DriverStatus s) { status = s; }
    
    Vehicle* getVehicle() const { return vehicle.get(); }
    
    bool isAvailable() const { return status == DriverStatus::AVAILABLE; }
    
    void addRideToHistory(const string& rideId) {
        rideHistory.push_back(rideId);
    }
    
    const vector<string>& getRideHistory() const { return rideHistory; }
};

#endif
