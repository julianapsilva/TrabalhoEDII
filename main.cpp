#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Informacoes.h"
#include "ArvBinBusca.h"

using namespace std;
using namespace std::chrono;

int comparacoes,movimentacoes;

void printDataSet(Informacoes dados[],int n)
{

// TESTANDO A LEITURA
    for(int i=0; i<n; i++)
    {
        cout << "data: " << dados[i].getData()<< endl;
        cout <<"cidade: " << dados[i].getCidade() <<"("<<dados[i].getEstado()<<")" << endl;
        cout <<"codigo: " << dados[i].getCodigo() << endl;
        cout << "casos: " << dados[i].getCasos() << endl;
        cout << "mortes: " << dados[i].getMortes() << endl;
        cout << "******************"<< endl;

    }

}

int split(Informacoes dados[], int beg, int ed)
{

    //fun��o para separar dividir um vetor em dois novos vetores, um com os elementos menores que o pivo e outro com os maiores
    Informacoes pivot = dados[ed]; //estrat�gia basica para escolher o pivo, usando o ultimo indice
    int i = beg;
    for (int j = beg; j < ed; j++)
    {       if (dados[j].getCasos() <= pivot.getCasos())
        {
            swap(dados[j], dados[i]);

            i++;
            movimentacoes++;
        }
    comparacoes++;
}
    swap(dados[i],dados[ed]);
    movimentacoes++;
    return i;
}
void quickSort(Informacoes dados[], int beg,int ed)    // m�todo nao estavel o resultado sera o vetor dados[] modificado
{
    if(beg<ed)
    {
        comparacoes++;
        int indexpivot=split(dados,beg,ed);
        quickSort(dados,beg,indexpivot-1);
        quickSort(dados,indexpivot,ed);
    }
}

void preprocess(Informacoes dados[],int n){
    //assumindo lista ordenada como no trabalho
    string cidade_atual="";
    int casosAteData=0;
    for(int i=0;i<n;i++){
        int temp=dados[i].getCasos();  //salva o numero de casos acumulados ate a data do registro para uso futuro
        if(cidade_atual==dados[i].getCidade()){ //ja tem registros dessa cidade, entao o calculo dos casos diarios � feito
               if(dados[i].getCasos()>casosAteData){
                dados[i].setCasos(dados[i].getCasos()-casosAteData);
                casosAteData=temp;
               }
               else{
                dados[i].setCasos(0);
                casosAteData=temp;
               }

        }
        else{

                cidade_atual=dados[i].getCidade();      //asumindo que o primeiro registro da cidade corresponde com o primeiro dia que teve infec��es
                casosAteData=dados[i].getCasos();

        }
    }

}

void mergeEstado(Informacoes dados[], int l, int m, int r)
{


    int n1 = m - l + 1;
    int n2 = r - m;
    // estruturas tempor�rias
    Informacoes *L =new Informacoes[n1];
    Informacoes *R = new Informacoes[n2];
    // copiando dados p estruturas tempor�rias
    for (int i = 0; i < n1; i++)
        L[i] = dados[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = dados[m + 1 + j];
    // Mesclar as variaveis tempor�rias de volta em dados[]
    int i = 0;
    int j = 0;
    // indice inicial vetor mesclado
    int k = l;
    while (i < n1 && j < n2)
    {
        if(L[i].getEstado()==R[j].getEstado())
        {
            if(L[i].getCidade()==R[j].getCidade())
            {
                if(L[i].getData()<=R[j].getData())
                {
                    dados[k] = L[i];
                    i++;
                }
                else
                {
                    dados[k] = R[j];
                    j++;
                }

            }
            else
            {

                if (L[i].getCidade() <= R[j].getCidade())
                {

                    dados[k] = L[i];
                    i++;
                }
                else
                {
                    dados[k] = R[j];
                    j++;
                }
            }

        }
        else
        {

            if (L[i].getEstado() <= R[j].getEstado())
            {

                dados[k] = L[i];
                i++;
            }
            else
            {
                dados[k] = R[j];
                j++;
            }
        }
        k++;

    }
    while (i < n1)
    {
        dados[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        dados[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void mergeSortEstado(Informacoes dados[],int l,int r)
{
    if(l>=r)
    {
        return;//retorna recursivamente
    }

    int m = (l+r-1)/2;
    mergeSortEstado(dados,l,m);
    mergeSortEstado(dados,m+1,r);
    mergeEstado(dados,l,m,r);
}
void mergeCasos(Informacoes dados[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // estruturas tempor�rias

    Informacoes* L = new Informacoes[n1];
    Informacoes* R = new Informacoes[n2];
    // copiando dados p estruturas tempor�rias
    for (int i = 0; i < n1; i++)
        L[i] = dados[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = dados[m + 1 + j];

    // Mesclar as variaveis tempor�rias de volta em dados[]

    int i = 0;
    int j = 0;

    // indice inicial vetor mesclado
    int k = l;

    while (i < n1 && j < n2)
    {
        comparacoes++;
        if (L[i].getCasos() <= R[j].getCasos())
        {
            dados[k] = L[i];
            i++;
            movimentacoes++;
        }
        else
        {
            dados[k] = R[j];
            j++;
            movimentacoes++;
        }
        k++;
    }

    // copiando elementos restantes, se houver
    while (i < n1)
    {
        comparacoes++;
        dados[k] = L[i];
        i++;
        k++;
        movimentacoes++;
    }

    while (j < n2)
    {
        comparacoes++;
        dados[k] = R[j];
        j++;
        k++;
        movimentacoes++;
    }
    delete[] R;
    delete[] L;
}
void mergeSortCasos(Informacoes dados[],int l,int r)
{
    if(l>=r)
    {
        return;//retorna recursivamente
    }
    int m = (l+r-1)/2;
    mergeSortCasos(dados,l,m);
    mergeSortCasos(dados,m+1,r);
    mergeCasos(dados,l,m,r);
}
void mergeInteiros(int dados[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    // estruturas tempor�rias
    int* L, * R;
    L = (int*)malloc(sizeof(Informacoes) * n1);
    R = (int*)malloc(sizeof(Informacoes) * n2);

    // copiando dados p estruturas tempor�rias
    for (int i = 0; i < n1; i++)
        L[i] = dados[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = dados[m + 1 + j];

    // Mesclar as variaveis tempor�rias de volta em dados[]


    int i = 0;
    int j = 0;

    // indice inicial vetor mesclado
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            dados[k] = L[i];
            i++;
        }
        else
        {
            dados[k] = R[j];
            j++;
        }
        k++;
    }

    // copiando elementos restantes, se houver
    while (i < n1)
    {
        dados[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        dados[k] = R[j];
        j++;
        k++;
    }
}
void mergeSortInteiros(int dados[],int l,int r)
{
    if(l>=r)
    {
        return;//retorna recursivamente
    }

    int m = (l+r-1)/2;
    mergeSortInteiros(dados,l,m);
    mergeSortInteiros(dados,m+1,r);
    mergeInteiros(dados,l,m,r);
}
void treeSort(Informacoes dados[],int n)
{
    ArvBinBusca *arv=new ArvBinBusca();

    for(int i = 0; i  < n; i++){
        if(dados[i].getCasos()==0){
                arv->global++;
                arv->comparacoes++;
            }
        else if(dados[i].getCasos()==1){
            arv->num++;
            arv->comparacoes++;
        }
            else{
            arv->insere(dados[i].getCasos());  // insere na ABB apenas valores diferentes de 0 e 1, para maximizar o desempenho
            arv->movimentacoes++;
            }
    }
    arv->ordenaVetor(dados);

    movimentacoes=arv->movimentacoes;
    comparacoes= arv->comparacoes;
    arv->movimentacoes=0;
    arv->comparacoes=0;
}

int random(int min, int max)
{
    return rand() % (max + 1 - min) + min;

}
void geraArrayComIndicesAleatorios(int n,int nMax,int* indices)
{

    for(int i=0; i<n; i++)
    {
        indices[i]=random(0,nMax);
    }
    mergeSortInteiros(indices,0,n-1);
}
void geraCSV(Informacoes dados[], int n)
{
    ofstream arq("brazil_covid19_cities_processado.csv");

    for(int i = 0; i < n; i++)
    {
        arq << dados[i].getData() << "," << dados[i].getEstado() << ","
            << dados[i].getCidade() << "," << dados[i].getCodigo() << ","
            << dados[i].getCasos() << "," <<  dados[i].getMortes()<< endl;
    }

    arq.close();
    cout << "Arquivo gerado com sucesso!"<< endl;
}
void leArquivoPreProcessado(Informacoes dados[],int n,int nMax, int opcao)
{
    ifstream arq("brazil_covid19_cities_processado.csv");

    int* indices= (int*)malloc(sizeof(int)*n);
    geraArrayComIndicesAleatorios(n,nMax,indices);
    if(arq.is_open())
    {
        string str;
        int j=0,a=0;
        getline(arq, str);
        while(getline(arq, str)&&a<n)
        {
            for(int f=0; f<n; f++)
            {
                if(indices[f]==j)
                {
                    char *subdado;
                    subdado = strtok( &str[0], ",");
                    int i=0;
                    while( subdado != NULL)
                    {
                        switch (i)
                        {
                        case 0:
                            dados[a].setData(subdado);
                            break;

                        case 1:
                            dados[a].setEstado(subdado);
                            break;

                        case 2:
                            dados[a].setCidade(subdado);
                            break;

                        case 3:
                            dados[a].setCodigo(atoi(subdado));
                            break;

                        case 4:
                            dados[a].setCasos(atoi(subdado));
                            break;

                        case 5:
                            dados[a].setMortes(atoi(subdado));
                            break;

                        }
                        i++;

                        subdado = strtok( NULL, ",");

                    }
                    a++;
                }
                //if(indices[f]>j)
                //  break;
            }
            j++;

        }
    }
    arq.close();
    if(opcao==1){
         printDataSet(dados,n);
    }
    else if(opcao==2){
        ofstream arq("saida.txt");
         arq << "IMPORTA��O DE 100 REGISTROS ALEAT�RIOS"<< endl;
            for(int i=0; i<n; i++)
    {
        arq << "data: " << dados[i].getData()<< endl;
        arq <<"cidade: " << dados[i].getCidade() <<"("<<dados[i].getEstado()<<")" << endl;
        arq <<"codigo: " << dados[i].getCodigo() << endl;
        arq<< "casos: " << dados[i].getCasos() << endl;
        arq << "mortes: " << dados[i].getMortes() << endl;
        arq<< "******************"<< endl;

    }

    }

}
void executaTeste(int n,int nMax,char metodo, int opcao)
{
    ofstream arq("saida.txt", std::ios_base::app);
    double mT=0;
    double mC=0,mM=0;
    for(int i=0; i<5; i++)
    {
        high_resolution_clock::time_point inicio = high_resolution_clock::now();
        Informacoes* dados = new Informacoes[n];
        leArquivoPreProcessado(dados,n,nMax,0);  //le n valores aleatorios
        comparacoes=0;
        movimentacoes=0;
        switch (metodo) {
             case'Q':
                 quickSort(dados, 0, n - 1);
                 break;
             case'M':
                 mergeSortCasos(dados, 0, n - 1);
                 break;
             case'T':
                 treeSort(dados,n);
                 break;

        }

        high_resolution_clock::time_point fim = high_resolution_clock::now();

        if(opcao==2){
        arq << metodo<< "(" <<n<<") "<<comparacoes << " " <<movimentacoes<< " "<<duration_cast<duration<double>>(fim - inicio).count() << " segundos" <<endl;
        }

        else if(opcao==1){
        cout << metodo<< "(" <<n<<") "<<comparacoes << " " <<movimentacoes<< " "<<duration_cast<duration<double>>(fim - inicio).count() << " segundos" <<endl;
        }
        mT +=duration_cast<duration<double>>(fim - inicio).count();
        mC+=(1.0/5.0)*comparacoes;
        mM+=(1.0/5.0)*movimentacoes;


    }
    mT=mT/5;
    if(opcao==2){
    arq << "("<<metodo<<") MEDIA ("<<n<<") "<<mC<< " " <<mM<< " "<<mT<<endl;
    }
    else if(opcao==1){
    cout << "("<<metodo<<") MEDIA ("<<n<<") "<<mC<< " " <<mM<< " "<<mT<<endl;
    }
    arq.close();

}
void Tester(int n, int nMax) {


    executaTeste(n, nMax, 'Q',2);
    executaTeste(n, nMax, 'M',2);
    executaTeste(n, nMax, 'T',2);


}
void leArquivoRaw(Informacoes dados[],int n, char* argumento[])
{
    ifstream arq(argumento[1]);
    if(arq.is_open())
    {
        //cout << "Informacoes armazenadas no arquivo:\n\n***" << endl;
        string str;
        int count = 1;
        int j=0;
        getline(arq, str);
        while(getline(arq, str))
        {
            count++;
            char *subdado;

            subdado = strtok( &str[0], ",");
            int i=0;
            while( subdado != NULL && j<n )
            {
                switch (i)
                {
                case 0:
                    dados[j].setData(subdado);
                    break;

                case 1:
                    dados[j].setEstado(subdado);
                    break;

                case 2:
                    dados[j].setCidade(subdado);
                    break;

                case 3:
                    dados[j].setCodigo(atoi(subdado));
                    break;

                case 4:
                    dados[j].setCasos(atoi(subdado));
                    break;

                case 5:
                    dados[j].setMortes(atoi(subdado));
                    break;

                }
                i++;
                subdado = strtok( NULL, ",");
            }
            j++;


        }

        cout << "***" << endl;

    }

    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}


void menu(Informacoes dados[], int n)
{
    int opcao, saida;
    cout<< "** BEM VINDO AO MENU **"<< endl;
    cout<< "Escolha uma das opcoes" << endl;
    cout<< "1) Pre-processamento dos dados"<< endl;
    cout<< "2) Importacao de N registros aleatorios" << endl;
    cout<< "3) MergeSort" << endl;
    cout<< "4) QuickSort" << endl;
    cout<< "5) TreeSort" << endl;

    cout<< "\nDigite: ";
    cin>> opcao;
    cout << "Deseja ver a saida na tela ou em arquivo?"<< endl;
    cout<< "1 para SAIDA NA TELA" << endl;
    cout<< "2 para SAIDA EM ARQUIVO" << endl;
    cout<< "\nDigite: ";
    cin>> saida;

    switch(opcao){

    case 1: //pre-processamento
       // leArquivoRaw(dados,n);
       // mergeSortEstado(dados,0,n-1);
       // preprocess(dados, n);
        if(saida==1){   // como o pre processamento foi feito antes de chamar o menu, as funcoes acima estao comentadas
            printDataSet(dados,10);
        }
        else if(saida==2){
            ofstream arq("saida.txt");
            for(int i=0;i<100;i++){
                arq << "data: " << dados[i].getData()<< endl;
                arq <<"cidade: " << dados[i].getCidade() <<"("<<dados[i].getEstado()<<")" << endl;
                arq <<"codigo: " << dados[i].getCodigo() << endl;
                arq<< "casos: " << dados[i].getCasos() << endl;
                arq << "mortes: " << dados[i].getMortes() << endl;
                arq << "******************"<< endl;
            }
        cout<< "Arquivo gerado com sucesso! Verifique na pasta o arquivo 'saida.txt'"<< endl;
        }
        break;

    case 2: // Importacao de registros aleatorios
        if(saida==1){
            leArquivoPreProcessado(dados,10,n,1);
        }
        else if(saida==2){
            leArquivoPreProcessado(dados,100,n,2);
            cout<< "Arquivo gerado com sucesso! Verifique na pasta o arquivo 'saida.txt'"<< endl;
        }
        break;

    case 3:// MergeSort
        if(saida==1){
            executaTeste(10, n, 'M',1);
        }

        else if(saida==2){
            executaTeste(100, n, 'M',2);
            cout<< "Arquivo gerado com sucesso! Verifique na pasta o arquivo 'saida.txt'"<< endl;
        }
        break;

    case 4:// QuickSort
        if(saida==1){
            executaTeste(10, n, 'Q',1);
        }

        else if(saida==2){
            executaTeste(100, n, 'Q',2);
            cout<< "Arquivo gerado com sucesso! Verifique na pasta o arquivo 'saida.txt'"<< endl;
        }
        break;

    case 5:// TreeSort
        if(saida==1){
            executaTeste(10, n, 'T',1);
        }

        else if(saida==2){
            executaTeste(100, n, 'T',2);
            cout<< "Arquivo gerado com sucesso! Verifique na pasta o arquivo 'saida.txt'"<< endl;
        }
    }
}


int main(int numeroargumentos, char* argumento[])
{
    ofstream arq("saida.txt");

    const int n = 1431490;
    Informacoes *dados=new Informacoes[n];
    leArquivoRaw(dados,n, argumento);
    mergeSortEstado(dados,0,n-1);
    preprocess(dados, n);
    geraCSV(dados,n);
   int Ns[] = { 10000, 20000, 50000, 100000};
   for(int i=0;i<4 ;i++){
        Tester(Ns[i],n);
    }
   menu(dados, n);

    return 0;
}
