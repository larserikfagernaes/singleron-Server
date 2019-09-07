//
//  DatabaseConnector.cpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//
/**
 * Basic example of creating a stand alone program linked against Connector/C++
 *
 * This example is not integrated into the Connector/C++ build environment.
 * You must run "make install" prior to following the build instructions
 * given here.
 *
 * To compile the standalone example on Linux try something like:
 *
 * /usr/bin/c++
 *   -o standalone
 *   -I/usr/local/include/cppconn/
 *   -Wl,-Bdynamic -lmysqlcppconn
 *    examples/standalone_example.cpp
 *
 * To run the example on Linux try something similar to:
 *
 *  LD_LIBRARY_PATH=/usr/local/lib/ ./standalone
 *
 * or:
 *
 *  LD_LIBRARY_PATH=/usr/local/lib/ ./standalone host user password database
 *
 */
/* Standard C++ includes */
#include "DatabaseConnector.hpp"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

/*
 Include directly the different
 headers from cppconn/ and mysql_driver.h + mysql_util.h
 (and mysql_connection.h). This will reduce your build time!
 */

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define EXAMPLE_HOST "localhost"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS "root"
#define EXAMPLE_DB "mysql"

using namespace std;

void DatabaseConnector::testFunc(){
    std::cout << "running test func";
}

DatabaseConnector::DatabaseConnector(string url, string user, string pass, string database){
    try {
        this->driver = sql::mysql::get_driver_instance();
        this->url = url;
        this->user = user;
        this->pass = pass;
        /* Using the Driver to create a connection */
        connection = driver->connect(url, user, pass);
        connection->setSchema(database);
        cout << "we have made a connection"; 
    } catch (sql::SQLException &e) {
        /*
         The MySQL Connector/C++ throws three different exceptions:
         - sql::MethodNotImplementedException (derived from sql::SQLException)
         - sql::InvalidArgumentException (derived from sql::SQLException)
         - sql::SQLException (derived from std::runtime_error)
         */
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

sql::Connection* DatabaseConnector::getConnection(){
    return this->connection;
}

void DatabaseConnector::testConnection(){
    std::unique_ptr<sql::Statement> stmt(this->connection->createStatement());
    std::unique_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT 'Welcome to Connector/C++' AS _message"));
    cout << "\t... running 'SELECT 'Welcome to Connector/C++' AS _message'" << endl;
    while (res->next()) {
        cout << "\t... MySQL replies: " << res->getString("_message") << endl;
        cout << "\t... say it again, MySQL" << endl;
        cout << "\t....MySQL replies: " << res->getString(1) << endl;
    }
}
