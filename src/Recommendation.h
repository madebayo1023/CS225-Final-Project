#pragma once

#include <map>
#include <fstream>
#include <string>
#include "MotionPicture.h"

using namespace std;

class Recommendation {
    public:
        /**
        * Creates the Recommendation object 
        *
        * @param file the dataset
        */
        Recommendation(string file);
        void reverse(string& str);
    private:
        map<MotionPicture, map<MotionPicture, double> > database;
        /**
        * Parses the dataset 
        *
        * @return a vector or each individual element for the MotionPicture object
        */
        std::vector<std::string> Split(const std::string& str, char delimiter1);
};
