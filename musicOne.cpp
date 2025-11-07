// musicOne.cpp
// Music Listening Report with Menu, Validation, File Output, and Loop
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
    char   menuChoice;
    string skillLevel;
    ofstream outFile;

    bool keepRunning = true;               // controls the main loop

    while (keepRunning) {
        // === Friendly Introduction Banner (only on first run) ===
        if (keepRunning) {                 // always true, but keeps banner once
            cout << "***************************************************" << endl;
            cout << "* Welcome to Your Music Listening Report! *" << endl;
            cout << "* Discover your weekly and yearly music habits *" << endl;
            cout << "***************************************************" << endl;
            cout << endl;
        }

        // === MENU ===
        cout << "Please choose an option:" << endl;
        cout << " 1 = Enter new listening session" << endl;
        cout << " 2 = View weekly report" << endl;
        cout << " 3 = Get skill level recommendation" << endl;
        cout << " 4 = Quit program" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> menuChoice;
        cin.ignore();                     // clear newline

        switch (menuChoice) {
        case '1': {
            cout << "\n--- Entering New Listening Session ---\n";

            // ---- Genre ----
            cout << "What's your favorite music genre? (e.g., Rock, Pop, Jazz): ";
            getline(cin, favoriteGenre);
            if (favoriteGenre.empty()) {
                favoriteGenre = "Unknown Genre";
                cout << "No genre entered. Using 'Unknown Genre'.\n";
            }

            // ---- Artist ----
            cout << "Who's your favorite band or artist? ";
            getline(cin, favoriteArtist);
            if (favoriteArtist.empty()) {
                favoriteArtist = "Unknown Artist";
                cout << "No artist entered. Using 'Unknown Artist'.\n";
            }

            // ---- Hours per week ----
            cout << "How many hours do you listen to music each week? (e.g., 5.5): ";
            cin >> hoursPerWeek;
            if (cin.fail() || hoursPerWeek < 0) {
                hoursPerWeek = 0.0;
                cout << "Invalid input. Setting hours to 0.0.\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            else {
                cin.ignore();          // consume newline after good number
            }

            // ---- Derived value ----
            hoursPerYear = hoursPerWeek * 52;

            // ---- Skill level (compound boolean) ----
            if (hoursPerWeek >= 10 && !favoriteGenre.empty() && !favoriteArtist.empty())
                skillLevel = "Dedicated Fan";
            else if (hoursPerWeek >= 3 && hoursPerWeek < 10)
                skillLevel = "Casual Listener";
            else
                skillLevel = "Just Starting Out";

            // ---- Console table ----
            cout << endl;
            cout << "=====================================" << endl;
            cout << " Music Listening Summary " << endl;
            cout << "=====================================" << endl;
            cout << left << setw(20) << "Genre:" << favoriteGenre << endl;
            cout << left << setw(20) << "Artist:" << favoriteArtist << endl;
            cout << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << endl;
            cout << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << endl;
            cout << left << setw(20) << "Skill Level:" << skillLevel << endl;
            cout << "=====================================" << endl;

            // ---- Save to file (appends each entry) ----
            outFile.open("report.txt", ios::app);   // append mode
            if (outFile.is_open()) {
                outFile << "=====================================\n";
                outFile << " Music Listening Summary \n";
                outFile << "=====================================\n";
                outFile << left << setw(20) << "Genre:" << favoriteGenre << "\n";
                outFile << left << setw(20) << "Artist:" << favoriteArtist << "\n";
                outFile << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << "\n";
                outFile << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << "\n";
                outFile << left << setw(20) << "Skill Level:" << skillLevel << "\n";
                outFile << "=====================================\n\n";
                outFile.close();
                cout << "Report appended to 'report.txt'\n";
            }
            else {
                cout << "Error: Could not save to 'report.txt'\n";
            }

            // after a successful entry we **stay in the loop** – menu will show again
            break;
        }

        case '2':
            cout << "\n--- Weekly Report View ---\n";
            cout << "Please run option 1 first to enter your data.\n";
            break;

        case '3':
            cout << "\n--- Skill Level Recommendation ---\n";
            cout << "Enter your data in option 1 to get a personalized recommendation!\n";
            break;

        case '4':
            keepRunning = false;          // exit the while loop
            break;

        default:
            cout << "\nInvalid choice. Please select 1, 2, 3, or 4.\n";
            break;
        } // end switch
    } // end while

    cout << "\nThank you for using the Music Listening Report!\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}
