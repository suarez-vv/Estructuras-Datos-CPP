//Autor: Suárez, V.V.
#include <bits/stdc++.h>
using namespace std;

class GrafoMatriz{
    //Matriz booleana 
    vector<vector<bool>> A;
    bool esDirigido;

    public:
        GrafoMatriz(size_t n, bool dirigido = true) : A(n, vector<bool>(n, false)), esDirigido(dirigido) {}

        size_t numVertices() const {return A.size();}; //Devolver tamanio del primer vector

        //Agregar arista u -> v
        void agregarArista(size_t u, size_t v){
            //Validaciones basicas evitar accesos invalidos
            if(u >= numVertices() || v >= numVertices()) return; //Si esta fuera del rango de la matriz

            A[u][v] =  true; //Arista de origen a destino
            if(!esDirigido) A[v][u] = true; //Si no es dirigido tambien direccionamos del destino al origen
        }

        void eliminarArista(size_t u, size_t v){
            if(u >= numVertices() || v >= numVertices()) return; //Si esta fuera del rango de la matriz

            A[u][v] = false;
            if(!esDirigido) A[v][u] = false;
        }

        bool existeArista(size_t u, size_t v){
            if(u >= numVertices() || v >= numVertices()) return false; //Si esta fuera del rango de la matriz

            return A[u][v];
        }

        void imprimir() const{
            cout << "\n\t Matriz de adyacencia ("
                 << (esDirigido? "dirigido" : "no dirigido")
                 << ")\n\n"; 

            for(size_t i =0; i<numVertices(); ++i){
                cout << "\t\t";
                for(size_t j=0; j<numVertices(); ++j){
                    cout << (A[i][j]? 1 : 0) << " ";
                }
                cout << endl;
            }
        }
};

int main(){
    GrafoMatriz G(4, true);
    G.agregarArista(0, 1);
    G.agregarArista(0, 2);
    G.agregarArista(1, 3);
    G.agregarArista(2, 3);

    G.imprimir();

    cout << "\n\tExiste 0->2 ?" << (G.existeArista(0, 2)? "Si" : "No");
    cout << "\n\tExiste 0->3 ?" << (G.existeArista(0, 3)? "Si" : "No");
    cout << endl;
    return 0;
}