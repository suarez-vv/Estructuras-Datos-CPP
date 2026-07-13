//Autor: Suárez, V.V.
#include <iostream>
#include <fstream>
#include <string>
#define CAP 8 //Capacidad maxima de jugadores 
using namespace std;

//Estructura para manejar nombre de cada jugador
struct Jugador{
    string nombre;
};

//Clase para crear y manejar la cola que contiene los nombres de los jugadores
class ColaJugadores{
    private:
        Jugador jugadores[CAP];
        int frente, fin;
        fstream Nombresjugadores;

        bool archivoJugadores(fstream &Nombresjugadores){ /*Crea la cola de jugadores en base a un archivo .txt guardado previamente*/
            Nombresjugadores.open("jugadores.txt", ios::in|ios::out);
            if(!Nombresjugadores){
                cout << "\n\t El archivo no se abrio correctamente.\n";
                return false;
            }else{
                Nombresjugadores.seekg(ios::beg);

                Jugador nomJugador;
                while(getline(Nombresjugadores, nomJugador.nombre)){ /*Lee cada jugador de una linea del archivo,
                    y lo ingresa a la cola con el metodo enqueue()*/
                    enqueue(nomJugador);
                }

                Nombresjugadores.close(); 
            }

            return true;
        }

    public :
        ColaJugadores (){ //Constructor de la cola
            frente = 0;
            fin = -1;
        }

        bool enqueue (const Jugador &j){ //Agregar un elemento (jugador) al final de la cola
            Jugador aux;
            if(isFull()){
                cout << "\n\t Lista de jugadores completa.\n";
                return false;
            }else{
                //Si el nombre del jugador se repite, le agregamos una etiqueta de (Copia) 
                for(int i=frente; i<=fin; i++){
                    if(jugadores[i].nombre == j.nombre){
                        aux.nombre = j.nombre + " (Copia)";
                        jugadores[++fin] = aux;
                        return true;
                    }
                }

                //Si el nombre esta vacio le agregamos una etiqueta de "BYE"
                if(j.nombre == ""){
                    aux.nombre = "BYE";
                    jugadores[++fin] = aux;
                    return true;
                }
                
                jugadores[++fin] = j; //Si no se cumple ninguna de las anteriores insertamos asi como venga
                return true;
            }

            return true;
        }

        //Quitar el primer elemento de la cola
        bool dequeue (){
            if(isEmpty()){
                cout << "\n\t La lista de jugadores esta vacia.\n";
                return false;
            }else{
                ++frente; //Eliminacion logica (Modificamos el frente y ya no tomamos en cuenta el elemento que estaba en esa posicion)
            }

            return true;
        }

        //Verificar si la cola esta vacia
        bool isEmpty () const{
            return frente > fin;
        }

        //Verificar si la cola esta llena
        bool isFull () const{
            return fin == CAP-1;
        }

        Jugador front () const{ //Sacamos el jugador que se encuentra en el frente de la cola
            if(isEmpty()){
                cout << "\n\t La lista de jugadores esta vacia.\n";
                Jugador vacio;
                vacio.nombre = "";
                return vacio;
            }else{
                return jugadores[frente];
            }
        }

        void crearColaConArchivo(){ //Metodo que llama a la funcion usada para crear una cola desde un archivo
            archivoJugadores(Nombresjugadores);
        }

        //Impresion de la lista de jugadores registrados
        bool print () const{
            if(isEmpty()){
                return false;
            }else{
                cout << "\n\t Los jugadores registrados para el torneo son: \n";
                for(int i=frente; i<=fin; i++){
                    cout << "\t\t" << i+1 << ".- "<< jugadores[i].nombre << endl;
                }
                return true;
            }
            return true;
        }
};