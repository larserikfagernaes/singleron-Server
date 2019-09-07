//
//  Authentication.cpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#include "Authentication.hpp"
#include "helloDragon/enteties/User.hpp"
#include <iostream>

#include "QueryFactory.hpp"
#include "sha.h"
#include "filters.h"
#include "base64.h"

using namespace std;

string SHA256HashString(string inputString){
    string digest;
    CryptoPP::SHA256 hash;
    
    CryptoPP::StringSource crptSource(inputString, true,new CryptoPP::HashFilter(hash,new CryptoPP::Base64Encoder (new CryptoPP::StringSink(digest))));
    
    return digest;
}

bool Authentication::validUser(string username, string password){
    std::string hashedPass = SHA256HashString(password);
    return QueryFactory::validUser(connection, username, hashedPass);
};
