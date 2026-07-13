//Autor: Suárez, V.V.
#include <iostream>
#include <string>

using namespace std;

class Empleado{
    private:
        static const int K=5;
        string nombre;
        Empleado* hijos[K]; //Arreglo de punteros a hijos
        int nHijos; //Numero actual de hijos
    public:
        //Constructor explicito
        explicit Empleado (const string& n): nombre(n), nHijos(0){
            for(int i=0; i<K; ++i) hijos[i] = nullptr;
        }

        //Evitamos copias
        Empleado(const Empleado&) = delete;
        Empleado& operator=(const Empleado&) = delete;

        //Destructor recursivo
        ~Empleado(){
            for(int i=0; i<K; ++i) delete hijos[i];

        }

        //Agregar subordinados si hay lugar 
        bool agregarSubordinado(Empleado* e){
            if(nHijos >= K) return false;
            hijos[nHijos++] = e;
            return true;
        }

        //recorrido en preorden: jefe -> hijos
        void imprimirPreorden(int nivel = 0)const{
            cout << "\n\tImpresion en preorden del arbol" << endl;
            cout << "\t" << string(nivel * 2, ' ') << "- " << nombre << endl;
            for(int i=0; i<nHijos; ++i){
                hijos[i] -> imprimirPreorden(nivel + 1);
            }
        }

        void imprimirPosorden(int nivel = 0)const{
            cout << "\n\tImpresion en posorden del arbol" << endl;
            cout << "\t" << string(nivel * 2, ' ') << "- " << nombre << endl;
            for(int i=nHijos-1; i<-1; --i){
                hijos[i] -> imprimirPreorden(nivel + 1);
            }
        }

        //Contar total de empleados en el subarbol
        int  contarEmpleados()const{
            int total = 1;
            for(int i=0; i<nHijos; ++i){
                total  += hijos[i]->contarEmpleados();
            }
            return total;   
        }

        //Calcular la altura
        int altura()const{
            int hmax = -1;
            for(int i=0; i<nHijos; ++i){
                hmax = max(hmax, hijos[i]->altura());
            }
            return hmax + 1;
        }

        //Calcular el grado maximoen todo el subarbol
        int gradoMaximo()const{
            int g = nHijos;
            for(int i=0; i<nHijos; ++i){
                g = max(g, hijos[i]->gradoMaximo());
            }
            return g;
        }

};

int main(){
    Empleado* CEO = new Empleado("CEO");
    Empleado* CTO = new Empleado("CTO");
    Empleado* CFO = new Empleado("CFO");
    Empleado* COO = new Empleado("COO");


    CEO->agregarSubordinado(CTO);
    CEO->agregarSubordinado(CFO);
    CEO->agregarSubordinado(COO);

    Empleado* DevLead = new Empleado("Lider Dev");
    CTO->agregarSubordinado(DevLead);
    DevLead->agregarSubordinado(new Empleado("Dev1"));
    DevLead->agregarSubordinado(new Empleado("Dev2"));

    CFO->agregarSubordinado(new Empleado("Finanzas1"));

    COO->agregarSubordinado(new Empleado("Ops1"));
    COO->agregarSubordinado(new Empleado("Ops2"));

    //Resultados
    cout << "\n******* Preorden **********" << endl;
    CEO->imprimirPreorden();

    cout << "\nTotal de empleados: " << CEO->contarEmpleados() << endl;
    cout << "\nAltura: " << CEO->altura() << endl;
    cout << "\nGrado maximo: " << CEO->gradoMaximo() << endl;

    delete CEO; //Libera todo, porque es la raiz

    return 0;
}