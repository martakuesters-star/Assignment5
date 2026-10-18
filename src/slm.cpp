#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "slm.h"

using namespace std;

/*
slm::slm(int k, float a) : k(k), a(a) {
    if (k <= 0) {
        throw invalid_argument("k must be a positive integer");
    }
    if (a < 0) {
        throw invalid_argument("pseudocount must be non-negative");
    }
    random_device randomd;
    random_number = mt19937(randomd());
}
*/

slm::slm(int kgram, float alpha) : kgram(kgram), alpha(alpha), random_number(random_device{}()) {
    if (kgram <= 0) {
        throw invalid_argument("k-gram must be a positive integer");
    }
    if (alpha < 0) {
        throw invalid_argument("pseudocount must be non-negative");
    }
}

void slm::train(const string& filename) {
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw runtime_error("can not open file '" + filename + "'");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    string training_content = buffer.str();
    const int training_content_len = static_cast<int>(training_content.size());

    file.close();

    // we need at least one k-gram followed by a character
    if (static_cast<int>(training_content.size()) <= kgram) {
        throw runtime_error("training text is too short for k-gram = " + to_string(kgram));
    }

    kgram_count.clear();
    transition.clear();
    alphabet.clear();

    // alphabet = distinct characters in the training text
    for (char c: training_content) {
        alphabet.insert(c);
    }

    // k-gram frequencies: every k-gram counts, including the last one
    // transitions: only k-grams that are followed by a character

    for (int i = 0; i + kgram <= training_content_len; ++i) {
        string current_kgram = training_content.substr(i, kgram);
        
        if (i + kgram < training_content_len) {
            char next_c = training_content[i + kgram];
            transition[current_kgram][next_c]++;
            kgram_count[current_kgram]++;
        }
    }
    // checking if there's a valid transition
    if (kgram_count.empty()) {
        throw runtime_error("no valid transitions in training text");
    }
}

string slm::generate_text(int outputsize) {
    string result;
    
    // choose a starting k-gram based on frequencies
    vector<string> kgrams;
    vector<double> kgram_weights;
    
    for (const auto& pair : kgram_count) {
        kgrams.push_back(pair.first);
        kgram_weights.push_back(pair.second);
    }
    
    discrete_distribution<int> start_dist(kgram_weights.begin(), kgram_weights.end());
    string current_w = kgrams[start_dist(random_number)];
    result += current_w;

    // convert alphabet set to a vector for consistent indexing
    vector<char> chars(alphabet.begin(), alphabet.end());

    // generate subsequent characters
    for (int i = 0; i < outputsize - kgram; ++i) {
        // stop if alpha is 0 and the current k-gram has no transitions
        if (alpha == 0.0 && kgram_count[current_w] == 0) {
            break;
        }

        vector<double> char_weights;
        
        // calculate the weight (n(w, c) + alpha) for every character in the alphabet
        for (char c : chars) {
            double weight = transition[current_w][c] + alpha;
            char_weights.push_back(weight);
        }

        // sample the next character
        discrete_distribution<int> char_dist(char_weights.begin(), char_weights.end());
        int chosen_index = char_dist(random_number);
        char next_c = chars[chosen_index];

        result += next_c;

        // update the current k-gram by dropping the first character and appending the new one
        current_w = current_w.substr(1) + next_c;
    }

    return result;
}