#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "MotionPicture.h"
#include "Recommendation.h"

int main() {
    vector<string> genre;
    genre.push_back("Action");
    string description = "Cat takes dog on a walk";
    vector<string> cast;
    cast.push_back("Danny DeVito");

    MotionPicture mp1("Test", true, 2022, 2023, "PG", 60, genre, 10, description, cast, 10000);

    // cout << mp1.getTitle() << endl;


    string file = "data/n_movies.csv";
    Recommendation rec(file);

    std::cout << rec.DijkstraAlgo("Better Call Saul", 5) << std::endl;;
    return 0;
}
