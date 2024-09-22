#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random string of a given length
string generateRandomString(int length = 25) {
    string letters = "abcdefghijklmnopqrstuvwxyz";
    string result;
    for (int i = 0; i < length; ++i) {
        result += letters[rand() % letters.size()];
    }
    return result;
}

int main(int argc, char* argv[]) {
    int n, m;
    // Seed the random number generator
    srand(time(0));

    // Reading n and m from the command line
	n = atoi(argv[1]);
	m = atoi(argv[2]);
    cout << n << " " << m << endl;

    // Generating and printing n words with their frequencies
    for (int i = 0; i < n; ++i) {
        // Generate a random word of wordLength
        string word = generateRandomString();
        // Generate a random frequency for the word
        int frequency = rand() % 100 + 1; // Frequency between 1 and 100
        cout << word << " " << frequency << endl;
    }

    return 0;
}