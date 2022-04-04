/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Andrew Capro
 * Version     : 1.0
 * Date        : March 23 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long counter = 0;
    for(int i = 0; i < length; i++){
        for(int j = i+1; j < length; j++){
            if (array[i] > array[j]){
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long count = mergesort(array, scratch, 0, length-1);
    delete [] scratch;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long value = 0;
    if (low < high){
        int mid = low + (high - low) / 2;
        value += mergesort(array, scratch, low, mid);
        value += mergesort(array, scratch, mid+1, high);
        int j = low;
        int k = mid + 1;
        for(int q = low; q <= high; q++){
            if (j <= mid && (k > high || array[j] <= array[k])){
                scratch[q] = array[j++];
            }
            else{
                scratch[q] = array[k++];
                value += mid - j + 1;
            }
        }
        for(int q = low; q <= high; q++){
            array[q] = scratch[q];
        }
    }
    return value;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if (argc != 1 && argc != 2) {
            cerr << "Usage: ./inversioncounter [slow]\n";
            return 1;
        }
    else if (argc == 2 && (string)argv[1] != "slow"){
        cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    const int len = values.size();
    if (len == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    else if(argc == 2){
        cout << "Number of inversions: " << count_inversions_slow(&values[0], len) << endl;
    }
    else if(argc == 1){
        cout << "Number of inversions: " << count_inversions_fast(&values[0], len) << endl;
    }
    return 0;
}
