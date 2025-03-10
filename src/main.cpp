#include <iostream>
#include "Request.cpp"
#include <iostream>
#include <string>
#include <sstream>

int main(){



    Request request;

    std::string rawHttpRequest =
        "GET /index.html HTTP/1.1\r\n"
        "Host: www.example.com\r\n"
        "User-Agent: Mozilla/5.0\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: en-US,en;q=0.5\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Connection: keep-alive\r\n"
        "\r\n";
    bool parseRequest = request.parse(rawHttpRequest);
    if (parseRequest) {
        std::cout << "Request parsed successfully!" << std::endl;
        std::string host = request.getHeaderValue("Host");

        std::string user_agent = request.getHeaderValue("User-Agent");
        std::string  connection = request.getHeaderValue("Connection");

        std::cout << user_agent << std::endl;
        std::cout << connection<< std::endl;
        std::cout << host << std::endl;
    } else {
        std::cout << "Failed to parse request." << std::endl;
    }



    return 0;
  }