#include <exception>
#include <iostream>

class SocketException : public std::exception {
 public:
  virtual const char* what() const throw() {
    return "Socket Exception Occured";
  }
};
