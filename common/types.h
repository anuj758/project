#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <memory>
#include <cmath>
#include <iostream>

using namespace std;

enum class RideStatus {
    REQUESTED,
    DRIVER_ASSIGNED,
    DRIVER_EN_ROUTE,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

enum class DriverStatus {
    AVAILABLE,
    ON_TRIP,
    OFFLINE
};

enum class VehicleType {
    BIKE,
    SEDAN,
    SUV,
    AUTO_RICKSHAW
};

enum class RideType {
    NORMAL,
    CARPOOL
};

struct Location {
    double latitude;
    double longitude;
    string address;
    
    Location(double lat = 0.0, double lng = 0.0, const string& addr = "")
        : latitude(lat), longitude(lng), address(addr) {}
    
    double distanceTo(const Location& other) const {
        // Simplified distance calculation (Euclidean distance)
        double dx = latitude - other.latitude;
        double dy = longitude - other.longitude;
        return sqrt(dx * dx + dy * dy) * 111.0; // Approximate km conversion
    }
};

#endif
