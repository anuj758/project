# RideShare System - Low Level Design Implementation

## Overview
This is a comprehensive implementation of a ride-sharing service platform (similar to Uber/Ola) built using C++ with a focus on clean object-oriented design, SOLID principles, and multiple design patterns.

## Architecture & Design Patterns Used

### 1. **Singleton Pattern**
- **RideManager**: Central coordinator that manages all rides, drivers, and riders
- Ensures single point of control for the entire system

### 2. **Strategy Pattern**
- **MatchingStrategy**: Pluggable algorithms for driver matching
  - `NearestDriverStrategy`: Finds closest available driver
  - `HighestRatedDriverStrategy`: Finds highest-rated available driver
- Easily extensible to add new matching algorithms

### 3. **Factory Pattern**
- **VehicleFactory**: Creates different types of vehicles (Bike, Sedan, SUV, Auto-Rickshaw)
- Encapsulates object creation logic and makes it easy to add new vehicle types

### 4. **Observer Pattern**
- **NotificationObserver**: Decoupled notification system
  - `RiderNotificationService`: Handles rider notifications
  - `DriverNotificationService`: Handles driver notifications
- Supports multiple notification channels without tight coupling

### 5. **Decorator Pattern**
- **FareCalculator**: Flexible pricing system
  - `BaseFareCalculator`: Basic fare calculation
  - `SurgePricingDecorator`: Adds surge pricing
  - `DiscountDecorator`: Applies discounts
- Allows dynamic composition of pricing rules

## SOLID Principles Implementation

### Single Responsibility Principle (SRP)
- Each class has a single, well-defined responsibility
- `Rider` manages rider-specific data
- `Driver` manages driver-specific data
- `Ride` manages ride lifecycle
- `RideManager` coordinates system operations

### Open/Closed Principle (OCP)
- System is open for extension, closed for modification
- New matching strategies can be added without changing existing code
- New vehicle types can be added through the factory
- New pricing rules can be added through decorators

### Liskov Substitution Principle (LSP)
- All derived classes can be substituted for their base classes
- All vehicle types can be used interchangeably
- All matching strategies are interchangeable
- All fare calculators are interchangeable

### Interface Segregation Principle (ISP)
- Interfaces are focused and specific
- `MatchingStrategy` only defines matching behavior
- `NotificationObserver` only defines notification behavior
- `FareCalculator` only defines fare calculation behavior

### Dependency Inversion Principle (DIP)
- High-level modules don't depend on low-level modules
- `RideManager` depends on abstractions (interfaces) not concrete implementations
- Strategies and calculators are injected as dependencies

## System Features

### Core Functionality
1. **User Management**: Register and manage riders and drivers
2. **Ride Booking**: Request rides with pickup/dropoff locations
3. **Driver Matching**: Multiple algorithms for driver assignment
4. **Ride Workflow**: Complete ride lifecycle management
5. **Vehicle Types**: Support for multiple vehicle categories
6. **Dynamic Pricing**: Flexible fare calculation with surge pricing and discounts
7. **Notifications**: Real-time updates to riders and drivers
8. **In-Memory Storage**: All data managed in memory using STL containers

### Supported Vehicle Types
- **Bike**: Single passenger, economical
- **Sedan**: 4 passengers, standard comfort
- **SUV**: 6 passengers, premium comfort
- **Auto-Rickshaw**: 3 passengers, local transport

### Matching Strategies
- **Nearest Driver**: Finds closest available driver
- **Highest Rated**: Finds best-rated available driver

### Pricing Features
- **Base Fare**: Distance-based calculation with vehicle type multipliers
- **Surge Pricing**: Dynamic pricing during peak hours
- **Discounts**: Promotional discounts and offers

## File Structure
\`\`\`
rideshare-system/
├── common/
│   └── types.h              # Common enums and structures
├── users/
│   ├── user.h               # Base user class
│   ├── rider.h              # Rider implementation
│   └── driver.h             # Driver implementation
├── vehicles/
│   └── vehicle.h            # Vehicle hierarchy
├── factories/
│   └── vehicle_factory.h    # Vehicle creation factory
├── rides/
│   └── ride.h               # Ride management
├── strategies/
│   └── matching_strategy.h  # Driver matching strategies
├── observers/
│   └── notification_observer.h # Notification system
├── pricing/
│   └── fare_calculator.h    # Fare calculation system
├── managers/
│   └── ride_manager.h       # Central system manager
├── main.cpp                 # Main simulation
├── compile_and_run.sh       # Build script
└── README.md               # This file
\`\`\`

## How to Run
## Prerequisites
1. **Install MinGW-w64**: Download from [MinGW-w64](https://www.mingw-w64.org/downloads/)
2. **Add to PATH**: Add MinGW bin directory to your system PATH
3. **Install VS Code Extensions**:
   - C/C++ (Microsoft)
   - C/C++ Extension Pack (Microsoft)

## Quick Setup Steps

### 1. Create Project Structure
Create the following folder structure in your VS Code workspace:
\`\`\`
rideshare-system/
├── .vscode/
│   ├── tasks.json
│   └── launch.json
├── common/
├── users/
├── vehicles/
├── factories/
├── rides/
├── strategies/
├── observers/
├── pricing/
├── managers/
└── main.cpp
\`\`\`

### 2. Copy Files
Copy all the header files to their respective folders and main.cpp to the root.

### 3. Build and Run

#### Option 1: Using Terminal (Recommended)
1. Open terminal in VS Code (`Ctrl+``)
2. Run: `g++ -std=c++14 -I. main.cpp -o rideshare_system.exe`
3. Run: `./rideshare_system.exe`

#### Option 2: Using VS Code Tasks
1. Press `Ctrl+Shift+P`
2. Type "Tasks: Run Task"
3. Select "Build RideShare System"
4. Then select "Run RideShare System"

#### Option 3: Using F5 (Debug)
1. Press `F5` to build and debug
2. The program will compile and run automatically

## Troubleshooting

### Common Issues:
1. **"g++ not found"**: Make sure MinGW is installed and added to PATH
2. **"Permission denied"**: Run VS Code as administrator
3. **Header not found**: Make sure all files are in correct folders

## Simulation Scenarios

The main program demonstrates:

1. **Basic Ride Request**: Using nearest driver strategy
2. **Strategy Switching**: Changing to highest-rated driver strategy
3. **Surge Pricing**: Applying surge pricing using decorator pattern
4. **Discount Application**: Applying discounts using decorator pattern
5. **Edge Case Handling**: No available drivers scenario

## Extensibility

The system is designed for easy extension:

### Adding New Vehicle Types
\`\`\`cpp
class Luxury : public Vehicle {
public:
    Luxury(const std::string& id, const std::string& plate)
        : Vehicle(id, plate, VehicleType::LUXURY, 2, 50.0) {}
    
    std::string getTypeString() const override { return "Luxury"; }
};
\`\`\`

### Adding New Matching Strategies
\`\`\`cpp
class ComboStrategy : public MatchingStrategy {
    // Combine distance and rating for optimal matching
};
\`\`\`

### Adding New Pricing Rules
\`\`\`cpp
class PeakHourDecorator : public FareDecorator {
    // Apply peak hour pricing
};
\`\`\`

## Trade-offs and Design Decisions

### Trade-offs Made
1. **Simplified Location System**: Used basic coordinate system instead of real GPS/mapping
2. **In-Memory Storage**: No persistence layer for simplicity
3. **Single-Threaded**: No concurrency handling to focus on design patterns
4. **Simplified Payment**: Mock payment processing

### Design Decisions
1. **Shared Pointers**: Used for automatic memory management and shared ownership
2. **Strategy Pattern**: Chosen over inheritance for matching algorithms for flexibility
3. **Decorator Pattern**: Preferred over inheritance for pricing to allow dynamic composition
4. **Observer Pattern**: Implemented for loose coupling in notification system

## Future Enhancements

The design supports easy addition of:
- **Scheduled Rides**: Advance booking functionality
- **Driver Ratings**: Post-ride rating system
- **Route Optimization**: Integration with mapping services
- **Real-time Tracking**: GPS-based location updates
- **Multi-city Support**: Expansion to multiple cities
- **Carpool Matching**: Advanced algorithms for shared rides

## Conclusion

This implementation demonstrates a clean, extensible architecture that follows SOLID principles and effectively uses multiple design patterns. The system is designed to be maintainable, testable, and easily extensible for future requirements.


## **Enjoy exploring the RideShare System!**
