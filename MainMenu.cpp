
#include "MainMenu.h"
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include<QGraphicsDropShadowEffect>

#include "DiscoverPage.h"
#include "Sidebar.h";



MainMenu::MainMenu(QWidget *parent):QMainWindow(parent) {
    setWindowTitle("TuneNext");
    resize(1000,700);
    setMinimumSize(QSize(900,650));
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background: qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #050505,stop:0.50 #100C07,stop:1 #1C1208);");

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    Sidebar* sideBar = new Sidebar(centralWidget);
    mainLayout->addWidget(sideBar);

    QWidget* contentWidget = new QWidget(centralWidget);
    QVBoxLayout* contentLayout = new QVBoxLayout(contentWidget);
    mainLayout->addWidget(contentWidget,1);


    QLabel* title = new QLabel("Welcome to TuneNext",contentWidget);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold; font-style: italic; color:#F59E0B;background:transparent");
    contentLayout->addWidget(title);

    QLabel* subtitle = new QLabel("Discover music that matches your preferences",contentWidget);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 16px;font-style: italic; color:rgba(248,250,252,175);background:transparent");
    contentLayout->addWidget(subtitle);
    contentLayout->addStretch();

    QLabel * submessage = new QLabel("Your next  favorite song is waiting",contentWidget);
    submessage->setAlignment(Qt::AlignCenter);
    submessage->setStyleSheet("font-size: 14px; font-style: italic; color: rgba(248,250,252,120);background:transparent");
    contentLayout->addWidget(submessage);
}
