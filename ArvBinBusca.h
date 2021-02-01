#ifndef ARVBINBUSCA_H_INCLUDED
#define ARVBINBUSCA_H_INCLUDED
#include "Informacoes.h"

class NoArv
{
  public:
    NoArv* esq; // ponteiro para o filho a esquerda
    int info;   // informação do No (int)
    NoArv* dir; // ponteiro para o filho a direita
};

class ArvBinBusca
{
public:
    int global=0;
    int num=0;
    int movimentacoes=0;
    int comparacoes=0;
    ArvBinBusca();
    ~ArvBinBusca();
    void insere(int val);
    void ordenaVetor(Informacoes dados[]);

private:
    NoArv* raiz; // ponteiro para o No raiz da árvore
    int auxOrdenaVetor(NoArv *p,Informacoes dados[],int i);
    NoArv* auxInsere(NoArv *p, int val);
    NoArv* libera(NoArv *p);
};

#endif // ARVBINBUSCA_H_INCLUDED
