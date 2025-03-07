#include "Request.h"
#include <string>
#include <map>
#include <iostream>
#include <sstream>
;


// constructior for the request class
Request::Request()
    : method("") , uri("") , version(""), headers(), body(""){
      //intialised attributes to default values
  }


 // parsing
  