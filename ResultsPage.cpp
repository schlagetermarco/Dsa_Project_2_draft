#include "ResultsPage.h"
#include <QVBoxLayout>
#include <QLabel>

ResultsPage::ResultsPage(QWidget *parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Your Recommendations", this);
    title->setStyleSheet("color:#F59E0B; font-size: 30px; font-weight: bold;");
    layout->addWidget(title);
}

void ResultsPage::displayRecommendations(std::vector<Song> songs) {
    recommendations = songs;
}
