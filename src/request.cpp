#include <string>
#include <map>
#include <iostream>
#include <sstream>
// Creating request class
class Request{
public:
  //Here I am initializing the data members if the class with the value
  // its in the public section because i need to create instances of it outside of the class
  Request();
  // this is use to access the http header within the other headers in the request
  // public acess as we need the header value from outside of the class
  std::string getHeaderValue(const std::string& headerName) const;

  // method to vallidate the overall request
  // public acess because we need the vaidate answer outside of our class for oother methods
  bool validate() const;
  // method to turn an object into a text that can be used for debugging
  // public as it is used outside the class to easily print or log the object state from outside the class
  std::string toString() const;




private:
  //used to store the method of the request (post , put , get , delete)
  std::string method;
  // hold the uniifor resource identifier
  std::string uri;
 // repersent the verion of http used in the request
  std::string version;
 // stored the body of the respones
  std::string body;
  


};
