cmake_minimum_required (VERSION 3.2)
Project(helloDragon)


include_directories(${root_SOURCE_DIR})
include_directories(/usr/local/include/cppconn)
include_directories(/usr/local/mysql-connector-c++-8.0.17/include/jdbc)
include_directories(/usr/local/include)
include_directories(/usr/local/include/cryptopp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(/Library/Frameworks/R.framework/Versions/3.6/Resources/library/RInside/include)
include_directories(/Library/Frameworks/R.framework/Versions/3.6/Resources/library/Rcpp/include)
include_directories(/Library/Frameworks/R.framework/Versions/3.6/Headers)


link_directories(${root_SOURCE_DIR})
link_directories(/usr/local/lib)
link_directories(/usr/local/mysql-connector-c++-8.0.17/lib64)
link_libraries(drogon trantor pthread dl)

#add_subdirectory (logicUnits)
#add_library(DatabaseConnector /Users/LarsErik/egenBedrift/singleron/singleronPlatform/helloDragon/helloDragon/helloDragon/logicUnits/DatabaseConnector.cpp )


IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    EXEC_PROGRAM (gcc ARGS "--version | grep '^gcc'|awk '{print $3}' | sed s'/)//g' | sed s'/-.*//g'" OUTPUT_VARIABLE version)
    MESSAGE(STATUS "This is gcc version:: " ${version})
    if(version LESS 5.4.0)
        MESSAGE(STATUS "gcc is too old")
        stop()
    elseif(version LESS 7.1.0)
        set(CMAKE_CXX_STD_FLAGS c++14)
        MESSAGE(STATUS "c++14")
    else()
        set(CMAKE_CXX_STD_FLAGS c++17)
        MESSAGE(STATUS "c++17")
    endif()
else()
    set(CMAKE_CXX_STD_FLAGS c++17)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=${CMAKE_CXX_STD_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=${CMAKE_CXX_STD_FLAGS}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

#jsoncpp
find_package (Jsoncpp REQUIRED)
include_directories(${JSONCPP_INCLUDE_DIRS})
link_libraries(${JSONCPP_LIBRARIES})

#uuid
find_package (UUID REQUIRED)
include_directories(${UUID_INCLUDE_DIR})
link_libraries(${UUID_LIBRARIES})

#OpenSSL
find_package (OpenSSL)
if(OpenSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
    link_libraries(${OPENSSL_LIBRARIES})
endif()

#zlib
find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIR})
link_libraries(${ZLIB_LIBRARIES})

#Find CPPCon 
#add_library(CPPCON STATIC /usr/local/mysql-connector-c++-8.0.17/lib64/libmysqlcppconn8-static.a)
#add_library( CPPCon SHARED /usr/local/mysql-connector-c++-8.0.17/lib64/libmysqlcppconn.dylib )

#find postgres
find_package(PostgreSQL)
if(PostgreSQL_FOUND)
include_directories(${PostgreSQL_INCLUDE_DIR})
link_libraries(${PostgreSQL_LIBRARIES})
endif()

#Find mysql, only mariadb client liberary is supported
find_package(MySQL)
if(MYSQL_FOUND)
    message(STATUS "inc:" ${MYSQL_INCLUDE_DIR})
    message(STATUS "libs:" ${MYSQL_CLIENT_LIBS})
    message(STATUS "version:" ${MYSQL_VERSION_STRING})
    if(MYSQL_VERSION_STRING STREQUAL "")
        message(STATUS "The mysql in your system is not the mariadb, so we can't use it in drogon")
    else()
        message(STATUS "Ok! We find the mariadb!")
        include_directories(${MYSQL_INCLUDE_DIR})
        link_libraries(${MYSQL_CLIENT_LIBS})
    endif()
endif()

#Find sqlite3.
find_package (SQLite3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  link_libraries(${SQLITE3_LIBRARIES})
endif()

AUX_SOURCE_DIRECTORY(./ SRC_DIR)
AUX_SOURCE_DIRECTORY(controllers CTL_SRC)
AUX_SOURCE_DIRECTORY(filters FILTER_SRC)
AUX_SOURCE_DIRECTORY(plugins PLUGIN_SRC)
AUX_SOURCE_DIRECTORY(models MODEL_SRC)


#FILE(GLOB Logic_Units_Sources RELATIVE "logicUnits" "*.cpp")
FILE(GLOB LOGIC_UNIT_FILES ${PROJECT_SOURCE_DIR}/helloDragon/logicUnits/*.cpp)
FILE(GLOB HELPERS_FILES ${PROJECT_SOURCE_DIR}/helloDragon/helpers/*.cpp)
FILE(GLOB ENTETIES_FILES ${PROJECT_SOURCE_DIR}/helloDragon/enteties/*.cpp)
FILE(GLOB SCP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/views/*.csp)
foreach(cspFile ${SCP_LIST})
    message(STATUS "cspFile:" ${cspFile})
    EXEC_PROGRAM(basename ARGS "${cspFile} .csp" OUTPUT_VARIABLE classname)
    message(STATUS "view classname:" ${classname})
    add_custom_command(OUTPUT ${classname}.h ${classname}.cc
            COMMAND drogon_ctl
            ARGS create view ${cspFile}
            DEPENDS ${cspFile}
            VERBATIM )
    set(VIEWSRC ${VIEWSRC} ${classname}.cc)
endforeach()

add_executable(helloDragon ${SRC_DIR} ${CTL_SRC} ${FILTER_SRC} ${VIEWSRC} ${PLUGIN_SRC} ${MODEL_SRC} ${HELPERS_FILES} ${ENTETIES_FILES} ${LOGIC_UNIT_FILES} ) 

target_link_libraries(helloDragon /usr/local/Cellar/mysql-connector-c++/1.1.9_2/lib/libmysqlcppconn.7.dylib)
target_link_libraries(helloDragon /usr/local/Cellar/cryptopp/8.1.0/lib/libcryptopp.a)
target_link_libraries(helloDragon /Library/Frameworks/R.framework/Versions/3.6/Resources/library/RInside/lib/libRInside.dylib)
target_link_libraries(helloDragon /Library/Frameworks/R.framework/Versions/3.6/Resources/lib/libR.dylib) 

