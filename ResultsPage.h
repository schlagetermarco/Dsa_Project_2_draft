
#pragma once
#include <QWidget>
#include <vector>
#include "Song.h"
#include "Favorites.h"

class ResultsPage: public QWidget {
    std::vector<Song> recommendations;
    Favorites favorites;

    double lastExecutionTime = 0.0;

public:
    ResultsPage(QWidget* parent = nullptr);
    void displayRecommendations(std::vector<Song> songs, double execTime);


};
