//Autor: Suárez, V.V.
#include <iostream>

using namespace std;

int x=0;

void hanoi(int n, char A, char B, char C){
    if(n==0) return;
    hanoi(n-1, A, C, B);
    x++;
    cout << "Torre a: " << A << "-> Torre b:" << B << "-> Torre c: " << C << "Valor n: " << n <<  endl;
    hanoi(n-1, B, A, C);
    //out << B << "->" << C << endl;

}

int main(){
    hanoi(3, 'A', 'B', 'C');
    cout << x;
    return 0;
}