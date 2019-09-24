//
//  Created by Gerardo De La Maza on 9/5/18.
//  Copyright © 2018 Gerardo De La Maza. All rights reserved.
//
//  AETG algorithm to generate test suites
//  tupleT2.hpp
//
//  Header file for tuplet2.cpp
//

#ifndef tupleT2_hpp
#define tupleT2_hpp

class tupleT2
{

public:
    int value;        //The value that forms a pair with the current value
    bool found;       //True if the pair is already covered
    tupleT2(int val); //Constructs a new tuple (x,y) val refers to the value y
};

#endif /* tupleT2_hpp */
