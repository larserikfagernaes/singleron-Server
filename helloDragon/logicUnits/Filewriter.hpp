//
//  Filewriter.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 21/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef Filewriter_hpp
#define Filewriter_hpp
#include "Authentication.hpp"
#include <stdio.h>
#include <iostream>
#include "helloDragon/helpers/LEOptional.hpp"

using namespace std;

class Filewriter {
    Authentication* auth;
    static void writeStringToFile(string filename, string data);
    static string getStringFromFile(string filename);
public:
    Filewriter(Authentication* auth){this-> auth = auth; };
    void encryptAndWriteData(string message, string filepath, string encodePassword);
    LEOptional<string> decryptData(string username, string password, string filename, string decodePassword);
};

#endif /* Filewriter_hpp */

