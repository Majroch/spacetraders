#define API "https://api.spacetraders.io"

#include <string>

// Function to send GET requests (not sure if it makes GET or POST requests anyway)
std::string GETData(std::string address);

// Function to send POST requests with data
std::string POSTData(std::string address, std::string data);

// Get file data from filename
std::string getFileData(std::string filename);

// Put file content into filename
void putFileData(std::string filename, std::string content);

// check if file exists
bool fileExists(std::string filename);

// Change string to lowercase
void _toLower(std::string *_str);

// Change string to uppercase
void _toUpper(std::string *_str);
