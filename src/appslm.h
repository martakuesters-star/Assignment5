#ifndef APPSLM_H
#define APPSLM_H
#include <string>
//#include "slm.h"

class appslm {
    private:
        std::string filename;
        int kgram;
        float alpha;
        int outputsize;
    public:
        appslm(int argc, char* argv[]);
        void run();
};
#endif // APPSLM_H