#include "util.h"

#include <curl/curl.h>
#include <json/value.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string GETData(std::string address, std::string data) {
    auto curl = curl_easy_init();
    if(curl) {
        std::string addr(API);
        addr.append(address);
        addr.append("?" + data);

        std::string response_string, header_string;
        curl_easy_setopt(curl, CURLOPT_URL, addr.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        return response_string;
    } else {
        return "ERROR";
    }
}

std::string POSTData(std::string address, std::string data) {
    auto curl = curl_easy_init();
    if(curl) {
        std::string addr(API);
        addr.append(address);

        std::string response_string, header_string;
        curl_easy_setopt(curl, CURLOPT_URL, addr.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        return response_string;
    } else {
        return "ERROR";
    }
}

std::string getFileData(std::string filename) {
    std::ifstream file(filename);

    std::string output = "";

    while(file) {
        std::string line;

        std::getline(file, line);

        output.append(line);
        output.append("\n");
    }

    file.close();

    return output;
}

void putFileData(std::string filename, std::string content) {
    std::ofstream file(filename);

    file << content << std::endl;

    file.close();
}

bool fileExists(std::string filename) {
    std::ifstream file(filename);
    if(!file.is_open()){
        return false;
    }

    return true;
}

void _toLower(std::string *_str) {
    for(long unsigned int i = 0; i < (*_str).length(); i++) {
        (*_str)[i] = tolower((*_str)[i]);
    }
}

void _toUpper(std::string *_str) {
    for(long unsigned int i = 0; i < (*_str).length(); i++) {
        (*_str)[i] = toupper((*_str)[i]);
    }
}

Json::Value fetchJson(std::string data) {
    Json::Reader reader;
    Json::Value root;
  
    bool parseSuccess = reader.parse(data, root, false);
  
    if (parseSuccess) {
        return root;
    }

    return NULL;
}

void renderMenu(std::vector<std::string> *options, bool show_exit) {
    for(unsigned int i = 0; i < (*options).size(); i++) {
        std::cout << i+1 << ". " << (*options)[i] << std::endl;
    }
    if(show_exit) {
        std::cout << "99. Exit" << std::endl;
    }
}

std::string setColor(std::string _str, std::string color, bool isBold){
    if(isBold)
    {
        return "\033[1;" + color + "m" + _str + "\033[0m";
    }
    return "\033[0;" + color + "m" + _str + "\033[0m";
}

void clearScreen() {
    system("clear");
}
