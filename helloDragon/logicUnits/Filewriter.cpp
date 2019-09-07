//
//  Filewriter.cpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 21/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#include "Filewriter.hpp"
#include "Authentication.hpp"

#include <fstream>
#include <optional>
#include <iostream>


using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cryptopp/default.h>
using CryptoPP::DefaultEncryptorWithMAC;
using CryptoPP::DefaultDecryptorWithMAC;

#include <cryptopp/filters.h>
using CryptoPP::StringSource;
using CryptoPP::StringSink;

#include <cryptopp/files.h>
using CryptoPP::FileSource;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

using namespace std;

//typedef uint8_t byte;

void Filewriter::writeStringToFile(string filename, string message){
    std::ofstream out(filename);
    out << message;
    out.close();
}

string Filewriter::getStringFromFile(string filename){
    ifstream t(filename);
    string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    
    return str;
}

void Filewriter::encryptAndWriteData(string message, string filepath, string encodePassword){
    string encrypted;
    
    
    StringSource ss1(message, true,
                     new DefaultEncryptorWithMAC((uint8_t*)encodePassword.data(), encodePassword.size(),
                                                 new HexEncoder(new StringSink(encrypted))));
    
    Filewriter::writeStringToFile(filepath, encrypted);
}

LEOptional<string> Filewriter::decryptData(string username, string password, string filename, string decodePassword){
    if (this->auth->validUser(username, password) == true){
        string decrypted;
        string encryptedSource = getStringFromFile(filename);
        
        
        
        StringSource ss(encryptedSource, true,
                         new HexDecoder(
                                        new DefaultDecryptorWithMAC(
                                                                    (uint8_t*)decodePassword.data(), decodePassword.size(),
                                                                    new StringSink(decrypted))));
        
        
        return LEOptional<string>(decrypted);
    }
    else {
        return LEOptional<string>();
    }
}
