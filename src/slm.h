#ifndef SLM_H
#define SLM_H
#include <string>
#include <map>
#include <random>
#include <set>

class slm {
    private:
        int k;
        float a;

        std::set<char> alphabet;
        std::map<std::string, int> kgram_count;
        std::map<std::string, std::map<char, int>> transition;
        std::string initial_kgram();

        std::mt19937 random_number;

        bool sample_next_char(const std::string& current_kgram, char& next_char);

    public:
        slm(int k, float a = 0.0);
        void train(const std::string& filename);
        std::string generate_text(int outputsize);
};
#endif // SLM_H