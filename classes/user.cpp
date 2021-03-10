#include "user.h"

User::User(std::string _username, std::string _token) {
   username = _username;
   token = _token;
}

std::string User::getToken() {
    return token;
}

std::string User::getUsername() {
    return username;
}
