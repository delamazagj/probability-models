//
//  Created by Gerardo De La Maza on 9/5/18.
//  Copyright © 2018 Gerardo De La Maza. All rights reserved.
//
//  AETG algorithm to generate test suites
//  t2Table.cpp
//
//  Implementation for all methods in t2Table.hpp
//

#include "t2Table.hpp"
#include "tupleT2.hpp"

//Constructor for t2Table()
//Takes in the number of factors and levels and generates a table
//with all possible pairs
t2Table::t2Table(int *nunmberOfFactors, int *numberOfLevels)
{

    numberOfPairs = 0;                                  //default declaration for the number of pairs
    factors = nunmberOfFactors;                         // number of factors
    levels = numberOfLevels;                            //number of levels
    tableSize = (((*factors) * (*levels)) - (*levels)); //The size of the table is factors*levels-levels
    table.resize(tableSize);                            //Allocates memory for the table to cover the size it needs
    totalNumbers = (*factors) * (*levels);              //The total number of possible values is factors*levels

    // Allocates memory for the array of number of uncovered pairs for each value
    uncoveredPairs.resize(totalNumbers);

    int counter = (*levels); //Used to count the levels on each factor

    // Inserts the 'y' values to each entry, forming all possible pairs
    // and set each value in the uncoveredPairs array to its maximun
    for (int i = 0; i < tableSize; i++)
    {
        uncoveredPairs[i] = ((*factors) - 1) * (*levels);
        for (int j = i + counter; j < totalNumbers; j++)
        {
            table[i].push_back(*new tupleT2(j));
            numberOfPairs++;
        }
        counter--;
        if (counter < 1)
            counter = (*levels);
    }
    for (int i = tableSize; i < tableSize + (*levels); i++)
        uncoveredPairs[i] = ((*factors) - 1) * (*levels);
}

int t2Table::getNumberOfPairs() { return numberOfPairs; } //Returns the current number of uncovered pairs

// Lookup funtion to check if a pair a,b is covered
// Returns false if it is uncovered
bool t2Table::lookup(int a, int b)
{

    //To find the pair easily, b should be greater than a
    //In case this condition is not met, both values are swapped
    if (a > b)
        swap(a, b);
    //Finds the pair and evaluates whether is covered
    if (table[a][(b - (a / (*levels) + 1) * (*levels))].found)
        return true;
    return false;
}

// Marks the pair a,b as covered
// Updates the array with the number of uncovered pairs
// Updates the total number of uncovered pairs
void t2Table::addPairs(int a, int b)
{

    //For simplicity when finding the pair, a should be < b
    if (a > b)
        swap(a, b);

    // Looks for the pair a,b and flags it as covered
    if (!table[a][(b - (a / (*levels) + 1) * (*levels))].found)
    {
        table[a][(b - (a / (*levels) + 1) * (*levels))].found = true;
        uncoveredPairs[a]--;
        uncoveredPairs[b]--;
        numberOfPairs--;
    }
}

//Marks all pairs in a test as covered
void t2Table::addPairsInTest(vector<int> test)
{

    for (int i = 0; i < (*factors) - 1; i++)
        for (int j = i + 1; j < (*factors); j++)
            addPairs(test[i], test[j]);
}

//Generates a test case after evaluating 50 candidates
vector<int> t2Table::generateTest(vector<int> order)
{

    bool firstFactor;                  //to check if the first factor of the test is being evaluated
    int mostPairs;                     //maximun uncovered pairs of the best level
    int newPairs;                      //new possible pairs than can be generated for a specific level
    int testPairs;                     //new pairs in an specific test
    int maxTestPairs = 0;              //maximun numbers of new pairs a test has among all candidates
    vector<int> *test;                 //a test
    vector<vector<int>> testSelection; //holds all candidate tests with the maximun new pairs
    vector<int> levelSelection;        //holds all levels of a factor with the maximun uncovered pairs

    //Creates a test after evaluating 50 candidates
    int j = 50;
    while (j--)
    {
        //sets default values for the variables
        testPairs = 0;
        test = new vector<int>(*factors, -1);
        firstFactor = true;

        //Creates a candidate test
        int t = *factors;
        while (t--)
        {
            //sets default values for the variables
            mostPairs = -1;
            newPairs = 0;
            levelSelection.clear();

            // if this is the first factor of the test, the level with the maximun
            // number of uncovered pairs is taken.
            // if there are several levels with the same maximun number of uncovered pairs,
            // they will be store in levelSelection and one will be randomly selected
            if (firstFactor)
            {
                firstFactor = false; //Next factor won't be the first one
                int from = order[t] * (*levels);
                int to = from + (*levels);
                for (int i = from; i < to; i++)
                {
                    if (uncoveredPairs[i] > mostPairs)
                    {
                        mostPairs = uncoveredPairs[i];
                        levelSelection.clear();
                        levelSelection.push_back(i);
                    }
                    else if (uncoveredPairs[i] == mostPairs)
                        levelSelection.push_back(i);
                }
            }

            // if this is not the first factor, then the level of the current factor that will
            // generate the most new pairs with the already selected levels of the other factors
            // for this test will be selected. In case there is more than one level that will generate
            // the most new pairs, then levelSelection will hold then and one will be picked randomly
            else
            {
                int from = order[t] * (*levels);
                int to = from + (*levels);
                for (int i = from; i < to; i++)
                {
                    newPairs = 0;
                    for (int s = 0; s < *factors; s++)
                    {
                        if ((*test)[s] != -1)
                        {
                            if (!lookup((*test)[s], i))
                                newPairs++;
                            if (newPairs > mostPairs)
                            {
                                mostPairs = newPairs;
                                levelSelection.clear();
                                levelSelection.push_back(i);
                            }
                            else if (newPairs == mostPairs)
                                levelSelection.push_back(i);
                        }
                    }
                }
            }

            //randomly selecting one level out of those that will generate the same
            //amount of new pairs
            (*test)[order[t]] = levelSelection[rand() % levelSelection.size()];

        } //A candidate test is formed

        //After a candidate test is generated, the ones that will produce the most
        //new pairs are held in testSelection. One will then be picked randomly
        for (int i = 0; i < (*factors) - 1; i++)
            for (int s = i + 1; s < (*factors); s++)
                if (!lookup((*test)[i], (*test)[s]))
                    testPairs++;

        if (testPairs > maxTestPairs)
        {
            maxTestPairs = testPairs;
            testSelection.clear();
            testSelection.push_back(*test);
        }
        else if (testPairs == maxTestPairs)
            testSelection.push_back(*test);

        delete test;

    } //A test is formed in (testSelection)

    //randomly selecting one of the best candidate test
    vector<int> goodTest = testSelection[(rand() % testSelection.size())];

    //returns the new test case
    return goodTest;
}

//Sets all pairs to uncovered and resets the uncoveredPairs array
void t2Table::setAllPairsToUncovered()
{

    numberOfPairs = 0;
    for (int i = 0; i < tableSize; i++)
    {
        uncoveredPairs[i] = ((*factors) - 1) * (*levels);
        int aux = table[i].size();
        for (int j = 0; j < aux; j++)
        {
            table[i][j].found = false;
            numberOfPairs++;
        }
    }
    for (int i = tableSize; i < tableSize + (*levels); i++)
        uncoveredPairs[i] = ((*factors) - 1) * (*levels);
}
