#ifndef USRPLIB_RX_H
#define USRPLIB_RX_H

#include <string>

namespace usrplib {

class Rx {

public:
   Rx()
   : address("192.168.10.2")
   {};

   /* Get/Set Methods */
   void setAddress( std::string &address_ ) { address = address_; }
   std::string getAddress() { return address; }

private:
   std::string address;

};

} // usrplib

#endif /* USRPLIB_RX_H */
