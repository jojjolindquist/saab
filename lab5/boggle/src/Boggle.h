// Klass Boggle som innehåller alla metoder för att kunna spela en runda av Boggle.
// Den har medlemsvariabler som är ett board med alla kastade tärningar, ett
// lexikon för att slå upp giltiga engelska ord, en mängd av besökta bokstavsgrannar
// på brädet. Klassen har även publika medlemsvariabler som lagrar orden som människan
// respektive datorn hittar på brädet.
// stias606 och johli622


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
    unordered_set<string> computerWords;

    /* Genererar ett bräde där tärningarna kastats slumpmässigt
     * och varje vald bokstav på varje tärning lagras i en koordinat i
     * ett Grid-objekt (board) */
    void createRandomBoard();

    /* Tar in en sträng av giltiga bokstäver av längd 16, lagrar sedan
     * varje bokstav i strängen som en koordinat i ett Grid-objekt (board) */
    void createCustomizedBoard(const string& letters);

    /* Returnerar board som en sträng i 4x4-format */
    string showBoard();

    /* Kontrollerar om en sträng av bokstäver faktiskt innehåller giltiga bokstäver
     * A-Z. Returnerar true/false. */
    bool containsValidLetters(const string& letters);

    /* Returnerar en sträng av de gissade orden (strängarna) från den inskickade
     * mängden. Returneras på formatet { "ORD1", "ORD2" }. */
    string wordsToString(const unordered_set<string>& wordsVec);

    /* Räknar ihop poängen som orden i den inskickade mängden ger. Beräknas
     * genom att ta ordlängden -4. Returnernar en int av poängen. */
    int score(const unordered_set<string>& wordsVec);

    /* Tar in ett gissat ord av människan, kallar på metoden wordOnBoard, och om den
     * returnerar sant, finns ordet på brädet. Om det finns, samt att ordet är ett giltigt
     * engelskt ord av minst längd 4, samt ej har gissats på förut, lägger denna metod till
     * ordet i humanWords och returnerar sant. */
    bool insertWord(string& word);

    /* Tar in ett gissat ord av människan. Itererar över brädet och skickar in varje koordinat
     * som första bokstav till metoden correctHumanGuess för att se om det gissade ordet kan
     * byggas upp med den bokstaven. Returnerar sant om correctHumanGuess returnerar sant. */
    bool wordOnBoard(string& word);

    /* Tar in ett gissat ord (correctWord, en koordinat (row, col) samt en sträng som först bara är bokstaven på
     *  koordinaten. Använder sedan rekursiv backtracking för att se om det går att bygga upp correctWord
     *  utifrån den första bokstaven och dess grannar. Kollar alltid om det nuvarande ordet (chosen) är ett
     *  prefix till correctWord, annars sluta söka. */
    bool correctHumanGuess(const string& correctWord, const int& row, const int& col, const string& chosen);

    /* Returnerar sant om substring är en substräng till word, samt börjar på index 0 (dvs ett prefix). */
    bool isPrefix(const string& substring, const string& word);

    /* Itererar genom hela brädet och skickar in varje koordinat som första bokstav till metoden ComputerSearch
     * för att hitta alla giltiga engelska ord av korrekt längd som börjar på den bokstaven och koordinaten på
     * brädet. */
    void findAllWords();

    /* Returnerar ett set med alla ord som kan bildas med en specifik bokstav på brädet och dess grannar.
     * Använder rekursiv backtracking för att hitta dessa ord, samt kollar hela tiden om variabeln prefix är
     * ett giltigt prefix för något engelskt ord. */
    unordered_set<string> computerSearch(const int& row, const int& col, const string& prefix);

    /* Återställer (tömmer) humanWords, computerWords, samt visited inför nästa spelrunda. */
    void reset();

private:
    Grid<string> board = Grid<string>(4,4);
    Lexicon lexicon = Lexicon(DICTIONARY_FILE);
    unordered_set<string> visited;

};

#endif
