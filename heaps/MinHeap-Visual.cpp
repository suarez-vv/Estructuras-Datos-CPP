//Autor: Suárez, V.V.
#include <iostream>
#include <cmath>
using namespace std;

const int MAX = 20;  //Tamaño de heap

class MinHeap{
    int data[MAX];
    int size;

    void siftUp(int i){
        cout << "\n\t siftUp desde i = " << i;
        while(i > 0){
            int parent = (i-1)/2;
            cout << "\n\t Comparar data[" << i << "]" << data[i];
            cout << " con padre data[" << parent << "]" << data[parent];

            if(data[i] >= data[parent]){
                cout << "\n\t Propiedad cumplida\n";
                break; //Propiedad cumplida
            }
            cout << "\n\t swap(" << data[i] << "," << data[parent] << ")\n";
            swap(data[i], data[parent]);
            i = parent;
        }
    }

    void siftDown(int i){
        cout << "\n\t siftDown desde i= " << i;
        while(true){
            int left = 2*i +1;
            int right = 2*i +2;
            int smallest = i;

            if(left < size && data[left] < data[smallest]){ //Comparacion con el hijo izquiero para saber cual es el menor
                cout << "\n\t Hijo izq menor: data[" << left << "] = " << data[left];
                smallest = left;
            }

            if(right < size && data[right] < data[smallest]){ //Comparacion con el hijo derecho para saber cual es el menor
                cout << "\n\t Hijo der menor: data[" << right << "] = " << data[right];
                smallest = right;
            }

            if(smallest == i){
                cout << "\n\t Propiedad cumplida\n";
                break;
            }

            cout << "\n\t swap(" << data[i] << "," << data[smallest] << ")";
            swap(data[i], data[smallest]);
            i = smallest;

        }
    }

    public:
        MinHeap() : size(0){}

        void insertRaw(int value){
            if(isFull()) return;

            data[size] = value; //el vector data en la posicion donde se inserto (el tamanio o numero de elementos que hay) inserta el valor que se le mando
            siftUp(size);
            size++;
            printArray();
        }

        void printArray() const{  //Impresion del Heap (vector)
            cout << "\n\t Heap arreglo.\n";
            cout << "\n\t";
            for(int i=0; i<size; ++i){
                cout << data[i] << " ";
            }
            cout << endl;
        }

        bool extractMin(int& out){
            if(isEmpty()) return false;

            out = data[0];
            cout << "\n\t min = " << out;
            data[0] = data[--size];
            if(size > 0) siftDown(0);
            printArray();
            return true;
        }

        bool isFull(){ //Verificar si el monticulo esta lleno
            if(size == MAX){
                cout << "\n\t El Heap esta lleno.";
                return true;
            }
            return false;
        }

        bool isEmpty(){ //Verificar si el monticulo esta vacio
            if(size == 0){
                cout << "\n\t El Heap esta vacio.";
                return true;
            }
            return false;
        }
};

int main(){
    MinHeap h;
    h.insertRaw(20);
    h.insertRaw(15);
    h.insertRaw(30);
    h.insertRaw(10);
    h.insertRaw(5);
    h.printArray(); //el menor queda en la raiz

    int x;
    //if(!(cin>x)) break;  Para verificar si se ingreso algo a la variable 'x'
    cout << "\n\t Ingresa x: ";
    cin >> x;
    h.insertRaw(x);

    int v;
    h.extractMin(v);

    cout << "\n\t menor v=" << v << endl;

    return 0;
}