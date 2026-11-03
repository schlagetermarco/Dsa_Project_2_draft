#include "DiscoverPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include "RecommendationSystem.h"
#include "MaxHeap.h"
#include "MergeSort.h"
#include <QMessageBox>
#include <algorithm>

using namespace std;


DiscoverPage::DiscoverPage(const std::vector<Song> &songList, QWidget *parent):QWidget(parent), songs(songList){

    QVBoxLayout* discoverLayout = new QVBoxLayout(this);
    discoverLayout->setContentsMargins(35,30,35,25);
    discoverLayout->setSpacing(18);

    QLabel* title = new QLabel("Discover new music",this);
    title->setStyleSheet("color: #F59E0B; font-size: 34px; font-weight: bold; background:transparent;");
    discoverLayout->addWidget(title);

    QLabel* description = new QLabel("Find songs that match your personal preferences",this);
    description->setStyleSheet("color:rgba(248,250,252,175); font-size:15px; background:transparent;");
    discoverLayout->addWidget(description);

    QLabel* genre = new QLabel("Genre",this);
    QComboBox* genreSelection = new QComboBox(this);
    genreSelection->addItems({"Any","Pop","Rock","Hip-Hop","Rap","Country","Electronic",
        "Jazz", "Classical"});
    discoverLayout->addWidget(genre);
    discoverLayout->addWidget(genreSelection);

    QLabel* mood = new QLabel("Mood",this);
    QComboBox* moodSelection = new QComboBox(this);
    moodSelection->addItems({"Any","Happy","Sad", "Chill", "Energetic"});
    discoverLayout->addWidget(mood);
    discoverLayout->addWidget(moodSelection);

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

    discoverLayout->addWidget(danceability);
    discoverLayout->addLayout(danceabilityLayout);

    QCheckBox* explicitSongs= new QCheckBox("Include explicit songs",this);
    discoverLayout->addWidget(explicitSongs);


    QLabel* songCount = new QLabel("Number of Recommendations",this);
    QComboBox* songCountSelection = new QComboBox(this);
    songCountSelection->addItems({"10","25","50","75","100"});
    discoverLayout->addWidget(songCount);
    discoverLayout->addWidget(songCountSelection);

    QLabel* adtLabel = new QLabel("Recommended algorithm",this);
    QComboBox* adtSelection = new QComboBox(this);
    adtSelection->addItems({"MaxHeap", "MergeSort"});
    discoverLayout->addWidget(adtLabel);
    discoverLayout->addWidget(adtSelection);

    QPushButton* recommendButton = new QPushButton("Get Recommendation",this);
    recommendButton->setFixedHeight(48);
    recommendButton->setCursor(Qt::PointingHandCursor);
    discoverLayout->addWidget(recommendButton);
    discoverLayout->addStretch();
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

    connect(recommendButton, &QPushButton::clicked, this,[this,genreSelection,moodSelection,danceabilitySlider,
        explicitSongs,songCountSelection,adtSelection]() {
        string genre = genreSelection->currentText().toStdString();
        string mood = moodSelection->currentText().toStdString();
        double danceability = danceabilitySlider->value()/100.0;
        bool includeExplicitSongs = explicitSongs->isChecked();

        QString adt = adtSelection->currentText();
        std::vector<Song> possibleRecommendations;

        for (Song song : songs) {

            song.recommendedScore = RecommendationSystem::parameterRecommendationScore(song,genre,mood,
                danceability,includeExplicitSongs);

            if (song.recommendedScore >= 0) {
                possibleRecommendations.push_back(song);
            }
        }
        if (possibleRecommendations.empty()) {
            QMessageBox::information(this,"No Recommendations Found","No songs matched your preferences");
            return;
        }

        int count = min((int)possibleRecommendations.size(),songCountSelection->currentText().toInt());

        vector<Song> recommendations;

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
    });

}
