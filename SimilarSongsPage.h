#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"
#include "ResultsPage.h"
#include <QStackedWidget>

class SimilarSongsPage: public QWidget {
    const std::vector<Song>& songs;
    Song userSong;
public:
        SimilarSongsPage(const std::vector<Song> &songList, ResultsPage* resultspage,QStackedWidget* pages, QWidget* parent=nullptr);

};
