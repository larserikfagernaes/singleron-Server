//
//  Optional.hpp
//  tmpTest
//
//  Created by Lars Erik Fagernæs on 28/08/2019.
//  Copyright © 2019 Lars Erik Fagernæs. All rights reserved.
//
#include <stdio.h>
#include <iostream>

#ifndef LEOptional_hpp
#define LEOptional_hpp

using namespace std;
template <typename T>
class LEOptional {
private:
    T ptr;
    
public:
    LEOptional(T value);
    LEOptional();
    T getData();
    bool hasValue();
};

template <typename T>
LEOptional<T>::LEOptional(T value)
{
    ptr = value;
}

template <typename T>
bool LEOptional<T>::hasValue(){
    return this->ptr != T(); 
//    return this->ptr != nullptr;
}

template <typename T>
T LEOptional<T>::getData(){
    return this->ptr;
}

template <typename T>
LEOptional<T>::LEOptional(){
    
}

#endif /* Optional_hpp */
