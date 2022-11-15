#pragma once

#include <map>
#include <fstream>
#include <vector>
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
    private:
        map<MotionPicture, int> mp_to_idx;
        map<int, MotionPicture> idx_to_mp;
        vector<vector<int>> adjacency_matrix;
        // have a vector of movie objects?
        /**
        * Parses the dataset 
        *
        * @return a vector or each individual element for the MotionPicture object
        */
        void reverse(string& str);
        std::vector<std::string> Split(const std::string& str, char delimiter1);
        std::vector<std::string> parseGenres(const std::string& str);
        std::vector<std::string> parseYears(const std::string& s);
        std::vector<std::string> parseCast(const std::string& s);
        MotionPicture operator[](int i);
        int operator[](MotionPicture mp);
};
