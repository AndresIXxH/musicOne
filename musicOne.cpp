// MusicOne 8.0
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <windows.h> // For SetConsoleTextAttribute
#include <array>
using namespace std;

enum SkillLevel { BEGINNER, CASUAL, DEDICATED, PRO };

struct MusicSession {
    string genre;
    string artist;
    double hoursPerWeek = 0.0;
    double hoursPerYear = 0.0;
    int numPlaylists = 0;
    array<int, 5> playlistSongs{}; // Initializes all to 0
    SkillLevel level = BEGINNER;
    string recommendation;
};

class MusicTracker {
private:
    static const int MAX_SESSIONS = 10;
    static const int MAX_PLAYLISTS = 5;
    MusicSession sessions[MAX_SESSIONS];
    int numSessions = 0;

    void setConsoleColor(WORD color) const {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    string convertSkillToString(SkillLevel sl) const {
        switch (sl) {
        case BEGINNER: return "Just Starting Out";
        case CASUAL: return "Casual Listener";
        case DEDICATED: return "Dedicated Fan";
        case PRO: return "Pro Curator";
        default: return "Unknown";
        }
    }

    double calculateAverageSongs(const array<int, 5>& songs, int num) const {
        if (num == 0) return 0.0;
        double sum = 0.0;
        for (int i = 0; i < num; ++i) {
            sum += songs[i];
        }
        return sum / num;
    }

    void calculateSession(MusicSession& session) const {
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

    void displayQuickTips(const MusicSession& session) const {
        cout << "\nQuick Tips (Top 3 for your level):\n";
        switch (session.level) {
        case BEGINNER:
            cout << "Tip 1: Start with 30-minute sessions of " << session.artist << ".\n";
            cout << "Tip 2: Create your first playlist.\n";
            cout << "Tip 3: Listen actively to lyrics.\n";
            break;
        case CASUAL:
            cout << "Tip 1: Dedicate " << fixed << setprecision(1) << (session.hoursPerWeek + 1) << " hours this week.\n";
            cout << "Tip 2: Explore similar artists.\n";
            cout << "Tip 3: Share a playlist with friends.\n";
            break;
        case DEDICATED:
            cout << "Tip 1: Analyze " << session.artist << "'s discography.\n";
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

public:
    MusicTracker() {
        // Constructor initializes everything to zero/safe state (already done via defaults)
        setConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); // Bright cyan
    }

    ~MusicTracker() {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // default white
    }

    void displayBanner() const {
        cout << "***************************************************\n";
        cout << "*     Welcome to Your Music Listening Tracker!    *\n";
        cout << "*   Discover your weekly and yearly music habits  *\n";
        cout << "***************************************************\n\n";
    }

    void displayMenu() const {
        cout << "Please choose an option:\n";
        cout << " 1 = Enter new listening session\n";
        cout << " 2 = View overall summary\n";
        cout << " 3 = Get skill level recommendation\n";
        cout << " 4 = Quit program\n";
        cout << "Enter your choice (1-4): ";
    }

    string collectStringInput(const string& prompt) const {
        string s;
        cout << prompt;
        getline(cin, s);
        if (s.empty()) {
            cout << "Nothing entered - using 'Unknown'.\n";
            return "Unknown";
        }
        return s;
    }

    double collectDoubleInput(const string& prompt) const {
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

    int collectIntInput(const string& prompt) const {
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

    void addSession() {
        if (numSessions >= MAX_SESSIONS) {
            cout << "Maximum " << MAX_SESSIONS << " sessions supported. Cannot add more.\n";
            return;
        }

        MusicSession& session = sessions[numSessions];
        cout << "\n--- Entering New Listening Session ---\n";

        session.genre = collectStringInput("What's your favorite music genre? (e.g., Rock, Pop, Jazz): ");
        session.artist = collectStringInput("Who's your favorite band or artist? ");
        session.hoursPerWeek = collectDoubleInput("How many hours do you listen to music each week? (e.g., 5.5): ");
        session.numPlaylists = collectIntInput("How many playlists do you have for this genre? ");

        if (session.numPlaylists > MAX_PLAYLISTS) {
            cout << "Maximum " << MAX_PLAYLISTS << " playlists supported.\n";
            session.numPlaylists = MAX_PLAYLISTS;
        }

        session.playlistSongs.fill(0); // Reset array

        for (int i = 0; i < session.numPlaylists; ++i) {
            string prompt = "How many songs in playlist " + to_string(i + 1) + "? (e.g., 20): ";
            session.playlistSongs[i] = collectIntInput(prompt);
            if (session.playlistSongs[i] == 0) {
                cout << "Assuming 10 songs for empty playlist.\n";
                session.playlistSongs[i] = 10;
            }
        }

        calculateSession(session);
        displaySummary(session);
        displayQuickTips(session);
        saveReportToFile(session);

        numSessions++;
    }

    void displaySummary(const MusicSession& session) const {
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

    void saveReportToFile(const MusicSession& session) const {
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

    void displayOverallSummary() const {
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

    void displaySkillRecommendation() const {
        cout << "\n--- Skill Level Recommendation ---\n";
        if (numSessions == 0) {
            cout << "Enter data in option 1 first!\n";
            return;
        }
        const MusicSession& lastSession = sessions[numSessions - 1];
        cout << "Based on " << fixed << setprecision(1) << lastSession.hoursPerWeek
            << " hours/week and " << lastSession.numPlaylists << " playlists:\n";
        string levelStr = convertSkillToString(lastSession.level);
        if (lastSession.level >= DEDICATED)
            cout << "Advanced Level: You're a music curator! Try producing a mix.\n";
        else
            cout << "Grower Level: " << levelStr
            << ". Aim for " << fixed << setprecision(1) << (10.0 - lastSession.hoursPerWeek)
            << " more hours/week to reach Dedicated Fan.\n";
    }

    void run() {
        bool firstRun = true;
        bool keepRunning = true;
        char menuChoice;

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
                char continueEntry;
                do {
                    addSession();
                    if (numSessions < MAX_SESSIONS) {
                        cout << "\nEnter another session? (y/n): ";
                        cin >> continueEntry;
                        cin.ignore();
                    }
                    else {
                        continueEntry = 'n';
                    }
                } while (continueEntry == 'y' || continueEntry == 'Y');
                break;
            }
            case '2':
                displayOverallSummary();
                break;
            case '3':
                displaySkillRecommendation();
                break;
            case '4':
                keepRunning = false;
                break;
            default:
                cout << "\nInvalid choice. Please enter 1-4.\n";
                break;
            }
        }
        cout << "\nThank you for using the Music Listening Tracker!\n";
        cout << "Press Enter to exit...";
        cin.get();
    }
};

int main() {
    MusicTracker tracker;
    tracker.run();
    return 0;
}
