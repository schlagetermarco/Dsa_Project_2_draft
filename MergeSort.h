#pragma once
#include <vector>
#include "Song.h"


//mergesort class
class MergeSort {


    static void mergeSort(std::vector<Song> &songs, int left, int right);
public:
    static void sort(std::vector<Song>& songs);
};
