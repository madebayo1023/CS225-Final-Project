#include "Recommendation.h"
#include <iostream>

using namespace std;
Recommendation::Recommendation(string file) {
  ifstream dataset;
  string line;
  dataset.open(file);
  int count = 0;
  getline(dataset, line);
  while (dataset.good()) {
    getline(dataset, line);
    std::vector<std::string> mp_string = Split(line, ',');
    std::vector<std::string> mp_years = parseYears(mp_string.at(1));
    bool is_movie = false;
    if (mp_years.size() == 2) is_movie = true;
    std::vector<std::string> mp_genre = parseGenres(mp_string.at(4));
    std::vector<std::string> mp_cast = parseCast(mp_string.at(7));
    int duration = parseDuration(mp_string[3]);
    int votes = parseVotes(mp_string[8]);
    
    if (is_movie) {
      MotionPicture mp(mp_string.at(0), is_movie, stoi(mp_years[0]), stoi(mp_years[1]), mp_string.at(2), duration, mp_genre, stod(mp_string.at(5)), mp_string.at(6), mp_genre, votes);
      // mp_to_idx[mp] = count;
      // idx_to_mp[count] = mp;
    } else {
      MotionPicture mp(mp_string.at(0), is_movie, stoi(mp_years[0]), -1, mp_string.at(2), duration, mp_genre, stod(mp_string.at(5)), mp_string.at(6), mp_genre, votes);
      // mp_to_idx[mp] = count;
      // idx_to_mp.insert({count, mp});
    }
    count++;
  }
  cout << mp_to_idx.size() << endl;
  cout << idx_to_mp.size() << endl;
}

std::vector<std::string> Recommendation::Split(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  int pos = 0;

  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      if (i - 1 >= 0 && str.at(i - 1) == '"') {
        pos++;
        
        if (pos % 2 == 0) {
        std::string substr = "";
        size_t idx = i - 2;
        while (str.at(idx) != '"') {
          substr += str.at(idx);
          idx--;
        }
        reverse(substr);
        if (!substr.empty()) substrs.push_back(substr);
        last = i;
        }
      } if (i + 1 < str.length() && str.at(i + 1) == '"') {
        pos++;
        
        if (pos % 2 != 0) {
          std::string substr = str.substr(last, i - last);
          last = i + 1;
          if (!substr.empty()) substrs.push_back(substr);
        }
      }
      else {
        if (pos % 2 == 0) {
          std::string substr = str.substr(last, i - last);
          last = i + 1;
          if (!substr.empty()) substrs.push_back(substr);
        }
      }
    }
  }
  if (last != str.size()) {
    std::string subs = str.substr(last + 1, str.length() - last - 2);
    if (!subs.empty()) substrs.push_back(subs);
  }
  return substrs;
}

void Recommendation::reverse(string& str) {
  int len = str.length();
    int n = len-1;
    int i = 0;
    while(i<=n){
      swap(str[i],str[n]);
      n = n-1;
      i = i+1;
  }
}

std::vector<std::string> Recommendation::parseGenres(const std::string& str) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == ',') {
      std::string substr = str.substr(last, i - last);
      last = i + 2;
      substrs.push_back(substr);
    }
  }
  if (last != str.size()) {
    std::string subs = str.substr(last, str.length() - last);
    if (!subs.empty()) substrs.push_back(subs);
  }
  return substrs;
}

std::vector<std::string> Recommendation::parseCast(const std::string& s) {
  size_t last = 0;
  std::vector<std::string> substrs;
  string str = s.substr(2, s.length() - 4);
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == ',') {
      std::string substr = str.substr(last, i - last);
      last = i + 3;
      if (!substr.empty()) substrs.push_back(substr);
    }
  }
  if (last != str.size()) {
    std::string subs = str.substr(last, str.length() - last);
    if (!subs.empty()) substrs.push_back(subs);
  }
  return substrs;
}

std::vector<std::string> Recommendation::parseYears(const std::string& s) {
  std::vector<std::string> substrs;
  string year1 = s.substr(1, 4);
  substrs.push_back(year1);
  if (s.at(8) != ' ') {
    string year2 = s.substr(8, 4);
    substrs.push_back(year2);
  }
  return substrs;
}

int Recommendation::parseDuration(const std::string& str) {
  string substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == ' ') {
      substrs = str.substr(0, i);
    }
  }
  return stoi(substrs);
}

int Recommendation::parseVotes(const std::string& str) {
  string substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) != ',') {
      substrs += str.at(i);
    }
  }
  return stoi(substrs);
}

// MotionPicture Recommendation::operator[](int i) {
//   return idx_to_mp[i];
// }

// int Recommendation::operator[](MotionPicture mp) {
//   return mp_to_idx[mp];
// }