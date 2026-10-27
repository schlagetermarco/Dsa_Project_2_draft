
#pragma once
#include <vector>
#include "Song.h"


class MaxHeap {
    std::vector<Song> songs;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(const Song& song);
    Song erase();
    Song peekTopRated() const;
    bool isEmpty() const;
    int size() const;
};


