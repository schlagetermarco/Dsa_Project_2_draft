#include "DataSetReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

std::vector<std::string> DataSetReader::loadLine(const std::string &line){
    istringstream data(line);
    string value;
    vector<string> values;
    bool doubleQuote=false;
    char character;
    while (data.get(character)) {
        if (character=='"') {
            doubleQuote=!doubleQuote;
        }else if (character==','&& !doubleQuote) {
            values.push_back(value);
            value.clear();
        }else {
            value+=character;
        }
    }
    values.push_back(value);
    return values;
}

void DataSetReader::parseLine(const std::vector<std::string> &data,vector<Song> &songs) {
    Song song;
    for (int i=0; i<data.size(); i++) {
        if (i==0) {
            song.index = stoi(data[i]);
            continue;
        }
        if (i==1) {
            song.trackID = data[i];
            continue;
        }
        if (i==2) {
            song.artistName = data[i];
            continue;
        }
        if (i==3) {
            song.albumName = data[i];
            continue;
        }
        if (i==4) {
            song.trackName = data[i];
            continue;
        }
        if (i==5) {
            song.popularity = stod(data[i]);
            continue;
        }
        if (i==6) {
            song.duration_ms = stoi(data[i]);
            continue;
        }
        if (i==7) {
            if (data[i]=="True")
                song.explicitSong=true;
            else
                song.explicitSong=false;
            continue;
        }
        if (i==8) {
            song.danceability = stod(data[i]);
            continue;
        }
        if (i==9) {
            song.energy = stod(data[i]);
            continue;
        }
        if (i==10) {
            song.key = stoi(data[i]);
            continue;
        }
        if (i==11) {
            song.loudness = stod(data[i]);
            continue;
        }
        if (i==12) {
            song.mode=stoi(data[i]);
            continue;
        }
        if (i==13) {
            song.speechiness = stod(data[i]);
            continue;
        }
        if (i==14) {
            song.acousticness = stod(data[i]);
            continue;
        }
        if (i==15) {
            song.instrumentalness = stod(data[i]);
            continue;
        }
        if (i==16) {
            song.liveness = stod(data[i]);
            continue;
        }
        if (i==17) {
            song.valence = stod(data[i]);
            continue;
        }
        if (i==18) {
            song.tempo = stod(data[i]);
            continue;
        }
        if (i==19) {
            song.time_signature= stoi(data[i]);
            continue;
        }
        if (i==20) {
            song.track_genre = data[i];
        }
    }
    songs.push_back(song);
}

std::vector<Song> DataSetReader::loadSongs(const std::string &fileName) {
    ifstream tracks(fileName);
    if(!tracks.is_open()) {
        throw std::runtime_error("Could not open file " + fileName);
    }

    string line;
    getline(tracks, line);
    vector<Song> songs;
    while(getline(tracks, line)) {
        vector<string> song;
        song = loadLine(line);
        parseLine(song,songs);
    }
    return songs;

}
