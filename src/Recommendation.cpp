#include "Recommendation.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;
/**
* Constructs Recommendation class
* * @param file dataset of Netflix MotionPictures
*/
Recommendation::Recommendation(string file) {
  ifstream dataset;
  string line;
  dataset.open(file);
  int count = 0;
  // title,year,certificate,duration,genre,rating,description,stars,votes
  getline(dataset, line);
  while (dataset.good())
  {
    getline(dataset, line);
    std::vector<std::string> mp_string = Split(line, ',');
    std::vector<std::string> mp_years = parseYears(mp_string.at(1));
    bool is_movie = true;
    if (mp_years.size() == 2)
      is_movie = false;
    std::vector<std::string> mp_genre = parseGenres(mp_string.at(4));
    std::vector<std::string> mp_cast = parseCast(mp_string.at(7));

    if (!is_movie)
    {
      MotionPicture *mp = new MotionPicture(mp_string.at(0), is_movie, stoi(mp_years[0]), stoi(mp_years[1]), mp_string.at(2), stoi(mp_string[3]), mp_genre, stod(mp_string.at(5)), mp_string.at(6), mp_genre, stoi(mp_string[8]));
      mp_to_idx[mp] = count;
      idx_to_mp[count] = mp;
    }
    else
    {
      MotionPicture *mp = new MotionPicture(mp_string.at(0), is_movie, stoi(mp_years[0]), -1, mp_string.at(2), stoi(mp_string[3]), mp_genre, stod(mp_string.at(5)), mp_string.at(6), mp_genre, stoi(mp_string[8]));
      mp_to_idx[mp] = count;
      idx_to_mp[count] = mp;
    }
    count++;
  }
  size_ = count;
  for (int i = 0; i < size_; i++)
  {
    vector<double> inner(size_, 0);
    adjacency_matrix.push_back(inner);
  }
  // std::cout << mp_to_idx.size() << " " << idx_to_mp.size() << std::endl;
  setSimilarity();

  // ofstream MyFile("data/adj.txt");
  // for (int i = 0; i < size_; i++) {
  //   for (int j = 0; j < size_; j++) {
  //     MyFile << adjacency_matrix[i][j] << " ";
  //   }
  //   MyFile << "\n";
  // }
}

/**
* Parses the dataset through delimiting by a character
* @param str string to parse
* * @param delimiter1 char to delimit by
* @return vector of each individual element for the MotionPicture object
*/
std::vector<std::string> Recommendation::Split(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  int pos = 0;
  int start = 0;
  if (str.at(0) == '"')
  {
    int idx = str.substr(1, substrs.size() - 1).find('"');
    substrs.push_back(str.substr(1, idx));
    start = idx + 3;
    last = idx + 3;
  }
  for (size_t i = start; i != str.length(); ++i)
  {
    if (str.at(i) == delimiter)
    {
      if (i - 1 >= 0 && str.at(i - 1) == '"')
      {
        pos++;
        if (pos % 2 == 0)
        {
          std::string substr = "";
          size_t idx = i - 2;
          while (str.at(idx) != '"')
          {
            substr += str.at(idx);
            idx--;
          }
          reverse(substr);
          if (!substr.empty())
            substrs.push_back(substr);
          last = i;
        }
      }
      if (i + 1 < str.length() && str.at(i + 1) == '"')
      {
        pos++;

        if (pos % 2 != 0)
        {
          std::string substr = str.substr(last, i - last);
          last = i + 1;
          if (!substr.empty())
            substrs.push_back(substr);
        }
      }
      else
      {
        if (pos % 2 == 0)
        {
          std::string substr = str.substr(last, i - last);
          last = i + 1;
          if (!substr.empty())
            substrs.push_back(substr);
        }
      }
    }
  }
  if (last != str.size())
  {
    std::string subs = str.substr(last, str.length() - last - 1);
    if (!subs.empty())
      substrs.push_back(subs);
  }
  return substrs;
}

/**
* Reverses a string 
* @param str the string to reverse
*/
void Recommendation::reverse(string& str) {
  int len = str.length();
  int n = len - 1;
  int i = 0;
  while (i <= n)
  {
    swap(str[i], str[n]);
    n = n - 1;
    i = i + 1;
  }
}

/**
* Parses genres
* * @param str string of genres
* @return vector of genres
*/
std::vector<std::string> Recommendation::parseGenres(const std::string& str) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i)
  {
    if (str.at(i) == ',')
    {
      std::string substr = str.substr(last, i - last);
      last = i + 2;
      substrs.push_back(substr);
    }
  }
  if (last != str.size())
  {
    std::string subs = str.substr(last, str.length() - last);
    if (!subs.empty())
      substrs.push_back(subs);
  }
  return substrs;
}

/**
* Parses cast
* * @param s string of cast members
* @return vector of cast members
*/
std::vector<std::string> Recommendation::parseCast(const std::string& s) {
  size_t last = 0;
  std::vector<std::string> substrs;
  string str = s.substr(1, s.length() - 2);
  for (size_t i = 0; i != str.length(); ++i)
  {
    if (str.at(i) == ',')
    {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      if (!substr.empty())
        substrs.push_back(substr);
    }
  }
  if (last != str.size())
  {
    std::string subs = str.substr(last, str.length() - last);
    if (!subs.empty())
      substrs.push_back(subs);
  }
  return substrs;
}

/**
* Parses years
* * @param s string representing the years
* @return vector of start and end years
*/
std::vector<std::string> Recommendation::parseYears(const std::string& s) {
  std::vector<std::string> substrs;
  string year1 = s.substr(0, 4);
  substrs.push_back(year1);
  if (s.size() > 4)
  {
    string year2 = s.substr(5, 4);
    substrs.push_back(year2);
  }
  return substrs;
}

/**
* Overloaded subscript operator
* * @param i index in idx_to_mp map
* @return corresponding MotionPicture pointer object at that index
*/
MotionPicture* Recommendation::operator[](int i) {
  return idx_to_mp[i];
}

/**
* Overloaded subscript operator
* * @param mp MotionPicture in mp_to_idx map
* @return corresponding index at that MotionPicture pointer object value
*/
int& Recommendation::operator[](MotionPicture mp) {
  return mp_to_idx[&mp];
}

/**
* Traverses adjacency matrix of Netflix MotionPictures
* @param MovieName title of MotionPicture object
* @param recommendations number of MotionPictures recommendations the user would like
* @return string of MotionPictures most similar to the one inputted by the user
*/
std::string Recommendation::DijkstraAlgo(std::string MovieName, unsigned recommendations) {
  int index = -1;
  if (int(recommendations) < 1)
  {
    return "Please Enter a Higher Number of Recommendations\n";
  }
  std::string ret = "Movie Recommendations\n";
  for (auto i : idx_to_mp)
  {
    if (i.second->getTitle() == MovieName)
    {
      index = i.first;
    }
  }
  if (index == -1)
  {
    return "Movie Not Found\n";
  }
  auto copymatrix = adjacency_matrix;
  double highestval = -1;
  int highestindex = -1;
  for (unsigned g = 0; g < adjacency_matrix[index].size(); g++)
  {
    if (adjacency_matrix[index][g] > highestval)
    {
      highestval = adjacency_matrix[index][g];
      highestindex = g;
      copymatrix[index][g] = -1;
    }
  }
  if (highestindex > -1)
  {
    ret = ret + idx_to_mp[highestindex]->getTitle() + ": " + std::to_string(highestval) + "\n";
  }
  if (recommendations == 1)
  {
    return ret;
  }
  for (unsigned k = 0; k < recommendations - 1; k++)
  {
    if (k < mp_to_idx.size() - 1)
    {
      highestval = -1;
      highestindex = -1;
      for (unsigned l = 0; l < copymatrix[index].size(); l++)
      {
        if (copymatrix[index][l] > highestval)
        {
          highestval = copymatrix[index][l];
          highestindex = l;
        }
      }

      if (highestindex > -1) {
        copymatrix[index][highestindex] = -1;
        ret = ret + idx_to_mp[highestindex]->getTitle() + ": " + std::to_string(highestval) + "\n";
      }
    }
  }
  return ret;
}

/**
* Traverses adjacency matrix of Netflix MotionPictures
* @param MovieName title of MotionPicture object
* @param recommendations number of MotionPictures recommendations the user would like
* @return string of MotionPictures most similar to the one inputted by the user
*/
std::string Recommendation::BFS(std::string MovieName, unsigned recommendations) {
  std::queue<std::pair<int, double>> queue;
  int index = -1;
  if (int(recommendations) < 1) {
    return "Please Enter a Higher Number of Recommendations\n";
  }
  std::string ret = "Movie Recommendations\n";
  for (auto i : idx_to_mp) {
    if (i.second->getTitle() == MovieName) {
      index = i.first;
    }
  }
  if (index == -1) {
    return "Movie Not Found\n";
  }
  auto copymatrix = adjacency_matrix;
  for (auto i : idx_to_mp) {
    if (i.second->getTitle() == MovieName) {
      index = i.first;
    }
  }

  for (unsigned k = 0; k < recommendations; k++) {
    if (k < mp_to_idx.size() - 1) {
      for (unsigned r = 0; r < copymatrix[index].size(); r++) {
        queue.push({r, copymatrix[index][r]});
      }
      std::pair<int, double> highest = {-1, -1};
      while(!queue.empty()) {
        std::pair<int, double> temp = queue.front();
        queue.pop();
        if (temp.second > highest.second) {
          highest = temp;
        }
      }
      if (highest.first > -1) {
        copymatrix[index][highest.first] = -1;
      }
      if (highest.second > -1) {
        ret = ret + idx_to_mp[highest.first]->getTitle() + ": " + std::to_string(highest.second) + "\n";
      }
    }
  }
  return ret;
}

/**
* Assigns weight to each edge in adjacency matrix, which represents the similarity between two MotionPicture objects
*/
void Recommendation::setSimilarity() {
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      if (i == j) {
        adjacency_matrix[i][j] = -1;
        break;
      }
      if (i >= j)
      {
        int sim = 0;
        if (idx_to_mp[i]->getCertificate() == idx_to_mp[j]->getCertificate())
        {
          adjacency_matrix[i][j] += 10;
          adjacency_matrix[j][i] += 10;
          sim++;
        }
        if (abs(idx_to_mp[i]->getStartYear() - idx_to_mp[j]->getStartYear()) <= 5)
        {
          adjacency_matrix[i][j] += 5;
          adjacency_matrix[j][i] += 5;
          sim++;
        }
        if (abs(idx_to_mp[i]->getEndYear() - idx_to_mp[j]->getEndYear()) <= 3)
        {
          adjacency_matrix[i][j] += 3;
          adjacency_matrix[j][i] += 3;
          sim++;
        }
        if (idx_to_mp[i]->getIsMovie() == idx_to_mp[j]->getIsMovie())
        {
          adjacency_matrix[i][j] += 8;
          adjacency_matrix[j][i] += 8;
          sim++;
        }
        if (abs(idx_to_mp[i]->getVotes() - idx_to_mp[j]->getVotes()) <= 1000)
        {
          adjacency_matrix[i][j] += 13;
          adjacency_matrix[j][i] += 13;
          sim++;
        }
        else if (abs(idx_to_mp[i]->getVotes() - idx_to_mp[j]->getVotes()) <= 25000)
        {
          adjacency_matrix[i][j] += 9;
          adjacency_matrix[j][i] += 9;
          sim++;
        }
        else if (abs(idx_to_mp[i]->getVotes() - idx_to_mp[j]->getVotes()) <= 50000)
        {
          adjacency_matrix[i][j] += 3;
          adjacency_matrix[j][i] += 3;
          sim++;
        }
        if (sim >= 5 && abs(idx_to_mp[i]->getRating() - idx_to_mp[j]->getRating()) <= 1)
        {
          adjacency_matrix[i][j] += 17;
          adjacency_matrix[j][i] += 17;
          sim++;
        }
        else if (sim >= 5 && abs(idx_to_mp[i]->getRating() - idx_to_mp[j]->getRating()) <= 1.25)
        {
          adjacency_matrix[i][j] += 12;
          adjacency_matrix[j][i] += 12;
          sim++;
        }
        else if (sim >= 5 && abs(idx_to_mp[i]->getRating() - idx_to_mp[j]->getRating()) <= 2)
        {
          adjacency_matrix[i][j] += 5;
          adjacency_matrix[j][i] += 5;
          sim++;
        }
        if (sim >= 5 && abs(idx_to_mp[i]->getDuration() - idx_to_mp[j]->getDuration()) <= 25)
        {
          adjacency_matrix[i][j] += 6;
          adjacency_matrix[j][i] += 6;
          sim++;
        }
        if (sim >= 7)
        {
          auto &genre1 = idx_to_mp[i]->getGenre();
          auto &genre2 = idx_to_mp[j]->getGenre();
          for (size_t k = 0; k < genre1.size(); k++)
          {
            for (size_t l = 0; l < genre2.size(); l++)
            {
              if (k >= l && genre1[k] == genre2[l])
              {
                adjacency_matrix[i][j] += 25;
                adjacency_matrix[j][i] += 25;
              }
            }
          }
          auto &actors1 = idx_to_mp[i]->getCast();
          auto &actors2 = idx_to_mp[j]->getCast();
          bool similarC = false;
          for (size_t k = 0; k < actors1.size(); k++)
          {
            for (size_t l = 0; l < actors2.size(); l++)
            {
              if (actors1[k] == actors2[l])
              {
                adjacency_matrix[i][j] += 30;
                adjacency_matrix[j][i] += 30;
                similarC = true;
                break;
              }
            }
            if (similarC)
              break;
          }
        }
      }
    }
  }
}

/**
* Deallocates all dynamic memory
*/
void Recommendation::clear() {
  for (auto& p1 : idx_to_mp) {
    delete p1.second;
  }
}

/**
* Destructor, Deallocates all dynamic memory
*/
Recommendation::~Recommendation() {
  clear();
}

// finds the betweenness centrality for a certain node/movie
int Recommendation::betweennessCentrality(MotionPicture *lookingFor)
{
  // find the total number of shortest paths between two movies
  // find the total number of shortest paths between two movies that include one other movie in the path
  // divide this by the previous value and summation for all connected components in our graph
  // list out all the paths you can form by going through all the movies
  // compare two movies and ensure they are both neighbors
  // if they are (which they should be since everything is connected) then see if its list of existing neighbors contains lookingFor (which is the node that you would hope to be on your path )
  // it is guranteed that every node is connected to every other node in the graph (can assume a dividend of 1 for each movie you go through)
  vector<double> betweenness_central_scores;
  for (size_t i = 0; i < adjacency_matrix.size(); i++)
  {
    for (size_t j = 0; j < adjacency_matrix[i].size(); j++)
    {
      // get the two current movies on which we are operating
      MotionPicture *movie1 = idx_to_mp(i);
      MotionPicture *movie2 = idx_to_mp(j);
      // get the list of neighbors for those two movies
      vector<double> neighbors1 = adjacency_matrix[i];
      vector<double> neighbors2 = adjacency_matrix[j];
      // check if both neighbors' lists include the movie we are looking for
      // in order to do this we need to check if the score for that movie is in the neighbors list for both movie1 and movie2
      int lookingFor_idx = mp_to_idx[lookingFor];
      double lookingFor_score = adjacency_matrix(adjacency_matrix[i].size() * i + lookingFor_idx);
      if (std::find(lookingFor_score, neighbors1.begin(), neighbors1.end()) && std::find(lookingFor_score, neighbors2.begin(), neighbors2.end()))
      {
        double score = 1 / 1;
        betweenness_central_scores.push_back(score);
      }
      else
      {
        double score = 0;
        betweenness_central_scores.push_back(score);
      }
    }
    int bt_score = 0;
    for (double &score : betweenness_central_scores)
    {
      if (score == 1)
      {
        bt_score++;
      }
    }
    return bt_score;
  }
}
