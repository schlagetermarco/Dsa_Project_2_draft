#pragma once
#include <string>
#include <vector>
#include "Song.h"

class DataSetReader {
    static std::vector<std::string> loadLine(const std::string& line);
    static void parseLine(const std::vector<std::string>& data, std::vector<Song> &songs);
public:
    static std::vector<Song> loadSongs(const std::string &fileName);
};

