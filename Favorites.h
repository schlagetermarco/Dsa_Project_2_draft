#pragma once
#include "Song.h"
#include <string>
#include <vector>
using namespace std;

//saving favorite classes
class Favorites {
    private:
        void saveFavorites() const;

        void loadFavorites();
        vector<Song> favoriteSongs;
    public:
        Favorites();
        void removeFavorite(const Song& song);
        const vector<Song>& getFavorites() const;

        bool isFavorite(const Song& song) const;
        void addFavorite(const Song& song);

};