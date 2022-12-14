#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <vector>
#include <stdexcept>
#include "../src/MotionPicture.h"
#include "../src/Recommendation.h"

TEST_CASE("MotionPicture Class Works", "[case-1]")
{
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
TEST_CASE("Recommendation Constructor Works", "[case-2]")
{
    string file = "test/test.csv";
    Recommendation rec(file);
    REQUIRE(rec.getSize() == 4);
    REQUIRE(rec.getSimilarity(2, 3) == 35); // Devil in Ohio & Cyberpunk: Edgerunner
    REQUIRE(rec.getSimilarity(0, 3) == 21); // The Crown & Cyberpunk: Edgerunner
    REQUIRE(rec.getSimilarity(0, 0) == -1); // The Crown & The Crown
}

TEST_CASE("Recommendation Dijkstra", "[case-3]")
{
    string file = "test/DijkstraTests.csv";
    Recommendation rec(file);
    REQUIRE(rec.DijkstraAlgo("Better Call Saul", 1) == "Movie Recommendations\nPeaky Blinders: 132.000000\n");
    REQUIRE(rec.DijkstraAlgo("Better Call Saul", 2) == "Movie Recommendations\nPeaky Blinders: 132.000000\nMoney Heist: 132.000000\n");
    REQUIRE(rec.DijkstraAlgo("Not a Movie", 1) == "Movie Not Found\n");
    REQUIRE(rec.DijkstraAlgo("Better Call Saul", -1) == "Please Enter a Higher Number of Recommendations\n");
    REQUIRE(rec.DijkstraAlgo("Better Call Saul", 3) == "Movie Recommendations\nPeaky Blinders: 132.000000\nMoney Heist: 132.000000\nBlack Mirror: Bandersnatch: 13.000000\n");
    REQUIRE(rec.DijkstraAlgo("Better Call Saul", 4) == "Movie Recommendations\nPeaky Blinders: 132.000000\nMoney Heist: 132.000000\nBlack Mirror: Bandersnatch: 13.000000\n");
}

TEST_CASE("Betweenness Centrality", "[case-4]")
{
    string file = "test/bt.csv";
    Recommendation rec(file);
    REQUIRE(rec.betweennessCentrality(2) == 7); // 2 = Peaky Blinders
    REQUIRE(rec.betweennessCentrality(5) == 7); // 5 = Black Mirror: Bandersnatch
    REQUIRE(rec.betweennessCentrality(8) == 9); // 8 = Glass Onion: A Knives Out Mystery
    REQUIRE(rec.betweennessCentrality(10) == 9); // 10 = Sons of the Caliphate
}

TEST_CASE("Recommendation BFS", "[case-5]") {
    string file = "test/BFSTests.csv";
    Recommendation rec(file);
    REQUIRE(rec.BFS("The Crown", 1) == "Movie Recommendations\nBetter Call Saul: 15.000000\n");
    REQUIRE(rec.BFS("The Crown", 2) == "Movie Recommendations\nBetter Call Saul: 15.000000\nPeaky Blinders: 15.000000\n");
    REQUIRE(rec.BFS("Not a Movie", 1) == "Movie Not Found\n");
    REQUIRE(rec.BFS("The Crown", -1) == "Please Enter a Higher Number of Recommendations\n");
    REQUIRE(rec.BFS("The Crown", 3) == "Movie Recommendations\nBetter Call Saul: 15.000000\nPeaky Blinders: 15.000000\nMoney Heist: 15.000000\n");
    REQUIRE(rec.BFS("The Crown", 4) == "Movie Recommendations\nBetter Call Saul: 15.000000\nPeaky Blinders: 15.000000\nMoney Heist: 15.000000\nBlack Mirror: Bandersnatch: 5.000000\n");
}
