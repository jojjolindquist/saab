// Boggleplay hanterar user input och skickar in alla svar till boggle-objektet för att
// kunna spela en omgång. Den har en metod som hanterar en spelomgång av boggle och en som
// raderar texten i konsollen.
// stias606 och johli622

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"


/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    cout << "Do you want to generate a random board?: " << endl;
    string answer;
    if (yesOrNo(answer)){ //om returnerar yes (true)
        boggle.createRandomBoard();
    }
    else{ //returnerar no (false)
        bool correctFormat = false;
        string letters;
        while (correctFormat == false){
            cout << "Write a string of 16 letters (A-Z): " << endl;
            getline(cin, letters);
            if (letters.size() == 16 && boggle.containsValidLetters(letters)){
                correctFormat = true;
            }
            else{
                cout << "The string does not have the correct format!" << endl;
            }
        }
        boggle.createCustomizedBoard(letters);
    }
    bool guess = true;
    while (guess){
        cout << "It's your turn!" << endl;
        cout << boggle.showBoard() << endl;
        cout << "Your words (" << boggle.humanWords.size() <<  "): " << boggle.wordsToString(boggle.humanWords) << endl;
        cout << "Your score: " << boggle.score(boggle.humanWords) << endl;
        cout << "Type a word (or press enter to end your turn): " << endl;
        string line;
        getline(cin, line);
        clearConsole();
        if (!line.empty()){ //tryckte enter
            if (boggle.insertWord(line)){ //lyckades sätta in ordet (ordet fanns på brädet och giltigt)
                cout << "You found a new word! \"" + toUpperCase(line) + "\"" << endl;
            }
            else{
                cout << "Please enter a new word of minimum length 4." << endl;
            }
        }
        else{ //tryckte enter pga tom line
            guess = false;
        }
    }
    cout << "It's my turn!" << endl;
    boggle.findAllWords();
    cout << "My words (" << boggle.computerWords.size() <<  "): " << boggle.wordsToString(boggle.computerWords) << endl;
    cout << "My score: " << boggle.score(boggle.computerWords) << endl;
    if (boggle.computerWords.size() > boggle.humanWords.size()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    } else { // datorn kan aldrig förlora då den hittar alla ord, antingen lika eller så vinner datorn
        cout << "Our scores are equal, well played! Both won. " << endl;
    }

}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
