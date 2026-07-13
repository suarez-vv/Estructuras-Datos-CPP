//Autor: Suárez, V.V.
#include "ArbolEnfrentamientos.h"

int main(){
    int selec;
    bool jugado = true; /*Si el torneo ya se jugo una vez, la simluacion no puede correr otra vez*/
    ColaJugadores j;
    j.crearColaConArchivo(); //Crear la cola de jugadores en base al archivo que contiene los nombres de estos.
    Bracket b;


    do{
        cout << "\n----------------------------------------------------------";
        cout << "\n\t\t\t ---> MENU <---";
        cout << "\n\t [1] Mostrar lista de jugadores a participar en el torneo.";
        cout << "\n\t [2] Simular torneo.";
        cout << "\n\t [3] Mostrar progreso del torneo.";
        cout << "\n\t [4] Mostrar campeon del torneo.";
        cout << "\n\t [5] Mostrar trayectoria del campeon.";
        cout << "\n\t [0] Salir del programa.";
        cout << "\n\n\t Elige una opcion: ";
        cin >> selec;

        switch(selec){
            case 1: 
                if(!j.print()){ //Mostrar los jugadores registrados para participar
                    cout << "\n\t No hay participantes registrados, el torneo ya se jugo o aun no ha abierto su convocatoria.\n";
                }
                break;
            case 2: //Construir el arbol en base a la cola de jugadores creada anteriormente
                if(b.construirDesdeCola(j, jugado)){
                    b.simular();
                }
                break;
            case 3: 
                b.mostrarRondas(); //Mostrar las rondas una vez que ya se jugo (simulo) el torneo
                break;
            case 4:
                if(b.campeon().nombre == "vacio"){
                    break;
                }else{
                    cout << "\n\t El campeon del torneo es:\n";
                    cout << "\n\t ---> " << b.campeon().nombre << " <---";
                }
                break;
            case 5:
                b.trayectoriaCampeon(); //Partidos jugados por el campeon
                break;
            case 0: cout << "\n\t Saliendo del programa...";
                break;
        }
    }while(selec != 0);
    
    return 0;
}