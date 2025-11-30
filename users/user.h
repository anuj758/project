#ifndef USER_H
#define USER_H

#include "../common/types.h"

class User {
protected:
    string userId;
    string name;
    string phone;
    Location currentLocation;

public:
    User(const string& id, const string& n, const string& p, const Location& loc)
        : userId(id), name(n), phone(p), currentLocation(loc) {}
    
    virtual ~User() = default;
    
    // Getters
    const string& getUserId() const { return userId; }
    const string& getName() const { return name; }
    const string& getPhone() const { return phone; }
    const Location& getCurrentLocation() const { return currentLocation; }
    
    // Setters
    void setCurrentLocation(const Location& loc) { currentLocation = loc; }
};

#endif
