//
//  Authentication.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef Authentication_hpp
#define Authentication_hpp

#include <stdio.h>
#include <iostream>
#include "helloDragon/enteties/User.hpp"
#include "mysql_connection.h"

using namespace std;

struct AuthenticationResponse{
public:
    AuthenticationResponse(bool valid_user, User user);
};

class Authentication{
    sql::Connection* connection;
public:
    Authentication(sql::Connection* connection) {this->connection = connection;};
    bool validUser(string username, string password);
};


#endif /* Authentication_hpp */
