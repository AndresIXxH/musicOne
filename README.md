# musicOne
Overview: 
This C++ console application, developed as part of an introductory programming assignment, tracks and analyzes users' music listening habits. It prompts for input on favorite genre, artist, weekly listening hours, and number of playlists; validates the data; computes derived metrics like annual listening time; and generates a formatted summary report displayed on-screen and saved to report.txt. The program uses a menu-driven interface with switch statements, if-else logic for recommendations, and loops (while, do-while, for) for repetition and control flow, adhering to concepts from Chapters 1-5 of the course textbook.
Features

Interactive Menu: Switch-based options for entering sessions, viewing reports, getting skill recommendations, or quitting.

Input Handling: Collects mixed data types (strings via getline for genre/artist with spaces, double for hours, int for playlists) with validation for invalid/negative values using cin.fail() and defaults.

Computations and Logic:
Derived value: Annual hours (hoursPerWeek * 52).
Skill level assignment via compound if-else (e.g., hours >= 10 && !strings.empty()).
Personalized tip via second compound if-else (e.g., hours >= 5 && playlists <= 3).

Output Formatting: Pretty table using setw(20), left alignment, fixed with setprecision(1) for floats.
File I/O: Appends reports to report.txt; option to view via ifstream and while(getline).
Loops: Main while for menu, do-while for multi-session entry, for loop for fixed-tip generation.
Error Handling: Graceful fallbacks for empty/invalid inputs; file open checks.

Requirements

C++ compiler (e.g., g++ or Visual Studio).
Standard libraries: <iostream>, <iomanip>, <string>, <fstream>.

Building and Running

Save the code as musicOne.cpp.
Compile: g++ -o musicOne musicOne.cpp (or build in Visual Studio).
Run: ./musicOne (Linux/Mac) or musicOne.exe (Windows).
Interact via the menu; sample inputs: Genre="Rock", Artist="The Beatles", Hours=7.5, Playlists=4. 
