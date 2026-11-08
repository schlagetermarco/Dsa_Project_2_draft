#include "Favorites.h"
#include <fstream>
using namespace std;

Favorites::Favorites() {
    loadFavorites();
}

//saves users favorite songs in a text file  
void Favorites::saveFavorites() const {
    ofstream file("favorites.txt");
    if (!file.is_open()) {
        return;
    }
    
    else{
        for(int i=0; i<favoriteSongs.size(); i++){
            file << favoriteSongs[i].trackID << endl;
            file << favoriteSongs[i].artistName << endl;
            file << favoriteSongs[i].albumName << endl;
            file << favoriteSongs[i].trackName << endl;
        }
    file.close();
    }

}

//loads favorites songs from text file
void Favorites::loadFavorites() {
    ifstream file("favorites.txt");
    if (!file.is_open()) {
        return;
    }

    //reads every line and puts everything in a vector
    Song song1;
    while (getline(file, song1.trackID)) {
        if(!getline(file, song1.artistName)){
            break;
        }
        if(!getline(file, song1.albumName)){
            break;
        }
        if(!getline(file, song1.trackName)){
            break;
        }


        if(!isFavorite(song1)){
            favoriteSongs.push_back(song1);
        }
       
    }

    file.close();
}

//checks favorites to see if song is already in there
bool Favorites::isFavorite(const Song& song) const{
    for(int i=0; i<favoriteSongs.size(); i++){
        if(song.trackID == favoriteSongs[i].trackID && song.artistName == favoriteSongs[i].artistName && song.albumName == favoriteSongs[i].albumName && song.trackName == favoriteSongs[i].trackName) {
            return true;
        }
    }

    return false;
}

//remove songs from favorites if user wants to
void Favorites::removeFavorite(const Song& song){
    for(int i=0; i<favoriteSongs.size(); i++){
        if(song.trackID == favoriteSongs[i].trackID && song.artistName == favoriteSongs[i].artistName && song.albumName == favoriteSongs[i].albumName && song.trackName == favoriteSongs[i].trackName) {

            //removes song from vector
            favoriteSongs.erase(favoriteSongs.begin() + i);
            saveFavorites();
    
            return;
        }
    }
}

//return vector of fav songs
const vector<Song>& Favorites::getFavorites() const{
    return favoriteSongs;
}

//adds song to favorites
void Favorites::addFavorite(const Song& song){
    if(!isFavorite(song)){
        favoriteSongs.push_back(song);


        saveFavorites();
    }
}