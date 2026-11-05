#include "MergeSort.h"

void MergeSort::mergeSort(std::vector<Song> &songs, int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(songs, left, mid);
    mergeSort(songs, mid + 1, right);

    std::vector<Song> leftSongs(songs.begin()+left, songs.begin()+mid+1);
    std::vector<Song> rightSongs(songs.begin()+mid+1, songs.begin()+right+1);


    int i=0;
    int j = 0;
    int k = left;

    while (i < leftSongs.size() && j < rightSongs.size()) {
        if (leftSongs[i].recommendedScore >= rightSongs[j].recommendedScore) {
            songs[k]=leftSongs[i];
            i++;
        }else {
            songs[k]=rightSongs[j];
            j++;
        }
        k++;
    }

    while (i< leftSongs.size()) {
        songs[k]=leftSongs[i];
        i++;
        k++;
    }

    while (j<rightSongs.size()) {
        songs[k]=rightSongs[j];
        j++;
        k++;
    }
}

void MergeSort::sort(std::vector<Song> &songs) {
    if (songs.empty()) {
        return;
    }

    mergeSort(songs, 0, songs.size() - 1);

}
