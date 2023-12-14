#include "poly.h"

int main(){
    double a, b, ans;
    int flag;
    ans = 0.0;
    cout << "a = ";
    cin >> a;
    cout <<"b = ";
    cin >> b;
    Polynom Px;
    Polynom Py;
    cout << "polynom 1:" << endl;
    Px.InputPolynom();
    cout << "polynom 2:" << endl;
    Py.InputPolynom();
    flag = Px.root_chords(&ans, a, b);
    if(flag){
        cout << "Polynom 1: number of iterations " << flag << endl;
        cout << "Polynom 1: the root on the segment (" <<  a << ", " << b << ") is equal to " << ans << endl;
    } else{
        cerr << "Poynom 1: the method is not applicable" << endl;
    }
    cout << "Polynom 1 + Polynom 2 = ";
    (Px + Py).OutputPolynom();
    cout << endl;
    double k;
    cout << "enter the number by which you want to multiply the polynomial:"<< endl;
    cin >> k; 
    cout << "Polynom 2 * " << k <<" = ";
    Py = MultConst(k, Py);
    Py.OutputPolynom();
    return 0;
}