#include "Recommendation.h"
#include <iostream>
using namespace std;
Recommendation::Recommendation(string file) {
    ifstream dataset;
    string line;
    dataset.open(file);
    // title,year,certificate,duration,genre,rating,description,stars,votes
    
    int count = 0;
    while (count < 1 && dataset.good()) {
        
        getline(dataset, line);
        getline(dataset, line);
        std::vector<std::string> mp_string = Split(line, ',');
        for (size_t i = 0; i < mp_string.size(); i++) {
            cout << i << ": " << mp_string.at(i) << endl;
        }
        count++;
    }
}


std::vector<std::string> Recommendation::Split(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }

  if (last != str.size()) {
    std::string subs = str.substr(last, str.length() - last);
    substrs.push_back(subs);
  }
  // size_t last = 0;
  // std::vector<std::string> substrs;
  // char quote = '"';
  // size_t end = 0;
  // for (size_t i = 0; i != str.length(); ++i) {
  //   if (str.at(i) == delimiter) {
  //     if (i + 1 < str.length() && str.at(i + 1) == quote) {

  //     } else {
  //       std::string substr = str.substr(last, i - last);
  //       last = i + 1;
  //       substrs.push_back(substr);
  //       end = str.length() - last;
  //     }
  //   }
  // }

  // if (last != str.size()) {
  //   std::string substr = str.substr(last, end);
  //   substrs.push_back(substr);
  // }
  return substrs;
}