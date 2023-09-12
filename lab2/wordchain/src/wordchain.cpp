#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void printSolution(stack<string>& result, const string& w1, const string& w2){
    string solution;
    while(!result.empty()){ //medan stack inte är tom
        string word = result.top(); //hämta första ordet på stacken
        result.pop(); //ta bort första ordet på stacken (last in first out)
        solution.append(word + "->");//skriv ut på form w1->w2->w3...
    }
    cout<<"Chain from "+ w2 + " back to " + w1 + ":"<< endl;
    cout<<solution<<endl;
    cout<<"Have a nice day."<<endl;
}

bool wordInList(const unordered_multimap<string,string>& engDictionary, const string& word) {
    bool foundWord = false;
    string firstLetter = string(1,word[0]);
    //TODO: använd find() för att hitta elementen för en key, och iterera bland dessa element
    //och kolla om ordet finns i listan.
    for (int i =0; i < engDictionary.size(); i++){
        if (engDictionary[i] == word){ //om ordet finns i vår ordlista
            foundWord = true; //returnera true
            break;
        }
    }
    return foundWord;
}
unordered_multimap<string,string> createDictionary(){
    vector<string> dictionary; //deklarerar en vektor
    unordered_multimap<string,string> engDictionary;
    ifstream words;
    string filename ="dictionary.txt";
    words.open(filename.c_str());
    string word;
    while (getline(words, word)) {
        string firstLetter = string(1,word[0]);
        engDictionary.insert(engDictionary.begin(), pair<string,string> (firstLetter, word)); //källa: https://www.geeksforgeeks.org/unordered_multimap-insert-in-c-stl/
        //för varje ord lägger vi de hos en nyckel med samma första bokstav.
        //begin() returnerar en iterator som pekar på första elementet i vår multimap.
        dictionary.push_back(word); //lägger till orden i slutet av vektorn, storlek ändras om behövs
    }
    words.close();
    return engDictionary;


}

vector<string> findNeighbours(const string& word, const unordered_multimap<string,string>& engDictionary){
    vector<string> neighbours;

    for (int i = 0; i < word.length(); i ++){ // går igenom alla bokstäver i ordet
        for (char letter : ALPHABET){ // går igenom alla bokstäver i alfabetet
            string copyWord = word;
            copyWord[i] = letter; //byter ut indexet till alla 26 bokstäver
            if (wordInList(engDictionary, copyWord)){ //kollar om giltigt engelskt ord
                neighbours.push_back(copyWord); //isåfall lägg till som granne
            }
            if (copyWord == "data"){
                cout<<"-----Neighbor is data-----"<<endl;
            }
        }
    }
    return neighbours;
}

void wordChain(const string& w1, const string& w2, const unordered_multimap<string,string>& engDictionary){
    queue<stack<string>> wordChains; // skapar tom queue innehållande stacks
    stack<string> s1;
    s1.push(w1); // lägger till första ordet i tom stack
    wordChains.push(s1); // lägger till stacken på queue
    vector<string> usedWords; // vektor med alla ord som använts i någon kedja
    usedWords.push_back(w1);
    while(!wordChains.empty()){ // så länge queue inte är tom
        stack<string> partialChain = wordChains.front(); // hämtar stacken längst fram i queue
        wordChains.pop(); // ta bort stacken från queue
        string topWord = partialChain.top(); // hämtar första ordet i stacken
        if (topWord == "data"){
            cout << "topword = data : " + topWord << endl;
            cout << "w2 : "+ w2 << endl;
        }
        if (topWord == w2){ // om topp-elementet är destinationselementet
            printSolution(partialChain, w1, w2);
            break;
        }else{
            vector<string> neighbors = findNeighbours(topWord,engDictionary);
            for (string neighbor : neighbors) { // går igenom alla grannar till ordet
               //cout << neighbor << endl;
                if (!wordInList(usedWords, neighbor)){ // kolla ifall ordet är använt
                    stack<string> copyStack = partialChain; // skapar kopia av del-stacken
                    copyStack.push(neighbor); // lägger till nya ordet i kedjan av ord
                    usedWords.push_back(neighbor); // lägger till att vi andvänt ordet
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
    unordered_multimap<string,string> engDictionary = createDictionary(); //skapar en ordlista
    wordChain(firstWord, secondWord, engDictionary);

    return 0;
}
