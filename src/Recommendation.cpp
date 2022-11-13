#include "Recommendation.h"
#include <iostream>

using namespace std;
Recommendation::Recommendation(string file) {
    ifstream dataset;
    string line;
    dataset.open(file);
    // title,year,certificate,duration,genre,rating,description,stars,votes
    
    int count = 0;
    while (count < 2 && dataset.good()) {
        
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
  int pos = 0;
  int bracket = 0;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      if (i + 1 < str.length() && str.at(i + 1) == '"') pos++;
      if (i - 1 >= 0 && str.at(i - 1) == '"') {
        pos++;
        std::string substr = "";
        size_t idx = i - 2;
        while (str.at(idx) != '"') {
          substr += str.at(idx);
          idx--;
        }
        reverse(substr);
        substrs.push_back(substr);
        last = i + 1;
      } else {
        if (pos % 2 == 0) {
          std::string substr = str.substr(last, i - last);
          last = i + 1;
          substrs.push_back(substr);
        }
      }
    }
  }
  if (last != str.size()) {
    std::string subs = str.substr(last, str.length() - last);
    substrs.push_back(subs);
  }
  return substrs;
}

void Recommendation::reverse(string& str)
{
  int len = str.length();
    int n = len-1;
    int i = 0;
    while(i<=n){
        //Using the swap method to switch values at each index
        swap(str[i],str[n]);
        n = n-1;
        i = i+1;
  }
}