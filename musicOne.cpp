// musicOne.cpp
// Music Listening Report Generator
// Demonstrates: OOP, input validation, file I/O, string formatting, RAII, modern C++

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include <cctype>

class MusicReport {
private:
    std::string genre;
    std::string artist;
    double hoursPerWeek;
    static constexpr int WEEKS_PER_YEAR = 52;

    // Clear invalid input
    static void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Trim whitespace
    static std::string trim(const std::string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t\r\n");
        return str.substr(first, last - first + 1);
    }

    // Title case: "indie rock" → "Indie Rock"
    static std::string toTitleCase(std::string s) {
        bool newWord = true;
        for (char& c : s) {
            if (std::isalpha(c)) {
                c = newWord ? std::toupper(c) : std::tolower(c);
                newWord = false;
            } else if (std::isspace(c)) {
                newWord = true;
            }
        }
        return s;
    }

    // Get non-empty string with default
    std::string getString(const std::string& prompt, const std::string& defaultVal) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin >> std::ws, input);
        input = trim(input);
        if (input.empty()) {
            std::cout << "No input. Using '" << defaultVal << "'.\n";
            return defaultVal;
        }
        return toTitleCase(input);
    }

    // Get valid hours (0–168)
    double getHours() {
        double h;
        do {
            std::cout << "How many hours do you listen to music each week? (e.g., 5.5): ";
            std::cin >> h;
            if (std::cin.fail() || h < 0 || h > 168) {
                std::cout << "Invalid. Enter 0–168.\n";
                clearInput();
            } else {
                clearInput();
                return h;
            }
        } while (true);
    }

    // Print report to any stream
    static void print(std::ostream& os, const std::string& g, const std::string& a, double w, double y) {
        os << "=====================================\n";
        os << " Music Listening Summary \n";
        os << "=====================================\n";
        os << std::left << std::setw(20) << "Favorite Genre:" << g << "\n";
        os << std::left << std::setw(20) << "Favorite Artist:" << a << "\n";
        os << std::left << std::setw(20) << "Hours per Week:" << std::fixed << std::setprecision(1) << w << "\n";
        os << std::left << std::setw(20) << "Hours per Year:" << std::fixed << std::setprecision(1) << y << "\n";
        os << "=====================================\n";
    }

public:
    void run() {
        // Banner
        std::cout << "********************************************\n";
        std::cout << "* Welcome to the Music Listening Report! *\n";
        std::cout << "* Let's analyze your music listening habits! *\n";
        std::cout << "********************************************\n\n";

        // Input
        genre = getString("What's your favorite music genre? (e.g., Rock, Pop, Jazz): ", "Unknown Genre");
        artist = getString("Who's your favorite band or artist? ", "Unknown Artist");
        hoursPerWeek = getHours();
        double hoursPerYear = hoursPerWeek * WEEKS_PER_YEAR;

        // Console
        std::cout << "\n";
        print(std::cout, genre, artist, hoursPerWeek, hoursPerYear);

        // File
        {
            std::ofstream file("report.txt");
            if (file.is_open()) {
                print(file, genre, artist, hoursPerWeek, hoursPerYear);
                std::cout << "Report saved to 'report.txt'\n";
            } else {
                std::cout << "Error: Could not save file.\n";
            }
        }
    }
};

int main() {
    try {
        MusicReport report;
        report.run();
    }
    catch (...) {
        std::cerr << "Unexpected error.\n";
        return 1;
    }

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
