#include <iostream>
#include "libs/util.h"

int main(void) {
	bool isTokenExists;

	isTokenExists = fileExists("token.txt");
	if(isTokenExists){

	}
	else{
		std::string choice;
		std::cout << "It seems that you don't have token file. Do you want to create account or log in? c/l";
		while(1){
			std::cout << "\n>> ";
			std::cin >> choice;
			if(choice == "c"){
				//CreateUserAccount();
				break;
			}
			else if(choice == "l"){
				break;
			}
		}
	}

    return 0;
}


