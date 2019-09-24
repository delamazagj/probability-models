//
//  Created by Gerardo De La Maza on 9/5/18.
//  Copyright © 2018 Gerardo De La Maza. All rights reserved.
//
//  AETG algorithm to generate test suites
//  main.cpp
//
//  This is an implementation of the AETG algorithm that generates test suites
//  Firstly, the user is asked to enter the number of factors and levels to generate an interaction table
//  Secondly, 50 candidate test cases will be generated and the best will be picked
//  Thirdly, test cases will be generated until all pairs are covered and a test suite is formed
//  Fourthly, 100 test suites will be generated and the best will be picked
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>
#include "t2Table.hpp"
#include "tupleT2.hpp"

using namespace std;

int main(int argc, const char *argv[])
{

    srand(time(NULL));                             //to be able to use rand()
    bool firstTestSuite = true;                    //to check when it is the first suite and set variables
    int *factors = new int(), *levels = new int(); //factors and levels

    vector<int> test;                                           //holds the test selected after generating 50 candidates
    vector<vector<int>> *suite = new vector<vector<int>>();     //holds a test suite
    vector<vector<int>> *bestSuite = new vector<vector<int>>(); //will hold the suite with less test cases
    int minTest = 0;                                            //number of tests in the best suite
    int maxTest = 0;                                            //number of tests in the worst suite
    int allTest = 0;                                            //total number of tests in all suites
    int testsInSuite;                                           //tests in a suite

    //Asking the user
    printf("Enter the number of factors (components): ");
    scanf("%d", factors);
    printf("Enter the number of levels (options): ");
    scanf("%d", levels);

    double runningTime = 0;
    double average = 0;
    unsigned seed; //for random order of factor

    t2Table *Table = new t2Table(factors, levels); //Creates a table containing all possible pairs
    //Starting the clock
    clock_t start = clock();

    //creates a vector with the factors
    vector<int> randomFactor = *new vector<int>(*factors);
    for (int i = 0; i < *factors; i++)
        randomFactor[i] = i;

    //Check all test suites
    for (int i = 0; i < 100; i++)
    {
        suite = new vector<vector<int>>();
        testsInSuite = 0;

        /* Runs till no other pair is found to be added
            A test suite is then formed */
        while (Table->getNumberOfPairs() > 0)
        {
            //Generates a random order of the factors
            seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle((randomFactor).begin(), (randomFactor).end(), default_random_engine(seed));

            test = Table->generateTest(randomFactor);
            (*suite).push_back(test);
            Table->addPairsInTest(test);
        } //A test suite is formed

        testsInSuite = (*suite).size();
        if (firstTestSuite)
        {
            firstTestSuite = false; //no first suite anymore
            *bestSuite = *suite;
            minTest = testsInSuite;
            maxTest = testsInSuite;
        }
        else if (testsInSuite > maxTest) //there is a new maxTest or worst result
            maxTest = testsInSuite;

        else if (testsInSuite < minTest) //there is a new bestSuite and minTest
        {
            *bestSuite = *suite;
            minTest = testsInSuite;
        }

        allTest += testsInSuite;
        Table->setAllPairsToUncovered();
        delete suite;

    }                                                       //All suites completed
    runningTime = double(clock() - start) / CLOCKS_PER_SEC; //holds time in secs
    average = runningTime / 100;

    printf("***********************************************\n");
    printf("  Best Test Suite: %d tests\n", minTest);
    printf("  Average Tests per Suite: %d tests\n", allTest / 100);
    printf("  Worst Test Suite: %d tests\n", maxTest);
    printf("  Average Execution Time: %.3lfs\n", average);
    printf("  Total Execution Time: %dm %ds  or  %.3lfs\n", int(runningTime) / 60, int(runningTime) % 60, runningTime);
    printf("***********************************************\n");

    //Creating and writing the results to a file
    FILE *filePointer;
    filePointer = fopen("TestSuite.txt", "w");

    fprintf(filePointer, "%d\n\n", minTest);
    for (int i = 0; i < minTest; i++)
    {
        for (int j = 0; j < (*factors); j++)
            fprintf(filePointer, "%d ", (*bestSuite)[i][j]);
        fprintf(filePointer, "\n");
    }

    fclose(filePointer);

    return 0;
}
