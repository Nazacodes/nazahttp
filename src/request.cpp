#include "Request.h"
#include <string>
#include <map>
#include <iostream>
#include <sstream>


// constructior for the request class
Request::Request()
    : method("") , uri("") , version(""), headers(), body(""){
      //intialised attributes to default values
  }

  //parsing data truning the http request into contents like request line . headers , body.
bool Request::parse(const std::string& rawRequest){
    // creates an input stremam from the rawRequest string.
    //allows us to use delimiters when spliting the valise adn turn them into diffrent data types
    std::istringstream requestStream(rawRequest);
    //used to read or store a line of text
    std::string line;
    // parsing the request line
    if(std::getline(requestStream, line)){
      std::istringstream lineStream(line);
      lineStream >> method >> uri >> version;
      if(method.empty() || uri.empty() || version.empty()){
        return false; // line request invalid

      }
    } else { return false;}

    // parse headers
    while (std::getline(requestStream, line) && line != "\r"){
      //key and value for each http header for when parsed
      std::string key , value;
      std::istringstream headerStream(line);
      //trim whitespaces from the value
      if (std::getline(headerStream , key, ':') && std::getline(headerStream, value)) {
        //first position of value without white spaces
        // if all characters are /t then it will return back std:string:npos
        size_t start = value.find_first_not_of("\t");
        //last posistion of value without white stasces
        // if all characters are /t then it will return back std:string:npos
        size_t end = value.find_last_not_of("\t");
        // Check if both start and end are valid
        if(start != std::string::npos && end != std::string::npos){
          // if both start and end are valid return the sub string of starting and start and ending at end+1 to be inclused for the end.
          value = value.substr(start , end-start+1);
        }
        // stores http headers in a map
        headers[key] = value;
      }
    }
    // parsing the body if present
    if (requestStream.peek() !=EOF){
      std:: ostringstream bodyStream;
      bodyStream << requestStream.rdbuf();
      body = bodyStream.str();
    }
    return true;
}

