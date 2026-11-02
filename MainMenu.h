#pragma once
#include <QMainWindow>

class QStackedWidget;
class QVPushButton;
class QWidget;

class MainMenu : public QMainWindow{
    QStackedWidget* pageStack;
    QWidget *homePage;
public:
    MainMenu(QWidget *parent = nullptr);

};
