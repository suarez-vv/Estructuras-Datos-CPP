//Autor: Suárez, V.V.
#include <iostream>
#include <string>

using namespace std;

class NodoFS{
    private:
        static const int K=6;
        string nombre;
        bool esDirectorio;
        size_t tam;
        NodoFS* hijos[K];
        int nHijos;

        NodoFS(const string& n, bool dir, size_t t)
            : nombre(n), esDirectorio(dir), tam(t), nHijos(0){
                for(int i=0; i<K; ++i) hijos[i] = nullptr;
            }

    public:
        //Constructores estaticos
        static NodoFS* directorio(const string& n){
            return new NodoFS(n, true, 0);
        }

        static NodoFS* archivos(const string& n, size_t bytes){
            return new NodoFS(n, false, bytes);
        }

        NodoFS(const NodoFS&) = delete;
        NodoFS& operator=(const NodoFS&) = delete;

        //Destructor
        ~NodoFS(){
            for(int i=0; i<nHijos; ++i) delete hijos[i];
        }

        //Agregar hijos si es directorio
        bool agregar(NodoFS* h){
            if(!esDirectorio || nHijos >= K) return false;
            hijos[nHijos++] = h;
            return true;
        }

        //Calcular tamanio total acumulado
        size_t tamanioTotal() const{
            if(!esDirectorio) return tam;
            size_t total = 0;
            for(int i=0; i<nHijos; ++i){
                total += hijos[i]->tamanioTotal();
            }
            return total;
        }

        //Listar rutas absolutas
        void listarRutas(const string& prefijo = "") const{
            string ruta = prefijo + "\\" + nombre;
            if(!esDirectorio){
                cout << ruta << " (" << tam << ") bytes\n";
                return;
            }
            for(int i=0; i<nHijos; ++i){
                hijos[i]->listarRutas();
            }
        }

        //Imprimir el arbol en postorden
        void imprimirPostOrden(int nivel = 0)const{
            //Primero recorrer hijos
            for(int i=0; i<nHijos; ++i){
                hijos[i]->imprimirPostOrden(nivel+1);
            }

            //Luego visitar el nodo actual
            cout << string(nivel * 2, ' ') << "- " << nombre; 
            if(!esDirectorio) cout << " (" << tam << ") bytes";
            cout << "\n";
        }
};

int main(){
    NodoFS* root = NodoFS::directorio("C:");
    NodoFS* home = NodoFS::directorio("home");
    NodoFS* user = NodoFS::directorio("user");
    NodoFS* docs = NodoFS::directorio("docs");
    NodoFS* imgs = NodoFS::directorio("imgs");

    NodoFS* tareaPdf = NodoFS::archivos("tarea.pdf", 38000);
    NodoFS* notasTxt = NodoFS::archivos("notas.txt", 1000);
    NodoFS* fotoPng = NodoFS::archivos("foto.png", 404200);

    NodoFS* etc = NodoFS::directorio("etc");
    NodoFS* conf = NodoFS::archivos("config.sys", 20000);

    root->agregar(home);
    root->agregar(etc);
    
    home->agregar(user);
    user->agregar(docs);
    user->agregar(imgs);

    cout << "\n\tPostorden\n";
    root->imprimirPostOrden();

    docs->agregar(tareaPdf);
    docs->agregar(notasTxt);
    imgs->agregar(fotoPng);

    etc->agregar(conf);

    cout << "\n\tPostOrden\n";
    root->imprimirPostOrden();
    
    return 0;
}