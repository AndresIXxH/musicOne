// musicOne(6.0).cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h> // For SetConsoleTextAttribute
using namespace std;

enum SkillLevel { BEGINNER, CASUAL, DEDICATED, PRO };

struct MusicSession {
    string genre;
    string artist;
    double hoursPerWeek;
    double hoursPerYear;
    int numPlaylists;
    int playlistSongs[5];
    SkillLevel level;
    string recommendation;
};

// Function prototypes
void displayBanner();
void setConsoleColor(WORD color);
void displayMenu();
string collectStringInput(const string& prompt);
double collectDoubleInput(const string& prompt);
int collectIntInput(const string& prompt);
string convertSkillToString(SkillLevel sl);
double calculateAverageSongs(const int songs[], int num);
void fillSession(MusicSession& session);
void calculateSession(MusicSession& session);
void displaySummary(const MusicSession& session);
void saveReportToFile(const MusicSession& session);
void displayQuickTips(const string& favoriteArtist, double hoursPerWeek, SkillLevel skillLevel);
void displayOverallSummary(const MusicSession sessions[], int numSessions);
const int MAX_PLAYLISTS = 5;
const int MAX_SESSIONS = 10;

int main() {
    MusicSession allSessions[MAX_SESSIONS];
    int numSessions = 0;
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
                if (numSessions >= MAX_SESSIONS) {
                    cout << "Maximum " << MAX_SESSIONS << " sessions supported. Cannot add more.\n";
                    break;
                }
                fillSession(allSessions[numSessions]);
                calculateSession(allSessions[numSessions]);
                displaySummary(allSessions[numSessions]);
                displayQuickTips(allSessions[numSessions].artist, allSessions[numSessions].hoursPerWeek, allSessions[numSessions].level);
                saveReportToFile(allSessions[numSessions]);
                numSessions++;
                cout << "\nEnter another session? (y/n): ";
                cin >> continueEntry;
                cin.ignore();
            } while (continueEntry == 'y' || continueEntry == 'Y');
            break;
        }
        case '2':
            displayOverallSummary(allSessions, numSessions);
            break;
        case '3': {
            cout << "\n--- Skill Level Recommendation ---\n";
            if (numSessions == 0) {
                cout << "Enter data in option 1 first!\n";
            }
            else {
                const MusicSession& lastSession = allSessions[numSessions - 1];
                cout << "Based on " << fixed << setprecision(1) << lastSession.hoursPerWeek
                    << " hours/week and " << lastSession.numPlaylists << " playlists:\n";
                SkillLevel sl = lastSession.level;
                string levelStr = convertSkillToString(sl);
                if (sl >= DEDICATED)
                    cout << "Advanced Level: You're a music curator! Try producing a mix.\n";
                else
                    cout << "Grower Level: " << levelStr
                        << ". Aim for " << fixed << setprecision(1) << (10.0 - lastSession.hoursPerWeek)
                        << " more hours/week to reach Dedicated Fan.\n";
            }
            break;
        }
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
    cout << " 2 = View overall summary\n";
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
void fillSession(MusicSession& session) {
    session.genre = collectStringInput("What's your favorite music genre? (e.g., Rock, Pop, Jazz): ");
    session.artist = collectStringInput("Who's your favorite band or artist? ");
    session.hoursPerWeek = collectDoubleInput("How many hours do you listen to music each week? (e.g., 5.5): ");
    session.numPlaylists = collectIntInput("How many playlists do you have for this genre? ");
    if (session.numPlaylists > MAX_PLAYLISTS) {
        cout << "Maximum " << MAX_PLAYLISTS << " playlists supported.\n";
        session.numPlaylists = MAX_PLAYLISTS;
    }
    for (int j = 0; j < MAX_PLAYLISTS; ++j) {
        session.playlistSongs[j] = 0;
    }
    for (int i = 0; i < session.numPlaylists; ++i) {
        string prompt = "How many songs in playlist " + to_string(i + 1) + "? (e.g., 20): ";
        session.playlistSongs[i] = collectIntInput(prompt);
        if (session.playlistSongs[i] == 0) {
            cout << "Assuming 10 songs for empty playlist.\n";
            session.playlistSongs[i] = 10;
        }
    }
    session.hoursPerYear = 0.0;
    session.level = BEGINNER;
    session.recommendation = "";
}
void calculateSession(MusicSession& session) {
    session.hoursPerYear = session.hoursPerWeek * 52;
    double avgSongs = calculateAverageSongs(session.playlistSongs, session.numPlaylists);
    if (session.hoursPerWeek >= 15) session.level = PRO;
    else if (session.hoursPerWeek >= 10) session.level = DEDICATED;
    else if (session.hoursPerWeek >= 3) session.level = CASUAL;
    else session.level = BEGINNER;
    if (session.hoursPerWeek >= 5 && avgSongs < 15)
        session.recommendation = "Your playlists are short - add more songs!";
    else if (avgSongs > 50)
        session.recommendation = "Impressive library size! Consider sharing.";
    else
        session.recommendation = "Balanced collection - keep discovering.";
}
void displaySummary(const MusicSession& session) {
    double avgSongs = calculateAverageSongs(session.playlistSongs, session.numPlaylists);
    cout << "\n=====================================\n";
    cout << " Music Listening Summary\n";
    cout << "=====================================\n";
    cout << left << setw(20) << "Genre:" << session.genre << endl;
    cout << left << setw(20) << "Artist:" << session.artist << endl;
    cout << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << session.hoursPerWeek << endl;
    cout << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << session.hoursPerYear << endl;
    cout << left << setw(20) << "Playlists:" << session.numPlaylists << endl;
    cout << left << setw(20) << "Skill Level:" << convertSkillToString(session.level) << endl;
    cout << left << setw(20) << "Tip:" << session.recommendation << endl;
    cout << left << setw(20) << "Avg Songs/Playlist:" << fixed << setprecision(0) << avgSongs << endl;
    cout << "=====================================\n";
}
void saveReportToFile(const MusicSession& session) {
    ofstream file("report.txt", ios::app);
    double avgSongs = calculateAverageSongs(session.playlistSongs, session.numPlaylists);
    if (file.is_open()) {
        file << "=====================================\n";
        file << " Music Listening Summary\n";
        file << "=====================================\n";
        file << left << setw(20) << "Genre:" << session.genre << "\n";
        file << left << setw(20) << "Artist:" << session.artist << "\n";
        file << left << setw(20) << "Hours/Week:" << fixed << setprecision(1) << session.hoursPerWeek << "\n";
        file << left << setw(20) << "Hours/Year:" << fixed << setprecision(1) << session.hoursPerYear << "\n";
        file << left << setw(20) << "Playlists:" << session.numPlaylists << "\n";
        file << left << setw(20) << "Skill Level:" << convertSkillToString(session.level) << "\n";
        file << left << setw(20) << "Tip:" << session.recommendation << "\n";
        file << left << setw(20) << "Avg Songs/Playlist:" << fixed << setprecision(0) << avgSongs << "\n";
        file << "Playlist Details:\n";
        for (int i = 0; i < session.numPlaylists; ++i) {
            file << " Playlist " << (i + 1) << ": " << session.playlistSongs[i] << " songs\n";
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
void displayOverallSummary(const MusicSession sessions[], int numSessions) {
    if (numSessions == 0) {
        cout << "\n--- Overall Summary ---\n";
        cout << "No sessions entered yet.\n";
        cout << "=====================================\n";
        return;
    }
    cout << "\n--- Overall Summary Across " << numSessions << " Sessions ---\n";
    double totalHoursWeek = 0.0;
    int totalPlaylists = 0;
    double maxHours = 0.0;
    string mostHoursArtist = "";
    int maxNumPL = 0;
    double totalHoursYear = 0.0;
    for (int i = 0; i < numSessions; ++i) {
        totalHoursWeek += sessions[i].hoursPerWeek;
        totalPlaylists += sessions[i].numPlaylists;
        totalHoursYear += sessions[i].hoursPerYear;
        if (sessions[i].hoursPerWeek > maxHours) {
            maxHours = sessions[i].hoursPerWeek;
            mostHoursArtist = sessions[i].artist;
        }
        if (sessions[i].numPlaylists > maxNumPL) {
            maxNumPL = sessions[i].numPlaylists;
        }
    }
    double avgHoursWeek = totalHoursWeek / numSessions;
    double avgPL = static_cast<double>(totalPlaylists) / numSessions;
    double avgHoursYear = totalHoursYear / numSessions;
    cout << "Average hours per week: " << fixed << setprecision(1) << avgHoursWeek << " hours\n";
    cout << "Average number of playlists per session: " << fixed << setprecision(1) << avgPL << "\n";
    cout << "Artist with most listening time: " << mostHoursArtist << " (" << fixed << setprecision(1) << maxHours << " hrs/week)\n";
    cout << "Maximum playlists in any session: " << maxNumPL << "\n";
    cout << "Average hours per year: " << fixed << setprecision(1) << avgHoursYear << " hours\n";
    cout << "=====================================\n";
}
