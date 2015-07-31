#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
using namespace std;

class heap{
    private: vector<int> minHeap;

    public: heap(){
        //
    }

    void imprimir(){
        int i;
        for(i=0; i<minHeap.size(); i++){
            cout<<minHeap[i]<<" ";
        }
        cout<<"\n";
    }

    void flotar (int pos){
        //El nodo sube hasta llegar a su posicion final
        if(pos==0){
            return;
        }
        int padre = (pos-1) / 2;
        if(minHeap[pos]<minHeap[padre]){
            swap(minHeap[pos],minHeap[padre]);
            flotar(padre);
        }
    }

    void hundir(int pos){
        //El nodo baja hasta llegar a su posicion final
        int hIzq = 2*pos+1, hDer = 2*pos+2;
        cout<<minHeap[hIzq]<<" "<<minHeap[hDer]<<"\n";
        if(hIzq<minHeap.size()){
            if(minHeap[pos]>minHeap[hIzq] && minHeap[hIzq]<minHeap[hDer]){
                swap(minHeap[pos],minHeap[hIzq]);
                hundir(hIzq);
            }
        }
        if(hDer<minHeap.size()){
            if(minHeap[pos]>minHeap[hDer] && minHeap[hIzq]>minHeap[hDer]){
                swap(minHeap[pos],minHeap[hDer]);
                hundir(hDer);
            }
        }
    }

    void insertar(int v){
        //Inserta un valor v en el heap
        minHeap.push_back(v);
        flotar(minHeap.size()-1);
    }

    void extraerMin(){
        //Extrae el mınimo valor del heap
        int minimo = minHeap[0];
        swap(minHeap[0],minHeap[minHeap.size()-1]);
        minHeap.erase(minHeap.end()-1);
        hundir(0);
    }

    void decrementarClave (int pos, int dec){
        //Decrementa el valor de la clave de un nodo dado
        if(minHeap[pos]>dec){
            minHeap[pos]=dec;
            flotar(pos);
        }
    }

    void probabilidades (int e, int d){
        int i, r;
        float n;
        for(i=0; i<1000000; i++){
            n = ((rand() % 100)+0.0)/100;
//            cout<<n<<" ";
            if(n<e && n>d){
                extraerMin();
            }
            if(n<d && n>d){
                r = rand() % 100;
                decrementarClave(i, r);
            }
            if(n<e && n<d){
                if(e<d){
                    extraerMin();
                }else{
                    r = rand() % 100;
                    decrementarClave(i, r);
                }
            }
            if(n>e && n>d){
                if(e>d){
                    extraerMin();
                }else{
                    r = rand() % 100;
                    decrementarClave(i, r);
                }
            }
        }
    }

};

int main ()
{
    time_t first, last;
    time(&first);
    //Crear el minHeap
    heap* A = new heap();
    int n;
    float e=0.5, d=0.5;
    for(int i=0; i<1000000; i++){
        n = rand() % 1000000;
        A->insertar(n);
    }
    //Operaciones aleatorias
    A->probabilidades(e,d);
    time(&last);
    double seconds = difftime(last,first);
    cout<<"\nTotal time="<<seconds<<"\n";

    return 0;
}
