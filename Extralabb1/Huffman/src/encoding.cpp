// Kod för att implementera Huffmancoding, dvs bygga upp en frekvenstabell och ett Huffman-träd
// för att sedan användas för att komprimera och dekomprimera filer.
// johli622 stias606

#include "encoding.h"
#include <queue>
#include "huffmanutil.h"

/*
 * Traverserar Huffman-trädet och skapar en map med koder för varje löv bestående av
 * 1:or och 0:or beroende på om man går till vänster eller höger i trädet.
 */
void preorderTraversal(HuffmanNode root, string path, map<int, string>& encodingMap){
    if (root.isLeaf()){
        encodingMap[root.character] = path;
        return;
    }else{
        preorderTraversal(*root.zero, path + "0", encodingMap);
        preorderTraversal(*root.one, path + "1", encodingMap);
    }
}

/*
 * Bygger upp en frekvenstabell utifrån given input,
 * räknar antalet av varje tecken och tilldelar sedan det tecknet dess frekvens
 * i frekvenstabellen
 */
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

/*
 * Skappar ett kodningsträd där varje löv är ett tecken, löven placeras strategiskt ut med hjälp
 * av en priorityqueue som sorterar tecknen baserat på deras frekvens. Metoden en map som kopplar
 * varje tecken till en frekvens. Tecken med hög frekvens placeras högt upp i trädet.
 */
HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode*> pqueue;
    HuffmanNode* firstMax, *secondMax;
    HuffmanNode* merge;
    for (auto it = freqTable.begin(); it != freqTable.end(); it ++){
        HuffmanNode* huffNode = new HuffmanNode(it->first, it->second, nullptr); // skapar nod med tecken, frekvens, utan några barn
        pqueue.push(huffNode);
    }
    while (pqueue.size() > 1){
        firstMax = pqueue.top();
        pqueue.pop();
        secondMax = pqueue.top();
        pqueue.pop();
        merge = new HuffmanNode(NOT_A_CHAR, (firstMax->count + secondMax->count), firstMax, secondMax);
        pqueue.push(merge);
    }
    return merge;
}

/*
 * Bygger upp en map där varje tecken är kopplat till dess binära kodning i
 * Huffman-trädet. Kallar på preorderTraversal som bygger upp strängen av tecknets binära kod.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    preorderTraversal(*encodingTree, "", encodingMap);
    return encodingMap;
}

/*
 * Metoden tar in input, en map som kopplar varje tecken till en sträng som
 * representerar en teckents binära kod i huffman-trädet och output. Med hjälp av encoding-map
 * förvandlas input-data till binär kod som skrivs till output.
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int sign;
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

/*
 * Läser bitar från den givna indatafilen en i taget och går igenom kodningsträdet för att skriva det
 * ursprungliga okomprimerade innehållet av filen till den givna utdataströmmen.
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* current = encodingTree;
    int sign;
    while((sign = input.readBit()) != -1){
        if (sign == 1){
            current = current->one;
        } else {
            current = current->zero;
        }
        if (current->isLeaf()){
            output.put(current->character);
            current = encodingTree; 
        }
     }
     input.clear(); // removes any current eof/failure flags
     input.seekg(0, ios::beg); // tells the stream to seek back to the beginning
}

/*
 * Den här funktionen komprimerar den givna indatafilen på den givna utdatafilen.
 * Den läser indatafilen ett tecken i taget, bygga upp en kodning av dess innehåll och
 * skriver en komprimerad version av den indatafilen,inklusive en header,
 * till den specificerade utdatafilen. Funktionen byggs på övriga kodningsfunktioner.
 */
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
    map<int, string> encodingMap = buildEncodingMap(huffNode);
    input.clear(); // removes any current eof/failure flags
    input.seekg(0, ios::beg); // tells the stream to seek back to the beginning
    encodeData(input, encodingMap, output);
    freeTree(huffNode);
}

/*
 * Läser bitarna från den givna indatafilen en i taget, inklusive en header som ligger i början av filen,
 * för att kunna skriva ursprungsinnehållet av den filen till filen specificerad av output-parametern.
 */
void decompress(ibitstream& input, ostream& output) {
    map<int, int>  frequencyTable; // ska byggas upp utifrån headern
    char ch;
    string key;
    string value;
    bool isKey = false;
    while(ch != '}'){ // motsvarar slutet av headern
        input.get(ch); // hämtar ut tecknet
        if (ch != '{' && ch != ' '){
           if(ch == ':' ){
                isKey = true; // nyckeln är klar, värdet kommer efter
           }else if(ch == ','){ // nu kommer nästa värde
               frequencyTable[stoi(key)] = stoi(value); // sätter in nyckeln och dess värde
               isKey = false; // nu har vi satt in key, vill hitta nästa
               key = ""; // återställer
               value = "";
            }else if (!isKey){
                key += ch; // bygger upp nyckeln
            }else {
                value += ch; // bygger upp värdet
            }
        }
    }
    frequencyTable[stoi(key)] = stoi(value); // lägg till sista
    HuffmanNode* huffNode = buildEncodingTree(frequencyTable);
    map<int, string> encdingMap = buildEncodingMap(huffNode);
    decodeData(input, huffNode, output);
    //freeTree(huffNode);
}

/*
 * Frigör utrymmet för alla noder i vårt Huffman-träd
 */
void freeTree(HuffmanNode* node) {
    HuffmanNode* current = node;
    if (current != nullptr){
        if (current->isLeaf()){ // ta bort alla löv!
            delete current;
            return;
        }else{
            freeTree(current->one); // rekursivt anrop så alla löv tas bort baklänges
            freeTree(current->zero);
            delete current;
        }
    }
}

