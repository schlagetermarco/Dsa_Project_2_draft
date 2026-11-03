#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"

class DiscoverPage: public QWidget{
    const std::vector<Song>& songs;
public:
    DiscoverPage(const std::vector<Song> &songList,QWidget* parent=nullptr);
};
