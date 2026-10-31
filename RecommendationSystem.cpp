#include "RecommendationSystem.h"
#include <cmath>

using namespace std;

double RecommendationSystem::parameterRecommendationScore(const Song &song, const std::string &genre,
    const std::string &mood, double danceability, bool explicitSong) {

    if (!explicitSong && song.explicitSong) {
        return -1.0;
    }

    double genreScore = 1.0;
    double danceabilityScore = 1.0;
    double moodScore = 1.0;
    double popularityScore = song.popularity/100.00;
    double recommendedScore=0.0;

    if (genre != "Any" && !genre.empty()) {
        if (genre == song.track_genre) {
            genreScore = 1.0;
        }else {
            genreScore = 0;
        }
    }

    if (danceability>=0.0) {
        danceabilityScore = 1.0- abs(song.danceability-danceability);
    }
    if (danceabilityScore<0.0) {
        danceabilityScore = 0.0;
    }

    if (mood != "Any" && !mood.empty()) {
        if (mood == "Happy") {
            moodScore = (song.energy + song.valence)/2.0;
        }else if (mood == "Sad") {
            moodScore = ((1.0-song.energy)+(1.0- song.valence))/2.0;
        }else if (mood == "Chill") {
            moodScore = 1.0-song.energy;
        }else if (mood=="Energetic") {
            moodScore = song.energy;
        }
    }

    recommendedScore= (0.35*genreScore)+(0.15*danceabilityScore)+(0.35*moodScore)+(0.15*popularityScore);
    return recommendedScore;

}



double RecommendationSystem::similarityRecommendationScore(const Song &song, const Song &likedSong, bool explicitSong) {
    if (!explicitSong && song.explicitSong) {
        return -1.0;
    }

    double danceabilityScore = 1.0-abs(likedSong.danceability-song.danceability);
    double energyScore= 1.0-abs(likedSong.energy-song.energy);
    double valenceScore= 1.0-abs(likedSong.valence-song.valence);
    double acousticnessScore= 1.0-abs(likedSong.acousticness-song.acousticness);
    double instrumentalnessScore= 1.0-abs(likedSong.instrumentalness-song.instrumentalness);
    double speechinessScore= 1.0-abs(likedSong.speechiness-song.speechiness);
    double livenessScore= 1.0-abs(likedSong.liveness-song.liveness);
    double tempoScore= 1.0-(abs(likedSong.tempo-song.tempo)/250.00);
    if (tempoScore<0.0) {
        tempoScore = 0.0;
    }
    double loudnessScore= 1.0-(abs(likedSong.loudness-song.loudness)/60.00);
    if (loudnessScore<0.0) {
        loudnessScore = 0.0;
    }
    double keyScore=0.0;
    if (likedSong.key==song.key) {
        keyScore=1.0;
    }

    double modeScore= 0.0;
    if (likedSong.mode==song.mode) {
        modeScore=1.0;
    }

    double timeSignatureScore= 0.0;
    if (likedSong.time_signature==song.time_signature) {
        timeSignatureScore=1.0;
    }


    double recommendedScore=(0.10*danceabilityScore)+(0.10*energyScore)+(0.10*valenceScore)+(0.10*acousticnessScore)+(0.10*instrumentalnessScore)+(0.10*speechinessScore)+(0.10*livenessScore)+(0.05*tempoScore)
    +(0.05*loudnessScore)+(0.10*keyScore)+(0.05*modeScore)+(0.05*timeSignatureScore);


    if (song.track_genre != likedSong.track_genre) {
        recommendedScore *=0.90;
    }
    return recommendedScore;
}

double RecommendationSystem::hybridRecommendationScore(const Song &song, const Song &likedSong,
    const std::string &genre, const std::string &mood, double danceability, bool explicitSong) {
    double paramScore = parameterRecommendationScore(song,genre,mood,danceability,explicitSong);
    double simScore = similarityRecommendationScore(song,likedSong,explicitSong);
    if (paramScore<0.0||simScore<0.0) {
        return -1.0;
    }
    double recommendedScore = (0.5*paramScore)+(0.5*simScore);
    return recommendedScore;
}
