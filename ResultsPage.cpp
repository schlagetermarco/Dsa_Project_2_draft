#include "ResultsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QFrame>
#include <QHBoxLayout>

ResultsPage::ResultsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Your Recommendations", this);
    title->setStyleSheet("color:#F59E0B; font-size: 30px; font-weight: bold;");
    layout->addWidget(title);
}

void ResultsPage::displayRecommendations(std::vector<Song> songs, double execTime) {
    recommendations = songs;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());

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
        listLayout->addWidget(songCard);
    }


    listLayout->addStretch();
    scrollArea->setWidget(list);
    layout->addWidget(scrollArea);
}
