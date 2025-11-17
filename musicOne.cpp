// musicOne.cpp
// Music Listening Report with Menu, Validation, File Output, Loops, Functions, and Console Color
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h>  // For console color on Windows (covered in class extensions)
using namespace std;

// Function prototypes
void displayBanner();
void setConsoleColor(WORD color);
void displayMenu();
string collectStringInput(string prompt);
double collectDoubleInput(string prompt);
int collectIntInput(string prompt);
bool validateDouble(double value);
bool validateInt(int value);
bool validateString(string str);
void performCalculations(double hoursPerWeek, int numPlaylists, double& hoursPerYear, string& skillLevel, string& recommendation);
void displaySummary(string favoriteGenre, string favoriteArtist, double hoursPerWeek, double hoursPerYear, int numPlaylists, string skillLevel, string recommendation);
void saveReportToFile(string favoriteGenre, string favoriteArtist, double hoursPerWeek, double hoursPerYear, int numPlaylists, string skillLevel, string recommendation);
void displayQuickTips(string favoriteArtist, double hoursPerWeek);
void viewReportFromFile();

int main() {
    // === Variables (declared once, reused each loop) ===
    string favoriteGenre;
    string favoriteArtist;
    double hoursPerWeek = 0.0;
    double hoursPerYear = 0.0;
    int numPlaylists = 0;
    string skillLevel;  // Moved declaration here for scope across cases
    string recommendation;  // Moved declaration here for scope across cases
    char menuChoice;
    char continueEntry;
    bool keepRunning = true;
    bool firstRun = true;

    // Set initial console color for prettiness
    setConsoleColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);  // Light cyan

    while (keepRunning) {
        // === Friendly Introduction Banner (only on first run) ===
        if (firstRun) {
            displayBanner();
            firstRun = false;
        }
        // === MENU ===
        displayMenu();
        cin >> menuChoice;
        cin.ignore(); // clear newline
        switch (menuChoice) {
        case '1': {
            cout << "\n--- Entering New Listening Session ---\n";
            // do-while loop to repeat entry until user quits
            do {
                // Collect inputs using functions
                favoriteGenre = collectStringInput("What's your favorite music genre? (e.g., Rock, Pop, Jazz): ");
                favoriteArtist = collectStringInput("Who's your favorite band or artist? ");
                hoursPerWeek = collectDoubleInput("How many hours do you listen to music each week? (e.g., 5.5): ");
                numPlaylists = collectIntInput("How many playlists do you have for this genre? ");

                // Perform calculations using function (fixed: correct params, no extra)
                performCalculations(hoursPerWeek, numPlaylists, hoursPerYear, skillLevel, recommendation);

                // Display summary
                displaySummary(favoriteGenre, favoriteArtist, hoursPerWeek, hoursPerYear, numPlaylists, skillLevel, recommendation);

                // Display tips with for loop
                displayQuickTips(favoriteArtist, hoursPerWeek);

                // Save to file using function
                saveReportToFile(favoriteGenre, favoriteArtist, hoursPerWeek, hoursPerYear, numPlaylists, skillLevel, recommendation);

                // Prompt to continue do-while
                cout << "\nEnter another session? (y/n): ";
                cin >> continueEntry;
                cin.ignore(); // clear newline
            } while (continueEntry == 'y' || continueEntry == 'Y');
            break;
        }
        case '2': {
            // View report using while loop for getline
            viewReportFromFile();
            break;
        }
        case '3': {
            // Recommendation with compound if/else (using last entered values)
            cout << "\n--- Skill Level Recommendation ---\n";
            if (hoursPerWeek == 0) {
                cout << "Enter your data in option 1 to get a personalized recommendation!\n";
            }
            else {
                cout << "Based on " << hoursPerWeek << " hours/week and " << numPlaylists << " playlists:\n";
                // Compound if/else
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

    // Reset color to default before exit
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    cout << "\nThank you for using the Music Listening Report!\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}

// Function to display the welcome banner
void displayBanner() {
    cout << "***************************************************" << endl;
    cout << "* Welcome to Your Music Listening Report! *" << endl;
    cout << "* Discover your weekly and yearly music habits *" << endl;
    cout << "***************************************************" << endl;
    cout << endl;
}

// Function to change console text color (Windows-specific)
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to display the menu
void displayMenu() {
    cout << "Please choose an option:" << endl;
    cout << " 1 = Enter new listening session" << endl;
    cout << " 2 = View weekly report" << endl;
    cout << " 3 = Get skill level recommendation" << endl;
    cout << " 4 = Quit program" << endl;
    cout << "Enter your choice (1-4): ";
}

// Function to collect and validate string input
string collectStringInput(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    if (!validateString(input)) {
        input = "Unknown";
        cout << "No input entered. Using 'Unknown'.\n";
    }
    return input;
}

// Function to collect and validate double input
double collectDoubleInput(string prompt) {
    double value;
    cout << prompt;
    cin >> value;
    if (cin.fail() || !validateDouble(value)) {
        value = 0.0;
        cout << "Invalid input. Setting to 0.0.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    else {
        cin.ignore(); // consume newline
    }
    return value;
}

// Function to collect and validate int input
int collectIntInput(string prompt) {
    int value;
    cout << prompt;
    cin >> value;
    if (cin.fail() || !validateInt(value)) {
        value = 0;
        cout << "Invalid input. Setting to 0.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    else {
        cin.ignore(); // consume newline
    }
    return value;
}

// Validation functions
bool validateString(string str) {
    return !str.empty();
}

bool validateDouble(double value) {
    return value >= 0;
}

bool validateInt(int value) {
    return value >= 0;
}

// Function to perform calculations and set skill level/recommendation
void performCalculations(double hoursPerWeek, int numPlaylists, double& hoursPerYear, string& skillLevel, string& recommendation) {
    hoursPerYear = hoursPerWeek * 52;
    // First compound if/else for skill level
    if (hoursPerWeek >= 10) {  // Assuming non-empty strings as validated
        skillLevel = "Dedicated Fan";
    }
    else if (hoursPerWeek >= 3 && hoursPerWeek < 10) {
        skillLevel = "Casual Listener";
    }
    else {
        skillLevel = "Just Starting Out";
    }
    // Second compound if/else for recommendation
    if (hoursPerWeek >= 5 && numPlaylists <= 3) {
        recommendation = "Explore more playlists!";
    }
    else if (hoursPerWeek < 5 || numPlaylists > 10) {
        recommendation = "You're balanced! Keep jamming!";
    }
    else {
        recommendation = "Time to build your library.";
    }
}

// Function to display the summary table
void displaySummary(string favoriteGenre, string favoriteArtist, double hoursPerWeek, double hoursPerYear, int numPlaylists, string skillLevel, string recommendation) {
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
}

// Function to save report to file
void saveReportToFile(string favoriteGenre, string favoriteArtist, double hoursPerWeek, double hoursPerYear, int numPlaylists, string skillLevel, string recommendation) {
    ofstream outFile("report.txt", ios::app); // append mode
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
}

// Function to display quick tips with for loop
void displayQuickTips(string favoriteArtist, double hoursPerWeek) {
    cout << "\nQuick Tips (Top 3):" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "Tip " << i << ": Listen to " << favoriteArtist << " for " << (hoursPerWeek / 3) << " hours today." << endl;
    }
}

// Function to view report from file using while loop
void viewReportFromFile() {
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
}
