#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> createDictionary(int wordLength){
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

bool letterIsUsed(const vector<string>& usedLetters, const string& letter){
    for (int i = 0; i < usedLetters.size(); i++){
        if (usedLetters[i] == letter){
            return true;
        }
    }
    return false;
}

/* Tar in en dictionary och en bokstav och returnerar en unordered multimap där varje
 * key är en sträng där bokstaven antingen finns eller inte finns på varje position.
 * Värdena till varje key är de ord där bokstaven finns på dessa positioner.*/
unordered_multimap<string, string> makePartitions(const vector<string>& engDictionary, const string letter){
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
        wordFamilies.insert(wordFamilies.begin(), pair<string,string> (key, word)); //källa: https://www.geeksforgeeks.org/unordered_multimap-insert-in-c-stl/
    }
    return wordFamilies;
}

void chooseFamily(vector<string>& engDictionary, const unordered_multimap<string, string>& wordFamilies){
    for(auto familiesIt = wordFamilies.begin(); familiesIt != wordFamilies.end(); familiesIt++){ //returnerar iterator som börjar vid start
        auto key = familiesIt->first; //first innebär hämta nyckeln (k) i nyckel-värde-paret (k,v)
        int members = wordFamilies.count(key); //räknar antalet ord (medlemmar) i varje familj
    //TODO: spara undan det största värdet varje omgång, gör sedan om vald familj till vektor och sätt engDictionary till den.
        //TESTA
    }
}

int main() {
    cout << "Welcome to Hangman." << endl;
    bool validLength = false;
    bool showWords = false;
    vector<string> engDictionary;
    int guesses;
    vector<string> usedLetters; //initerar en vektor för använda bokstäver
    while(!validLength){
        cout << "Please choose a valid word length:" << endl;
        int wordLength;
        cin >> wordLength; //hämtar ordlängd
        engDictionary = createDictionary(wordLength);
        if(!engDictionary.empty()){ //om giltig ordlängd
            validLength = true; //gå ur loopen
        }
    }
    bool validNumber = false;
    while(!validNumber){
        cout << "Enter number of guesses you want (>0):" << endl;
        cin >> guesses;
        //TODO: fråga om datatypskontroll
        if(guesses > 0){
            validNumber = true;
        }
    }
    cout << "Do you want to see the available words after each round? (Y/N):" << endl;
    string answer;
    cin >> answer;
    if (answer == "Y" || answer == "y")
    {
        showWords = true; //nu vill vi visa ordlistan varje runda
    }
    //TODO: en metod som visar allting.
    while(guesses > 0){ //Sätt guesses till 0 när man gissat rätt!
        cout << "Guess an unused letter: " << endl;
        string guessedLetter;
        cin >> guessedLetter;
        if (!letterIsUsed(usedLetters, guessedLetter)){ //inte gissat denna bokstav förut
            //....
            unordered_multimap<string,string> wordFamilies = makePartitions(engDictionary, guessedLetter);
            chooseFamily(engDictionary, wordFamilies);
            //om strängen som returnernas = tom, dra bort gissningar
            usedLetters.push_back(guessedLetter);
        }
    }

    //TODO: 1 metod för att visa UI som tar in strängen.
    //TODO: 1 metod som tar in gissade bokstaven och returnerar en map med ordfamilj
    //TODO: 1 metod som kollar om gissat förut på ordet.
    //TODO: 1 metod som returnerar vilken ordfamilj vi ska ta.
    //TODO: ta bort gissning om ordfamilj inte innehåller bokstaven
    //TODO: visa ordet om slut på gissningar
    //TODO: gratulera om gissat rätt
    //Ändra dictionaryn varje gång efter ordfamilj, referens i metoderna
    //(c) Be anva ̈ndaren gissa en bokstav och upprepa till hen gissar en bokstav hen ej gissat fo ̈rut. Sa ̈kersta ̈ll
    //att exakt en bokstav matats in och att det a ̈r en bokstav i alfabetet.
    return 0;
}
