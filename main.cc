#include <drogon/drogon.h>
#include <iostream>
#include "helloDragon/helpers/RInstance.hpp"
#include <RInside.h>                            // for the embedded R via RInside

int main(int argc, char **argv) {
    //Set HTTP listener address and port
//    for (int i = 0; i < groups.size(); i++){
//        output_string += std::to_string(i) + " = " + std::to_string(groups[i]) + "\n";
//    }
    RInside R(argc, argv);              // create the one embedded R instance

    
    drogon::app().addListener("0.0.0.0",80);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
