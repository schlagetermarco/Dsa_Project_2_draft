
#include "MainMenu.h"
#include <QLabel>
#include <QString>
#include <QWidget>
#include "DiscoverPage.h"
#include "Sidebar.h"
#include <QVBoxLayout>
#include<QPushButton>
#include<QStackedWidget>
#include "DataSetReader.h"
#include "ResultsPage.h"
#include "SimilarSongsPage.h"
#include "HybridSearchPage.h"
using namespace std;

//main menu
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

    //title of home page
    QLabel* title = new QLabel("Welcome to TuneNext",homePage);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold; font-style: italic; color:#F59E0B;background:transparent");
    contentLayout->addWidget(title);

    //subtitle
    QLabel* subtitle = new QLabel("Discover music that matches your preferences",homePage);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("font-size: 16px;font-style: italic; color:rgba(248,250,252,175);background:transparent");
    contentLayout->addWidget(subtitle);

    //home page instructions
    QLabel* homepageInstruct = new QLabel("\n\nDiscover - Unlock music based on your choices\n\nSimiliar Songs - Find songs similiar to ones you already love\n\nHybrid Search - Combination of both of the above methods",homePage);
    homepageInstruct->setAlignment(Qt::AlignCenter);
    homepageInstruct->setStyleSheet("font-size: 22px; font-style: italic; color: orange ;background:transparent");
    contentLayout->addWidget(homepageInstruct);
    
    //add nunmber of songs in our dataset
    QLabel* numOfSongs = new QLabel("\n\n\nBrowse "+QString::number(songs.size())+" songs!",homePage);
    numOfSongs->setAlignment(Qt::AlignCenter);
    numOfSongs->setStyleSheet("color: #F59E0B; font-size: 40px; font-weight: bold; font-style: italic; font-style: italic;background:transparent");
    contentLayout->addWidget(numOfSongs);
    
    contentLayout->addStretch();

    //bottom text
    QLabel * submessage = new QLabel("Your next  favorite song is waiting",homePage);
    submessage->setAlignment(Qt::AlignCenter);
    submessage->setStyleSheet("font-size: 14px; font-style: italic; color: rgba(248,250,252,120);background:transparent");
    contentLayout->addWidget(submessage);

    
    ResultsPage* resultsPage = new ResultsPage();
    DiscoverPage* discoverPage = new DiscoverPage(songs,resultsPage,pages);
    SimilarSongsPage* similarSongsPage = new SimilarSongsPage(songs,resultsPage,pages);
    HybridSearchPage* hybridSearchPage = new HybridSearchPage(songs,resultsPage,pages);

    //add pages
    pages->addWidget(homePage);
    pages->addWidget(discoverPage);
    pages->addWidget(similarSongsPage);
    pages->addWidget(hybridSearchPage);
    pages->addWidget(resultsPage);

    pages->setCurrentWidget(homePage);

    QList<QPushButton*> buttons = sideBar->findChildren<QPushButton*>();


    //buttons to switch page
    for (QPushButton* button : buttons) {
        if (button->text() == "Home") {
            connect(button,&QPushButton::clicked,this,[pages,homePage]() {
                pages->setCurrentWidget(homePage);
            });
        }else if (button->text() == "Discover") {
            connect(button,&QPushButton::clicked,this,[pages,discoverPage]() {
                pages->setCurrentWidget(discoverPage);});
        }else if (button->text() == "Similar Songs") {
            connect(button,&QPushButton::clicked,this,[pages,similarSongsPage]() {
                pages->setCurrentWidget(similarSongsPage);});
        }else  if (button->text() == "Hybrid Search") {
            connect(button,&QPushButton::clicked,this,[pages,hybridSearchPage]() {
                 pages->setCurrentWidget(hybridSearchPage);});
        }
    }
}
