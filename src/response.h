#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>



class Response{
    public:

        //Constroctor
        Response();

        // setting status
        void setStatusMessage(const std::string& status_message);
        void setStatusCode(const std::string& status_code );
        // setting headers
        void setHeaders(const std::string& header_name, const std::string& header_value);
        //  setting body
        void setBody(const std::string& body);



    private:
        std::string status_code;
        std::string status_message;
        // body
        //headers
};



#endif