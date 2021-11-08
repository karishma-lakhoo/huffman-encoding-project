#include <iostream>
#include <map>
#include <vector>
#include <queue>


using namespace std;

class Node{
public:
    char character;
    unsigned frequency;  // this is the frequency of the character
    Node* Left;
    Node* Right;
//    int asciiIndex;
//    bool isLeaf; // decide if its a leaf when building a tree

    Node();
    Node* createNode(char ch, unsigned freq, Node* l, Node* r);
    ~Node();
};

Node::Node() {
    character = '*';
    frequency = 0;
    Left = nullptr;
    Right = nullptr;
//    asciiIndex = 0;
}

Node::~Node() {
    delete Left;
    delete Right;
}

Node *Node::createNode(char ch, unsigned int freq, Node *l, Node *r) {
    Node* node = new Node();
    node->character = ch;
    node->frequency = freq;
    node->Left = l;
    node->Right = r;
//    node->asciiIndex = 0;
//        isLeaf = false;
    return node;
}

struct compare{
    bool operator()(Node* left, Node* right){
        return left->frequency < right->frequency;
    }

};
bool valueComparison(const pair<char, int> &a, const pair<char, int> &b){
    return a.second< b.second;
}

class HuffmanTree{
public:
    unsigned treeSize; //current size of the huffman tree
    unsigned treeCapacity; //capacity of the tree
    Node** array; // array of node pointers
    vector<Node> nodeVector; //vector of node pointers
    vector<pair<char, int>> characterFrequencyVector;
    HuffmanTree();
    HuffmanTree* minHeapHuffmanTree = new HuffmanTree(); // this also creates an empty tree
    HuffmanTree* createHuffmanTree(unsigned treeCapacity); // this creates an empty tree



    void buildingTheHuffmanTree();
    void sortedVectorOfCharacterFrequencyPairs(); // this stores the input in a vector that is sorted according to the frequency of the characters
    void swapHuffmanTreeNodes(Node** a, Node** b);
//    bool heapSizeOne(priority_queue<Node*, vector<Node*>, compare> priorityQueueOfNodes);

//    so here i can choose to create my own minHeap or i can use a priority queue with a compare function. The priority queue is the easier option

};

HuffmanTree::HuffmanTree() {
    treeSize = 0;
    treeCapacity = 0;
    array = nullptr;
//    what if i changed the array to a vector, since then i wouldnt need to allocate memory in advance and i could simply access it without pointers

}

//HuffmanTree *HuffmanTree::createHuffmanTree(unsigned int capacity){
//    HuffmanTree* minHeapHuffmanTree = new HuffmanTree();
//    minHeapHuffmanTree->treeSize = 0;
//    minHeapHuffmanTree->treeCapacity = capacity;
////    minHeapHuffmanTree->array = (Node**) malloc(minHeapHuffmanTree->treeCapacity *sizeof(Node*)); // this allocates memory for the array of pointers and returns a pointer to i
//    return minHeapHuffmanTree;
//}




void HuffmanTree::sortedVectorOfCharacterFrequencyPairs() {
    string inputString;
    getline(cin, inputString);
    map<char, int> frequencyMap;
    for(char i: inputString){
        frequencyMap[i]++;
    }

    for(auto &it : frequencyMap){
        characterFrequencyVector.emplace_back(it.first, it.second);
    }
    sort(characterFrequencyVector.begin(), characterFrequencyVector.end(), valueComparison);
    //this part just prints the frequency vector
    for(auto i: characterFrequencyVector){
        cout << i.first << " " << i.second << endl;
    }

}



void HuffmanTree::buildingTheHuffmanTree() {
    //    this is the priority queue that will store all the nodes - i think im gonna use this instead of the tree
    priority_queue<Node*, vector<Node*>, compare> priorityQueueOfNodes;

    // here we are pushing all the leaf nodes to the priority queue
//    for(auto &i : characterFrequencyVector){
//        Node* tempNode = new Node();
//        tempNode->createNode(i.first, i.second, nullptr, nullptr);
//        priorityQueueOfNodes.push(tempNode);
//    }
//
//    //iterating through the heap while it does not become size 1
//    while(priorityQueueOfNodes.size() != 1){
//        cout << "asdf" << endl;
//    }


}





void HuffmanTree::swapHuffmanTreeNodes(Node **nodeOne, Node **nodeTwo) {
    Node* temp = *nodeOne;
    *nodeOne = *nodeTwo;
    *nodeTwo = temp;
}
// this checks if the heap has a size of 1
//bool HuffmanTree::heapSizeOne(priority_queue<Node*, vector<Node*>, compare> priorityQueueOfNodes) {
//    if(priorityQueueOfNodes.size() == 1){
//        return true;
//    }
//    else{
//        return false;
//    }
//}



//void sortedVectorOfCharacterFrequencyPairs(string& inputString){
//    map<char, int> frequencyMap;
//    for(char i: inputString){
//        frequencyMap[i]++;
//    }
//
//    vector<pair<char, int>> characterFrequencyVector;
//    for(auto &it : frequencyMap){
//        characterFrequencyVector.emplace_back(it.first, it.second);
//    }
//    sort(characterFrequencyVector.begin(), characterFrequencyVector.end(), valueComparison);
//    for(auto i: characterFrequencyVector){
//        cout << i.first << " " << i.second << endl;
//    }
//}


int main(){
    HuffmanTree test;
//    test.sortedVectorOfCharacterFrequencyPairs();
    cout << endl;
    cout << endl;
//    test.buildingTheHuffmanTree();


    return 0;
}


