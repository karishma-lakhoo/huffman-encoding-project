#include <iostream>
#include <map>
#include <vector>


using namespace std;

class BinaryHeap{

public:
    vector<int> data;

    int parentIndex(int idx){
        return (idx-1)/2;
    }

    int leftChildIndex(int idx){
        return (2*idx)+1;
    }

    int rightChildIndex(int idx){
        return (2*idx)+2;
    }
    void swop(int &x, int &y){
        int temp = x;
        x = y;
        y = temp;
    }


    //  this function is going to be used in the push function when we push values to the parent nodes, and we want to check if this violates the heap property
    void heap_index_up(int &idx){
        int parent_index = parentIndex(idx);
//        this is to check if the parent node value violates the heap property
        if(data[parent_index] < data[idx] && idx != 0){
            swop(data[idx], data[parent_index]);
//            this repeats until the the root node which has an index of 0
            heap_index_up(parent_index);
        }
    }

    // this function adjusts the value at node index idx since it and its 2 children violates the heap property
    void heap_index_down(int idx){
        int left_index = leftChildIndex(idx);
        int right_index = rightChildIndex(idx);
        int largest_index = idx;

// now to compare the value at the parent node with its children and find the largest child
        if(data[left_index] > data[idx]&& left_index < data.size()){
            largest_index = left_index;
        }
        if(data[right_index] > data[largest_index] && right_index < data.size()){
            largest_index = right_index;
        }
        if(largest_index != idx){
            swop(data[idx], data[largest_index]);
//            this repeats until the last node with the largest value
            heap_index_down(largest_index);
        }
    }

    void push(int value){
        data.push_back(value);
        int index_of_new_element = data.size() - 1;
        heap_index_up(index_of_new_element);
    }

    void pop(){
//        replacing the root of the heap with the last element and removing the largest value (the root in this case)
        data[0] = data.back();
        data.pop_back();
        heap_index_down(0);

    }

    void print(){
        for(auto &v : data){
            cout << v << " ";
        }
        cout << endl;
    }
};



////reformatted
lass BinaryHeap{

        public:
        vector<int> data;

        int parentIndex(int idx){
            return (idx-1)/2;
        }

        int leftChildIndex(int idx){
            return (2*idx)+1;
        }

        int rightChildIndex(int idx){
            return (2*idx)+2;
        }
        void swop(int &x, int &y){
            int temp = x;
            x = y;
            y = temp;
        }
        void heap_index_up(int &idx);

        void heap_index_down(int idx);

        void push(int value);
        void pop();
        void print();

};

void BinaryHeap::heap_index_up(int &idx) {
    int parent_index = parentIndex(idx);
//        this is to check if the parent node value violates the heap property
    if(data[parent_index] < data[idx] && idx != 0){
        swop(data[idx], data[parent_index]);
//            this repeats until the the root node which has an index of 0
        heap_index_up(parent_index);
    }
}


// this function adjusts the value at node index idx since it and its 2 children violates the heap property
void BinaryHeap::heap_index_down(int idx) {
    int left_index = leftChildIndex(idx);
    int right_index = rightChildIndex(idx);
    int largest_index = idx;

// now to compare the value at the parent node with its children and find the largest child
    if(data[left_index] > data[idx]&& left_index < data.size()){
        largest_index = left_index;
    }
    if(data[right_index] > data[largest_index] && right_index < data.size()){
        largest_index = right_index;
    }
    if(largest_index != idx){
        swop(data[idx], data[largest_index]);
//            this repeats until the last node with the largest value
        heap_index_down(largest_index);
    }
}
void BinaryHeap::push(int value) {
    data.push_back(value);
    int index_of_new_element = data.size() - 1;
    heap_index_up(index_of_new_element);

}

void BinaryHeap::pop() {
    //replacing the root of the heap with the last element and removing the largest value (the root in this case)
    data[0] = data.back();
    data.pop_back();
    heap_index_down(0);
}
void BinaryHeap::print() {
    for(auto &v : data){
        cout << v << " ";
    }
    cout << endl;
}





