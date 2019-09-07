//
//  QueryFactory.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 13/07/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef QueryFactory_hpp
#define QueryFactory_hpp

#include <stdio.h>
#include <iostream>
#include "mysql_connection.h"

using namespace std;

class QueryFactory{
public: 
    static bool validUser(sql::Connection*, string username, string passHash);
};

#endif /* QueryFactory_hpp */
