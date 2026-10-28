#include <iostream>
using namespace std;

int cuadricula[9];
int cantidad= 0;
bool usado[10];

bool ComprobarSiEsMagico() {
    int* c = cuadricula;
    int s[8]= {c[0]+c[1]+c[2], c[3]+c[4]+c[5],
         c[6]+c[7]+c[8],c[0]+c[3]+c[6],c[1]+c[4]+c[7],
          c[2]+c[5]+c[8],c[0]+c[4]+c[8],c[2]+c[4]+c[6]};

    for (int i=0; i<8; i++)
        if (s[i]!=15) {
            return false;
        }
    return true;
}
void llenartab(int p) {
    if (p==9) {
        if (ComprobarSiEsMagico()) {
            cantidad++;
        }
        return;
    }
    if (cuadricula[p]!=0) {
        llenartab(p+1);
        return;
    }
    for (int q=1; q<=9; q++) {
        if (usado[q]) continue;
        if (p%3==2 && cuadricula[p-2]+ cuadricula[p-1]+ q!=15) continue;
        cuadricula[p]=q;
        usado[q]=true;
        llenartab(p+1);
        cuadricula[p]=0;
        usado[q]=false;
    }
}

int main() {
    for (int i=0;i<9;i++) {
        cin>>cuadricula[i];
        if (cuadricula[i]!=0) {
            usado[cuadricula[i]]=true;
        }
    }
    llenartab(0);
    cout<<cantidad<<"\n";
    return 0;
}