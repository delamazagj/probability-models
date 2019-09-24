//  Created by Gerardo De La Maza on 9/5/18.
//  Copyright © 2018 Gerardo De La Maza. All rights reserved.
//
//  AETG algorithm to generate test suites
//  tupleT2.cpp
//
//  Creates the value that forms a pair with the corresponded entry in the hash table.
//  All values (pairs) are created as not found as default.
//

#include "tupleT2.hpp"

//Constructor for tupleT2()
tupleT2::tupleT2(int val)
{
    found = false;
    value = val;
}
