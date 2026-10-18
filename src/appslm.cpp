#include <iostream>
#include <fstream>
#include <stdexcept>
#include "appslm.h"
#include "slm.h"

using namespace std;

/*
$ slm 2 moby_dick.txt 5
$ slm -a 0.01 3 moby_dick.txt 40
*/

appslm::appslm(int argc, char* argv[]) {
    // user provides 3 arguments ('-a' option not provided -> alpha = 0):
    if (argc == 4) { 
        alpha = 0.0; 
        
        kgram = stoi(argv[1]);
        filename = argv[2];
        outputsize = stoi(argv[3]);
    }

    // user provides 5 arguments ('-a' argument is provided):
    else if (argc == 6) { 
        if (string(argv[1]) != "-a") {
            throw invalid_argument("invalid argument '" + string(argv[1]) + "'");
        }

        alpha = stof(argv[2]);
        kgram = stoi(argv[3]);
        filename = argv[4];
        outputsize = stoi(argv[5]);
    }

    // if the user doesn't provide enough arguments:
    else {
        throw invalid_argument("invalid number of arguments");
    }

    // if the arguments provided by the user are negative:
    if (alpha < 0.0) {
        throw invalid_argument("-a value can not be negative");
    }

    if (kgram < 1) {
        throw invalid_argument("k-gram must be a positive integer");
    }

    if (outputsize < kgram) {
        throw invalid_argument("output size should be greater than or equal to k-gram value (" + to_string(kgram) + ")");
    }
}

void appslm::run() {
    /* 
    // test code:
    cout << "a: " << to_string(alpha) << ", kgram: " << to_string(kgram) << ", output size: " << to_string(outputsize) << ", filename: " << filename << endl;
    return;
    */

    // passing the contents of the file to the model slm (train and generate text)
    slm model(kgram, alpha);
    model.train(filename);

    string result = model.generate_text(outputsize);
    cout << result << endl;
}