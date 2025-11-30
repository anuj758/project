#ifndef VEHICLE_H
#define VEHICLE_H

#include "../common/types.h"

class Vehicle {
protected:
    string vehicleId;
    string licensePlate;
    VehicleType type;
    int capacity;
    double baseFareRate;

public:
    Vehicle(const string& id, const string& plate, VehicleType t, 
            int cap, double rate)
        : vehicleId(id), licensePlate(plate), type(t), capacity(cap), baseFareRate(rate) {}
    
    virtual ~Vehicle() = default;
    
    const string& getVehicleId() const { return vehicleId; }
    const string& getLicensePlate() const { return licensePlate; }
    VehicleType getType() const { return type; }
    int getCapacity() const { return capacity; }
    double getBaseFareRate() const { return baseFareRate; }
    
    virtual string getTypeString() const = 0;
};

class Bike : public Vehicle {
public:
    Bike(const string& id, const string& plate)
        : Vehicle(id, plate, VehicleType::BIKE, 1, 8.0) {}
    
    string getTypeString() const override { return "Bike"; }
};

class Sedan : public Vehicle {
public:
    Sedan(const string& id, const string& plate)
        : Vehicle(id, plate, VehicleType::SEDAN, 4, 12.0) {}
    
    string getTypeString() const override { return "Sedan"; }
};

class SUV : public Vehicle {
public:
    SUV(const string& id, const string& plate)
        : Vehicle(id, plate, VehicleType::SUV, 6, 18.0) {}
    
    string getTypeString() const override { return "SUV"; }
};

class AutoRickshaw : public Vehicle {
public:
    AutoRickshaw(const string& id, const string& plate)
        : Vehicle(id, plate, VehicleType::AUTO_RICKSHAW, 3, 6.0) {}
    
    string getTypeString() const override { return "Auto-Rickshaw"; }
};

#endif
