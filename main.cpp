
#include <iostream>
#include <vector>
#include "MaxHeap.h"

bool testOrder(const std::vector<double>& scores, const char* testName) {
    MaxHeap heap;

    for (int i = 0; i < scores.size(); i++) {
        Song song{"Song " + std::to_string(i + 1), 4.0, scores[i]};
        heap.insert(song);
    }

    for (double expected : {50.0, 40.0, 30.0, 20.0, 10.0}) {
        Song top = heap.erase();

        if (top.recommendedScore != expected) {
            std::cout << "FAIL: " << testName
                      << " (expected " << expected
                      << ", got " << top.recommendedScore << ")\n";
            return false;
        }
    }

    if (!heap.isEmpty()) {
        std::cout << "FAIL: " << testName << " (heap not empty)\n";
        return false;
    }

    std::cout << "PASS: " << testName << '\n';
    return true;
}

int main() {
    bool ascending = testOrder(
        {10.0, 20.0, 30.0, 40.0, 50.0},
        "ascending insertion"
    );

    bool descending = testOrder(
        {50.0, 40.0, 30.0, 20.0, 10.0},
        "descending insertion"
    );

    return (ascending && descending) ? 0 : 1;
}
