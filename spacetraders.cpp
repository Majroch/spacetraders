#include <iostream>
#include "libs/util.h"

int main(void) {
	bool isTokenExists;

	isTokenExists = fileExists("token.txt");
	if(isTokenExists){

	}
	else{
		std::string choice;
		std::cout << "It seems that you don't have token file. Do you want to create account?";
		std::cout << "\n>> ";
		std::cin >> choice;
        _toLower(&choice);
		if(choice == "y" || choice == "yes" || choice == "ye"){
			//CreateUserAccount();
            std::cout << "Good, we will create you the account" << std::endl;
		}
		else if(choice == "n" || choice == "N"){
            return -1;
		}
	}

    return 0;
}


