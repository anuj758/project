#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include "../vehicles/vehicle.h"

class VehicleFactory {
public:
    static unique_ptr<Vehicle> createVehicle(VehicleType type, 
                                           const string& id, 
                                           const string& plate) {
        switch (type) {
            case VehicleType::BIKE:
                return make_unique<Bike>(id, plate);
            case VehicleType::SEDAN:
                return make_unique<Sedan>(id, plate);
            case VehicleType::SUV:
                return make_unique<SUV>(id, plate);
            case VehicleType::AUTO_RICKSHAW:
                return make_unique<AutoRickshaw>(id, plate);
            default:
                return nullptr;
        }
    }
};

#endif
