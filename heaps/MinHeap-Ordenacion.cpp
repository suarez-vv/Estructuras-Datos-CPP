//Autor: Suárez, V.V.
#include <iostream>
using namespace std;

class MinHeap{
    int data[50];
    int size;

    void siftDown(int i){
        while(true){
            int left = 2*i +1;
            int right = 2*i +2;
            int smallest = i;

            if(left < size && data[left] < data[smallest]){
                smallest = left;
            }

            if(right < size && data[right] < data[smallest]){
                smallest = right;
            }

            if(smallest == i) break;

            swap(data[i], data[smallest]);
            i = smallest;

        }
    }

    public:
        MinHeap(): size(0) {}

        void insert(int v){
            data[size] = v;
            int i = size;

            //Reordenar hacia arriba
            while(i > 0 && data[i] < data[(i-1)/2]){
                swap(data[i], data[(i-1)/2]);
                i = (i-1)/2;
            }
            ++size;
        }

        int extractMin(){
            if(size == 0) {cout << "\n\t Heap vacio.\n"; return -1;}
            int minVal = data[0];
            siftDown(0);
            return minVal;
        }

        void print(){
            for(int i=0; i<size; ++i) cout << data[i] << " ";
            cout << endl;
        }
};

int main(){
    MinHeap h;
    int values[] = {10, 4, 1, 15, 20, 0, 8};
    for(int v :  values) h.insert(v);
    h.print();

    cout << "\n\n\t Minimo: " << h.extractMin() << endl;
    h.print();
    return 0;
}