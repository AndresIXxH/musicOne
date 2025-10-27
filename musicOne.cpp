// musicOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    string favoriteGenre;      // Variable to store the user's favorite music genre
    string favoriteArtist;    // Variable to store the user's favorite band or artist
    int hoursPerWeek;         // Variable to store hours spent listening to music per week
    int hoursPerYear;         // Variable to calculate hours spent listening per year

    // This prompts user for their favorite music genre
    cout << "Hey music lover! What's your favorite music genre? (e.g., Rock, Pop, Jazz): ";
    getline(cin, favoriteGenre);

    // This prompts user for their favorite band or artist
    cout << "Awesome! Who's your favorite band or artist? ";
    getline(cin, favoriteArtist);

    // This prompts user for hours spent listening to music per week
    cout << "How many hours do you jam out to music each week? ";
    cin >> hoursPerWeek;

    // This calculates total hours spent listening to music in a year (hours per week * 52 weeks)
    hoursPerYear = hoursPerWeek * 52;

    // This displays a fun, personalized paragraph with the user's input and calculation
    cout << endl << "Rock on! You're a huge fan of " << favoriteGenre << " music, especially when it's by "
        << favoriteArtist << "! Listening for " << hoursPerWeek
        << " hours a week means you spend a whopping " << hoursPerYear
        << " hours a year grooving to your favorite tunes. Keep the music flowing!" << endl;

    return 0;
}
