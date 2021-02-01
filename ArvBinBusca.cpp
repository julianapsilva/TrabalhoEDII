#include <iostream>
#include "ArvBinBusca.h"

using namespace std;

ArvBinBusca::ArvBinBusca()
{
    raiz = NULL;
}

void ArvBinBusca::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

NoArv* ArvBinBusca::auxInsere(NoArv *p, int val)
{
    if(p == NULL)
    {
        p = new NoArv();
        p->info=val;
        p->esq=NULL;
        p->dir=NULL;
    }
    else if(val < p->info)
        p->esq=auxInsere(p->esq, val);
    else
        p->dir=auxInsere(p->dir, val);
    comparacoes++;
    return p;
}

void ArvBinBusca::ordenaVetor(Informacoes dados[]){
    for(int i=0;i<(global+num);i++){
            if(i<global){
                dados[i].setCasos(0); // inserindo todas as entradas que foram 0
            }
          else{
            dados[i].setCasos(1); // inserindo todas as entradas que foram 1
          }
          movimentacoes++;
    }
    global+=num;

    auxOrdenaVetor(raiz,dados,global);
}


int ArvBinBusca::auxOrdenaVetor(NoArv *p,Informacoes dados[], int i )
{
        if(p==NULL){ return global;}

        global=auxOrdenaVetor(p->esq,dados,global);
        dados[global++].setCasos(p->info);
        movimentacoes++;
        auxOrdenaVetor(p->dir,dados,global);

        return global;
}

ArvBinBusca::~ArvBinBusca()
{
    raiz = libera(raiz);
}

NoArv* ArvBinBusca::libera(NoArv *p)
{
    if(p != NULL)
    {
        p->esq=libera(p->esq);
        p->dir=libera(p->dir);
        delete p;
        p = NULL;
    }
    return p;
}
