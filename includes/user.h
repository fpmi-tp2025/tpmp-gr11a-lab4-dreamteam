#ifndef USER_H
#define USER_H

#include <string>

struct User {
    int id;
    std::string username;
    std::string role;
};

class Auth {
public:
    static bool login(const std::string& username, const std::string& password, User& user);
};

#endif
