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

    std::cout << setColor("[    LOANS    ]", "32", true) << std::endl;
    for(unsigned int i = 0; i < data["loans"].size(); i++) {
        std::cout << std::endl << setColor("[ Loan Type: ", "34", true) << setColor(data["loans"][i]["type"].asString(), "34", false) << setColor(" ]", "34", true) << std::endl;
        std::cout << setColor("\tAmount: ", "34", true) << data["loans"][i]["amount"].asString() << std::endl;
        std::cout << setColor("\tCollateral Required: ", "34", true) << data["loans"][i]["collateralRequired"].asString() << std::endl;
        std::cout << setColor("\tRate: ", "34", true) << data["loans"][i]["rate"].asString() << std::endl;
        std::cout << setColor("\tTerm In Days: ", "34", true) << data["loans"][i]["termInDays"].asString() << std::endl << std::endl;
    }
    std::cout << "\nType loan name. Enter 'null' for leaving:" << std::endl;
    std::cout << ">> ";
    std::string type = "";
    std::cin >> type;
    _toUpper(&type);

    if(type != "NULL"){
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

    std::cout << setColor("[    SHIPS    ]", "32", true) << std::endl;
    for(unsigned int i = 0; i < data["ships"].size(); i++){
        std::cout << std::endl << setColor("[ Type: ", "34", true) << setColor(data["ships"][i]["type"].asString(), "34", false) << setColor(" ]", "34", false) << std::endl;
        std::cout << setColor("\tClass: ", "34", true) << data["ships"][i]["class"].asString() << std::endl;
        std::cout << setColor("\tMax Cargo: ", "34", true) << data["ships"][i]["maxCargo"].asString() << std::endl;
        std::cout << setColor("\tSpeed: ", "34", true) << data["ships"][i]["speed"].asString() << std::endl;
        std::cout << setColor("\tManufacturer: ", "34", true) << data["ships"][i]["manufacturer"].asString() << std::endl;
        std::cout << setColor("\tPlating: ", "34", true) << data["ships"][i]["plating"].asString() << std::endl;
        std::cout << setColor("\tWeapons: ", "34", true) << data["ships"][i]["weapons"].asString() << std::endl;
        for(unsigned int j = 0; j < data["ships"][i]["purchaseLocations"].size(); j++){
            std::cout << setColor("\t\tLocation: ", "34", true) << data["ships"][i]["purchaseLocations"][j]["location"].asString() << std::endl;
            std::cout << setColor("\t\tPrice: ", "34", true) << data["ships"][i]["purchaseLocations"][j]["price"].asString() << std::endl;
        }
    }
    std::cout << "\nEnter ship name or 'null' for leaving:" << std::endl;
        std::cout << "type: ";
    std::string type = "", location = "";
    std::cin >> type;
    _toUpper(&type);

    if(type != "NULL"){
        std::cout << "\nlocation: ";
        std::cin >> location;
        _toUpper(&location);


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
    std::cout << setColor("[    FUEL    ]", "32", true) << std::endl;
    std::cout << "Credits: " << data["user"]["credits"].asString() << std::endl << std::endl;

    // json_data = GETData("/game/ships", "token=" + (*user).getToken());
    // data = fetchJson(json_data);

}

void renderUserInfo(User *user) {
    std::string json_data = GETData("/users/" + (*user).getUsername(), "token=" + (*user).getToken());
    Json::Value data = fetchJson(json_data);
    std::cout << setColor("[    USER INFO    ]", "32", true) << std::endl;
    std::cout << "Username: " << data["user"]["username"].asString() << std::endl;
    std::cout << "Credits: " << data["user"]["credits"].asString() << std::endl;
    std::cout << setColor("\n[    ACTIONS    ]", "32", true) << std::endl;
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
