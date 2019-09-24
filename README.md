# probability-models


Here is an implementation of the AETG algorithm in C++. I created a class named tupleT2 to store the value that forms a pair with another. All values are set as not found by default since in the beginning no pairs have been covered yet. There is also a class named t2Table that holds the data structure (hash table) containing all the interaction pairs. This is an example of how it abstractly looks for 3^4:

Entries
0 3, 4, 5, 6, 7, 8, 9, 10, 11
1 3, 4, 5, 6, 7, 8, 9, 10, 11
2 3, 4, 5, 6, 7, 8, 9, 10, 11
3 6, 7, 8, 9, 10, 11
4 6, 7, 8, 9, 10, 11
5 6, 7, 8, 9, 10, 11
6 9, 10, 11
7 9, 10, 11
8 9, 10, 11

For example, pair 3-9 is found in entry 3 of the table. 

The algorithm loops 50 times in order to create a test case. While doing this, it creates 50 candidate tests. The best candidates (the ones that generate the most new pairs) are set aside and one is picked randomly. This test is then added to the suite and the found pairs in the table are updated. The algorithm will generate tests until the number of uncovered or not found pairs reaches 0. This means that all pairs are accounted for. Then, all the generated tests count as a suite. As instructed, my program loops 100 times (creates 100 suites) and picks the suite with the least number of tests and writes it to a file named TestSuite.txt. It also gets the number of tests in the suite with most tests. At the same time, it records the total number of tests throughout all suites to obtain the average number of tests per suite. The total and average execution times are also recorded. At the end, all this information is shown in an understandable way.

The results for all samples are stored in the files 2^10.txt, 3^4.txt, 3^13.txt, 4^40.txt, and 10^20.txt. The table with all the results against the ones from the AETG is stored in a file named ResultsTable.docx

The program uses functionalities found in C++11, so please run it in a computer that supports it. In order to compile and run the program, I have also included a makefile. To compile the program please first type the command:

### `make`

This will generate all .o files and an executable named output. After this, please type the command:

### `make out`




