
#pragma once
#include "Song.h"
#include <string>

//recommendation system class 
class RecommendationSystem {

public:
    static double parameterRecommendationScore(const Song& song, const std::string& genre, const std::string& mood , double danceability, bool explicitSong);
    static double similarityRecommendationScore(const Song& song, const Song& likedSong, bool explicitSong);
    static double hybridRecommendationScore(const Song& song, const Song& likedSong, const std::string& genre, const std::string& mood , double danceability, bool explicitSong);
};
