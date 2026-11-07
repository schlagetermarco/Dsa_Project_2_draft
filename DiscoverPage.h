#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"
#include "ResultsPage.h"
#include <QStackedWidget>

//discover page class
class DiscoverPage: public QWidget{

    const std::vector<Song>& songs;
public:
    DiscoverPage(const std::vector<Song> &songList, ResultsPage* resultspage,QStackedWidget* pages, QWidget* parent=nullptr);
};
