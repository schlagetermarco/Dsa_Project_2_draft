#include "SimilarSongsPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include "RecommendationSystem.h"
#include "MaxHeap.h"
#include "MergeSort.h"
#include <QMessageBox>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <QLineEdit>

using namespace std;

SimilarSongsPage::SimilarSongsPage(const std::vector<Song> &songList, ResultsPage *resultspage, QStackedWidget *pages,
    QWidget *parent): QWidget(parent),songs(songList){

    QVBoxLayout* similarSongLayout = new QVBoxLayout(this);
    similarSongLayout->setContentsMargins(25,25,25,25);
    similarSongLayout->setSpacing(25);


    QLabel* title = new QLabel("Similar Songs",this);
    title->setStyleSheet("color: #F59E0B; font-size: 30px; font-weight: bold; background:transparent;");
    similarSongLayout->addWidget(title);


    QLabel* searchText = new QLabel("Search for a song you like:",this);
    searchText->setStyleSheet("color: #F8FAFC; font-size: 16px; background:transparent;");
    similarSongLayout->addWidget(searchText);

    QLineEdit* searchSong = new QLineEdit(this);
    searchSong->setPlaceholderText("Search by song title or artist...");
    searchSong->setStyleSheet("background-color: #21190F; color: #F8FAFC; border: 1px solid #49351B;"
                              "border-radius: 8px; padding: 10px; font-size: 14px;");

    similarSongLayout->addWidget(searchSong);

    QComboBox* matchingSongs = new QComboBox(this);
    matchingSongs->setStyleSheet("background-color: #21190F; color: #F8FAFC; border: 1px solid #49351B;"
                              "border-radius: 8px; padding: 10px; font-size: 14px;");

    matchingSongs->addItem("Select a song");
    similarSongLayout->addWidget(matchingSongs);

    connect(searchSong, &QLineEdit::textChanged,this,[this,matchingSongs](const QString &text){
        matchingSongs->clear();
        matchingSongs->addItem("Select a song");
        if (text.trimmed().isEmpty()) {
            return;
        }

        int matches = 0;
        for (int i = 0; i < songs.size(); ++i) {
            const Song &song = songs[i];
            QString songTitle = QString::fromStdString(song.trackName);
            QString songArtist = QString::fromStdString(song.artistName);

            if (songTitle.contains(text, Qt::CaseInsensitive)|| songArtist.contains(text, Qt::CaseInsensitive)) {
                matchingSongs->addItem(songTitle+" - "+songArtist,i);
                matches++;
                if (matches>=20) {
                    break;
                }
            }
        }
    });

    connect(matchingSongs, &QComboBox::currentIndexChanged,this,[this,matchingSongs](int index) {
        if (index <= 0) {
            return;
        }

        int chosenSong=matchingSongs->itemData(index).toInt();
        userSong = songs[chosenSong];
    });

    QCheckBox* explicitSongs= new QCheckBox("Include explicit songs",this);
    similarSongLayout->addWidget(explicitSongs);

    QLabel* songCount = new QLabel("Number of Recommendations",this);
    QComboBox* songCountSelection = new QComboBox(this);
    songCountSelection->addItems({"10","25","50","75","100"});
    similarSongLayout->addWidget(songCount);
    similarSongLayout->addWidget(songCountSelection);

    QLabel* adtLabel = new QLabel("Recommended algorithm",this);
    QComboBox* adtSelection = new QComboBox(this);
    adtSelection->addItems({"MaxHeap", "MergeSort"});
    similarSongLayout->addWidget(adtLabel);
    similarSongLayout->addWidget(adtSelection);

    QPushButton* recommendButton = new QPushButton("Get Recommendation",this);
    recommendButton->setFixedHeight(48);
    recommendButton->setCursor(Qt::PointingHandCursor);
    similarSongLayout->addWidget(recommendButton);
    similarSongLayout->addStretch();
    setStyleSheet("QLabel{ color:#F8FAFC; background:transparent}"

                  "QComboBox{background-color:#21190F;color:#F8FAFC; border: 1px solid rgba(245,158,11,90);"
                  " border-radius: 8px; padding:9px; font-size: 14px;} "

                  "QComboBox QAbstractItemView{background-color:#21190F;color:#F8FAFC;"
                  "selection-background-color: #F59E0B; selection-color: #100C07;} "

                  "QCheckBox{color:#F8FAFC; spacing:8px;}"

                  "QSlider::groove:horizontal{background:#3A2A17; height: 6px; border-radius: 3px;}"

                  "QSlider::sub-page:horizontal{background:#F59E0B; border-radius: 3px;}"

                  "QSlider::handle:horizontal{background:#FBBF24; border-radius: 8px; margin: -5px 0; width:26px}"

                  "QPushButton{background-color:#F59E0B; color:#100C07; font-size: 15px; font-weight: bold;"
                  "border-radius: 10px; border: none;}"

                  "QPushButton:hover{background-color: #FBBF24}");

    connect(recommendButton, &QPushButton::clicked, this,[this,matchingSongs,explicitSongs,
        songCountSelection,adtSelection,resultspage,pages]() {
        if (matchingSongs->currentIndex()<=0) {
            QMessageBox::warning(this,"No Song Selected",
                "Please search and select a song first.");
            return;
        }

        bool includeExplicitSongs = explicitSongs->isChecked();
        QString adt = adtSelection->currentText();
        vector<Song> possibleRecommendations;
        unordered_set<string> repeated_songs;

        for (Song song : songs) {
            if (song.index== userSong.index) {
                continue;
            }

            song.recommendedScore = RecommendationSystem::similarityRecommendationScore(song,
                userSong,includeExplicitSongs);

            string songIdentifier = song.trackName+"|"+ song.artistName;

            if (song.recommendedScore >= 0 && repeated_songs.find(songIdentifier)==repeated_songs.end() ) {
                possibleRecommendations.push_back(song);
                repeated_songs.insert(songIdentifier);
            }
        }

        int count = min((int)possibleRecommendations.size(),songCountSelection->currentText().toInt());

        vector<Song> recommendations;
         auto start = chrono::high_resolution_clock::now();

        if (adt=="MaxHeap") {
            MaxHeap topSongs;
            for (const Song& song : possibleRecommendations) {
                topSongs.insert(song);
            }
            for (int i = 0; i < count; i++) {
                recommendations.push_back(topSongs.erase());
            }
        }else if (adt=="MergeSort") {
            MergeSort::sort(possibleRecommendations);
            for (int i = 0; i < count; i++) {
                recommendations.push_back(possibleRecommendations[i]);
            }
        }
        auto end = chrono::high_resolution_clock::now();
        double execTime = chrono::duration<double,milli>(end-start).count();
        resultspage->displayRecommendations(recommendations, execTime);
        pages->setCurrentWidget(resultspage);

    });

}
