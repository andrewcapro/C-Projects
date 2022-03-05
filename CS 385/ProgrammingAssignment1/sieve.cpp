/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Andrew Capro
 * Date        : 1/30/2022
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;
class PrimesSieve {
public:
    PrimesSieve(int limit); 
    ~PrimesSieve() {
        delete [] is_prime_;
    }
    int num_primes() const {
        return num_primes_;
    }
    void display_primes() const;
private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;
    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    int check = limit_;
    while(is_prime_[check] == false){
        check-=1;
    }
    max_prime_ = check;
}
void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl;
    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    int count_spaces = 0;
    const int max_prime_width = num_digits(max_prime_); 
    int primes_per_row = 80 / (max_prime_width + 1);
    if(count_num_primes() < primes_per_row){
        for (int i = 2; i <= max_prime_; i++){
            if (i == max_prime_){
                cout << i;
            }
            else if(is_prime_[i]){
                cout << i << " ";
            }
        }
    }
    else{
        for (int i = 2; i <= max_prime_; i++){
            if (is_prime_[i]){
                int count = max_prime_width - num_digits(i);
                while(count > 0){
                    cout << " ";
                    count--;
                }
                
                if(count_spaces >= primes_per_row - 1){
                    cout << i << endl;
                    count_spaces = 0;
                }
                else if(i == max_prime_){
                    cout << i;
                    count_spaces = 0;
                } 
                else{
                    cout << i << " ";
                    count_spaces++;
                }
                /*if(count_spaces >= primes_per_row - num_digits(max_prime_) || i == max_prime_){
                    cout << i;
                    count_spaces = 0;
                } else{
                cout << i << " ";
                count_spaces++;
                }
                if(count_spaces >= primes_per_row){
                    cout << endl;
                    count_spaces = 0;
                }*/
            }
        }
    }
}
int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}
void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 0; i <= limit_; i++){
        is_prime_[i] = true;
    }

    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i]){
            for(int j = i*i; j <= limit_; j += i){
                is_prime_[j] = false;
            }
        }
    }
}
int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    int num2 = num;
    int digits = 1;
    while (num2 / 10 >= 1){
        digits++;
        num2 /= 10;
    }
    // Hint: No strings are needed. Keep dividing by 10.
    return digits;
}
int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit = 0;
    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);
    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve s(limit);
    s.display_primes();
    
    return 0;
}