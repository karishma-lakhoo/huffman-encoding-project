#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>


using namespace std;

unordered_map<char, int> suffering;
// A Tree node
class TreeNode{
public:
    char ch;
    int freq;
    TreeNode *left, *right;
};

// Function to allocate a new tree node
TreeNode* getNode(char ch, int freq, TreeNode* left, TreeNode* right)
{
    TreeNode* node = new TreeNode();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

void BuildFreq(string line){

    for (int i = 0; line[i]; i++){
        if (suffering.find(line[i]) == suffering.end()){
            suffering.insert(make_pair(line[i], 1));
        }

        else{
            suffering[line[i]]++;
        }
    }

    for (auto& pain : suffering){
        cout << pain.first << " ";
    }

    cout << endl;

    for (auto& pain : suffering){
        cout<< pain.second << " ";
    }
}


class comp{
public:
    bool operator()(TreeNode* l, TreeNode* r){
        return l->freq > r->freq;
    }
};

void encode(TreeNode* root, string str, unordered_map<char, string> &huffCode)
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffCode);
    encode(root->right, str + "1", huffCode);
}

void decode(TreeNode* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }

    if (!root->left && !root->right)
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] =='0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}


void buildHuffmanTree(string line){
    priority_queue<TreeNode*, vector<TreeNode*>, comp> pq;


    for (auto pair: suffering) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1){

        TreeNode *left = pq.top(); pq.pop();
        TreeNode *right = pq.top();	pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    TreeNode* root = pq.top();

    unordered_map<char, string> huffCode;
    encode(root, "", huffCode);

    string str = "";
    for (char ch: line) {
        str += huffCode[ch];
    }

    cout << str << '\n';

    cout << "Total Bits (Original):" << line.length()*8 << endl;

    cout << "Total Bits (Coded):" << str.length() << endl;

    int index = -1;
    cout << "\nDecoded string is: \n";
    while (index < (int)str.size() - 2) {
        decode(root, index, str);
    }
}

int main(){
    string line;

    getline(cin, line);

    BuildFreq(line);

    cout << endl;

    buildHuffmanTree(line);

    return 0;
}