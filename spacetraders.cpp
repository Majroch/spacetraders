#include <iostream>
#include "libs/util.h"
// This file is imported in libs/util.h
//#include "classes/user.h"
#include <json/value.h>
#include <vector>
#include <unistd.h>

void showLoans(User *user) {
    clearScreen();
    std::string json_data = GETData("/game/loans", "token=" + (*user).getToken());
    Json::Value data = fetchJson(json_data);

    std::cout << "###### LOANS ######" << std::endl;
    for(unsigned int i = 0; i < data["loans"].size(); i++) {
        std::cout << std::endl << "Loan Type: " << data["loans"][i]["type"].asString() << std::endl;
        std::cout << "\tAmount: " << data["loans"][i]["amount"].asString() << std::endl;
        std::cout << "\tCollateral Required: " << data["loans"][i]["collateralRequired"].asString() << std::endl;
        std::cout << "\tRate: " << data["loans"][i]["rate"].asString() << std::endl;
        std::cout << "\tTerm In Days: " << data["loans"][i]["termInDays"].asString() << std::endl << std::endl;
    }
    std::cout << "###################" << std::endl << std::endl;
    
    sleep(10);
}

int main(void) {
	bool isTokenExists = fileExists("token.txt");

	if(!isTokenExists) {
		std::string choice = "";

		std::cout << "Do you want to create account?" << std::endl;
		std::cout << ">> ";

		std::cin >> choice;
        _toLower(&choice);

		if(choice != "y" && choice != "yes" && choice != "ye"){
            return -1;
        }

        std::cout << "Good, we will create you the account" << std::endl;

        std::cout << std::endl << "So, tell me your username: ";
        std::string username = "";

        std::cin >> username;

        if(username == "") {
            std::cout << "Your username cannot be blank." << std::endl;
            return -1;
        }

        std::string user_credentials = POSTData("/users/" + username + "/token", "");

        putFileData("token.txt", user_credentials);
    }

    // We have a token.txt file
    // Now we need to load it

    std::string user_credentials = getFileData("token.txt");
    Json::Value data = fetchJson(user_credentials);

    User user(data["user"]["username"].asString(), data["token"].asString());

    std::vector<std::string> menu;
    menu.push_back("Show available loans");

    while(true) {
        clearScreen();
        renderUserInfo(&user);
        renderMenu(&menu, true);

        std::string choice;
        std::cout << ">> ";
        std::cin >> choice;

        if(choice == "1") {
            showLoans(&user);
        } else if(choice == "99") {
            std::cout << "Exitting..." << std::endl;
            return 0;
        }
    }
    
    return 0;
}
