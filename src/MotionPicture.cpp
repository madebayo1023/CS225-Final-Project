#include "MotionPicture.h"

/*
* Default constructor
*/
MotionPicture::MotionPicture() {}

/**
* Constructor that creates a MotionPicture object 
*
* @param title of The MotionPicture object
* @param is_movie of The MotionPicture object
* @param start_year of The MotionPicture object
* @param end_year of The MotionPicture object
* @param certificate of The MotionPicture object
* @param duration of The MotionPicture object
* @param genre of The MotionPicture object
* @param rating of The MotionPicture object
* @param description of The MotionPicture object
* @param cast of The MotionPicture object
* @param votes of The MotionPicture object
*/
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

/**
* Overloaded less than operator 
*
* @return boolean value if this is less than righthand object
*/
bool MotionPicture::operator<(const MotionPicture& rhs) const {
    (void) rhs;
    return true; // we are not concerned with maintaining an ordered map
}

/**
* Returns the motion picture title 
*
* @return title of The MotionPicture object
*/
std::string& MotionPicture::getTitle() { return title; }

/**
        * Returns true if MotionPicture is a movie, false otherwise
        *
        * @return whether The MotionPicture object is a movie
        */
bool& MotionPicture::getIsMovie() { return is_movie; }

/**
* Returns the motion picture start year 
*
* @return start year of The MotionPicture object
*/
int& MotionPicture::getStartYear() { return start_year; }

/**
* Returns the motion picture end year if it exists, otherwise it returns -1 
*
* @return end year of The MotionPicture object
*/
int& MotionPicture::getEndYear() { return end_year; }

/**
* Returns the motion picture certificate rating 
*
* @return certificate rating  of The MotionPicture object
*/
string& MotionPicture::getCertificate() {return certificate; }

/**
* Returns the motion picture duration
*
* @return duration  of The MotionPicture object
*/
int& MotionPicture::getDuration() { return duration; }

/**
* Returns the motion picture genre 
*
* @return genre of The MotionPicture object
*/
vector<string>& MotionPicture::getGenre() { return genre; }

/**
* Returns the motion picture rating 
*
* @return rating  of The MotionPicture object
*/
double& MotionPicture::getRating() { return rating; }

/**
* Returns the motion picture description 
*
* @return description of The MotionPicture object
*/
string& MotionPicture::getDescription() { return description; }

/**
* Returns the motion picture cast 
*
* @return cast of The MotionPicture object
*/
vector<string>& MotionPicture::getCast() { return cast; }

/**
* Returns the motion picture votes
*
* @return votes of The MotionPicture object
*/
int& MotionPicture::getVotes() { return votes; }