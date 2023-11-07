// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "lexicon.h"
#include <unordered_set>

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    unordered_set<string> humanWords;
    void createRandomBoard();
    void createCustomizedBoard(string letters);
    void showBoard();
    bool containsValidLetters(string letters);
    string wordsToString();
    int score();
    bool insertWord(string word);
    bool wordOnBoard(string word);
    bool recursiveSearch(string correctWord, int row, int col, string chosen);
    bool isPrefix(string substring, string word);

private:
    Grid<string> board = Grid<string>(4,4);
    Lexicon lexicon = Lexicon("EnglishWords.dat");
    unordered_set<string> visited;
};

#endif
