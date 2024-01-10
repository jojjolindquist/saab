/* En variant av spelet hänga gubbe, då datorn spelar fult. Den väljer utifrån den gissade bokstaven
* den ordfamilj (där alla ord har den bokstaven på samma position) med flest värden (ord), varav
* det blir svårare för spelaren att gissa rätt. */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* Skapar en engelsk ordbok (dictionary) i form av en vektor av strängar av given (ord)längd.*/
vector<string> createDictionary(const int& wordLength){
    //unordered_multimap<string,string> engDictionary;
    vector<string> engDictionary;
    ifstream words;
    string filename ="dictionary.txt";
    words.open(filename.c_str());
    string word;
    while (getline(words, word)) {
        if (word.length() == wordLength){ //om ordet matchar ordlängden tar vi med det
            engDictionary.push_back(word); //vet inte hur många ord som har denna längd så vektor bra datatyp.
        }
    }
    words.close();
    return engDictionary;
}


/*Tar in en vektor av använda/gissade bokstäver (strängar) samt en bokstav (sträng)
* och kontrollerar om bokstaven finns i vektorn. Returnernar en bool. */
bool letterIsUsed(const vector<string>& usedLetters, const string& letter){
    for (int i = 0; i < usedLetters.size(); i++){
        if (usedLetters[i] == letter){
            return true;
        }
    }
    return false;
}

/* Tar in en dictionary (vektor) och en bokstav (sträng) och returnerar en unordered multimap där varje
* key är en sträng där bokstaven antingen finns eller inte finns på varje position.
* Värdena till varje key är de ord där bokstaven finns på dessa positioner.*/
unordered_multimap<string, string> makePartitions(const vector<string>& engDictionary, const string& letter){
    unordered_multimap<string, string> wordFamilies;
    for (string word : engDictionary){
        string key = "";
        for (char wordLetter : word){
            if (string(1,wordLetter) == letter){ //för varje position där bokstaven finns i ordet
                key.append(letter); //lägg till den bokstaven i key
            }
            else{
                key.append("-"); //annars lägg till "-"
            }
        } //koppla därefter denna key till detta ord och vi kommer få alla möjliga alternativ i vår multimap
        //aaab
        //baaa
        wordFamilies.insert(wordFamilies.begin(), pair<string,string> (key, word)); //källa: https://www.geeksforgeeks.org/unordered_multimap-insert-in-c-stl/
    }
    return wordFamilies;
}


/* Tar in en ordlängd (int) och returnerar en sträng lika många "-" som ordlängden.*/
string createEmptyWordForm(const int& wordLength){
    string emptyWordForm = "";
    for(int i = 0; i < wordLength; i++){
        emptyWordForm.append("-");
    }
    return emptyWordForm;
}


/* Tar in två olika ordformer (tex (a--a) och (-bb-)) som garanterat har samma längd.
* Slår sedan ihop dessa ordformer till en (tex (abba)). */
void mergeForms(string& currentWordForm, const string& mergeWordForm){
    for (int i = 0; i < currentWordForm.length(); i++){
        if(string(1,mergeWordForm[i]) != "-"){ //om symbolen på index i har någon bokstav
            currentWordForm[i] = mergeWordForm[i]; //sätt då den index i för currentWordForm
        }
    }
}


/* Tar in en ordlista (vektor) och en multimap vars nyckel är ett mönster och värden alla ord med det bokstavsmönstret.
* Jämför sedan familjernas storlek (antal värden) och sparar undan den nyckel störst familj varje omgång. Metoden gör
* sedan om den största familjen till en vektor av strängar (värdena), samt tilldelar engDictionary den.
* Metoden returnerar mönstret (nyckeln) för den största familjen.*/
string chooseFamily(vector<string>& engDictionary, const unordered_multimap<string, string>& wordFamilies){
    pair<int, string> biggestFamily;//lagrar information om största familj på form (antal ord, nyckel i multimap)
    biggestFamily.first = -1; //ingen annan kommer ha -1 som antal ord, initierar.
    biggestFamily.second = "";
    auto familiesIt = wordFamilies.begin();
    while(familiesIt != wordFamilies.end()){
        auto key = familiesIt->first; //first innebär hämta nyckeln (k) i nyckel-värde-paret (k,v)
        int members = wordFamilies.count(key); //räknar antalet ord (medlemmar) i varje familj
        if (members > biggestFamily.first){ //hittat en familj med fler medlemmar?
            biggestFamily.first = members;
            biggestFamily.second = key;
        }
       advance(familiesIt, members); //ökar iteratorn med antal värden i key, så vi inte itererar genom alla par (onödigt)
                                    //källa: https://stackoverflow.com/questions/1057529/how-to-increment-an-iterator-by-2
    }
    vector<string> newDictionary;
    auto familyIt = wordFamilies.find(biggestFamily.second);//returnerar iterator som börjar vid orden med firstLetter
    for(int i = 0; i < biggestFamily.first; i++){
        string word = familyIt->second; //second innebär hämta värdet (v) i nyckel-värde-paret (k,v)
        newDictionary.push_back(word); //
        familyIt++;
    }
    engDictionary = newDictionary;
    return biggestFamily.second;
}


/*En metod för att visa allt det grafiska med spelet. Visar gissade ord, antal gissningar kvar, ordlistan om det är valt,
* samt bokstäverna som gissats rätt i ordet. */
void showHangman(const vector<string>& usedLetters, int& guesses, const bool& showWords, const string& currentWordForm, const vector<string>& dictionary){
    string showUsedLetters;
    for (string letter : usedLetters){ //skapa en läslig sträng av alla bokstäver
        showUsedLetters.append(letter + " ");
    }
    if(showWords){ //om vi vill visa ordlistan
        cout << "Available words in wordlist: " << endl;
        for (string word : dictionary){
            cout << word << endl;
        }
    }
    cout << "Used letters: " + showUsedLetters << endl;
    cout << "Guesses left: " + to_string(guesses) << endl;
    cout << "Word: " + currentWordForm << endl;
}


/* Tar in ett ordmönster och returnerar false om alla chars är "-" (dvs den gissade bokstaven finns inte
* i ordfamiljen). Annars returneras true. */
bool guessedLetterInWord(string wordForm){
    for(char letter : wordForm){
        if (string(1, letter) != "-"){
            return true;
        }
    }
    return false;
}


/* Tar in ett ordmönster, och om varje char är en bokstav (dvs inte "-"), returnerar true
* (dvs användaren har gissat rätt). Annars returneras false. */
bool guessedRight(string wordForm){
    for(char letter : wordForm){
        if (string(1, letter) == "-"){
            return false;
        }
    }
    return true;
}


bool isInteger(string guesses){
    bool isNumber = true;
    for (char character : guesses){
        if (!isdigit(character)){
            isNumber = false;
        }
    }
    return isNumber;
}


string chooseDifficultFamily(vector<string>& engDictionary, const unordered_multimap<string, string>& wordFamilies, string letter){
    //ska nu välja den familj där bokstaven finns minst antal gånger.
    pair<int, string> difficultFamily;//lagrar information om största familj på form (antal ord, nyckel i multimap)
    difficultFamily.first = 2147483647; //ingen annan kommer ha större än detta, maxvärde int
    difficultFamily.second = "";
    auto familiesIt = wordFamilies.begin();
    while(familiesIt != wordFamilies.end()){
        string key = familiesIt->first; //first innebär hämta nyckeln (k) i nyckel-värde-paret (k,v)
        int numOfLetter = 0;

        for (char symbol : key){ //går igenom varje symbol i nyckeln
            if (string(1, symbol) != "-"){ //om inte "-" så är det en bokstav
                numOfLetter++;
            }
        }
        int members = wordFamilies.count(key); //räknar antalet ord (medlemmar) i varje familj
        if (numOfLetter < difficultFamily.first){ //hittat en familj med färre antal av bokstaven?
            difficultFamily.first = numOfLetter;
            difficultFamily.second = key;
        }
       advance(familiesIt, members); //ökar iteratorn med antal värden i key, så vi inte itererar genom alla par (onödigt)
                                    //källa: https://stackoverflow.com/questions/1057529/how-to-increment-an-iterator-by-2
    }
       vector<string> newDictionary;
       auto familyIt = wordFamilies.find(difficultFamily.second);//returnerar iterator som börjar vid orden med firstLetter
       for(int i = 0; i < wordFamilies.count(difficultFamily.second); i++){ //itererar genom alla ord i den nya familjen
           string word = familyIt->second; //second innebär hämta värdet (v) i nyckel-värde-paret (k,v)
           newDictionary.push_back(word);
           familyIt++;
       }
       engDictionary = newDictionary; //sätter vår dictionary till den nya ordfamiljen
       return difficultFamily.second; //returnerar ordformen
}
/*
 * Hittar den ordfamilj med flest medlemmar och som innehåller lika många av letters som count. Om den inte hittar en familj
 * som matchar kommer antalet medlemmar att vara -1.
 */
pair<int, string> findEvilFamily(const unordered_multimap<string, string>& wordFamilies, string letter, int count){
    pair<int, string> difficultFamily;//lagrar information om största familj på form (antal medlemmar, nyckel i multimap)
    difficultFamily.first = -1; //ingen annan kommer ha negativt antal medlemmar
    difficultFamily.second = "";
    auto familiesIt = wordFamilies.begin();
    while(familiesIt != wordFamilies.end()){
        string key = familiesIt->first; //first innebär hämta nyckeln (k) i nyckel-värde-paret (k,v)
        int numOfLetter = 0;
        for (char symbol : key){ //går igenom varje symbol i nyckeln
            if (string(1, symbol) != "-"){ //om inte "-" så är det en bokstav
                numOfLetter++;
            }
        }
        int members = wordFamilies.count(key); //räknar antalet ord (medlemmar) i varje familj
        if (numOfLetter == count && members > difficultFamily.first){ //hittat en familj med färre antal av bokstaven?
            difficultFamily.first = members;
            difficultFamily.second = key;
        }
       advance(familiesIt, members); //ökar iteratorn med antal värden i key, så vi inte itererar genom alla par (onödigt)
                                    //källa: https://stackoverflow.com/questions/1057529/how-to-increment-an-iterator-by-2
    }
    return difficultFamily;
}

/*
 * Hittar den stösta ordfamilj som innehåller av bokstaven. Detta gör det i många fall mycket svårare för spelaren
 */
string veryEvilFamily(vector<string>& engDictionary, const unordered_multimap<string, string>& wordFamilies, string letter){
    bool familyFound = false;
    int numbOfLetters = 0;
    pair<int, string> difficultFamily;
    while(!familyFound){
        difficultFamily = findEvilFamily(wordFamilies, letter, numbOfLetters);
        if(difficultFamily.first != -1){ // vi har nu hittat största ordfamiljen med minst antal bosktäver
            familyFound = true;
        }else{
            numbOfLetters ++;
        }
    }
    vector<string> newDictionary;
    auto familyIt = wordFamilies.find(difficultFamily.second);//returnerar iterator som börjar vid orden med firstLetter
    for(int i = 0; i < difficultFamily.first; i++){
        string word = familyIt->second; //second innebär hämta värdet (v) i nyckel-värde-paret (k,v)
        newDictionary.push_back(word);
        familyIt++;
    }
    engDictionary = newDictionary; //sätter vår dictionary till den nya ordfamiljen
    return difficultFamily.second; //returnerar ordformen
}

int main() {
    bool play = true;
    while (play){
        cout << "Welcome to Hangman." << endl;
        bool validLength = false;
        bool showWords = false;
        string currentWordForm;
        vector<string> engDictionary;
        int guesses;
        vector<string> usedLetters; //initerar en vektor för använda bokstäver
        while(!validLength){
            cout << "Please choose a valid word length:" << endl;
            string wordLength;
            cin >> wordLength; //hämtar ordlängd
            if (isInteger(wordLength)){
                engDictionary = createDictionary(stoi(wordLength));
                if (!engDictionary.empty()){ //om giltig ordlängd
                    validLength = true; //gå ur loopen
                    currentWordForm = createEmptyWordForm(stoi(wordLength));
                }
            }
        }
        bool validNumber = false;
        while(!validNumber){
            string answGuesses;
            cout << "Enter number of guesses you want (>0):" << endl;
            cin >> answGuesses;
            if(isInteger(answGuesses)){
                if (stoi(answGuesses) > 0){
                    validNumber = true;
                    guesses = stoi(answGuesses); //kontrollerat nu att input är på korrekt form
                }
            }
        }
        cout << "Do you want to see the available words after each round? (Y/N):" << endl;
        string answer;
        cin >> answer;
        if (answer == "Y" || answer == "y")
        {
            showWords = true; //nu vill vi visa ordlistan varje runda
        }
        while(guesses > 0){ //Sätt guesses till 0 när man gissat rätt!
            showHangman(usedLetters, guesses, showWords, currentWordForm, engDictionary);
            cout << "Guess an unused letter: " << endl;
            string guessedLetter;
            cin >> guessedLetter;
            if (ALPHABET.find(guessedLetter) != string::npos && guessedLetter.size() == 1){ //string::npos indikerar att input inte fanns i alfabetet (ingen bokstav)
                if (!letterIsUsed(usedLetters, guessedLetter)){ //inte gissat denna bokstav förut
                    unordered_multimap<string,string> wordFamilies = makePartitions(engDictionary, guessedLetter);
                    string mergeWordForm;
                    if (guesses == 1){ //om gissningar 1 ska vi välja en svårare familj till sista gissningen
                        string keyDiffFamily = chooseDifficultFamily(engDictionary, wordFamilies, guessedLetter);
                            mergeWordForm = keyDiffFamily; //sätt mergeWordForm till svåraste familjen
                    }
                    else{
                        mergeWordForm = veryEvilFamily(engDictionary, wordFamilies, guessedLetter);
                    }
                    if (!guessedLetterInWord(mergeWordForm)){//om den gissade bokstaven inte finns med i vår nya ordfamilj
                        guesses--; //ta bort en gissning
                    }
                    mergeForms(currentWordForm, mergeWordForm); //slå ihop den nya bokstavsformen med den gamla (tex (a--a) med (-bb-))
                    //om strängen som returnernas = tom, dra bort gissningar
                    if (guessedRight(currentWordForm)){
                        showHangman(usedLetters, guesses, showWords, currentWordForm, engDictionary);
                        guesses = -1; //sätter till en siffra som ej går att få om man förlorar
                    }
                    usedLetters.push_back(guessedLetter);
                }
            }
        }
        if (guesses == -1){
            cout << "Congratulations! You guessed the right word! ";
        }
        else{ //förlorat
            currentWordForm = engDictionary[0]; //sätter "valda" ordet till första ordet i vår dictionary
            showHangman(usedLetters, guesses, showWords, currentWordForm, engDictionary);
            cout << "You lost, the word was: " + currentWordForm + " " << endl;
        }

        cout << "Do you want to play again? (Y/N):" << endl;
        string playAgain;
        cin >> playAgain;
        if (playAgain == "N" || playAgain == "n")
        {
            play = false; //nu vill vi visa ordlistan varje runda
        }
    }
    return 0;
}
