#ifndef RIDER_H
#define RIDER_H

#include "user.h"
#include <vector>

class Rider : public User {
private:
    double rating;
    vector<string> rideHistory;

public:
    Rider(const string& id, const string& name, const string& phone, 
          const Location& loc, double r = 5.0)
        : User(id, name, phone, loc), rating(r) {}
    
    double getRating() const { return rating; }
    void setRating(double r) { rating = r; }
    
    void addRideToHistory(const string& rideId) {
        rideHistory.push_back(rideId);
    }
    
    const vector<string>& getRideHistory() const { return rideHistory; }
};

#endif
