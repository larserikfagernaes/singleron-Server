//
//  RInstance.hpp
//  helloDragon
//
//  Created by Lars Erik Fagernæs on 02/09/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//

#ifndef RInstance_hpp
#define RInstance_hpp
#include <stdio.h>
#include <iostream>
#include <RInside.h>                            // for the embedded R via RInside

class RInstance
{
public:
    static RInstance& getInstance()
    {
        static RInstance    instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    
    RInside getRInside(){return RInside::instance();}
    RInstance(RInstance const&)               = delete;
    void operator=(RInstance const&)  = delete;
    
private:
//    RInside R;
    int counter = 0;
    RInstance() {}                    // one time constructor
};

#endif /* RInstance_hpp */
