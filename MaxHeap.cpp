#include "MaxHeap.h"
#include <stdexcept>

//maxHeap implementation

//brings value up by heapify up
void MaxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index-1) / 2;
        if (songs[index].recommendedScore <= songs[parent].recommendedScore) {
            break;
        }
        std::swap(songs[index], songs[parent]);
        index = parent;
    }
}

//brings value down by heapify down
void MaxHeap::heapifyDown(int index) {

    while (2*index+1 < songs.size()) {
        int leftChild = 2*index + 1;
        int rightChild= -1;
        if (2*index+2 < songs.size()) {
            rightChild = 2*index + 2;
        }

        int greatest = leftChild;

        if ((rightChild != -1) &&
            (songs[leftChild].recommendedScore < songs[rightChild].recommendedScore)) {
            greatest = rightChild;
        }

        if (songs[index].recommendedScore >= songs[greatest].recommendedScore) {
            break;
        }

        std::swap(songs[index], songs[greatest]);
        index = greatest;
    }
}

//insertion into heap
void MaxHeap::insert(const Song &song) {
    songs.push_back(song);
    heapifyUp(songs.size() - 1);
}

//removes value from heap
Song MaxHeap::erase() {
    if (songs.empty()) {
        throw std::runtime_error("There are no songs in the heap");
    }
    Song top = songs[0];
    songs[0]=songs.back();
    songs.pop_back();
    if (!songs.empty()) {
        heapifyDown(0);
    }
    return top;
}

//gets top rated song
Song MaxHeap::peekTopRated() const {
    if (songs.empty()) {
        throw std::runtime_error("There are no songs in the heap");
    }
    return songs[0];
}

//checks if heap is empty
bool MaxHeap::isEmpty() const {
    return songs.empty();
}

//returns heap size
int MaxHeap::size() const {
    return songs.size();
}
