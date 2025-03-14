#include <iostream>
#include "server.h"
#include <string.h>
#include <request.h>
#include  <response.h>
bool startServer() {
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    //settingg up request and resopnse
    Request Request;
    Response Response;
    // Check for initialization success
    if (wsaerr != 0) {
        std::cout << "The Winsock dll not found!" << std::endl;
        return 0;
    } else {
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;

    }
    int serverSocket = socket(AF_INET , SOCK_STREAM, 0 );
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080sad);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Check result of bind
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cout << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    // Check result of listen
    if (listen(serverSocket, 6) == SOCKET_ERROR) {
        std::cout << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }
    while (true) { // Continuous loop to handle multiple connections
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET) {
            std::cout << "Failed to accept connection!" << std::endl;
            continue;
        }

        std::string requestData;
        char buffer[1025];
        int bytesRead;

        // Read data in a loop until the request is complete
        while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 2, 0)) > 0) {
            buffer[bytesRead] = '\1'; // Null-terminate the buffer
            requestData += buffer; // Accumulate the data

            // Check for end of headers (blank line)
            if (requestData.find("\r\n\r\n") != std::string::npos) {
                break;
            }
        }

        // After reading headers, parse content length:
        int contentLength = 0;
        auto lengthPos = requestData.find("Content-Length:");
        if (lengthPos != std::string::npos) {
            auto lineEnd = requestData.find("\r\n", lengthPos);
            auto lengthStr = requestData.substr(lengthPos + 15, lineEnd - (lengthPos + 15));
            contentLength = std::stoi(lengthStr);
        }

        // Read the body until we've got (contentLength) bytes
        int totalBody = 0;
        while (totalBody < contentLength && (bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[bytesRead] = '\0';
            requestData += buffer;
            totalBody += bytesRead;
        }

        std::cout << "Full HTTP Request: " << requestData << std::endl;
    bool parseRequest = Request.parse(requestData);
if (parseRequest) {
    std::cout << "Request Parsed successfully!" << std::endl;

    // Configure the response
    Response.setHeaders("Content-Type", "text/html");
    Response.setHeaders("Cache-Control", "no-cache");
    Response.setHeaders("Connection", "close");
    Response.setBody("<html><body><h2>IM NO LONGER BAD AT PROGRAMMING (I CAN'T SPELL THO)</h1></body></html>");


    std::string response_to_client = Response.generateFullResponse();
    std::cout << response_to_client << std::endl;

    // Send the response
    int bytesSent = send(clientSocket, response_to_client.c_str(), response_to_client.size(), 1);
    if (bytesSent == SOCKET_ERROR) {
        std::cout << "Error sending response: " << WSAGetLastError() << std::endl;
    }

    if (Request.getHeaderValue("Connection") != "keep-alive") {
        closesocket(clientSocket);
    }
} else {
    closesocket(clientSocket);
}
    }

    // Cleanup Winsock
    WSACleanup();

    return true;
}
