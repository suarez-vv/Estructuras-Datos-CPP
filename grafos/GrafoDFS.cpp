//Autor: Suárez, V.V.
#include <bits/stdc++.h>
using namespace std;

struct DFSTools{
    const vector<vector<int>>& adj;
    bool dirigido;
    vector<int> color;
    vector<int> tin, tout, parent;
    int timer = 0;
    bool hayCiclo = false;

    DFSTools(const vector<vector<int>>& g, bool dir)
        : adj(g), dirigido(dir), color(g.size(), 0), 
        parent(g.size(), -1), tin(g.size(), -1),
        tout(g.size(), -1) {}

    void dfs_visit(int u){
        color[u] = 1;       //gris
        tin[u] = timer++;   //tiempo de entrada

        for(int v: adj[u]){
            if(color[v] == 0){
                parent[v] = u;
                dfs_visit(v);
            }else if(color[v] == 1){
                if(dirigido || v != parent[u]) hayCiclo = true;
            }
        }

        tout[u] = timer++; //tiempo de salida
        color[u] = 2; //negro
    }

    void run_all(){
        for(size_t u=0; u<adj.size(); ++u)
            if(color[u] == 0) dfs_visit(int(u));
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, d; //n vertices, m aristas, d dirigido  (mala practica)

    cout << "\n\t Dame el numero de vertices: ";
    cin >> n;
    cout << "\n\t Dame el numero de aristas: ";
    cin >> m;
    cout << "\n\t El grafo es dirigido? (1-si / 0-no): ";
    cin >> d; //Ingreso de vertices, aristas y si es dirigido (pedir al usuario)
    vector<vector<int>> adj(n);
    auto addEdge = [&](int u, int v){
        adj[u].push_back(v);
        if(!d) adj[v].push_back(u);
    };

    for(int i=0; i<m; ++i){
        int u, v;
        cout << "\n\t Dame el valor de u: ";
        cin >> u;
        cout << "\n\t Dame el valor de v: ";
        cin >> v; //Pedir al usuario
        addEdge(u, v);
    }

    DFSTools dfs(adj, d==1);
    dfs.run_all();

    cout << "\n\ttin: "; for(int x:dfs.tin) cout << x << " ";
    cout << endl;

    cout << "\n\ttout: "; for(int x:dfs.tout) cout << x << " ";
    cout << endl;

    cout << "\n\tCiclo? " << (dfs.hayCiclo? "si":"no");

    return 0;
}