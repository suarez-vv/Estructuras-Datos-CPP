//Autor: Suárez, V.V.
#include <ctime>
#include <cmath>
#include "ColaJugadores.h"

//Estructura para el manejo de nodos que cada arbol
struct Nodo{
    Jugador val;
    int goles, levelLeaf;
    Nodo* izq;
    Nodo* der;
    explicit Nodo(int ll, Jugador v) : val(v), goles(0), levelLeaf(ll), izq(nullptr), der(nullptr){};
};

//Clase para manejar los enfrentamientos y estructuracion del arbol
class Bracket{
    private :
        Nodo* raiz ;
        int maxLevelLeafs; //Altura del arbol (nivel en el que se encontraran los jugadores al inicio del torneo)

    public:
        Bracket(){ /*Constructor, establece la raiz del arbol en nullptr (aun no se crea el arbol), y ademas 
            establece el nivel en el que estaran las hojas (jugadores)*/
            raiz = nullptr;
            maxLevelLeafs = ceil(log(CAP)/log(2)); /*Para obtener la altura de las hojas usamos la formula matematica para arboles m-arios completos,
            que dice, techo de log base m de l (siendo m=2 por ser un arbol binario, y CAP l=numero de hojas), es menor o igual a la altura del arbol*/
        }; 

        ~Bracket(){ //Destructor
            liberar(raiz);
        }

        // Construye arbol completo a partir de lista  cola de hojas
        bool construirDesdeCola (ColaJugadores &cola, bool &jugado){
            if(!jugado){
                /*Si el torneo ya fue simulado una vez, la lista se borro, y por lo tanto no se puede jugar de nuevo*/
                cout << "\n\t El torneo ya fue jugado en esta edicion, espera la proxima convocatoria.\n";
                return false;
            }
            jugado = false;
            //Al inicio, la raiz siempre estara con todos sus datos vacios
            Jugador vacio;
            vacio.nombre = "vacio";
            raiz = new Nodo(0, vacio);
            llenar(raiz, cola); //Primera llamada para la creacion del arbol vacio,, excepto las hojas
            return true;
        };

        // Simula rondas llenando ganadores hacia la raiz
        void simular (){
            srand(time(0)); //Semillero para numeros aleatorios
            int cont = 0; //Variable auxiliar para imprimir en que ronda del torneo nos encontramos
            while(raiz->val.nombre == "vacio"){
                simularRecursivo(raiz);
                /*Mientras el nombre de la raiz esta vacio imprimimos la ronda con un numero*/
                if(raiz->val.nombre == "vacio") imprimirRondas(++cont, raiz);
            }
            /*Cuando el nombre de la raiz ya no esta vacio mandamos un indicador (-1) para imprimirla como ronda final*/
            imprimirRondas(-1, raiz);
        }

        //Logica recursiva para la simulacion de los partidos
        void simularRecursivo(Nodo* n){
            if(!n) return; //Verificacion si la raiz no existe
            if(!n->izq || !n->der) return; //Verificacion si uno de los hijos no existe
            if(n->izq->val.nombre == "vacio" || n->der->val.nombre == "vacio"){
                /*Si los hijos izq o der estan vacios, quiere decir que ahi aun no se ha jugado el partido, entonces se simula*/
                simularRecursivo(n->izq);
                simularRecursivo(n->der);
            }else{
                if(!verificacionesSimular(n)){ //Verificaciones relacionadas con los 'BYE', o partidos por default
                    do{
                        n->izq->goles = 0 + rand()%(5+1-0); //Creamos un numero aleatorio para los goles del nodo de la izquierda
                        n->der->goles = 0 + rand()%(5+1-0); //Creamos un numero aleatorio para los goles del nodo de la derecha
                    }while(n->izq->goles == n->der->goles);//Si el numero generado es igual (empate) que se repita la generacion de los numeros
                } 
                if(n->izq->goles > n->der->goles) n->val = n->izq->val; /*Si la cantidad de goles del nodo de la izquierda es mayor que el de la derecha
                pasa el jugador del nodo de la izquierda*/
                else n->val = n->der->val; //Si la cantidad de goles del nodo de la derecha es mayor que el de la izquierda, pasa el jugador (nodo) de la derecha
                    
                return;
            }
        }
        
        ///// Verificacion si en algun partido no hay jugador (hay un 'BYE'), que hacer para cada caso, y quien pasa. //////
        bool verificacionesSimular(Nodo* n){
            if(n->izq->val.nombre == "BYE" && n->der->val.nombre == "BYE"){ /* Si en ninguno de los nodos hay un jugador valido (hay un 'BYE'), pasa
                el de la izquierda para continuar con el torneo */
                n->izq->goles = 3;
                n->der->goles = 0;
                return true;
            }

            if(n->izq->val.nombre == "BYE" && n->der->val.nombre != "BYE"){ /* Si el nodo de la izquierda no tiene jugador (hay un 'BYE'), pasa automaticamente el jugador
                del nodo de la derecha con una diferencia de 3 goles a favor*/
                n->izq->goles = 0;
                n->der->goles = 3;
                return true;
            }
            if(n->der->val.nombre == "BYE" && n->izq->val.nombre != "BYE"){ /* Si el nodo de la derecha no tiene jugador (hay un 'BYE'), pasa automaticamente el jugador
                del nodo de la izquierda con una diferencia de 3 goles a favor*/
                n->izq->goles = 3;
                n->der->goles = 0;
                return true;
            }

            return false; //Si no se entro a ninguna de estas condiciones, quiere decir que en ambos nodos hay jugadores validos
        }

        // Impresion de las rondas del torneo segun se va simulando el mismo
        void imprimirRondas (int ronda, Nodo *n) const{
            if(ronda == -1){
                cout << "\n\n\t -------------------------------> RONDA FINAL <----------------------------------------"; //Ronda final (Ultimos dos equipos)
                imprimirJuego(n);

                cout << "\n\n\t -------------------------------> CAMPEON <----------------------------------------"; //Imprimir al campeon
                cout << "\n\n\t\t\t\t   --->>> " << n->val.nombre << " <<<---\n";
            }else{
                cout << "\n\n\t -------------------------------> RONDA " << ronda << " <----------------------------------------"; //Rondas de cuartos hasta semifinales
                imprimirRecursivo(n);
            }
        }

        //Llamada recursiva para imprimir cada ronda segun se va simulando el torneo
        void imprimirRecursivo(Nodo* n) const{
            if(n->izq->goles == 0 && n->der->goles == 0){ /*Si no hay goles en los hijos izq y der, seguimos recursando, si imprimos en este momento,
                imprimiriamos el partido que aun no se juega, los nodos en su nombre seria diferente a vacio, pero no tendrian goles, y el nodo en el
                que nos encontramos estaria vacio*/
                imprimirRecursivo(n->izq);
                imprimirRecursivo(n->der);
            }else{
                /*Cuando ya hay goles, quieres decir que el nodo en el que estamos, contiene al ganador, podemos imprimir el partido entre hijos izq y der*/
                imprimirJuego(n);         
                return;
            }
        }

        //Funcion para llenar el arbol desde la raiz, todo vacio, excepto las hojas (ahi se encuentran inicialmente los jugadores)
        void llenar(Nodo* n, ColaJugadores& cola){
            //Verificamos si estamos un nodo antes del nivel donde estaran las hojas (Los jugadores para la primera ronda)
            if(n->levelLeaf == (maxLevelLeafs-1)){
                /*Si estamos un nodo antes de las hojas entonces creamos nodo izquierdo y derecho con nombres de los jugadores en lugar de vacios*/
                n->izq = new Nodo(n->levelLeaf+1, cola.front()); 
                cola.dequeue(); //Una vez obtuvimos el nombre del jugador, lo sacamos de la cola
                n->der = new Nodo(n->levelLeaf+1, cola.front());
                cola.dequeue();
                return;
            }

            //Si no estamos un nodo antes de las hojas creamos los nodos vacios
            Jugador vacio;
            vacio.nombre = "vacio";
            //LLenamos el nodo de la izquierda con todos sus datos vacios 
            n->izq = new Nodo(n->levelLeaf+1, vacio);
            llenar(n->izq, cola); //Paso recursivo para crear rama hacia la izquierda
            //Llenamos el nodo de la izquierda con todos sus datos vacios
            n->der = new Nodo(n->levelLeaf+1, vacio);
            llenar(n->der, cola); //Paso recursivo para crear rama hacia la derecha
        };

        //Liberacion de memoria
        static void liberar(Nodo* nodo){
            if(!nodo) return; 
            liberar(nodo->der); //Liberamos todo lo que se encuentre a la izq y der, y finalmente el nodo raiz
            liberar(nodo->izq);
            delete nodo;
        }

        //Devolver al jugador campeon
        Jugador campeon () const{
            if(!raiz || raiz->val.nombre == "vacio"){ /*Si la no existe, o la raiz existe pero contiene "vacio", el torneo aun no llega a esa fase o no se ha jugado*/
                Jugador vacio;
                vacio.nombre = "vacio";
                cout << "\n\t El torneo aun no ha sido jugado, aun no hay un campeon.\n";
                return vacio;
            }
            return raiz->val; //Retornamos el jugador que quedo en la raiz (el campeon)
        }
        
        //Mostrar que partidos jugo el campeon y resultados
        void trayectoriaCampeon () const{
            if(!raiz || raiz->val.nombre == "vacio"){ //Si no hay raiz o esta vacia, el torneo aun no se juega
                cout << "\n\t El torneo aun no ha sido jugado, aun no hay un campeon.\n";
                return;
            }
            int cont = 1;
            string campeon = raiz->val.nombre; /*Usamos una variable para guardar el nombre del campeon, y poder seguirlo por los
            nodos que paso*/
            cout << "\n\t La trayectoria del campeon fue:\n\n";
            trayectoriaRecursivo(raiz, campeon, cont);
            cout << "\n\n\t\t\t\t >>>>>>>> CAMPEON <<<<<<<<";
            cout << "\n\n\t\t\t\t\t--> " << raiz->val.nombre << " <--";

            return;
        }

        //Recursividad para seguir el camino del campeon
        void trayectoriaRecursivo(Nodo* n, const string campeon, int& ronda) const{
            if(n->izq->izq == nullptr && n->der->der == nullptr){ /*Comprobamos si estamos un nivel por encima de las hojas (es decir,
                un nivel por encima de la primera ronda)*/
                cout << "\n\n\t\t\t --------------- RONDA " << ronda << "----------------"; //Impresion la primera vez que entramos a esta condicion
                imprimirJuego(n);
                ++ronda;
                return;
            }
            if(campeon == n->izq->val.nombre) trayectoriaRecursivo(n->izq, campeon, ronda); /*Si el nombre del campeon aparece a la izq pasamos a ese nodo, sino
            pasamos a la dereca*/
            else trayectoriaRecursivo(n->der, campeon, ronda);

            if(n->izq->levelLeaf == 1){ //Indicador para imprimir que estamos en la ronda final
                cout << "\n\n\t\t\t ---------------- RONDA FINAL ----------------";
            }else{ //Ronda normal
                cout << "\n\n\t\t\t ----------------- RONDA " << ronda << "----------------";
                ++ronda;
            }
            imprimirJuego(n); //Impresion de cada juego
        }

        //Mostrar las rondas cuando el torneo ya finalizo
        void mostrarRondas(){
            if(!raiz || raiz->val.nombre == "vacio"){ //Si la raiz no existe o esta vacia, aun no se juega el torneo
                cout << "\n\t El torneo aun no se ha jugado.\n";
                return;
            }
            int cont = 1; //Para el numero de la ronda
            int nivelHoja = maxLevelLeafs; /*Usamos una variable auxiliar para empezar a imprimir desde las hojas, esta la iremos disminuyendo, segun
            subamos en el arbol*/
            while(nivelHoja != 0){
                if(nivelHoja == 1){
                    cout << "\n\n\t\t\t --------------- RONDA FINAL" << " -----------------";
                }else{
                    cout << "\n\n\t\t\t --------------- RONDA " << cont << " -----------------";
                }
                mostrarRondasRecursivo(raiz, nivelHoja); 
                --nivelHoja; //Actualizamos la altura (nivel de hoja)
                ++cont; 
            }
            cout << "\n\n\t\t\t --------------> CAMPEON <--------------";
            cout << "\n\n\t\t\t\t    ---> " << raiz->val.nombre << " <---";
        }

        //Metodo recursivo para mostrar las rondas una vez que el torneo ya finalizo
        void mostrarRondasRecursivo(Nodo* n, int nivelHoja){
            if(n->izq->levelLeaf == nivelHoja && n->der->levelLeaf == nivelHoja){ /*Si los nodos la izq y a la der en su atributo levelLeaf son iguales
                a nuestra variable de control del nivel de hoja que debemos imprimir, imprimimos los juegos en ese nivel*/
                imprimirJuego(n);
                return;
            }
            mostrarRondasRecursivo(n->izq, nivelHoja); //Recursion a la izq
            mostrarRondasRecursivo(n->der, nivelHoja); //Recursion a la der
        }

        //Funcion para imprimir un partido, pasa como variable el nodo padre y se imprime el partido entre sus hijos izq vs der
        void imprimirJuego(Nodo *n) const{
            cout << "\n\n\t\t" << n->izq->val.nombre << " vs " << n->der->val.nombre << " -> ";
            cout << n->izq->val.nombre << " (" << n->izq->goles << ") - (" << n->der->goles << ") " << n->der->val.nombre;
            cout << " --- Gana: " << n->val.nombre;
        }
};