#include "HybridSearchPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include "RecommendationSystem.h"
#include <QSlider>
#include "MaxHeap.h"
#include "MergeSort.h"
#include <QMessageBox>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <QLineEdit>

using namespace std;

HybridSearchPage::HybridSearchPage(const std::vector<Song> &songList, ResultsPage *resultspage, QStackedWidget *pages,
    QWidget *parent): QWidget(parent),songs(songList) {


    QVBoxLayout* HybridSongLayout = new QVBoxLayout(this);
    HybridSongLayout->setContentsMargins(25,25,25,25);
    HybridSongLayout->setSpacing(12);

    QLabel* title = new QLabel("Hybrid Search",this);
    title->setStyleSheet("color: #F59E0B; font-size: 30px; font-weight: bold; background:transparent;");
    HybridSongLayout->addWidget(title);


    QLabel* searchText = new QLabel("Search for a song you like:",this);
    searchText->setStyleSheet("color: #F8FAFC; font-size: 16px; background:transparent;");
    HybridSongLayout->addWidget(searchText);

    QLineEdit* searchSong = new QLineEdit(this);
    searchSong->setPlaceholderText("Search by song title or artist...");
    searchSong->setStyleSheet("background-color: #21190F; color: #F8FAFC; border: 1px solid #49351B;"
                              "border-radius: 8px; padding: 10px; font-size: 14px;");

    HybridSongLayout->addWidget(searchSong);

    QComboBox* matchingSongs = new QComboBox(this);
    matchingSongs->setStyleSheet("background-color: #21190F; color: #F8FAFC; border: 1px solid #49351B;"
                              "border-radius: 8px; padding: 10px; font-size: 14px;");

    matchingSongs->addItem("Select a song");
    HybridSongLayout->addWidget(matchingSongs);

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

    QLabel* genre = new QLabel("Genre",this);
    QComboBox* genreSelection = new QComboBox(this);
    genreSelection->addItems({"Any","Pop","Rock","Hip-Hop","Rap","Country","Electronic",
        "Jazz", "Classical"});
    HybridSongLayout->addWidget(genre);
    HybridSongLayout->addWidget(genreSelection);

    QLabel* mood = new QLabel("Mood",this);
    QComboBox* moodSelection = new QComboBox(this);
    moodSelection->addItems({"Any","Happy","Sad", "Chill", "Energetic"});
    HybridSongLayout->addWidget(mood);
    HybridSongLayout->addWidget(moodSelection);

    QLabel* danceability = new QLabel("Danceability",this);
    QSlider* danceabilitySlider = new QSlider(Qt::Horizontal,this);
    danceabilitySlider->setRange(0,100);
    danceabilitySlider->setValue(50);
    QLabel* danceVal = new QLabel("50",this);

    connect(danceabilitySlider, &QSlider::valueChanged,danceVal,[danceVal](int value) {
        danceVal->setText(QString::number(value));
    });

    QHBoxLayout* danceabilityLayout = new QHBoxLayout();
    danceabilityLayout->addWidget(danceabilitySlider);
    danceabilityLayout->addWidget(danceVal);

    HybridSongLayout->addWidget(danceability);
    HybridSongLayout->addLayout(danceabilityLayout);

    QCheckBox* explicitSongs= new QCheckBox("Include explicit songs",this);
    HybridSongLayout->addWidget(explicitSongs);


    QLabel* songCount = new QLabel("Number of Recommendations",this);
    QComboBox* songCountSelection = new QComboBox(this);
    songCountSelection->addItems({"10","25","50","75","100"});
    HybridSongLayout->addWidget(songCount);
    HybridSongLayout->addWidget(songCountSelection);

    QLabel* adtLabel = new QLabel("Recommended algorithm",this);
    QComboBox* adtSelection = new QComboBox(this);
    adtSelection->addItems({"MaxHeap", "MergeSort"});
    HybridSongLayout->addWidget(adtLabel);
    HybridSongLayout->addWidget(adtSelection);

    QPushButton* recommendButton = new QPushButton("Get Recommendation",this);
    recommendButton->setFixedHeight(48);
    recommendButton->setCursor(Qt::PointingHandCursor);
    HybridSongLayout->addWidget(recommendButton);
    HybridSongLayout->addStretch();
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
        songCountSelection,adtSelection,genreSelection, moodSelection,
        danceabilitySlider,resultspage,pages]() {

        if (matchingSongs->currentIndex()<=0) {
            QMessageBox::warning(this,"No Song Selected",
                "Please search and select a song first.");
            return;
        }

        bool includeExplicitSongs = explicitSongs->isChecked();
        QString adt = adtSelection->currentText();
        string genre = genreSelection->currentText().toStdString();
        string mood = moodSelection->currentText().toStdString();
        double danceability = danceabilitySlider->value()/100.0;
        vector<Song> possibleRecommendations;
        unordered_set<string> repeated_songs;

        for (Song song : songs) {
            if (song.index== userSong.index) {
                continue;
            }

            song.recommendedScore = RecommendationSystem::hybridRecommendationScore(song,
                userSong,genre,mood,danceability,includeExplicitSongs);

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
