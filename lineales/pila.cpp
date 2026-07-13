//Autor: Suárez, V.V.
#include <iostream>
#include <string>
#define TAM 5

using namespace std;

class Pila{
    public:
        int datos[TAM];
        int tope;

         Pila(){
            tope = -1;
        }

        bool isEmpty(){
            return tope == -1;
        }

        bool isFull(){
            return tope == 4;
        }

        void push(int v){
            if(isFull()){
                cout << "Pila llena" << endl;
            }else{
                datos[++tope] = v;
            }
        }

        void pop(){
            if(isEmpty()){
                cout << "Pila vacia";
            }else{
                tope--;
            }
        }

        void mostrar(){
            if(isEmpty()){
                cout << "\n\n\tLa pila se encuentra vacia.";
            }else{
                cout << "\n\n\t Pila: \n";
                cout << "\t";
                for(int i=tope; i>=0; --i){
                    cout << datos[i] << " ";
                }
            }
        }
};

void callPush(Pila &pila);
void callPop(Pila &pila);

int main(){
    Pila pila;
    int selec;

    do{
        cout << "\n\n\t\t\t---> MENU <---";
        cout << "\n\t [1] Push";
        cout << "\n\t [2] Pop";
        cout << "\n\t [3] Mostrar pila";
        cout << "\n\t [0] Salir del programa";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: callPush(pila);
                break;
            case 2: callPop(pila);
                break;
            case 3: pila.mostrar();
                break;
            case 0: return 0;
                break;
            default: cout << "\n\n\tERROR. Opcion invalida.";
                break;
        }

    }while(selec != 0);

    return 0;
}

void callPush(Pila &pila){
    int num;
    char resp;
    do{
        if(pila.isFull()){
            cout << "\n\nLa pila esta llena, no se pueden insertar mas elementos.";
            break;
        }else{
            cout << "\n\n\tDame el numero que quieres insertar: ";
            cin >> num;
            pila.push(num);
        }
        pila.mostrar();
        do{
            cout << "\n\nQuieres insertar otro elemento? s/n: ";
            cin >> resp;
            cin.ignore();
        }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
    }while(resp == 's' || resp == 'S');
}

void callPop(Pila &pila){
    char resp;
    do{
        if(pila.isEmpty()){
            cout << "\n\nLa pila esta vacia, no se pueden extraer elementos de ella.";
            break;
        }else{
                pila.mostrar();
                cout << "\n\tExtrayendo elemento de la pila...";
                pila.pop();
                pila.mostrar();
                do{
                    cout << "\n\nQuieres extraer otro elemento? s/n: ";
                    cin >> resp;
                    cin.ignore();
                }while(resp != 's' && resp != 'S' && resp != 'n' && resp != 'N');
            
        }
    }while(resp == 's' || resp == 'S');
}