/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Andrew Capro
 * Version : 1.0
 * Date    : January 21, 2022
 * Description : Computes the square root of a double using Newton's Method
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

double num = 0;
double epsilon = 0;
double last_guess = 1;
double next_guess = 1;
double sqrt(double num, double epsilon){
    if (epsilon == (double)0){
        epsilon = (double)1e-7;
    }
    if (num < (double)0){
        return numeric_limits<double>::quiet_NaN();
    }
    if (num == (double)0 || num == (double)1){
        return num;
    }
    do{
        last_guess = next_guess;
        next_guess = (last_guess + num / last_guess) / 2;
    } while (!(abs(last_guess - next_guess) <= abs(epsilon)));
    return next_guess;
}

int main(int argc, char* argv[]){
    
    istringstream iss;

    if(argc != 2 && argc != 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> num)){
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    if(argc == 3){
        iss.clear();
        iss.str(argv[2]);
        if(!(iss >> epsilon)){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    if(epsilon <= 0){
        cerr << "Error: Epsilon argument must be a positive double." << endl;
        return 1;
    }
    }
    double result = sqrt(num,epsilon);
    cout << fixed << setprecision(8) << result;
}
   