#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>


using namespace std;

class Node{
public:
    unsigned char character;
    unsigned frequency;  // this is the frequency of the character
    Node* Left;
    Node* Right;
    int asciiIndex;
    int priority = -1;

    static Node* createNode(unsigned char ch, unsigned freq, Node* l, Node* r, int priority);
    ~Node();
};


Node::~Node() {
    delete Left;
    delete Right;
}

Node* Node::createNode(unsigned char ch, unsigned int freq, Node* l, Node* r, int priority) {
    Node* node = new Node();
    node->character = ch;
    node->frequency = freq;
    node->Left = l;
    node->Right = r;
    node->asciiIndex = int(ch);
    node->priority = priority;
    return node;
}


struct compare{
    bool operator()(Node* left, Node* right){
        return left->frequency > right->frequency;
    }

};


bool combinedComparison(const pair<unsigned char, int> &a, const pair<unsigned char, int> &b){
    if(a.second == b.second){
        int asciiIntA = int(a.first);
        int asciiIntB = int(b.first);
        return asciiIntA < asciiIntB;
    }
    else{
        return a.second < b.second;
    }
}

bool combinedComparisonNodes(Node* a, Node* b) {
    if(a->frequency == b->frequency){
        int priorityA = int(a->priority);
        int priorityB = int(b->priority);
        return priorityA < priorityB;
    }
    else{
        return a->frequency < b->frequency;
    }
}

class HuffmanDecoder{
public:
    string inputKeys;
    string inputFrequencies;
    string inputStringEncoded = "100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000";
    vector<Node*> nodeVector; //vector of node pointers
    vector<pair<unsigned char, int>> characterFrequencyVector;
    void nodeVectorPrint();
    string codeString;
    map<unsigned char, string> codeMap;
    map<unsigned char, string>::iterator it;

    HuffmanDecoder();
    void sortedVectorOfCharacterFrequencyPairs(); // this stores the input in a vector that is sorted according to the frequency of the characters
    void pop_front_on_vector(vector<Node*> &nodeVect);
    Node* creatingTheTree();
    void getCodes(Node* root, string str);
    string stringDecoder(Node* root);


//    number of bits used in the original string

    void countBitsOriginal();
    void countBitsEncoded(string binaryNumber);

//    number of bits used in the encoded string


};

HuffmanDecoder::HuffmanDecoder() {
}

void HuffmanDecoder::sortedVectorOfCharacterFrequencyPairs() {
//    getline(cin, inputKeys);
//    getline(cin, inputFrequencies);

    inputKeys = "b o r t y a h l   e s";
    inputFrequencies = "1 1 1 1 1 2 4 4 7 7 8";
    vector<int> inputFrequenciesVector;
    for(int i = 0; i < (inputFrequencies.length()/2)+1; i++){
        int temp = int(inputFrequencies[2*i] - 48);
        inputFrequenciesVector.push_back(temp);
    }
    map<char, int> frequencyMap;
    for(int i = 0; i < (inputKeys.length()/2)+1; i++){
        frequencyMap[inputKeys[2*i]] = inputFrequenciesVector[i];
    }

    for(auto &it : frequencyMap){
        characterFrequencyVector.emplace_back(it.first, it.second);
    }

    std::sort(characterFrequencyVector.begin(), characterFrequencyVector.end(), combinedComparison);

//    //this part just prints the frequency vector
//    for(auto i: characterFrequencyVector){
//        cout << i.first << " ";
//    }
//    cout << endl;
//    for(auto i: characterFrequencyVector){
//        cout << i.second << " ";
//    }
//    cout << endl;
}

void HuffmanDecoder::pop_front_on_vector(vector<Node*> &nodeVect) {
    if(nodeVect.size() > 0){
        nodeVect.erase(nodeVect.begin());
    }
}

void HuffmanDecoder::nodeVectorPrint() {
    for(auto &i : nodeVector){
        cout << i->frequency << "\t";
    }
    cout << endl;
    for(auto &i : nodeVector){
        cout << i->character << "\t";
    }
    cout << endl;
    for(auto &i : nodeVector){
        cout << i->priority << "\t";
    }

    cout << endl;
    cout << endl;

}

Node* HuffmanDecoder::creatingTheTree() {
    // here we are pushing all the leaf nodes to the priority queue
    for(int i = 0; i < characterFrequencyVector.size(); i++){
        unsigned char tempChar = characterFrequencyVector[i].first;
//        cout << tempChar << ": ";
        int priorityAsciiChar = int(characterFrequencyVector[i].first);
//        cout << priorityAsciiChar << endl;
        Node* internalNodeLeaf = Node::createNode(tempChar, characterFrequencyVector[i].second, nullptr, nullptr, priorityAsciiChar);
        nodeVector.push_back(internalNodeLeaf);
    }

//    extracting the 2 minimum leaves, adding them and pushing them to the queue
    while(nodeVector.size() != 1){
        Node* left = nodeVector.front();
        pop_front_on_vector(nodeVector);


        Node* right = nodeVector.front();
        pop_front_on_vector(nodeVector);

//      creating an internal node with the frequency equal to the sum of the left and right nodes
        int internalFrequency = left->frequency + right->frequency;
//        Node* internalNode = Node::createNode('$', internalFrequency, left, right, left->asciiIndex + right->asciiIndex);
        Node* internalNode = Node::createNode('*', internalFrequency, left, right, (((float(left->priority + right->priority)/244)*55)+42));
//        internalNode->createNode('$', internalFrequency, left, right); //'$' is a special value for internal nodes, not use
//      add this new node to the priority queue
        nodeVector.push_back(internalNode);


//        this is where i need to reorder it

        std::sort(nodeVector.begin(), nodeVector.end(), combinedComparisonNodes);

//        nodeVectorPrint();
    }
    Node* root = nodeVector[0];
    return root;

}


void HuffmanDecoder::getCodes(Node* root, string str){
    if(root == nullptr){
        return;
    }
//    this is for when it reaches a leaf node
    if(!(root->Left) && !(root->Right)){
        codeMap[root->character] = str;
//        cout << root->character << " :" << str << endl;
    }
    if(root->Left){
        getCodes(root->Left, str + "0");
    }
    if(root->Right){
        getCodes(root->Right, str + "1");
    }

}

//string HuffmanDecoder::printCodesForString() {
//    string outputString;
//    for(auto &i: inputString){
//        it = codeMap.find(i);
//        outputString += it->second;
//    }
//    return outputString;
//}

string HuffmanDecoder::stringDecoder(Node* root){
    string outputString  = "";
    Node* temp = root;
    for(int i = 0; i < inputStringEncoded.length(); i++){
        if(inputStringEncoded[i] == '0'){
            temp = temp->Left;
        }
        else if(inputStringEncoded[i] == '1'){
            temp = temp->Right;
        }
        if(!(temp->Left) && !(temp->Right)){
            outputString += curr->character;
            temp = root;
        }
    }
    return outputString;
}


//
//void Huffman1Tree::countBitsOriginal() {
//    unsigned int num = 0;
//    num = inputString.length()*8;
//    cout << "Total Bits (Original): " <<  num << endl;
//
//}
//
//void Huffman1Tree::countBitsEncoded(string binaryNumber) {
//    cout << "Total Bits (Coded): "  << binaryNumber.length() << endl;
//
//}


int main(){
    HuffmanDecoder test;
    string stringOfCodes;
    string output;
    test.sortedVectorOfCharacterFrequencyPairs();
    Node* root = test.creatingTheTree();
    test.getCodes(root, stringOfCodes);
    output = test.stringDecoder(root);
    cout << output << endl;
//    test.countBitsOriginal();
//    test.countBitsEncoded(output);

    return 0;
};
