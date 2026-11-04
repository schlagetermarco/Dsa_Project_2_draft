#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"
#include "ResultsPage.h"
#include <QStackedWidget>


class HybridSearchPage : public QWidget{

    const std::vector<Song>& songs;
    Song userSong;

    public:
    HybridSearchPage(const std::vector<Song> &songList, ResultsPage* resultspage,QStackedWidget* pages, QWidget* parent=nullptr);

};