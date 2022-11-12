#include "MotionPicture.h"


MotionPicture::MotionPicture(string title, bool is_movie, int start_year, int end_year, string certificate, int duration, vector<string> genre,
                        double rating, string description, vector<string> cast, int votes) {
                    this->title = title;
                    this->is_movie = is_movie;
                    this->start_year = start_year;
                    this->end_year = end_year;
                    this->certificate = certificate;
                    this->duration = duration;
                    this->genre = genre;
                    this->rating = rating;
                    this->description = description;
                    this->cast = cast;
                    this->votes = votes;
                 }
std::string& MotionPicture::getTitle() { return title; }
bool& MotionPicture::getIsMovie() { return is_movie; }
int& MotionPicture::getStartYear() { return start_year; }
int& MotionPicture::getEndYear() { return end_year; }
string& MotionPicture::getCertificate() {return certificate; }
int& MotionPicture::getDuration() { return duration; }
vector<string>& MotionPicture::getGenre() { return genre; }
double& MotionPicture::getRating() { return rating; }
string& MotionPicture::getDescription() { return description; }
vector<string>& MotionPicture::getCast() { return cast; }
int& MotionPicture::getVotes() { return votes; }