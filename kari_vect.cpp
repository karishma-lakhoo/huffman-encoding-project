#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
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
//    bool isLeaf; // decide if its a leaf when building a tree

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
//        isLeaf = false;
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

class Huffman1Tree{
public:
    unsigned treeSize; //current size of the huffman tree
    unsigned treeCapacity; //capacity of the tree
    vector<Node*> nodeVector; //vector of node pointers
    vector<pair<unsigned char, int>> characterFrequencyVector;
    vector<Node*> NodeHeap;
    void nodeVectorPrint();
    string codeString;

    Huffman1Tree();
    void sortedVectorOfCharacterFrequencyPairs(); // this stores the input in a vector that is sorted according to the frequency of the characters
    void pop_front_on_vector(vector<Node*> &nodeVect);
    Node* creatingTheTree();
    void getCodes(Node* root, string str);
    void printCodes();
// traversing through the tree


//    number of bits used in the original string

//    number of bits used in the encoded string

};

Huffman1Tree::Huffman1Tree() {
    treeSize = 0;
    treeCapacity = 0;

}

void Huffman1Tree::sortedVectorOfCharacterFrequencyPairs() {
    string inputString;
//    getline(cin, inputString);
    inputString = "she sells sea shells by the sea shore";
    map<char, int> frequencyMap;
    for(char i: inputString){
        frequencyMap[i]++;
    }

    for(auto &it : frequencyMap){
        characterFrequencyVector.emplace_back(it.first, it.second);
    }

    std::sort(characterFrequencyVector.begin(), characterFrequencyVector.end(), combinedComparison);

    //this part just prints the frequency vector
    for(auto i: characterFrequencyVector){
        cout << i.first << " " << i.second << endl;
    }
    cout << "*****" << endl;
}

void Huffman1Tree::pop_front_on_vector(vector<Node*> &nodeVect) {
    if(nodeVect.size() > 0){
        nodeVect.erase(nodeVect.begin());
    }
}

void Huffman1Tree::nodeVectorPrint() {
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

Node* Huffman1Tree::creatingTheTree() {
    // here we are pushing all the leaf nodes to the priority queue
    for(int i = 0; i < characterFrequencyVector.size(); i++){
        unsigned char tempChar = characterFrequencyVector[i].first;
        cout << tempChar << ": ";
        int priorityAsciiChar = int(characterFrequencyVector[i].first);
        cout << priorityAsciiChar << endl;
        Node* internalNodeLeaf = Node::createNode(tempChar, characterFrequencyVector[i].second, nullptr, nullptr, priorityAsciiChar);
        nodeVector.push_back(internalNodeLeaf);
    }

    cout << "before editing" << endl;
    nodeVectorPrint();

    cout << "after editing" << endl;
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

        nodeVectorPrint();
    }
    Node* root = nodeVector[0];
    return root;




//    //checking if all the nodes got pushed as leafs to the priority queue
//    while(nodeVector.size() != 0){
//        int i = 1;
//        cout << "asdf" << " " << i << endl;
//        cout << "its printing something dodgy here" << endl;
////        this is what are have stored in the min heap
//        cout << nodeVector.front()->frequency << endl;
//        cout << nodeVector.front()->Left->frequency << endl;
//        cout << nodeVector.front()->Right->frequency << endl;
//
//    }

}

void Huffman1Tree::getCodes(Node* root, string str) {
    if(root == nullptr){
        return;
    }
//    this is for when it reaches a leaf node
    if(!(root->Left) && !(root->Right)){
        cout << root->character << " :" << str << endl;
    }
    if(root->Left){
        getCodes(root->Left, str + "0");
    }
    if(root->Right){
        getCodes(root->Right, str + "1");
    }

}

void Huffman1Tree::printCodes() {
    getCodes(nodeVector[0], codeString);
}


int main(){
    Huffman1Tree test;
    string stringOfCodes;
    test.sortedVectorOfCharacterFrequencyPairs();
    Node* root = test.creatingTheTree();
    cout << "freq" << endl;
    cout << root->frequency << endl;
    test.getCodes(root, stringOfCodes);

    return 0;
};
