#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
vector<string> createDictionary(){
    vector<string> dictionary;
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
    string copyWord = word;
    for (int i = 0; i < word.length(); i ++){ // går igenom alla bokstäver i ordet
        for (char letter : ALPHABET){ // går igenom alla bokstäver i alfabetet
            copyWord[i] = letter;
            // kolla om copyword finns i dictionary
        }
    }
}
void wordchain(const string& w1, const string& w2, const vector<string>& dictionary){
    queue<stack<string>> wordChains; // skapar tom queue innehållande stack
    stack<string> s1;
    s1.push(w1); // lägger till första ordet i tom stack
    wordChains.push(s1); // lägger till stacken på queue
    while(!wordChains.empty()){ // så länge queue inte är tom
        stack<string> partialChain = wordChains.front(); // hämtar stacken längst fram i queue
        string topWord = partialChain.top(); // hämtar första ordet i stacken
        if (topWord == w2){ // om topp-elementet är destinationselementet
            // print result
        }else{
            for (string neighbor : findNeighbours(topWord, dictionary)) { // går igenom alla grannar till ordet

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


    // TODO: Finish the program!

    return 0;
}
