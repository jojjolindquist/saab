/* Programmet Ordkedja förbinder ett ord till ett annat genom att byta ut en bokstav i taget under
 * villkoret att ett giltigt ord bildas i varje delsteg och att alla ord i kedjan är lika långa.
 * Programmet skriver ut den kortaste ordkedjan mellan dessa två ord. */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/* Skriver ut varje steg som ordet gått genom för att bli det andra ordet
 * genom att bygga upp en sträng som tar med varje ord på stacken. */
void printSolution(stack<string>& result, const string& w1, const string& w2){
    string solution;
    while(!result.empty()){ //medan stack inte är tom
        string word = result.top(); //hämta första ordet på stacken
        result.pop(); //ta bort första ordet på stacken (last in first out)
        if(result.empty()){
            solution.append(word);
        }
        else{
            solution.append(word + "->");//skriv ut på form w1->w2->w3...
        }
    }
    cout<<"Chain from "+ w2 + " back to " + w1 + ":"<< endl;
    cout<<solution<<endl;
    cout<<"Have a nice day."<<endl;
}


/* Tar in en ordlängd (int) och lägger till alla ord med den ordlängden i en ordlista (multimap), där
 * nyckeln är första bokstaven i ordet och värdena alla ord med detta prefix. Returnerar
 * sedan denna multimap (ordlistan).*/
unordered_set<string> createDictionary(int wordLength){ //behöver inte ha const på int
    unordered_set<string> engDictionary;
    ifstream words;
    string filename ="dictionary.txt";
    words.open(filename.c_str());
    string word;
    while (getline(words, word)) {
        if (word.length() == wordLength){ //om ordet matchar ordlängden tar vi med det i vår multimap, samt kategoriserar efter första bokstaven
            engDictionary.insert(word);
        }
    }
    words.close();
    return engDictionary;
}

/* Tar in ett ord (sträng) och byter ut varje position till varje bokstav i alfabetet. Kollar därefter
 * i ordlistan om det nya ordet är ett giltigt ord. Om det är ett giltigt ord läggs det till i en vektor
 * av strängar, vilken returneras. */
vector<string> findNeighbours(const string& word, const unordered_set<string>& engDictionary){
    vector<string> neighbours;
    for (int i = 0; i < word.length(); i ++){ // går igenom alla bokstäver i ordet
        for (char letter : ALPHABET){ // går igenom alla bokstäver i alfabetet
            string copyWord = word;
            copyWord[i] = letter; //byter ut indexet till alla 26 bokstäver
            if (engDictionary.find(copyWord) != engDictionary.end()){ //kollar om giltigt engelskt ord
                neighbours.push_back(copyWord); //isåfall lägg till som granne
            }
        }
    }
    return neighbours;
}


/* Tar in två ord (strängar) av lika längd, som det ska skapas en ordkedja mellan. Använder bredd-först-sökning
 * och flera andra metoder för att hitta den kortaste kedjan av giltiga engelska ord. När hittad skrivs denna kedja
 * ut via anrop till annan metod. */
void wordChain(const string& w1, const string& w2, const unordered_set<string>& engDictionary){
    queue<stack<string>> wordChains; // skapar tom queue innehållande stacks
    stack<string> s1;
    s1.push(w1); // lägger till första ordet i tom stack
    wordChains.push(s1); // lägger till stacken på queue
    unordered_set<string> usedWords; // vektor med alla ord som använts i någon kedja
    usedWords.insert(w1);
    while(!wordChains.empty()){ // så länge queue inte är tom
        stack<string> partialChain = wordChains.front(); // hämtar stacken längst fram i queue
        wordChains.pop(); // ta bort stacken från queue
        string topWord = partialChain.top(); // hämtar första ordet i stacken
        if (topWord == w2){ // om topp-elementet är destinationselementet
            printSolution(partialChain, w1, w2);
            break;
        }else{
            vector<string> neighbors = findNeighbours(topWord,engDictionary);
            for (string neighbor : neighbors) { // går igenom alla grannar till ordet
                if (usedWords.find(neighbor) == usedWords.end()){ // kolla ifall ordet är använt
                    stack<string> copyStack = partialChain; // skapar kopia av del-stacken
                    copyStack.push(neighbor); // lägger till nya ordet i kedjan av ord
                    usedWords.insert(neighbor); // lägger till att vi andvänt ordet
                    wordChains.push(copyStack); // lägger till kedjan längst bak i queue
                }
            }
        }
    }
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    string firstWord;
    string secondWord;
    cin >> firstWord; // hämtar första ordet
    cin >> secondWord; // hämtar andra ordet
    int wordLength = firstWord.length();
    unordered_set<string> engDictionary = createDictionary(wordLength); //skapar en ordlista
    wordChain(firstWord, secondWord, engDictionary);

    return 0;
}
