#include <string>

class User {
    private:
    std::string username;
    std::string token;

    public:
    User(std::string _username, std::string _token);

    std::string getUsername();
    std::string getToken();
};
