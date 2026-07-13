//Autor: Suárez, V.V.
#include <iostream>

using namespace std;

//Buscar factorial
long long factorial(long long fact){
    if(fact < 0) return -1; //Caso base, numero menor o igual a 1 no es valido para factorial
    if(fact > 20) return -2; //Caso base para evitar un desbordamiento por la capacidad de la variable
    cout << fact;
    if(fact == 0 || fact == 1) return 1; //Caso base, el factorial de 0 y 1 es 1
    cout << "*";

    return fact * factorial(fact-1); //Llamada recursiva restandole 1 al numero mandado
}

//Sumar n numeros naturales positivos
int sumaNaturales(int n){
    if(n < 1) return -1; //Caso base, el valor debe ser >=1
    if(n == 1) return 1;//Caso base

    return n + sumaNaturales(n-1); //Llamada recursiva restandole 1 al numero que se mando 
}

//Busqueda binaria de un elemento
int busquedaBinaria(const int v[], int lo, int hi, int bus){
    if(lo > hi) return -1; //Caso base
    int mid = lo + (hi - lo)/2;
    if(v[mid] == bus) return mid; //Caso base
    if(bus < v[mid]) return busquedaBinaria(v, lo, mid-1, bus); //Llamada recursiva actualizando el limite alto
    else return busquedaBinaria(v, mid+1, hi, bus); //Llamada recursiva actualizando el limite bajo
}

int main(){
    const int tam = 10; 
    int selec, n, nRes, nAux, buscar, resBuscar; 
    int v[tam] = {-8, -7, 1, 3, 5, 7, 10, 13, 16, 18};
    long long nFact, resFact, auxFact;
    do{
        cout << "\n------------------------------------------------------------------------";
        cout << "\n\n\t\t ---> MENU <---\n";
        cout << "\n\t [1] Factorial";
        cout << "\n\t [2] Sumar 'n' primeros numeros naturales";
        cout << "\n\t [3] Buscar numero en vector ordenado";
        cout << "\n\t [0] Salir del programa";
        cout << "\n\n\t Elige una opcion: ";
        cin>> selec;

        switch(selec){
            case 1:
                //Factorial
                auxFact = 1;
                cout << "\n\tDame el numero para obtener su factorial: ";
                cin >> nFact;
                cout << "\t";
                resFact = factorial(nFact);
                for(int i=1; i<nFact+1; i++){ //Haciendo el factorial con un ciclo
                    auxFact = auxFact * i;
                }
                if (resFact == -2){
                    cout << "\n\tEste programa no puede hacer factoriales de numeros mayores a 20";
                    break;
                };
                if(auxFact == resFact){ //Comprobacion del resultado
                    if(resFact == -1) cout << "\n\tEl factorial no aplica para numeros negativos";
                    else cout << "\n\tFactorial (" << nFact << ") = " << resFact;
                }else cout << "\n\tEl resultado fue incorrecto";
                break;
            case 2:
                //Sumar n numeros naturales
                cout << "\n\tDame el numero hasta el que quieres sumar: ";
                cin >> n;
                nRes = sumaNaturales(n);
                nAux = n*(n+1)/2; //Obtener el valor con la formula de Gauss para comparar
                if(nRes == -1) cout << "\n\tEl numero hasta el que se quiere sumar debe ser positivo";
                else cout << "\n\tS (" << n << ") (recursivo) = " << nRes << "\tS (" << n << ") (formula) = " << nAux;
                break;
            case 3:
                //Busqueda binaria
                cout << "\n\tEl vector es:\n"; //Impresion del vector
                cout << "\t";
                for(int i=0; i<tam; i++){
                    cout << v[i] << " ";
                }
                cout << "\n\n\tDame el numero que quieres buscar en el vector: ";
                cin >> buscar;
                resBuscar = busquedaBinaria(v, 0, tam-1, buscar);
                if(resBuscar == -1) cout << "\n\tBuscar (" << buscar << ") -> No se encuentra en el vector: " << resBuscar;
                else cout << "\n\tBuscar (" << buscar << ") -> Se encuentra en el vector en el indice: " << resBuscar; //Devuelve indice donde esta el numero
                break;
            case 0: cout << "\n\tSaliendo del programa...\n\n";
                break;
            default: cout << "\n\tOpcion invalida\n";
                break;
        }
    }while(selec !=0);

    return 0;
}