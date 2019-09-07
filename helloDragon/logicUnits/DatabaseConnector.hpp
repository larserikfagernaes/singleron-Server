//
//  DatabaseConnector.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef DatabaseConnector_hpp
#define DatabaseConnector_hpp

#include <stdio.h>
#include <iostream>
#include "mysql_connection.h"
#include "mysql_driver.h"

using namespace std;

class DatabaseConnector{
    sql::Driver* driver;
    std::string url;
    std::string user;
    std::string pass;
    std::string database;
    sql::Connection* connection;
    public:
    DatabaseConnector(string url, string user, string pass, string database);
    void testConnection();
    sql::Connection* getConnection();
    static void testFunc();
};

#endif /* DatabaseConnector_hpp */
