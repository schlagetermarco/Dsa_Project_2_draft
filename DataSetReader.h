#pragma once
#include <string>
#include <vector>
#include "Song.h"

//class for reading and parsing songs and putting in vector

class DataSetReader {

    static std::vector<std::string> loadLine(const std::string& line);
    static void parseLine(const std::vector<std::string>& data, std::vector<Song> &songs);
public:
    static std::vector<Song> loadSongs(const std::string &fileName);
};

