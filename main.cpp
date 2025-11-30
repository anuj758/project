#include "managers/ride_manager.h"
#include "factories/vehicle_factory.h"
#include "strategies/matching_strategy.h"
#include "observers/notification_observer.h"
#include "pricing/fare_calculator.h"

int main() {
    cout << "=== RIDESHARE SYSTEM SIMULATION ===" << endl;
    
    // Get singleton instance
    RideManager* rideManager = RideManager::getInstance();
    
    // Create notification services (Observer pattern)
    auto riderNotificationService = make_shared<RiderNotificationService>();
    auto driverNotificationService = make_shared<DriverNotificationService>();
    
    rideManager->addObserver(riderNotificationService);
    rideManager->addObserver(driverNotificationService);
    
    // Create vehicles using Factory pattern
    auto bikeVehicle = VehicleFactory::createVehicle(VehicleType::BIKE, "V001", "MH01AB1234");
    auto sedanVehicle = VehicleFactory::createVehicle(VehicleType::SEDAN, "V002", "MH01CD5678");
    auto suvVehicle = VehicleFactory::createVehicle(VehicleType::SUV, "V003", "MH01EF9012");
    auto autoVehicle = VehicleFactory::createVehicle(VehicleType::AUTO_RICKSHAW, "V004", "MH01GH3456");
    
    // Create drivers
    auto driver1 = make_shared<Driver>("D001", "Mohit Garg", "9876543210", 
                                     Location(19.0760, 72.8777, "Mumbai Central"), 
                                     move(bikeVehicle), 4.8);
    
    auto driver2 = make_shared<Driver>("D002", "Parmeshwar Rane", "9876543211", 
                                     Location(19.0896, 72.8656, "Dadar"), 
                                     move(sedanVehicle), 4.9);
    
    auto driver3 = make_shared<Driver>("D003", "Atul Jain", "9876543212", 
                                     Location(19.1136, 72.8697, "Bandra"), 
                                     move(suvVehicle), 4.7);
    
    auto driver4 = make_shared<Driver>("D004", "Krishna Veerwal", "9876543213", 
                                     Location(19.0544, 72.8322, "Colaba"), 
                                     move(autoVehicle), 4.6);
    
    // Create riders
    auto rider1 = make_shared<Rider>("R001", "Pratik Mandalkar", "9123456789", 
                                   Location(19.0728, 72.8826, "Fort"), 4.5);
    
    auto rider2 = make_shared<Rider>("R002", "Netra Mohekar", "9123456790", 
                                   Location(19.1197, 72.9073, "Andheri"), 4.7);
    
    // Add users to system
    rideManager->addDriver(driver1);
    rideManager->addDriver(driver2);
    rideManager->addDriver(driver3);
    rideManager->addDriver(driver4);
    
    rideManager->addRider(rider1);
    rideManager->addRider(rider2);
    
    // Print initial system status
    rideManager->printSystemStatus();
    
    cout << "\n=== SCENARIO 1: Basic Ride Request (Nearest Driver Strategy) ===" << endl;
    
    // Request a ride using nearest driver strategy
    Location pickup1(19.0760, 72.8777, "Gateway of India");
    Location dropoff1(19.0896, 72.8656, "Dadar Station");
    
    auto ride1 = rideManager->requestRide("R001", pickup1, dropoff1, VehicleType::SEDAN);
    
    if (ride1) {
        cout << "\nStarting ride..." << endl;
        rideManager->startRide(ride1->getRideId());
        
        cout << "\nCompleting ride..." << endl;
        rideManager->completeRide(ride1->getRideId());
    }
    
    cout << "\n=== SCENARIO 2: Switching to Highest Rated Driver Strategy ===" << endl;
    
    // Switch to highest rated driver strategy
    rideManager->setMatchingStrategy(make_unique<HighestRatedDriverStrategy>());
    
    Location pickup2(19.1136, 72.8697, "Bandra West");
    Location dropoff2(19.0544, 72.8322, "Colaba Causeway");
    
    auto ride2 = rideManager->requestRide("R002", pickup2, dropoff2, VehicleType::SUV);
    
    if (ride2) {
        cout << "\nStarting ride..." << endl;
        rideManager->startRide(ride2->getRideId());
        
        cout << "\nCompleting ride..." << endl;
        rideManager->completeRide(ride2->getRideId());
    }
    
    cout << "\n=== SCENARIO 3: Surge Pricing (Decorator Pattern) ===" << endl;
    
    // Apply surge pricing using Decorator pattern
    auto baseFareCalc = make_unique<BaseFareCalculator>();
    auto surgeFareCalc = make_unique<SurgePricingDecorator>(move(baseFareCalc), 2.0);
    rideManager->setFareCalculator(move(surgeFareCalc));
    
    // Switch back to nearest driver strategy
    rideManager->setMatchingStrategy(make_unique<NearestDriverStrategy>());
    
    Location pickup3(19.0760, 72.8777, "CST Station");
    Location dropoff3(19.1197, 72.9073, "Andheri East");
    
    auto ride3 = rideManager->requestRide("R001", pickup3, dropoff3, VehicleType::BIKE);
    
    if (ride3) {
        cout << "\nStarting ride..." << endl;
        rideManager->startRide(ride3->getRideId());
        
        cout << "\nCompleting ride..." << endl;
        rideManager->completeRide(ride3->getRideId());
    }
    
    cout << "\n=== SCENARIO 4: Discount Applied (Decorator Pattern) ===" << endl;
    
    // Apply discount using Decorator pattern
    auto baseFareCalc2 = make_unique<BaseFareCalculator>();
    auto discountFareCalc = make_unique<DiscountDecorator>(move(baseFareCalc2), 0.15);
    rideManager->setFareCalculator(move(discountFareCalc));
    
    Location pickup4(19.0544, 72.8322, "Marine Drive");
    Location dropoff4(19.0896, 72.8656, "Prabhadevi");
    
    auto ride4 = rideManager->requestRide("R002", pickup4, dropoff4, VehicleType::AUTO_RICKSHAW);
    
    if (ride4) {
        cout << "\nStarting ride..." << endl;
        rideManager->startRide(ride4->getRideId());
        
        cout << "\nCompleting ride..." << endl;
        rideManager->completeRide(ride4->getRideId());
    }
    
    cout << "\n=== SCENARIO 5: No Available Driver ===" << endl;
    
    // Try to request a ride when no drivers are available for the vehicle type
    Location pickup5(19.0760, 72.8777, "Churchgate");
    Location dropoff5(19.1136, 72.8697, "Bandra");
    
    cout << "Requesting ride with all drivers busy..." << endl;
    
    // Make all drivers busy first
    driver1->setStatus(DriverStatus::ON_TRIP);
    driver2->setStatus(DriverStatus::ON_TRIP);
    driver3->setStatus(DriverStatus::ON_TRIP);
    driver4->setStatus(DriverStatus::ON_TRIP);
    
    auto ride5 = rideManager->requestRide("R001", pickup5, dropoff5, VehicleType::SEDAN);
    
    // Reset driver status
    driver1->setStatus(DriverStatus::AVAILABLE);
    driver2->setStatus(DriverStatus::AVAILABLE);
    driver3->setStatus(DriverStatus::AVAILABLE);
    driver4->setStatus(DriverStatus::AVAILABLE);
    
    // Final system status
    cout << "\n=== FINAL SYSTEM STATUS ===" << endl;
    rideManager->printSystemStatus();
    
    cout << "\n=== SIMULATION COMPLETED ===" << endl;
    
    return 0;
}
