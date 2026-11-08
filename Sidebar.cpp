
#include "Sidebar.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include<QGraphicsDropShadowEffect>
#include<QVBoxLayout>
#include<QString>

//makes sidebar with buttons
Sidebar::Sidebar(QWidget *parent):QWidget(parent) {

    //fixes width for window resizing
    setFixedWidth(180);
    QVBoxLayout* sideBarLayout = new QVBoxLayout(this);
    sideBarLayout->setAlignment(Qt::AlignTop);
    sideBarLayout->setContentsMargins(1,10,1,25);
    sideBarLayout->setSpacing(1);

    setStyleSheet("background-color: rgba(8,8,10,200); border-radius: 12px;");

    //name at top
    QLabel*sideBarTitle = new QLabel("TuneNext",this);
    sideBarTitle->setFixedSize(150,45);
    sideBarTitle->setAlignment(Qt::AlignCenter);
    sideBarTitle->setStyleSheet("font-size:23px; font-weight:bold; color:#F59E0B; padding-bottom: 15px; border:none;");
    sideBarLayout->addWidget(sideBarTitle,0,Qt::AlignCenter);

    QString buttonStyle="QPushButton{background-color:rgba(12,10,8,190); color: #F8FAFC; border:none; font-size: 15px;"
                        "text-align: left; padding-left: 12px;}"
                        "QPushButton:hover{background:qlineargradient(x1:0,y1:0,x2:1,y2:1,stop:0 rgba(245,158,11,65),"
                        "stop:1 rgba(245,158,11,15)); color: #FBBF24; border:none}";

        //buttons for sidebar
    QPushButton* homeButton = new QPushButton("Home", this);
    homeButton->setFixedHeight(42);
    homeButton->setStyleSheet(buttonStyle);
    sideBarLayout->addWidget(homeButton);

    QPushButton* searchParamButton= new QPushButton("Discover", this);
    searchParamButton->setFixedHeight(42);
    searchParamButton->setStyleSheet(buttonStyle);
    sideBarLayout->addWidget(searchParamButton);

    QPushButton* searchSimilarSongButton= new QPushButton("Similar Songs", this);
    searchSimilarSongButton->setFixedHeight(42);
    searchSimilarSongButton->setStyleSheet(buttonStyle);
    sideBarLayout->addWidget(searchSimilarSongButton);

    QPushButton* hybridSearchButton= new QPushButton("Hybrid Search", this);
    hybridSearchButton->setFixedHeight(42);
    hybridSearchButton->setStyleSheet(buttonStyle);
    sideBarLayout->addWidget(hybridSearchButton);

    QPushButton* favoritesButton= new QPushButton("Favorites", this);
    favoritesButton->setFixedHeight(42);
    favoritesButton->setStyleSheet(buttonStyle);
    sideBarLayout->addWidget(favoritesButton);
    


}
