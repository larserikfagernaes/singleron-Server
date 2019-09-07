//
//  User.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 14/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <iostream>

enum UserRole { admin };


using namespace std;

class User {
    string username;
    UserRole role; 
    public:
    User(string username, UserRole role);
};


#endif /* User_hpp */
