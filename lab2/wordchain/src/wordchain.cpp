#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void printSolution(stack<string>& result){
    while(!result.empty()){
        string word = result.top();
        result.pop();
        cout << word << "->" <<endl;
    }
}

bool findWord(const vector<string>& dictionary, const string& word) {
    bool foundWord = false;
    for (int i =0; i < dictionary.size(); i++){
        if (dictionary[i] == word){
            foundWord = true;
            break;
        }
    }
    return foundWord;
}
vector<string> createDictionary(){
    vector<string> dictionary;
    string arr[200];
    ifstream input;
    string filename ="dictionary.txt";
    input.open(filename.c_str());
    string line;
    while (getline(input, line)) {
        dictionary.push_back(line);
    }
    input.close();
    return dictionary;


}

vector<string> findNeighbours(const string& word, const vector<string>& dictionary){
    vector<string> neighbours;
    string arr[100];

    for (int i = 0; i < word.length(); i ++){ // går igenom alla bokstäver i ordet
        for (char letter : ALPHABET){ // går igenom alla bokstäver i alfabetet
            string copyWord = word;
            copyWord[i] = letter;
            if (findWord(dictionary, copyWord)){
                neighbours.push_back(copyWord);
            }
        }
    }
    return neighbours;

}
void wordchain(const string& w1, const string& w2, const vector<string>& dictionary){
    queue<stack<string>> wordChains; // skapar tom queue innehållande stack
    stack<string> s1;
    s1.push(w1); // lägger till första ordet i tom stack
    wordChains.push(s1); // lägger till stacken på queue
    vector<string> usedWords; // vektor med alla ord som använts i någon kedja
    usedWords.push_back(w1);
    while(!wordChains.empty()){ // så länge queue inte är tom
        stack<string> partialChain = wordChains.front(); // hämtar stacken längst fram i queue
        wordChains.pop(); // ta bort stacken från queue
        string topWord = partialChain.top(); // hämtar första ordet i stacken
        cout << topWord << endl;
        if (topWord == w2){ // om topp-elementet är destinationselementet
            printSolution(partialChain);
            break;
        }else{
            for (string neighbor : findNeighbours(topWord, dictionary)) { // går igenom alla grannar till ordet
                cout << neighbor << endl;
                if (!findWord(usedWords, neighbor)){ // kolla ifall ordet är använt
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
    vector<string> dictionary = createDictionary();
    wordchain(secondWord, firstWord, dictionary);

    // TODO: Finish the program!

    return 0;
}
