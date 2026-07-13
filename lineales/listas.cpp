//Autor: Suárez, V.V.
#include <iostream>

using namespace std;

class Nodo{
    public:
        int dato;
        Nodo* siguiente;

        //Constructor de la clase
        Nodo(int v){
            dato = v;
            siguiente = nullptr;
        }
};

class Lista{
    public:
        Nodo* cabeza;

        //Constructor
        Lista(){
            cabeza = nullptr;
        }

        void insertarInicio(int v){
            Nodo* nuevo = new Nodo(v);
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }                                /*Lista es de tipo: LIFO*/

        void eliminarInicio(){
            if(!cabeza){
                return;
            }else{
                Nodo* tmp = cabeza;
                cabeza = cabeza->siguiente;
                delete tmp;
            }
        }

        bool buscar(int v){
            Nodo* aux = cabeza;
            while(aux){
                if(aux->dato == v){
                    return true;
                }
                aux = aux->siguiente;   //  aux++;
            }

            return false;
        }

        void mostrar(){
            Nodo* aux = cabeza;
            cout << "\nMostrando la lista:\n\n";
            while(aux){
                cout << aux->dato << " -> ";
                aux = aux->siguiente;
            }
            cout << "NULL\n\n";
        }
};

int main(){
    Lista lista;
    lista.insertarInicio(1);
    lista.insertarInicio(2);
    lista.insertarInicio(3);
    lista.mostrar();
    lista.eliminarInicio();
    lista.mostrar();
    bool buscar = lista.buscar(1);
    if(buscar){
        cout << "\nSi esta\n";
    }else{
        cout << "\nNo esta\n";
    }
    return 0;
}

