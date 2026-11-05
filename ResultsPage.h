
#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"

class ResultsPage: public QWidget {

    std::vector<Song> recommendations;
public:
    ResultsPage(QWidget* parent = nullptr);
    void displayRecommendations(std::vector<Song> songs, double execTime);


};
