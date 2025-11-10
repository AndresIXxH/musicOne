// musicOne.cpp
// Music Listening Report with Menu, Validation, File Output, and Loops
// Uses only Chapters 1–4
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main() {
    // === Variables (declared once, reused each loop) ===
    string favoriteGenre;
    string favoriteArtist;
    double hoursPerWeek = 0.0;
    double hoursPerYear = 0.0;
    int numPlaylists = 0;  // NEW: int input for mixed types
    char menuChoice;
    string skillLevel;
    string recommendation;  // NEW: for second compound if/else
    char continueEntry;     // NEW: for do-while loop
    ofstream outFile;
    bool keepRunning = true; // controls the main loop
    bool firstRun = true;    // NEW: controls banner to print only once

    while (keepRunning) {
        // === Friendly Introduction Banner (only on first run) ===
        if (firstRun) {
            cout << "***************************************************" << endl;
            cout << "* Welcome to Your Music Listening Report! *" << endl;
            cout << "* Discover your weekly and yearly music habits *" << endl;
            cout << "***************************************************" << endl;
            cout << endl;
            firstRun = false;
        }

        // === MENU ===
        cout << "Please choose an option:" << endl;
        cout << " 1 = Enter new listening session" << endl;
        cout << " 2 = View weekly report" << endl;
        cout << " 3 = Get skill level recommendation" << endl;
        cout << " 4 = Quit program" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> menuChoice;
        cin.ignore(); // clear newline

        switch (menuChoice) {
        case '1': {
            cout << "\n--- Entering New Listening Session ---\n";
            // NEW: do-while loop to repeat entry until user quits
            do {
                // ---- Genre (string with spaces) ----
                cout << "What's your favorite music genre? (e.g., Rock, Pop, Jazz): ";
                getline(cin, favoriteGenre);
                if (favoriteGenre.empty()) {
                    favoriteGenre = "Unknown Genre";
                    cout << "No genre entered. Using 'Unknown Genre'.\n";
                }

                // ---- Artist (string with spaces) ----
                cout << "Who's your favorite band or artist? ";
                getline(cin, favoriteArtist);
                if (favoriteArtist.empty()) {
                    favoriteArtist = "Unknown Artist";
                    cout << "No artist entered. Using 'Unknown Artist'.\n";
                }

                // ---- Hours per week (double) ----
                cout << "How many hours do you listen to music each week? (e.g., 5.5): ";
                cin >> hoursPerWeek;
                if (cin.fail() || hoursPerWeek < 0) {
                    hoursPerWeek = 0.0;
                    cout << "Invalid input. Setting hours to 0.0.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else {
                    cin.ignore(); // consume newline after good number
                }

                // ---- NEW: Playlists (int) ----
                cout << "How many playlists do you have for this genre? ";
                cin >> numPlaylists;
                if (cin.fail() || numPlaylists < 0) {
                    numPlaylists = 0;
                    cout << "Invalid input. Setting playlists to 0.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                else {
                    cin.ignore(); // consume newline
                }

                // ---- Derived value ----
                hoursPerYear = hoursPerWeek * 52;

                // ---- First compound if/else block for skill level ----
                if (hoursPerWeek >= 10 && !favoriteGenre.empty() && !favoriteArtist.empty())
                    skillLevel = "Dedicated Fan";
                else if (hoursPerWeek >= 3 && hoursPerWeek < 10)
                    skillLevel = "Casual Listener";
                else
                    skillLevel = "Just Starting Out";

                // ---- NEW: Second compound if/else block for recommendation ----
                if (hoursPerWeek >= 5 && numPlaylists <= 3) {
                    recommendation = "Explore more playlists!";
                }
                else if (hoursPerWeek < 5 || numPlaylists > 10) {
                    recommendation = "You're balanced—keep jamming!";
                }
                else {
                    recommendation = "Time to build your library.";
                }

                // ---- Console table ----
                cout << endl;
                cout << "=====================================" << endl;
                cout << " Music Listening Summary " << endl;
                cout << "=====================================" << endl;
                cout << left << setw(20) << "Genre:" << favoriteGenre << endl;
                cout << left << setw(20) << "Artist:" << favoriteArtist << endl;
                cout << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << endl;
                cout << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << endl;
                cout << left << setw(20) << "Playlists:" << numPlaylists << endl;
                cout << left << setw(20) << "Skill Level:" << skillLevel << endl;
                cout << left << setw(20) << "Tip:" << recommendation << endl;
                cout << "=====================================" << endl;

                // ---- NEW: for loop that runs a fixed number of times (3 tips) ----
                cout << "\nQuick Tips (Top 3):" << endl;
                for (int i = 1; i <= 3; i++) {
                    cout << "Tip " << i << ": Listen to " << favoriteArtist << " for " << (hoursPerWeek / 3) << " hours today." << endl;
                }

                // ---- Save to file (appends each entry) ----
                outFile.open("report.txt", ios::app); // append mode
                if (outFile.is_open()) {
                    outFile << "=====================================\n";
                    outFile << " Music Listening Summary \n";
                    outFile << "=====================================\n";
                    outFile << left << setw(20) << "Genre:" << favoriteGenre << "\n";
                    outFile << left << setw(20) << "Artist:" << favoriteArtist << "\n";
                    outFile << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << "\n";
                    outFile << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << "\n";
                    outFile << left << setw(20) << "Playlists:" << numPlaylists << "\n";
                    outFile << left << setw(20) << "Skill Level:" << skillLevel << "\n";
                    outFile << left << setw(20) << "Tip:" << recommendation << "\n";
                    outFile << "=====================================\n\n";
                    outFile.close();
                    cout << "Report appended to 'report.txt'\n";
                }
                else {
                    cout << "Error: Could not save to 'report.txt'\n";
                }

                // Prompt to continue do-while
                cout << "\nEnter another session? (y/n): ";
                cin >> continueEntry;
                cin.ignore(); // clear newline

            } while (continueEntry == 'y' || continueEntry == 'Y');

            // after sessions, stay in main while loop – menu will show again
            break;
        }
        case '2': {
            // NEW: Implement view report using while loop for getline
            cout << "\n--- Weekly Report View ---\n";
            ifstream inFile("report.txt");
            if (inFile.is_open()) {
                string line;
                cout << "--- Full Report from report.txt ---\n";
                while (getline(inFile, line)) {
                    cout << line << endl;
                }
                inFile.close();
                cout << "--- End of Report ---\n";
            }
            else {
                cout << "No report.txt found. Enter data in option 1 first!\n";
            }
            break;
        }
        case '3': {
            // NEW: Implement recommendation with compound if/else
            cout << "\n--- Skill Level Recommendation ---\n";
            if (hoursPerWeek == 0) {
                cout << "Enter your data in option 1 to get a personalized recommendation!\n";
            }
            else {
                cout << "Based on " << hoursPerWeek << " hours/week and " << numPlaylists << " playlists:\n";
                if (hoursPerYear >= 500 && numPlaylists >= 5) {
                    cout << "Pro Level: You're a music curator! Try producing a mix.\n";
                }
                else {
                    cout << "Grower Level: " << skillLevel << ". Aim for " << (10 - hoursPerWeek) << " more hours/week.\n";
                }
            }
            break;
        }
        case '4':
            keepRunning = false; // exit the while loop
            break;
        default:
            cout << "\nInvalid choice. Please select 1, 2, 3, or 4.\n";
            break;
        } // end switch
    } // end while (main loop)

    cout << "\nThank you for using the Music Listening Report!\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}
