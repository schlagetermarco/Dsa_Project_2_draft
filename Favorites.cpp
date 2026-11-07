#include "Favorites.h"
#include <fstream>
using namespace std;

Favorites::Favorites() {
    loadFavorites();
}

void Favorites::saveFavorites() const {
    ofstream file("favorites.txt");
    if (!file.is_open()) {
        return;
    }
    
    else{
        for(int i=0; i<favoriteSongs.size(); i++){
            file << favoriteSongs[i].trackID << "," << favoriteSongs[i].artistName << "," << favoriteSongs[i].albumName << "," << favoriteSongs[i].trackName << endl;
        }

    file.close();
    }

}

void Favorites::loadFavorites() {
    ifstream file("favorites.txt");
    if (!file.is_open()) {
        return;
    }

    Song song1;
    while (getline(file, song1.trackID, ',')) {
        if(!getline(file, song1.artistName)){
            break;
        }
        if(!getline(file, song1.albumName, ',')){
            break;
        }
        if(!getline(file, song1.trackName, ',')){
            break;
        }


        if(!isFavorite(song1)){
            favoriteSongs.push_back(song1);
        }
       
    }

    file.close();
}
bool Favorites::isFavorite(const Song& song) const{
    for(int i=0; i<favoriteSongs.size(); i++){
        if(song.trackID == favoriteSongs[i].trackID && song.artistName == favoriteSongs[i].artistName && song.albumName == favoriteSongs[i].albumName && song.trackName == favoriteSongs[i].trackName) {
            return true;
        }
    }

    return false;
}

void Favorites::removeFavorite(const Song& song){
    for(int i=0; i<favoriteSongs.size(); i++){
        if(song.trackID == favoriteSongs[i].trackID && song.artistName == favoriteSongs[i].artistName && song.albumName == favoriteSongs[i].albumName && song.trackName == favoriteSongs[i].trackName) {
            
            favoriteSongs.erase(favoriteSongs.begin() + i);
            saveFavorites();
    
            return;
        }
    }
}

const vector<Song>& Favorites::getFavorites() const{
    return favoriteSongs;
}

void Favorites::addFavorite(const Song& song){
    if(!isFavorite(song)){
        favoriteSongs.push_back(song);


        saveFavorites();
    }
}