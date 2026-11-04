#include "ResultsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

ResultsPage::ResultsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Your Recommendations", this);
    title->setStyleSheet("color:#F59E0B; font-size: 30px; font-weight: bold;");
    layout->addWidget(title);
}

void ResultsPage::displayRecommendations(std::vector<Song> songs) {
    recommendations = songs;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(this->layout());
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* list = new QWidget(this);
    QVBoxLayout* listLayout = new QVBoxLayout(list);

    for (const Song& song : recommendations) {
        QString songInfo= QString::fromStdString(song.trackName) + " - "+
            QString::fromStdString(song.artistName) + " ("+
                QString::fromStdString(song.track_genre) + ")";

        QLabel* songLabel = new QLabel(songInfo, list);
        songLabel->setStyleSheet("color: #F8FAFC; font-size: 15px; padding: 10px;");

        listLayout->addWidget(songLabel);
    }
    listLayout->addStretch();
    scrollArea->setWidget(list);
    layout->addWidget(scrollArea);
}
