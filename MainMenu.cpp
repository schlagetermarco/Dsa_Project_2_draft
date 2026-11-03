
#include "MainMenu.h"
#include <QLabel>
#include <QWidget>
#include "DiscoverPage.h"
#include "Sidebar.h"
#include <QVBoxLayout>
#include<QPushButton>
#include<QStackedWidget>
#include "DataSetReader.h"
using namespace std;

MainMenu::MainMenu(QWidget *parent):QMainWindow(parent) {
    songs = DataSetReader::loadSongs("../data/dataset.csv");

    setWindowTitle("TuneNext");
    resize(1000,700);
    setMinimumSize(QSize(900,650));

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    centralWidget->setStyleSheet("background: qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 #050505,stop:0.50 #100C07,stop:1 #1C1208);");

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    Sidebar* sideBar = new Sidebar(centralWidget);
    mainLayout->addWidget(sideBar);

    QStackedWidget* pages = new QStackedWidget(centralWidget);
    mainLayout->addWidget(pages,1);

    QWidget* homePage = new QWidget();
    QVBoxLayout* contentLayout = new QVBoxLayout(homePage);



    QLabel* title = new QLabel("Welcome to TuneNext",homePage);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold; font-style: italic; color:#F59E0B;background:transparent");
    contentLayout->addWidget(title);

    QLabel* subtitle = new QLabel("Discover music that matches your preferences",homePage);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 16px;font-style: italic; color:rgba(248,250,252,175);background:transparent");
    contentLayout->addWidget(subtitle);
    contentLayout->addStretch();

    QLabel * submessage = new QLabel("Your next  favorite song is waiting",homePage);
    submessage->setAlignment(Qt::AlignCenter);
    submessage->setStyleSheet("font-size: 14px; font-style: italic; color: rgba(248,250,252,120);background:transparent");
    contentLayout->addWidget(submessage);

    DiscoverPage* discoverPage = new DiscoverPage(songs);
    pages->addWidget(homePage);
    pages->addWidget(discoverPage);

    pages->setCurrentWidget(homePage);

    QList<QPushButton*> buttons = sideBar->findChildren<QPushButton*>();

    for (QPushButton* button : buttons) {
        if (button->text() == "Home") {
            connect(button,&QPushButton::clicked,this,[pages,homePage]() {
                pages->setCurrentWidget(homePage);
            });
        }else if (button->text() == "Discover") {
            connect(button,&QPushButton::clicked,this,[pages,discoverPage]() {
                pages->setCurrentWidget(discoverPage);
            });
        }
    }
}
