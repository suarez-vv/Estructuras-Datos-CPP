//Autor: Suárez, V.V.
#include <bits/stdc++.h>
using namespace std;

class GrafoPonderado{
    /* adj guarda todas las aristas en pares
    (v, w) v = nodo vecino
    w = peso/costo de arista  u -> v*/
    vector<vector<pair<size_t, int>>> adj;
    bool esDirigido;

    public:
        GrafoPonderado(size_t n, bool dirigido = true)
            : adj(n), esDirigido(dirigido){}

        size_t numVertices() const {return adj.size();}

        void agregarArista(size_t u, size_t v, int w){
            //Validaciones basicas evitar accesos invalidos
            if(u >= numVertices() || v >= numVertices()) return; //Si esta fuera del rango de la matriz

            adj[u].push_back({v, w});
            if(!esDirigido){
                adj[v].push_back({u, w});
            }
        }

        void imprimir() const{
            cout << "\n\t Grafo Ponderado ("
                 << (esDirigido? "dirigido" : "no dirigido")
                 << ")\n\n"; 

            for(size_t i =0; i<numVertices(); ++i){
                cout << "\t\t" << i << ": ";
                for(auto [v, w] : adj[i]){
                    cout << "(" << v << ", w= " << w << ")";
                }
                cout << endl;
            }
        }

        void dijkstra(size_t s, vector<int>& dist, vector<int>& parent){
            size_t n = numVertices();
            const int INF = 1e9;  //Numero grande como infinito

            //Iniciamos distancias y padres
            dist.assign(n, INF); //Al inicio nade es alcanzado
            parent.assign(n, -1); //-1 sin padre

            if(s >= n) return;  //Si la fuente es invalida

            dist[s] = 0; //Distancia de fuente a s es igual

            //priority queue de pares (distancia, nodo)
            using P = pair<int, size_t>;
            //Usamos el greater para que sea min-heap
            priority_queue<P, vector<P>, greater<P>> pq;

            pq.push({0, s}); // Insertamos fuente con distancia 0

            while(!pq.empty()){
                auto [du, u] = pq.top();
                pq.pop();

                if(du != dist[u]) continue;

                for(auto [v,w] : adj[u]){
                    if(dist[u] + w < dist[v]){
                        dist[v] = dist[u] + w; //Nueva mejor distancia

                        parent[v] = (int)u;  //El mejor camino

                        pq.push({dist[v], v}); //Metemos la nueva distancia a la cola
                    }
                }
            }

        }
};

int main(){
    GrafoPonderado G(4, true);

    G.agregarArista(0, 1, 2);
    G.agregarArista(0, 2, 5);
    G.agregarArista(1, 2, 1);
    G.agregarArista(1, 3, 3);
    G.agregarArista(2, 3, 2);

    G.imprimir();

    size_t fuente = 0;
    vector<int> dist, parent;
    G.dijkstra(fuente, dist, parent);

    cout << "\n\t Distancia minima desde " << fuente << ":\n";
    for(size_t u=0; u<G.numVertices(); ++u){
        if(dist[u] == 1e9)
            cout << "\n\t" << u << ": Inf\n";
        else
            cout << "\n\t" << u << ": " << dist[u] << "\n";
    }

    //Desde una fuente a un destino
    size_t destino = 3;
    if(destino >= G.numVertices() || dist[destino] == 1e9){
        cout << "\n\t No hay camino.\n";
    }else{
        vector<size_t> camino;
        for(int x=(int)destino; x != -1; x=parent[x]){
            camino.push_back((size_t)x);
        }
        reverse(camino.begin(), camino.end()); //Mostrar el vector al reves

        cout << "\n\tCamino minimo " << fuente << " -> " << destino << ": ";
        for(size_t i=0; i<camino.size(); ++i){
            cout << camino[i];
            if(i+1 < camino.size()) cout << " -> ";
        }
        cout << "\n\t Costo total: " << dist[destino] << "\n";
        
    }
    
    return 0;
}