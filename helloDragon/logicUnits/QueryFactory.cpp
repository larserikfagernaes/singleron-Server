//
//  QueryFactory.cpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#include "QueryFactory.hpp"
#include <cppconn/prepared_statement.h>
#include <iostream>

#include "sha.h"
#include "filters.h"
#include "base64.h"


bool QueryFactory::validUser(sql::Connection* con, string username, string passHash){
    bool validPassword = false;
    
    sql::PreparedStatement *prep_stmt = con->prepareStatement("SELECT * FROM users WHERE username = ?");
    prep_stmt->setString(1, username);
    std::unique_ptr<sql::ResultSet > res(prep_stmt->executeQuery());
    while (res->next()) {
        if (res->getString("password").compare(passHash)){
            return true;
        }
    }
    
    return false;
}

