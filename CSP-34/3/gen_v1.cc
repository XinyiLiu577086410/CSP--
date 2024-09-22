#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Function to read words from file and count their frequencies
unordered_map<string, int> countWordFrequencies(const string& filename) {
    ifstream file(filename);
    unordered_map<string, int> wordFreq;
    string word;

    while (file >> word) {
        ++wordFreq[word];
    }

    return wordFreq;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <n> <m> <file>" << endl;
        return 1;
    }

    // int n = atoi(argv[1]);
    int m = atoi(argv[1]);

    string filename = argv[2];

    // Count word frequencies from the file
    unordered_map<string, int> wordFreq = countWordFrequencies(filename);

    // Print the first n words and their frequencies

	cout << wordFreq.size() << " " << m << endl;
    
	for (const auto& pair : wordFreq) {
        cout << pair.first << " " << pair.second << endl;
    }

    return 0;
}