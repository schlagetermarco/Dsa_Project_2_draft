#include "DiscoverPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>


DiscoverPage::DiscoverPage(QWidget *parent):QWidget(parent) {
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
    discoverLayout->addWidget(explicitSongs);

    QLabel* songCount = new QLabel("Number of Recommendations",this);
    QComboBox* songCountSelection = new QComboBox(this);
    songCountSelection->addItems({"10","25","50","75","100"});
    discoverLayout->addWidget(songCount);
    discoverLayout->addWidget(songCountSelection);

    QLabel* adtLabel = new QLabel("Recommended algorithm",this);
    QComboBox* adtSelection = new QComboBox(this);
    adtSelection->addItems({"MaxHeap, MergeSort"});
    discoverLayout->addWidget(adtLabel);
    discoverLayout->addWidget(adtSelection);

    QPushButton* recommendButton = new QPushButton("Get Recommendation",this);
    recommendButton->setFixedHeight(48);
    recommendButton->setCursor(Qt::PointingHandCursor);
    discoverLayout->addWidget(recommendButton);

}
