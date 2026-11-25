// ----------------------------------------------------------------------------
// Question 3: Student Scores
// Reads the scores of 5 students into an array and uses loops to find the
// average, highest and lowest scores, then lists the scores in entry order.
// ----------------------------------------------------------------------------
#include <iomanip>
#include <iostream>

#include "input_utils.h"

using namespace std;

const int NUM_STUDENTS = 5;
const int MIN_SCORE = 0;
const int MAX_SCORE = 100;

int main() {
    int scores[NUM_STUDENTS];  // a) array to store the scores

    cout << "Enter the scores for " << NUM_STUDENTS << " students:\n";

    // b) read the scores, validating that each is a whole number from 0 to 100
    for (int i = 0; i < NUM_STUDENTS; i++) {
        scores[i] = input::readInt("Enter score for student " + to_string(i + 1) + ": ",
                                   MIN_SCORE, MAX_SCORE);
    }

    // Loop to calculate the total, highest and lowest.
    // Start from the first score so the result is correct for any valid scores.
    int total = 0;
    int highest = scores[0];
    int lowest = scores[0];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        total += scores[i];
        if (scores[i] > highest) highest = scores[i];
        if (scores[i] < lowest) lowest = scores[i];
    }
    const double average = static_cast<double>(total) / NUM_STUDENTS;

    // d) all scores in the order they were entered
    cout << "\nScores entered:\n";
    for (int i = 0; i < NUM_STUDENTS; i++) {
        cout << "Student " << (i + 1) << ": " << scores[i] << "\n";
    }

    // c) average, highest and lowest
    cout << fixed << setprecision(2);
    cout << "\nAverage score: " << average << "\n";
    cout << "Highest score: " << highest << "\n";
    cout << "Lowest score: " << lowest << "\n";
    return 0;
}
