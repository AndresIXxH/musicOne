// musicOne(6.0).cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h> // For SetConsoleTextAttribute
using namespace std;

enum SkillLevel { BEGINNER, CASUAL, DEDICATED, PRO };

// Function prototypes
void displayBanner();
void setConsoleColor(WORD color);
void displayMenu();
string collectStringInput(const string& prompt);
double collectDoubleInput(const string& prompt);
int collectIntInput(const string& prompt);
string convertSkillToString(SkillLevel sl);
double calculateAverageSongs(const int songs[], int num);
void performCalculations(double hoursPerWeek, int numPlaylists, const int playlistSongs[], double& hoursPerYear,
    SkillLevel& skillLevel, string& recommendation);
void displaySummary(const string& favoriteGenre, const string& favoriteArtist,
    double hoursPerWeek, double hoursPerYear, int numPlaylists,
    const SkillLevel& skillLevel, const string& recommendation, const int playlistSongs[]);
void saveReportToFile(const string& favoriteGenre, const string& favoriteArtist,
    double hoursPerWeek, double hoursPerYear, int numPlaylists,
    const SkillLevel& skillLevel, const string& recommendation, const int playlistSongs[]);
void displayQuickTips(const string& favoriteArtist, double hoursPerWeek, SkillLevel skillLevel);
void viewReportFromFile();

int main() {
    string favoriteGenre = "Unknown", favoriteArtist = "Unknown";
    string recommendation;
    double hoursPerWeek = 0.0, hoursPerYear = 0.0;
    int numPlaylists = 0;
    const int MAX_PLAYLISTS = 5;
    int playlistSongs[MAX_PLAYLISTS] = {0};  // Initialize to 0
    char menuChoice = ' ', continueEntry = ' ';
    bool keepRunning = true;
    bool firstRun = true;
    setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); // Bright cyan
    while (keepRunning) {
        if (firstRun) {
            displayBanner();
            firstRun = false;
        }
        displayMenu();
        cin >> menuChoice;
        cin.ignore();
        switch (menuChoice) {
        case '1': {
            cout << "\n--- Entering New Listening Session ---\n";
            do {
                favoriteGenre = collectStringInput("What's your favorite music genre? (e.g., Rock, Pop, Jazz): ");
                favoriteArtist = collectStringInput("Who's your favorite band or artist? ");
                hoursPerWeek = collectDoubleInput("How many hours do you listen to music each week? (e.g., 5.5): ");
                numPlaylists = collectIntInput("How many playlists do you have for this genre? ");
                if (numPlaylists > MAX_PLAYLISTS) {
                    cout << "Maximum " << MAX_PLAYLISTS << " playlists supported.\n";
                    numPlaylists = MAX_PLAYLISTS;
                }
                for (int i = 0; i < numPlaylists; ++i) {
                    string prompt = "How many songs in playlist " + to_string(i + 1) + "? (e.g., 20): ";
                    playlistSongs[i] = collectIntInput(prompt);
                    if (playlistSongs[i] == 0) {
                        cout << "Assuming 10 songs for empty playlist.\n";
                        playlistSongs[i] = 10;
                    }
                }
                SkillLevel sl = BEGINNER;  // Default
                performCalculations(hoursPerWeek, numPlaylists, playlistSongs, hoursPerYear, sl, recommendation);
                displaySummary(favoriteGenre, favoriteArtist, hoursPerWeek, hoursPerYear,
                    numPlaylists, sl, recommendation, playlistSongs);
                displayQuickTips(favoriteArtist, hoursPerWeek, sl);
                saveReportToFile(favoriteGenre, favoriteArtist, hoursPerWeek, hoursPerYear,
                    numPlaylists, sl, recommendation, playlistSongs);
                cout << "\nEnter another session? (y/n): ";
                cin >> continueEntry;
                cin.ignore();
            } while (continueEntry == 'y' || continueEntry == 'Y');
            break;
        }
        case '2':
            viewReportFromFile();
            break;
        case '3':
            cout << "\n--- Skill Level Recommendation ---\n";
            if (hoursPerWeek == 0.0) {
                cout << "Enter data in option 1 first!\n";
            }
            else {
                cout << "Based on " << fixed << setprecision(1) << hoursPerWeek
                    << " hours/week and " << numPlaylists << " playlists:\n";
                SkillLevel sl;
                // Recompute skill level for last session (simplified)
                if (hoursPerWeek >= 15) sl = PRO;
                else if (hoursPerWeek >= 10) sl = DEDICATED;
                else if (hoursPerWeek >= 3) sl = CASUAL;
                else sl = BEGINNER;
                string levelStr = convertSkillToString(sl);
                if (sl >= DEDICATED)
                    cout << "Advanced Level: You're a music curator! Try producing a mix.\n";
                else
                    cout << "Grower Level: " << levelStr
                        << ". Aim for " << fixed << setprecision(1) << (10.0 - hoursPerWeek)
                        << " more hours/week to reach Dedicated Fan.\n";
            }
            break;
        case '4':
            keepRunning = false;
            break;
        default:
            cout << "\nInvalid choice. Please enter 1-4.\n";
            break;
        }
    }
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // default white
    cout << "\nThank you for using the Music Listening Report!\n";
    cout << "Press Enter to exit...";
    cin.get();
    return 0;
}
// ==================== Functions ====================
void displayBanner() {
    cout << "***************************************************\n";
    cout << "* Welcome to Your Music Listening Report! *\n";
    cout << "* Discover your weekly and yearly music habits *\n";
    cout << "***************************************************\n\n";
}

void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void displayMenu() {
    cout << "Please choose an option:\n";
    cout << " 1 = Enter new listening session\n";
    cout << " 2 = View weekly report\n";
    cout << " 3 = Get skill level recommendation\n";
    cout << " 4 = Quit program\n";
    cout << "Enter your choice (1-4): ";
}

string collectStringInput(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    if (s.empty()) {
        cout << "Nothing entered - using 'Unknown'.\n";
        return "Unknown";
    }
    return s;
}

double collectDoubleInput(const string& prompt) {
    double d;
    cout << prompt;
    cin >> d;
    if (cin.fail() || d < 0) {
        cout << "Invalid - using 0.0\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return 0.0;
    }
    cin.ignore();
    return d;
}

int collectIntInput(const string& prompt) {
    int i;
    cout << prompt;
    cin >> i;
    if (cin.fail() || i < 0) {
        cout << "Invalid - using 0\n";
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }
    cin.ignore();
    return i;
}

string convertSkillToString(SkillLevel sl) {
    switch (sl) {
    case BEGINNER: return "Just Starting Out";
    case CASUAL: return "Casual Listener";
    case DEDICATED: return "Dedicated Fan";
    case PRO: return "Pro Curator";
    default: return "Unknown";
    }
}

double calculateAverageSongs(const int songs[], int num) {
    if (num == 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < num; ++i) {
        sum += songs[i];
    }
    return sum / num;
}

void performCalculations(double hoursPerWeek, int numPlaylists, const int playlistSongs[], double& hoursPerYear,
    SkillLevel& skillLevel, string& recommendation) {
    hoursPerYear = hoursPerWeek * 52;
    double avgSongs = calculateAverageSongs(playlistSongs, numPlaylists);
    if (hoursPerWeek >= 15) skillLevel = PRO;
    else if (hoursPerWeek >= 10) skillLevel = DEDICATED;
    else if (hoursPerWeek >= 3) skillLevel = CASUAL;
    else skillLevel = BEGINNER;
    if (hoursPerWeek >= 5 && avgSongs < 15)
        recommendation = "Your playlists are short - add more songs!";
    else if (avgSongs > 50)
        recommendation = "Impressive library size! Consider sharing.";
    else
        recommendation = "Balanced collection - keep discovering.";
}

void displaySummary(const string& favoriteGenre, const string& favoriteArtist,
    double hoursPerWeek, double hoursPerYear, int numPlaylists,
    const SkillLevel& skillLevel, const string& recommendation, const int playlistSongs[]) {
    double avgSongs = calculateAverageSongs(playlistSongs, numPlaylists);
    cout << "\n=====================================\n";
    cout << " Music Listening Summary\n";
    cout << "=====================================\n";
    cout << left << setw(20) << "Genre:" << favoriteGenre << endl;
    cout << left << setw(20) << "Artist:" << favoriteArtist << endl;
    cout << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << endl;
    cout << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << endl;
    cout << left << setw(20) << "Playlists:" << numPlaylists << endl;
    cout << left << setw(20) << "Skill Level:" << convertSkillToString(skillLevel) << endl;
    cout << left << setw(20) << "Tip:" << recommendation << endl;
    cout << left << setw(20) << "Avg Songs/Playlist:" << fixed << setprecision(0) << avgSongs << endl;
    cout << "=====================================\n";
}

void saveReportToFile(const string& favoriteGenre, const string& favoriteArtist,
    double hoursPerWeek, double hoursPerYear, int numPlaylists,
    const SkillLevel& skillLevel, const string& recommendation, const int playlistSongs[]) {
    ofstream file("report.txt", ios::app);
    double avgSongs = calculateAverageSongs(playlistSongs, numPlaylists);
    if (file.is_open()) {
        file << "=====================================\n";
        file << " Music Listening Summary\n";
        file << "=====================================\n";
        file << left << setw(20) << "Genre:" << favoriteGenre << "\n";
        file << left << setw(20) << "Artist:" << favoriteArtist << "\n";
        file << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << hoursPerWeek << "\n";
        file << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << hoursPerYear << "\n";
        file << left << setw(20) << "Playlists:" << numPlaylists << "\n";
        file << left << setw(20) << "Skill Level:" << convertSkillToString(skillLevel) << "\n";
        file << left << setw(20) << "Tip:" << recommendation << "\n";
        file << left << setw(20) << "Avg Songs/Playlist:" << fixed << setprecision(0) << avgSongs << "\n";
        file << "Playlist Details:\n";
        for (int i = 0; i < numPlaylists; ++i) {
            file << "  Playlist " << (i + 1) << ": " << playlistSongs[i] << " songs\n";
        }
        file << "=====================================\n\n";
        file.close();
        cout << "Report saved to report.txt\n";
    }
    else {
        cout << "Error saving file!\n";
    }
}

void displayQuickTips(const string& favoriteArtist, double hoursPerWeek, SkillLevel skillLevel) {
    cout << "\nQuick Tips (Top 3 for your level):\n";
    switch (skillLevel) {
    case BEGINNER:
        cout << "Tip 1: Start with 30-minute sessions of " << favoriteArtist << ".\n";
        cout << "Tip 2: Create your first playlist.\n";
        cout << "Tip 3: Listen actively to lyrics.\n";
        break;
    case CASUAL:
        cout << "Tip 1: Dedicate " << fixed << setprecision(1) << (hoursPerWeek + 1) << " hours this week.\n";
        cout << "Tip 2: Explore similar artists.\n";
        cout << "Tip 3: Share a playlist with friends.\n";
        break;
    case DEDICATED:
        cout << "Tip 1: Analyze " << favoriteArtist << "'s discography.\n";
        cout << "Tip 2: Attend a live show.\n";
        cout << "Tip 3: Mix in new genres.\n";
        break;
    case PRO:
        cout << "Tip 1: Produce a fan remix.\n";
        cout << "Tip 2: Write a review blog.\n";
        cout << "Tip 3: Curate for others.\n";
        break;
    }
}

void viewReportFromFile() {
    cout << "\n--- Weekly Report View ---\n";
    ifstream file("report.txt");
    if (file.is_open()) {
        string line;
        cout << "--- Full Report ---\n";
        while (getline(file, line))
            cout << line << endl;
        file.close();
        cout << "--- End of Report ---\n";
    }
    else {
        cout << "No report.txt found yet. Enter some data first!\n";
    }
}
