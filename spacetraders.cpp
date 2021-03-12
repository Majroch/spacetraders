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
    std::cout << "###################" << std::endl;
    std::cout << "Type loan name. Enter 'null' for leaving:" << std::endl;
    std::cout << ">> ";
    std::string type = "";
    std::cin >> type;
    //std::cout << type << std::endl;

    if(type != "null"){
        std::string callback = POSTData("/users/" + (*user).getUsername() + "/loans" + "?token=" + (*user).getToken(), "type=" + type);
        if(callback == "ERROR")
        {
            std::cout << "Wrong loan name." << std::endl;
        }
    }
}

void showShips(User *user){
    clearScreen();
    std::string json_data = GETData("/game/ships", "token=" + (*user).getToken());
    Json::Value data = fetchJson(json_data);

    std::cout << "###### SHIPS ######" << std::endl;
    for(unsigned int i = 0; i < data["ships"].size(); i++){
        std::cout << std::endl << "[Type: " << data["ships"][i]["type"].asString() << "]" << std::endl;
        std::cout << "\tClass: " << data["ships"][i]["class"].asString() << std::endl;
        std::cout << "\tMax Cargo: " << data["ships"][i]["maxCargo"].asString() << std::endl;
        std::cout << "\tSpeed: " << data["ships"][i]["speed"].asString() << std::endl;
        std::cout << "\tManufacturer: " << data["ships"][i]["manufacturer"].asString() << std::endl;
        std::cout << "\tPlating: " << data["ships"][i]["plating"].asString() << std::endl;
        std::cout << "\tWeapons: " << data["ships"][i]["weapons"].asString() << std::endl;
        for(unsigned int j = 0; j < data["ships"][i]["purchaseLocations"].size(); j++){
            std::cout << "\t\tLocation: " << data["ships"][i]["purchaseLocations"][j]["location"].asString() << std::endl;
            std::cout << "\t\tPrice: " << data["ships"][i]["purchaseLocations"][j]["price"].asString() << std::endl;
        }
    }
    std::cout << "###################" << std::endl;
    std::cout << "Enter ship name or 'null' for leaving:" << std::endl;
        std::cout << "type: ";
    std::string type = "", location = "";
    std::cin >> type;
    std::cout << "\nlocation: ";
    std::cin >> location;

    if(type != "null"){

        std::string callback = POSTData("/users/" + (*user).getUsername() + "/ships" + "?token=" + (*user).getToken(), "location=" + location + "&type=" + type);
        if(callback == "ERROR"){
            std::cout << "Wrong ship data." << std::endl;
        } 
    }
}

void buyFuel(User *user)
{
    clearScreen();
    std::string json_data = GETData("/users/" + (*user).getUsername(), "token=" + (*user).getToken());
    Json::Value data = fetchJson(json_data);
    std::cout << "###### FUEL ######" << std::endl;
    std::cout << "Credits: " << data["user"]["credits"].asString() << std::endl << std::endl;

    // json_data = GETData("/game/ships", "token=" + (*user).getToken());
    // data = fetchJson(json_data);

}

void renderUserInfo(User *user) {
    std::string json_data = GETData("/users/" + (*user).getUsername(), "token=" + (*user).getToken());
    Json::Value data = fetchJson(json_data);
    std::cout << "###### USER INFO ######" << std::endl;
    std::cout << "Username: " << data["user"]["username"].asString() << std::endl;
    std::cout << "Credits: " << data["user"]["credits"].asString() << std::endl;
    std::cout << "#######################" << std::endl << std::endl;
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

        std::cout << std::endl << "Create username:" << std::endl;
        std::cout << ">> ";
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
    menu.push_back("Loans");
    menu.push_back("Ships show/buy/sell");
    menu.push_back("Fuel");
    menu.push_back("Planets");
    menu.push_back("Trade");
    menu.push_back("Help");

    while(true) {
        clearScreen();
        //std::cout << "\033[1;32mbold red text\033[0m\n";
        renderUserInfo(&user);
        renderMenu(&menu, true);

        std::string choice;
        std::cout << "\n>> ";
        std::cin >> choice;
        _toLower(&choice);

        if(choice == "1" || choice == "loans") {
            showLoans(&user);

        } else if(choice == "2" || choice == "ships") {
            showShips(&user);

        } else if(choice == "99" || choice == "exit") {
            std::cout << "Exitting..." << std::endl;
            return 0;
        }
    }
    
    return 0;
}
