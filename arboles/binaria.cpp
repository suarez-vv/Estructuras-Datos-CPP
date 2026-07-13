//Autor: Suárez, V.V.
#include <iostream>

using namespace std;

int binSearch(const int a[], int lo, int hi, int x){
    if(lo > hi) return -1; //caso 
    int mid = lo + (hi - lo)/2;
    if(a[mid] == x) return mid; //caso base
    if(x < a[mid]) return binSearch(a, lo, mid-1, x); //actualizar alto
    else return binSearch(a, mid+1, hi, x); //actualizar bajo
}

int main(){
    const int n = 10;
    int pos, num;
    int a[n] = {-5, -2, 0, 1, 3, 5, 7, 9, 12, 15};
    cout << "\nEl vector es:\n";
    for(int i=0; i<n; i++){
        cout << a[i] << " ";
    }
    cout << "\n\nDame el numero que quieres buscar en el vector: ";
    cin >> num;
    pos = binSearch(a, 0, n-1, num);
    if(pos == -1) cout << "\nEl numero " << num << " no se encuentra en el vector.\n";
    else cout << "\n\nEl numero: " << num << " SI se encuentra en el vector en la posicion: " << pos << ".\n";

    return 0;
}