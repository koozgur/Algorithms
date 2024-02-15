#include <string>
#include <climits>

int recursive_alignment(std::string sequence_A, 
                        std::string sequence_B, 
                        int gap, 
                        int mismatch, 
                        int match, 
                        std::string &possible_alignment, 
                        int call_count
                        );

int dp_table_alignment(std::string sequence_A, 
                        std::string sequence_B, 
                        int gap, 
                        int mismatch, 
                        int match, 
                        std::string &possible_alignment
                        );

/*
g++ test.cpp the3.cpp -Wall -std=c++11 -o test
*/
