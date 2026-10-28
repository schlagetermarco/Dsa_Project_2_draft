#pragma once
#include <string>
#include <vector>
#include "Song.h"

class DataSetReader {
    static std::vector<std::string> loadLine(const std::string& line);
public:
    static std::vector<Song> loadSongs(const std::string &fileName);
};

