#pragma once
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include "ResultsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>
#include <QHBoxLayout>

//page with the title and results are added later
ResultsPage::ResultsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Your Recommendations", this);
    title->setStyleSheet("color:#F59E0B; font-size: 30px; font-weight: bold;");
    layout->addWidget(title);
}

//gives list of the song cards and how long the search actually took
void ResultsPage::displayRecommendations(std::vector<Song> songs, double execTime) {
    recommendations = songs;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());

    //gets rid of old results
    while ((layout->count()) > 1) {
        QLayoutItem* item = layout->takeAt(1);
        if (item->widget() != nullptr) {
            delete item->widget();
        }
        delete item;
    }

    QLabel* time= new QLabel("Execution Time " + QString::number(execTime, 'f',3)+ " ms", this);
    time->setStyleSheet("color: #F59E0B; font-size: 14px; background: transparent;");
    layout->addWidget(time);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* list = new QWidget(this);
    QVBoxLayout* listLayout = new QVBoxLayout(list);

    //make card for each song recommended
    for (const Song& song : recommendations) {
        QFrame* songCard = new QFrame(list);
        songCard->setObjectName("songCard");
        songCard->setStyleSheet("QFrame#songCard{background-color: #21190F;border-radius: 12px; "
                                "border: 1px solid #49351B;}");

        QHBoxLayout* cards = new QHBoxLayout(songCard);
        cards->setContentsMargins(18,12,18,12);
        cards->setSpacing(15);

        QLabel* cardIcon = new QLabel("♫",songCard);
        cardIcon->setFixedWidth(40);
        cardIcon->setAlignment(Qt::AlignCenter);

        cardIcon->setStyleSheet("color: #F59E0B; font-size: 30px; background: transparent; border: none");

        QVBoxLayout* songDetails = new QVBoxLayout();
        songDetails->setSpacing(4);

        QLabel* songTitle = new QLabel(QString::fromStdString(song.trackName),songCard);
        songTitle->setStyleSheet("color: #F8FAFC;font-size: 16px; font-weight: bold; border:none;"
                                 "background:transparent;");

        QLabel* artist = new QLabel(QString::fromStdString(song.artistName),songCard);
        artist->setStyleSheet("color: #B6ACA0; font-size: 13px; background: transparent; border:none;");

        songDetails->addWidget(songTitle);
        songDetails->addWidget(artist);

        cards->addWidget(cardIcon);
        cards->addLayout(songDetails,1);

        //adding favorite button for users to save their favorite songs
        QPushButton* favoriteButton = new QPushButton("Save", songCard);
        favoriteButton->setStyleSheet("background-color: #F59E0B;""color: black;""font-size: 14px;""border-radius: 6px;""padding: 8px;");
        cards->addWidget(favoriteButton);

        //check if song is favorite and change text on button to saved
        if(favorites.isFavorite(song)){
            favoriteButton->setText("Saved");
        }

        //connect button to favorites class
        connect(favoriteButton, &QPushButton::clicked, [this, favoriteButton, song]() {
            if (favorites.isFavorite(song)) {

                //remove from favorites if alreayd there
                favoriteButton->setText("Save");
                favorites.removeFavorite(song);
                
            } 
            //add to favorites if not already there
            else {
                favorites.addFavorite(song);
                favoriteButton->setText("Saved");
            }
        });


        listLayout->addWidget(songCard);
    }


    listLayout->addStretch();
    scrollArea->setWidget(list);
    layout->addWidget(scrollArea);
}
