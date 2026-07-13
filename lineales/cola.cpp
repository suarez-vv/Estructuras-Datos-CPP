//Autor: Suárez, V.V.
#include <iostream>
#define TAM 5

using namespace std;

class Cola{
    public:
        int datos[TAM];
        int frente, fin;

        Cola(){
            frente = 0;
            fin = -1;
        }

        bool isEmpty(){
            return frente > fin;
        }

        bool isFull(){
            return fin == TAM-1;
        }

        void enqueue(int v){
            if(isFull()){
                cout << "Cola llena" << endl;
            }else{
                datos[++fin] = v;
            }
        }

        void dequeue(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
            }else{
                ++frente;
            }
        }

        int front(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
                return -1;
            }else{
                return datos[frente];
            }
        }

        int size(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
                return -1;
            }else{
                return fin - frente + 1;
            }
        }

        void clear(){
            frente = 0;
            fin = -1;
        }

        void mostrar(){
            if(isEmpty()){
                cout << "Cola vacia" << endl;
            }else{
                cout << "La cola es: \n";
                for(int i=frente; i<=fin; i++){
                    cout << datos[i] << " ";
                }
            }
        }
};

int main(){
    Cola cola;
    int x;

    cola.enqueue(1);
    cout << "\nSe inserto: 1";
    cola.enqueue(2);
    cout << "\nSe inserto: 2";
    cout << endl;
    cola.mostrar();
    cola.dequeue();
    cout << "\nSe extrajo un elemento";
    cout << endl;
    cola.mostrar();
    x = cola.size();
    cout << endl;
    cout << "El tamanio de la cola es: " << x << endl;
    cola.dequeue();
    cout << "\nSe extrajo un elemento";
    cout << endl;
    cola.mostrar();
    

    return 0;
}