#ifndef FARE_CALCULATOR_H
#define FARE_CALCULATOR_H

#include "../rides/ride.h"

class FareCalculator {
public:
    virtual ~FareCalculator() = default;
    virtual double calculateFare(const Ride& ride) = 0;
    virtual string getDescription() const = 0;
};

class BaseFareCalculator : public FareCalculator {
private:
    double baseFare;
    double perKmRate;

public:
    BaseFareCalculator(double base = 50.0, double rate = 10.0)
        : baseFare(base), perKmRate(rate) {}
    
    double calculateFare(const Ride& ride) override {
        double distance = ride.getDistance();
        double vehicleMultiplier = 1.0;
        
        // Apply vehicle type multiplier
        if (ride.getDriver() && ride.getDriver()->getVehicle()) {
            vehicleMultiplier = ride.getDriver()->getVehicle()->getBaseFareRate() / 10.0;
        }
        
        return (baseFare + (distance * perKmRate)) * vehicleMultiplier;
    }
    
    string getDescription() const override {
        return "Base Fare Calculator";
    }
};

// Decorator Pattern for additional pricing features
class FareDecorator : public FareCalculator {
protected:
    unique_ptr<FareCalculator> baseCalculator;

public:
    FareDecorator(unique_ptr<FareCalculator> calc)
        : baseCalculator(move(calc)) {}
};

class SurgePricingDecorator : public FareDecorator {
private:
    double surgeMultiplier;

public:
    SurgePricingDecorator(unique_ptr<FareCalculator> calc, double multiplier = 1.5)
        : FareDecorator(move(calc)), surgeMultiplier(multiplier) {}
    
    double calculateFare(const Ride& ride) override {
        double baseFare = baseCalculator->calculateFare(ride);
        return baseFare * surgeMultiplier;
    }
    
    string getDescription() const override {
        return baseCalculator->getDescription() + " + Surge Pricing";
    }
};

class DiscountDecorator : public FareDecorator {
private:
    double discountPercentage;

public:
    DiscountDecorator(unique_ptr<FareCalculator> calc, double discount = 0.1)
        : FareDecorator(move(calc)), discountPercentage(discount) {}
    
    double calculateFare(const Ride& ride) override {
        double baseFare = baseCalculator->calculateFare(ride);
        return baseFare * (1.0 - discountPercentage);
    }
    
    string getDescription() const override {
        return baseCalculator->getDescription() + " + Discount Applied";
    }
};

#endif
