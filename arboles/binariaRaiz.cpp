//Autor: Suárez, V.V.
#include <iostream>
#include <cstdint>
#include <cstring>

using namespace std;

float sqrt(float n){
    //Casos base
    if(n < 0.0f) return -1.0f;
    if(n == 0.0f) return 0.0f;
    if(n == 1.0f) return 1.0f;
    //Intervalo
    /*
    si n>= 1 la raiz esta entre [0, n]
    si 0 < n < 1 la raiz esta entre [0, 1]
    */
   float lo = 0.0f;
   float hi = (n >= 1.0f)? n : 1.0f;
   
   // 1e-7 = error de calculo
   // Cada iteracion reduce a la mitad el intervalo
   for (int i=0; i<100; ++i){
        float mid = lo + (hi - lo) * 0.5f;
        float sq = mid * mid;

        if(sq <= n){
            lo = mid;
        }else{
        hi = mid;
        }
   }

   return (lo + hi) * 0.5f;
}

int main(){
    float n, r;
    char resp;
    do{
        cout << "\n\t-----------------------------------";
        cout << "\n\tDame un numero para la raiz: ";
        cin >> n;

        //Calcular a raiz
        r = sqrt(n);
        if(r == -1){
            cout << "\n\tEste programa no puede calcular raices de numeros imaginarios\n";
        }else{
            cout << "\n\tLa raiz aproximada es: " << r;
        }

        do{
            cout << "\n\n\tQuieres buscar otra raiz? s/n: ";
            cin.ignore();
            cin >> resp;
        }while(resp != 'n' && resp != 'N' && resp != 's' && resp != 'S');
    }while(resp == 'S' || resp == 's');
    return 0;
}