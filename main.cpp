#include <iostream>
#include <fstream>
#include <random>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

random_device rd;
uniform_int_distribution<int> dist(1, 100);
string guess;
vector <char> word_vector;
string word;
int choice, score = 0;

string get_word() {
    int line = dist(rd);
    int current_line = 0;

    ifstream words("words.txt");
    while (getline(words, word)) {
        current_line++;

        if (current_line == line) {
            break;
        }
    }
    words.close();
    return word;
}

bool correct_spot(int index) {
    if (word_vector[index] == guess[index]) {
        return true;
    }
    else return false;
}

bool in_word(int index) {
    for (int i = 0; i < word.length(); i++)
    {
        if (guess[index] == word_vector[i]) {
            word_vector[i] = ' ';
            return true;
        }
    }
    return false;
}

int game(int score_number) {
    word = get_word();
    int tries = 0;
    while (tries < 6) {
        while (true) {
            cout << "Enter word: ";
            cin >> guess;
            if (guess.length() == 5) {
                tries++;
                word_vector.clear();
                for (int i = 0; i < word.length(); i++) {
                    word_vector.push_back(word[i]);
                }
                break;
            }
        }
        for (int i = 0; i < word.length(); i++) {
            if (correct_spot(i)) {
                cout << "\033[0;32m" << guess[i] << "\033[0m" << " | ";
            }
            else if (in_word(i)) {
                cout << "\033[0;33m" << guess[i] << "\033[0m" << " | ";
            }
            else {
                cout << "\033[0;31m" << guess[i] << "\033[0m" << " | ";
            }
        }      
        cout << "\n";
        if (guess == word) {
            cout << "You guessed the word in " << tries << " tries\n";
            score++;
            return 0;
        }
    }
    cout << "You didn't guess the word. The word was " << word << "\n";
    return score;
}

int main() {
	cout << "Welcome to Wordle!\nYou'll have to attempt to guess a 5 letter word\nYou have 6 tries\nMAKE SURE YOU ENTER WORDS IN LOWERCASE\n\n";
    cout << "\033[0;32mLetter in correct spot\033[0m\n\033[0;33mLetter is in the word, but not in the correct spot\033[0m\n\033[0;31mLetter is not in the word\033[0m\n\n";
    game(score);

    while (true) {
        cout << "Score: " << score;
        cout << "\n1. Play again\n2. Quit\n";
        cin >> choice;
        if (choice == 1) {
            game(score);
        }
        else if (choice == 2) {
            break;
        }
    }
}
