//
//  Created by Gerardo De La Maza on 9/5/18.
//  Copyright © 2018 Gerardo De La Maza. All rights reserved.
//
//  AETG algorithm to generate test suites
//  t2Table.hpp
//
//  This is the header file for hashTable.cpp
//  Creates a hash Table that contains all uncovered and covered pairs.
//  It is used to generate a single test case after evaluating 50 candidates
//
//

#ifndef t2Table_hpp
#define t2Table_hpp

#include <random>
#include <vector>
#include "tupleT2.hpp"

using namespace std;

// Hast Table to store all the pairs
class t2Table
{

private:
    int tableSize;                 //The size of the hash table
    int totalNumbers;              //Total number of values factors*levels
    int numberOfPairs;             //Total number of pairs
    int *factors;                  //Number of factors
    int *levels;                   //Number of Levels
    vector<int> uncoveredPairs;    //Stores the number of uncovered pairs for each value
    vector<vector<tupleT2>> table; //The hash table with all the possible pairs

public:
    t2Table(int *nunmberOfFactors, int *numberOfLevels); //Constructs a table with all the pairs
    int getNumberOfPairs();                              //Returns the number of uncovered pairs
    bool lookup(int a, int b);                           //Searches for pair(a,b). Returns true if it is covered
    void addPairs(int a, int b);                         //Adds pairs (a,b) as covered
    void addPairsInTest(vector<int> test);               //Adds all pairs in test as covered
    void setAllPairsToUncovered();                       //Sets all pairs to uncovered to start next suite
    vector<int> generateTest(vector<int> randomFactor);  //Generates a test after evaluating 50 candidates
};

#endif /* t2Table_hpp */
