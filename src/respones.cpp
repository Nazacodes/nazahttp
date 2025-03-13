#include "Response.h"


#include <sstream>

// constructor for the class
Response::Response()
    : status_code("200") , status_message("ok") , body("") , headers(){

  }

void Response::setStatusMessage(const std::string& status_message){
    this->status_message = status_message;
}

void Response::setStatusCode(const std::string& status_code){
    this->status_code = status_code;
}


void Response::setHeaders(const  std::string& header_name , const std::string& header_value){
     this->headers[header_name] = header_value;
  }

void Response::setBody(const std::string& body){
    this->body = body;
}

std::string Response::generateFullResponse() const{
    std:: ostringstream responsestream;
    responsestream << "HTTP/1.1" << status_code << " " << status_message;
    for (const auto& header : headers){
        responsestream << header.first ;
    }
}