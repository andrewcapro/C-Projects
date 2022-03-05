/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Andrew Capro
 * Date        : 2/4/2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>
using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    size_t n = s.length();
    for(size_t i = 0; i < n; i++){
        if(!(islower(s[i]))){
            cerr << "Error: String must contain only lowercase letters." << endl;
            return false;
        } 
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    size_t n = s.length();
    unsigned int vector = 0;
    unsigned int setter = 0;
    for(size_t i = 0; i < n; i++){
        setter = 0;
        setter = 1 << (s[i] - 'a');
        if((vector & setter) != 0){
            cerr << "Duplicate letters found." << endl;
            return false;
        }
        vector = vector | setter;
    }
    cout << "All letters are unique." << endl;
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2){
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }
    if(is_all_lowercase(argv[1])){
        all_unique_letters(argv[1]);
    }
}
