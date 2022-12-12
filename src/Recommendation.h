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
        * Constructs Recommendation class
        * * @param file dataset of Netflix MotionPictures
        */
        Recommendation(string file);

        /**
        * Destructor, Deallocates all dynamic memory
        */
        ~Recommendation();

        /**
        * Copy constructor for Recommendation class
        * @param rhs object to be copied
        */
        Recommendation(const Recommendation &rhs) = default;

        /**
        * Operator equals assignment for Recommendation class
        * @param rhs object to be copied
        */
        Recommendation& operator=(const Recommendation &rhs) = default;

        /**
        * Traverses adjacency matrix of Netflix MotionPictures
        * @param MovieName title of MotionPicture object
        * @param recommendations number of MotionPictures recommendations the user would like
        * @return string of MotionPictures most similar to the one inputted by the user
        */
        std::string DijkstraAlgo(std::string MovieName, unsigned recommendations);

        /**
        * Traverses adjacency matrix of Netflix MotionPictures
        * @param MovieName title of MotionPicture object
        * @param recommendations number of MotionPictures recommendations the user would like
        * @return string of MotionPictures most similar to the one inputted by the user
        */
        std::string BFS(std::string MovieName, unsigned recommendations);

        /**
        * Traverses adjacency matrix of Netflix MotionPictures
        * @param lookingFor title of target MotionPicture object
        * @return int representing
        */
        int betweennessCentrality(int lookingFor);

        /**
        * Returns the edge weight between two MotionPictures
        * @param idx1 index of the first MotionPicture
        * * @param idx2 index of the second MotionPicture
        * @return value of the edge between the two MotionPicture objects
        */
        double getSimilarity(int idx1, int idx2);

        /**
        * Returns the number of MotionPictures in dataset
        * @return number of MotionPicture objects
        */
        int getSize();
    private:
        map<MotionPicture*, int> mp_to_idx;
        map<int, MotionPicture*> idx_to_mp;
        vector<vector<double>> adjacency_matrix;
        int size_;
        /**
        * Reverses a string 
        * @param str the string to reverse
        */
        void reverse(string& str);

        /**
        * Parses the dataset through delimiting by a character
        * @param str string to parse
        * * @param delimiter1 char to delimit by
        * @return vector of each individual element for the MotionPicture object
        */
        std::vector<std::string> Split(const std::string& str, char delimiter1);

        /**
        * Parses genres
        * * @param str string of genres
        * @return vector of genres
        */
        std::vector<std::string> parseGenres(const std::string& str);

        /**
        * Parses years
        * * @param s string representing the years
        * @return vector of start and end years
        */
        std::vector<std::string> parseYears(const std::string& s);

        /**
        * Parses cast
        * * @param s string of cast members
        * @return vector of cast members
        */
        std::vector<std::string> parseCast(const std::string& s);

        /**
        * Overloaded subscript operator
        * * @param i index in idx_to_mp map
        * @return corresponding MotionPicture pointer object at that index
        */
        MotionPicture* operator[](int i);

        /**
        * Overloaded subscript operator
        * * @param mp MotionPicture in mp_to_idx map
        * @return corresponding index at that MotionPicture pointer object value
        */
        int& operator[](MotionPicture mp);

        /**
        * Deallocates all dynamic memory
        */
        void clear();

        /**
        * Assigns weight to each edge in adjacency matrix, which represents the similarity between two MotionPicture objects
        */
        void setSimilarity();
};
