#ifndef NOTIFICATION_OBSERVER_H
#define NOTIFICATION_OBSERVER_H

#include "../rides/ride.h"

class NotificationObserver {
public:
    virtual ~NotificationObserver() = default;
    virtual void onRideStatusChanged(shared_ptr<Ride> ride) = 0;
    virtual void onDriverAssigned(shared_ptr<Ride> ride) = 0;
    virtual void onPaymentCompleted(shared_ptr<Ride> ride) = 0;
};

class RiderNotificationService : public NotificationObserver {
public:
    void onRideStatusChanged(shared_ptr<Ride> ride) override {
        cout << "[RIDER NOTIFICATION] Ride " << ride->getRideId() 
             << " status changed to: " << ride->getStatusString() << endl;
    }
    
    void onDriverAssigned(shared_ptr<Ride> ride) override {
        cout << "[RIDER NOTIFICATION] Driver " << ride->getDriver()->getName()
             << " has been assigned to your ride " << ride->getRideId() << endl;
    }
    
    void onPaymentCompleted(shared_ptr<Ride> ride) override {
        cout << "[RIDER NOTIFICATION] Payment of $" << ride->getFare()
             << " completed for ride " << ride->getRideId() << endl;
    }
};

class DriverNotificationService : public NotificationObserver {
public:
    void onRideStatusChanged(shared_ptr<Ride> ride) override {
        if (ride->getDriver()) {
            cout << "[DRIVER NOTIFICATION] Ride " << ride->getRideId() 
                 << " status changed to: " << ride->getStatusString() << endl;
        }
    }
    
    void onDriverAssigned(shared_ptr<Ride> ride) override {
        cout << "[DRIVER NOTIFICATION] You have been assigned to ride " 
             << ride->getRideId() << endl;
    }
    
    void onPaymentCompleted(shared_ptr<Ride> ride) override {
        cout << "[DRIVER NOTIFICATION] Payment received for ride " 
             << ride->getRideId() << endl;
    }
};

#endif
