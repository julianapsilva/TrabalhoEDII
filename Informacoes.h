#ifndef INFORMACOES_H_INCLUDED
#define INFORMACOES_H_INCLUDED
#include <string>
using namespace std;

class Informacoes{

    private:
         string data;
         string estado;
         string cidade;
         int codigo;
         int casos;
         int mortes;


    public:
       //getters
       string getData(){return data;}
        string getEstado() {return estado;}
        string getCidade() {return cidade;}
        int getCodigo(){return codigo;}
        int getCasos(){return casos;}
        int getMortes(){return mortes;}
        //setters
        void setData(string data){this->data=data;}
        void setEstado(string estado){this->estado=estado;}
        void setCidade(string cidade){this->cidade=cidade;}
        void setCodigo(int codigo){this->codigo=codigo;}
        void setCasos(int casos){this->casos=casos;}
        void setMortes(int mortes){this->mortes=mortes;}

};

#endif // INFORMACOES_H_INCLUDED
