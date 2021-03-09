#include "util.h"

#include <curl/curl.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string GETData(std::string address) {
    auto curl = curl_easy_init();
    if(curl) {
        std::string addr(API);
        addr.append(address);

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
