#pragma once
#include <string>

struct  Song {
    int index = 0;
    std::string trackID;
    std::string artistName;
    std::string albumName;
    std::string trackName ;
    double popularity=0.0;
    int duration_ms = 0;
    bool explicitSong = false;
    double danceability = 0.0;
    double energy= 0.0;
    int key= 0;
    double loudness= 0.0;
    int mode= 0;
    double speechiness= 0.0;
    double acousticness= 0.0;
    double instrumentalness= 0.0;
    double liveness= 0.0;
    double valence= 0.0;
    double tempo= 0.0;
    int time_signature= 0;
    std::string track_genre;
    double recommendedScore= 0.0;
};

