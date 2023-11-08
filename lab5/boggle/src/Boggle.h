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
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    unordered_set<string> humanWords;
    unordered_set<string> computerWords;
    void createRandomBoard();
    void createCustomizedBoard(string letters);
    void showBoard();
    bool containsValidLetters(string letters);
    string wordsToString(unordered_set<string> wordsVec);
    int score(unordered_set<string> wordsVec);
    bool insertWord(string word);
    bool wordOnBoard(string word);
    bool correctHumanGuess(string correctWord, int row, int col, string chosen);
    bool isPrefix(string substring, string word);
    void findAllWords();
    unordered_set<string> computerSearch(int row, int col, string letter);
    void reset();

private:
    Grid<string> board = Grid<string>(4,4);
    Lexicon lexicon = Lexicon("EnglishWords.dat");
    unordered_set<string> visited;

};

#endif
