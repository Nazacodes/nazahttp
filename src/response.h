#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <map>


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

            //validator
            bool validator() const;
            // generating full response
            std::string generateFullResponse() const;

        private:
            std::string status_code;
            std::string status_message;
            // body
            std::string body;
            //headers
            std::map<std::string , std::string> headers;
    };



#endif