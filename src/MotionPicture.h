#pragma once 

#include <string>
#include <vector>

using namespace std;

class MotionPicture {
    public:
        /*
        * Default constructor
        */
        MotionPicture();
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
        MotionPicture(string title, bool is_movie, int start_year, int end_year, string certificate, int duration, vector<string> genre,
                        double rating, string description, vector<string> cast, int votes);
        /**
        * Returns the motion picture title 
        *
        * @return title of The MotionPicture object
        */
        std::string& getTitle();
        /**
        * Overloaded less than operator 
        *
        * @return boolean value if this is less than righthand object
        */
        bool operator<(const MotionPicture& rhs) const;
        /**
        * Returns true if MotionPicture is a movie, false otherwise
        *
        * @return whether The MotionPicture object is a movie
        */
        bool& getIsMovie();
        /**
        * Returns the motion picture start year 
        *
        * @return start year of The MotionPicture object
        */
        int& getStartYear();
        /**
        * Returns the motion picture end year if it exists, otherwise it returns -1 
        *
        * @return end year of The MotionPicture object
        */
        int& getEndYear();
        /**
        * Returns the motion picture certificate rating 
        *
        * @return certificate rating  of The MotionPicture object
        */
        string& getCertificate();
        /**
        * Returns the motion picture duration
        *
        * @return duration  of The MotionPicture object
        */
        int& getDuration();
        /**
        * Returns the motion picture genre 
        *
        * @return genre of The MotionPicture object
        */
        vector<string>& getGenre();
        /**
        * Returns the motion picture rating 
        *
        * @return rating  of The MotionPicture object
        */
        double& getRating();
        /**
        * Returns the motion picture description 
        *
        * @return description of The MotionPicture object
        */
        string& getDescription();
        /**
        * Returns the motion picture cast 
        *
        * @return cast of The MotionPicture object
        */
        vector<string>& getCast();
        /**
        * Returns the motion picture votes
        *
        * @return votes of The MotionPicture object
        */
        int& getVotes();
    private:
        std::string title;
        bool is_movie;
        int start_year;
        int end_year;
        string certificate;
        int duration;
        vector<string> genre;
        double rating;
        string description;
        vector<string> cast;
        int votes;
};