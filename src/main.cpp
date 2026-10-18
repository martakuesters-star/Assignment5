#include <iostream>
#include <exception>
#include "appslm.h"

using namespace std;

int main(int argc, char* argv[]){
    try {
        appslm app(argc, argv);
        app.run();
    }
    catch (const exception& e) {
        cerr << "slm: " << e.what() << endl;
        return 1;
    }
    return 0;
}