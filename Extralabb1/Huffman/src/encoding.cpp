// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include <queue>
#include "huffmanutil.h"
// TODO: include any other headers you need

void preorderTraversal(HuffmanNode* root, string path, map<int, string>& encodingMap){
    if (root->isLeaf()){
        encodingMap[root->character] = path;
        return;
    }else{
        preorderTraversal(root->zero, path + "0", encodingMap);
        preorderTraversal(root->one, path + "1", encodingMap);
    }
}

map<int, int> buildFrequencyTable(istream& input) {
    // ett tecken är en byte
    map<int, int> freqTable;
    int sign;
    while((sign = input.get()) != -1){ // vi har gått igenom hela filen
        if (freqTable.find(sign) != freqTable.end()){ // tecknet finns redan
            int frequency = freqTable[sign];
            freqTable[sign] = ++frequency; // öka frekvensen
        }else{
            freqTable[sign] = 1; // första gången detta tecken hittas
        }
    }
    freqTable[PSEUDO_EOF] = 1;
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> pqueue;
    HuffmanNode* firstMax, *secondMax, *merge;
    for (auto it = freqTable.begin(); it != freqTable.end(); it ++){
        HuffmanNode huffNode = HuffmanNode(it->first, it->second, nullptr); // skapar nod med tecken, frekvens, utan några barn
        pqueue.push(huffNode);
    }
    while (pqueue.size() > 1){
        firstMax = new HuffmanNode(pqueue.top());
        pqueue.pop();
        secondMax = new HuffmanNode(pqueue.top());
        pqueue.pop();
        merge = new HuffmanNode(NOT_A_CHAR, (firstMax->count + secondMax->count), firstMax, secondMax);
        pqueue.push(*merge);
    }

    return merge;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    preorderTraversal(encodingTree, "", encodingMap);
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int sign;
    cout << input.get() << endl;
    string path;
    while((sign = input.get()) != -1){ // vi har gått igenom hela filen
        path += encodingMap.at(sign);
    }
    path += encodingMap.at(PSEUDO_EOF);;
    for(char n : path){
        int number = n - '0'; // källa: https://stackoverflow.com/questions/439573/how-to-convert-a-single-char-into-an-int
        output.writeBit(number);
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* current = new HuffmanNode(*encodingTree);
    int sign;
    while((sign = input.readBit()) != -1){
        if (sign == 1){
            current = current->one;
        }else{
            current = current->zero;
        }
        if (current->isLeaf()){
            output.put(current->character);
            //current = new HuffmanNode(*encodingTree);
            current = encodingTree;
        }

    }
    input.clear(); // removes any current eof/failure flags
    input.seekg(0, ios::beg); // tells the stream to seek back to the beginning

}

void compress(istream& input, obitstream& output) {
    map<int, int>  frequencyTable = buildFrequencyTable(input);
    string strFreqTable = "{";
    for (pair<int, int> pair: frequencyTable){
        strFreqTable += to_string(pair.first) + ":" +to_string(pair.second) + ", ";
    }
    strFreqTable.pop_back();
    strFreqTable.pop_back();
    strFreqTable += "}";

    output << strFreqTable;
    HuffmanNode* huffNode = buildEncodingTree(frequencyTable);
    map<int, string> encdingMap = buildEncodingMap(huffNode);
    input.clear(); // removes any current eof/failure flags
    input.seekg(0, ios::beg); // tells the stream to seek back to the beginning
    encodeData(input, encdingMap, output);
    freeTree(huffNode);
}


void decompress(ibitstream& input, ostream& output) {
    string  strFreqTable;
    map<int, int>  frequencyTable;
    char ch;
    string key;
    string value;
    bool isKey = false;
    while(ch != '}'){
        input.get(ch);
        if (ch != '{' && ch != ' '){
            if(ch == ':' ){
                isKey = true;
            }else if(ch == ','){
                frequencyTable[stoi(key)] = stoi(value);
                isKey = false;
                key = "";
                value = "";
            }else if (!isKey){
                key += ch;
            }else {
                value += ch;
            }
        }
    }
    frequencyTable[stoi(key)] = stoi(value); // lägg till sista
    HuffmanNode* huffNode = buildEncodingTree(frequencyTable);
    map<int, string> encdingMap = buildEncodingMap(huffNode);
    decodeData(input, huffNode, output);
    freeTree(huffNode);
}

void freeTree(HuffmanNode* node) {
    HuffmanNode* current = node;
    if (current != nullptr){
        if (current->isLeaf()){
            delete current;
            return;
        }
        else{
            freeTree(current->one);
            freeTree(current->zero);
            delete current;
        }
    }
}
