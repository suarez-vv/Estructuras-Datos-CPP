//Autor: Suárez, V.V.
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void siftDown(vector<int>& arr, int n, int i){
        while(true){
            int largest = i, left = 2*i +1, right = 2*i + 2;

            if(left < n && arr[left] < arr[largest]){
                largest = left;
            }

            if(right < n && arr[right] < arr[largest]){
                largest = right;
            }

            if(largest == i) break;

            swap(arr[i], arr[largest]);
            i = largest;

        }
    }

void heapSort(vector<int>& arr, int n){
    //Construir max-heap
    for(int i = n/2 -1; i>=0; --i) siftDown(arr, n, i);
    //extraer maximos al final
    for(int i = n-1; i>=1; --i){
        swap(arr[0], arr[i]);
        siftDown(arr, n, i);
    }
}

void print(vector<int>& arr, int n){
            for(int i=0; i<n; ++i) cout << arr[i] << " ";
            cout << endl;
        }

int main(){
    int n = 1000;
    vector<int> vec(n);
    srand(time(0));

    // Llenar vector con numeros aleatorios
    for (int i = 0; i < n; i++) {
        vec[i] = rand() % 100 + 1;
    }

    cout << "\nVector original:\n";
    print(vec, n);

    // inica el cronometro
    auto start = high_resolution_clock::now();

    heapSort(vec,n);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    // acaba el cronometro

    cout << "\nVector ordenado con Bubble Sort:\n";
    print(vec, n);

    cout << "\nTiempo de ejecucion: " << duration.count() << " ms\n";

    return 0;
}