#pragma once
#include <QMainWindow>
#include<vector>
#include "Song.h"

class QStackedWidget;
class QVPushButton;
class QWidget;

class MainMenu : public QMainWindow{
    QStackedWidget* pageStack;
    QWidget *homePage;
    std::vector<Song> songs;

public:
    MainMenu(QWidget *parent = nullptr);

};
