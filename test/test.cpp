#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include "../src/MotionPicture.h"
#include "../src/Recommendation.h"

TEST_CASE("MotionPicture Class Works", "[case-1]") {
    vector<string> genre = {"Action"};
    string description = "Cat takes dog on a walk";
    vector<string> cast = {"Danny DeVito"};

    MotionPicture mp1("Test", true, 2022, 2023, "PG", 60, genre, 10, description, cast, 10000);

    REQUIRE(mp1.getTitle() == "Test");
    REQUIRE(mp1.getIsMovie() == true);
    REQUIRE(mp1.getStartYear() == 2022);
    REQUIRE(mp1.getEndYear() == 2023);
    REQUIRE(mp1.getCertificate() == "PG");
    REQUIRE(mp1.getDuration() == 60);
    REQUIRE(mp1.getGenre() == genre);
    REQUIRE(mp1.getRating() == 10);
    REQUIRE(mp1.getDescription() == description);
    REQUIRE(mp1.getCast() == cast);
    REQUIRE(mp1.getVotes() == 10000);
}
TEST_CASE("Recommendation Constructor Works", "[case-2]") {
    string file = "test/test.csv";
    Recommendation rec(file);
}