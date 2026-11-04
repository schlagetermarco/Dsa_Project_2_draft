cmake_minimum_required(VERSION 4.3)
project(Project)

set(CMAKE_CXX_STANDARD 20)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Project
        main.cpp
        MaxHeap.cpp
        MaxHeap.h
        Song.cpp
        Song.h
        MergeSort.cpp
        MergeSort.h
        DataSetReader.cpp
        DataSetReader.h
        RecommendationSystem.cpp
        RecommendationSystem.h
        MainMenu.cpp
        MainMenu.h
        Sidebar.cpp
        Sidebar.h
        DiscoverPage.cpp
        DiscoverPage.h
        ResultsPage.cpp
        ResultsPage.h
        SimilarSongsPage.cpp
        SimilarSongsPage.h
        HybridSearchPage.cpp
        HybridSearchPage.h)
target_link_libraries(Project PRIVATE Qt6::Widgets)
