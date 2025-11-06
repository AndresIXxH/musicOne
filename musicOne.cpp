// musicOne.cpp
// Music Listening Report with Menu, Validation, and File Output
// Uses only Chapters 1–4: iostream, string, iomanip, ofstream, switch, if/else, basic math

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

int main() {
    // === Variables ===
    string favoriteGenre;        // User's favorite music genre
    string favoriteArtist;       // User's favorite band or artist
    double hoursPerWeek;         // Hours listened per week
    double hoursPerYear;         // Calculated: hoursPerWeek * 52
    char menuChoice;             // User's menu selection: '1', '2', or '3'
    string skillLevel;           // Recommendation based on hours and genre/artist input

    // === Friendly Introduction Banner ===
    cout << "***************************************************" << endl;
    cout << "*     Welcome to Your Music Listening Report!     *" << endl;
    cout << "*   Discover your weekly and yearly music habits  *" << endl;
    cout << "***************************************************" << endl;
    cout << endl;

    // === MENU: Selection with switch ===
    cout << "Please choose an option:" << endl;
    cout << "  1 = Enter new listening session" << endl;
    cout << "  2 = View weekly report" << endl;
    cout << "  3 = Get skill level recommendation" << endl;
    cout << "Enter your choice (1, 2, or 3): ";
    cin >> menuChoice;
    cin.ignore(); // Clear newline from input buffer

    // Switch to handle menu
    switch (menuChoice) {
        case '1':
            cout << "\n--- Entering New Listening Session ---\n";

            // Input 1: Favorite genre (string with spaces)
            cout << "What's your favorite music genre? (e.g., Rock, Pop, Jazz): ";
            getline(cin, favoriteGenre);

            // Validate: if empty, use default
            if (favoriteGenre.empty()) {
                favoriteGenre = "Unknown Genre";
                cout << "No genre entered. Using 'Unknown Genre'.\n";
            }

            // Input 2: Favorite artist (string with spaces)
            cout << "Who's your favorite band or artist? ";
            getline(cin, favoriteArtist);

            // Validate: if empty, use default
            if (favoriteArtist.empty()) {
                favoriteArtist = "Unknown Artist";
                cout << "No artist entered. Using 'Unknown Artist'.\n";
            }

            // Input 3: Hours per week (double)
            cout << "How many hours do you listen to music each week? (e.g., 5.5): ";
            cin >> hoursPerWeek;

            // Validate input: check for failure or negative
            if (cin.fail() || hoursPerWeek < 0) {
                hoursPerWeek = 0.0;
                cout << "Invalid input. Setting hours to 0.0.\n";
                cin.clear();                    // Clear error flag
                cin.ignore(10000, '\n');        // Discard bad input
            }

            // Derived value: total hours per year
            hoursPerYear = hoursPerWeek * 52;

            // === Compound Boolean Conditions (if/else) ===
            // Condition 1: High listener with known favorites
            if (hoursPerWeek >= 10 && !favoriteGenre.empty() && !favoriteArtist.empty()) {
                skillLevel = "Dedicated Fan";
            }
            // Condition 2: Casual but consistent
            else if (hoursPerWeek >= 3 && hoursPerWeek < 10) {
                skillLevel = "Casual Listener";
            }
            // Default
            else {
                skillLevel = "Just Starting Out";
            }

            // === Formatted Output Table (Console) ===
            cout << endl;
            cout << "=====================================" << endl;
            cout << "   Music Listening Summary   " << endl;
            cout << "=====================================" << endl;
            cout << left << setw(20) << "Genre:"       << favoriteGenre << endl;
            cout << left << setw(20) << "Artist:"      << favoriteArtist << endl;
            cout << left << setw(20) << "Hours/Week:"  << fixed << setprecision(1) << hoursPerWeek << endl;
            cout << left << setw(20) << "Hours/Year:"  << fixed << setprecision(1) << hoursPerYear << endl;
            cout << left << setw(20) << "Skill Level:" << skillLevel << endl;
            cout << "=====================================" << endl;

            // === Save to File: report.txt ===
            ofstream outFile("report.txt");
            if (outFile.is_open()) {
                outFile << "=====================================\n";
                outFile << "   Music Listening Summary   \n";
                outFile << "=====================================\n";
                outFile << left << setw(20) << "Genre:"       << favoriteGenre << "\n";
                outFile << left << setw(20) << "Artist:"      << favoriteArtist << "\n";
                outFile << left << setw(20) << "Hours/Week:"  << fixed << setprecision(1) << hoursPerWeek << "\n";
                outFile << left << setw(20) << "Hours/Year:"  << fixed << setprecision(1) << hoursPerYear << "\n";
                outFile << left << setw(20) << "Skill Level:" << skillLevel << "\n";
                outFile << "=====================================\n";
                outFile.close();
                cout << "Report successfully saved to 'report.txt'\n";
            }
            else {
                cout << "Error: Could not save to 'report.txt'\n";
            }
            break;

        case '2':
            cout << "\n--- Weekly Report View ---\n";
            cout << "Please run option 1 first to enter your data.\n";
            break;

        case '3':
            cout << "\n--- Skill Level Recommendation ---\n";
            cout << "Enter your data in option 1 to get a personalized recommendation!\n";
            break;

        default:
            cout << "\nInvalid choice. Please select 1, 2, or 3.\n";
            break;
    }

    cout << "\nThank you for using the Music Listening Report!\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}
