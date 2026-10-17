#include <fstream>
#include <stdexcept>
#include <vector>
#include "slm.h"

using namespace std;

slm::slm(int k, float a) {
    random_device randomd;
    random_number = mt19937(randomd());
}

void slm::train(const string& filename) {
    ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        throw runtime_error("can not open file '" + filename + "'");
    }

    string text_content = "";
    char c;
    while (file.get(c)) {
        text_content += c;
        alphabet.insert(c);
    }

    file.close();

    // fazer uma excessão para ver se o texto é longo o suficiente

    kgram_count.clear();
    transition.clear();

    // talvez um for que vai extrair os k-grams e transições do texto?
}

string slm::generate_text(int outputsize) {
    if (outputsize < k) {
        return string("");
    }

    string current_kgram = initial_kgram();

    string output = current_kgram;

    return string();
}

bool slm::sample_next_char(const string& current_kgram, char& next_char) {
    return false;
}

string slm::initial_kgram() {
    return string();
}