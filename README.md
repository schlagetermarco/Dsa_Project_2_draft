TuneNext — Music Recommendation System

TuneNext is a C++ desktop application that recommends songs based on user preferences and song similarity. It uses the Spotify Tracks Dataset, containing approximately 114,000 songs, and compares two custom algorithms, Max Heap and Merge Sort, to rank recommendations and measure their execution times.

Features
Discover: Receive recommendations based on genre, mood, danceability, and explicit-song preferences.
Similar Songs: Search for a song by title or artist and receive recommendations for similar tracks.
Hybrid Search: Combine a selected song with personal preferences to generate recommendations.
Algorithm Selection: Choose between Max Heap and Merge Sort.
Performance Comparison: View algorithm execution times in milliseconds.
Adjustable Results: Select 10, 25, 50, 75, or 100 recommendations.
Favorites: Save favorite songs and access them after restarting the application.

Technologies Used
C++
Qt 6 Widgets
CMake
CLion
Spotify Tracks Dataset (CSV)

Requirements
To build and run TuneNext, install:
A C++17-compatible compiler, such as MinGW-w64.
Qt 6 with the Widgets module.
CMake.
CLion or another IDE that supports CMake projects.
The application was developed on Windows using Qt 6.12.0 and MinGW.

Installation and Running Instructions
1. Clone the Repository

2. Install Qt
Download and install Qt from:
https://www.qt.io/download

3. Open the Project in CLion
Launch CLion.
Select Open.
Allow CLion to load the project.

4. Configure CMake
In CLion, navigate to:
Settings → Build, Execution, Deployment → CMake

For the Windows Qt installation used during development, add the following options: -DCMAKE_PREFIX_PATH="C:/Qt/6.12.0/mingw_64"

Change the path if Qt is installed in a different location.

5. Configure the Dataset
Ensure the Spotify dataset is located in the project's data folder and named dataset.csv.
The dataset is available at:
https://www.kaggle.com/datasets/maharshipandya/-spotify-tracks-dataset

6. Build and Run
Reload the project.
Select the TuneNext executable as the run configuration.
Build the project.
Run the application.
Once launched, the TuneNext interface will appear.

How to Use TuneNext

Discover
Select a genre, mood, danceability preference, number of recommendations, and algorithm. Click Get Recommendation to view the ranked songs.

Similar Songs
Search for a song by title or artist, select it from the dropdown, choose the number of recommendations and algorithm, and click Get Recommendation.

Hybrid Search
Select a song and specify genre, mood, danceability, and other preferences. Choose an algorithm and generate recommendations.

Algorithm Comparison
Run a recommendation search using Max Heap and then repeat it using Merge Sort with the same settings. Compare the execution times displayed on the results page.

Algorithms

Max Heap: Uses a custom max heap to organize songs by recommendation score. The highest scoring songs are retrieved by repeatedly removing the heap root.

Merge Sort: Uses a custom Merge Sort implementation to sort songs in descending order of recommendation score.
Both approaches have an overall ranking time complexity of O(n log n), where n is the number of songs being ranked.

Dataset

Spotify Tracks Dataset by Maharshi Pandya:
https://www.kaggle.com/datasets/maharshipandya/-spotify-tracks-dataset

Project Information
Developed for DSA project 2


