
#include "MainMenu.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>


MainMenu::MainMenu(QWidget *parent):QMainWindow(parent) {
    setWindowTitle("TuneNext");
    resize(1000,700);
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    QWidget* sideBar = new QWidget(centralWidget);
    sideBar->setFixedWidth(180);
    QVBoxLayout* sideBarLayout = new QVBoxLayout(sideBar);
    sideBarLayout->setContentsMargins(15,25,15,25);
    mainLayout->addWidget(sideBar);
    centralWidget->setStyleSheet("background-color: #111827;");

    QWidget* contentWidget = new QWidget(centralWidget);
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    mainLayout->addWidget(contentWidget);


    QLabel* title = new QLabel("Welcome to TuneNext",contentWidget);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold; font-style: italic; color:#A78BFA;");
    contentLayout->addWidget(title);




}
