/* File:   MallaRegular.h
 * Author: Alemol
 * Created on 3 de diciembre de 2019, 12:26
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

#include <list>
//#include <inttypes.h>
#include <vector>
#include <math.h>
#include <time.h>

template <class T>
class MallaRegular;
    
template <class T>
class Casilla{
    std::list<T> puntos;
    
    public:
        friend class MallaRegular<T>;
        Casilla(): puntos(){};
        Casilla(const Casilla& orig): puntos(orig.puntos){};
        ~Casilla(){};
        unsigned numPuntosCasilla(){return puntos.size();};
        void insertarC(const T &dato){ puntos.push_back(dato); }
        
        T* buscarC (const T &dato){ 
            typename std::list<T>::iterator ite=puntos.begin();
            for(; ite!=puntos.end();ite++){
                if(*ite == dato)
                    return &(*ite);
            }
        }
        
        bool borrarC (T &dato){  
            typename std::list<T>::iterator it= puntos.begin();
            for(; it!=puntos.end();++it)
                if(*it==dato){
                    puntos.erase(it);
                    return true;
                }
            return false;
        }
               
};        
        
template <class T>
class MallaRegular {  
    float xMin,xMax,yMin,yMax, tamCasillaX, tamCasillaY,tamLogico,numDivX,numDivY; //ToDo:: gestionar numDivisiones correctamente
    Casilla<T> *obtenerCasilla(float x, float y);
    std::vector<std::vector<Casilla<T> > >mallaR;
    unsigned numElementosTotales;
    
public:
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY,
            float numDivisionesX,float numDivisionesY);//ToDo: Tenemos que calcular el numero divisiones en el constructor, está por hacer
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY); // Calcula un tamaño para X e Y automaticamente
    MallaRegular(const MallaRegular& orig);
    virtual ~MallaRegular(){};
    
    void insertar(float x,float y, const T &dato);
    T* buscar(float x,float y, const T &dato);
    bool borrar(float x,float y, const T &dato);
    
    unsigned numElementos();
    unsigned maxElementosPorCelda(); 
    bool fueraAmbito(float x, float y);
    T buscarCercano (float x, float y); //ToDo: cambiar por otro
    float mediaElementosPorCelda();
    
    ///-------Sin Terminar -----------///
    
};

template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY,float numDivisionesX,float numDivisionesY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),tamLogico(0),numDivX(numDivisionesX),numDivY(numDivisionesY),tamCasillaX(xMax/(xMax-xMin)),tamCasillaY(yMax/(yMax-yMin)){
    mallaR.insert(mallaR.begin(), numDivX, std::vector<Casilla<T> >(numDivY));
};

    
template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),tamLogico(0),
        tamCasillaX(xMax/(xMax-xMin)), tamCasillaY(yMax/(yMax-yMin)){
    mallaR.insert(mallaR.begin(), numDivX, std::vector<Casilla<T> >(numDivY));
}


template <class T>
MallaRegular<T>::MallaRegular(const MallaRegular& orig): xMin(orig.xMin), xMax(orig.xMax), yMin(orig.yMin), yMax(orig.yMax),
        tamCasillaX(orig.tamCasillaX),tamCasillaY(orig.tamCasillaY),tamLogico(orig.tamLogico){};

template <class T>
T* MallaRegular<T>::buscar(float x, float y, const T& dato){
    Casilla<T> *posC = obtenerCasilla(x,y);
    return *posC;
}

template <class T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y){
    float numX=(x+xMin)/tamCasillaX;
    float numY=(y+yMin)/tamCasillaY;
    return &mallaR[numX][numY]; //ToDo: esta fuera del rango
}

template <class T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    Casilla<T> *cas=obtenerCasilla(x,y);
    cas->insertarC(dato);
    tamLogico++;
}

template <class T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
    Casilla<T> *cas=obtenerCasilla(x,y);
    if(cas->borrarC(dato)){
        tamLogico--;
        return true;
    }
    return false;
}

template <class T>
unsigned MallaRegular<T>::numElementos(){
    return tamLogico;
}

template <class T>
T MallaRegular<T>::buscarCercano(float x, float y){ //ToDo:Revisar funcionamiento
    T cercano;
    double distancia=99999999;
    Casilla<T> *cas;
    int p=numDivX;
    
    for (int k=1; k<numDivX; k++){
        int cont=0;     
        for (float i=x-(tamCasillaX*k); i<x+(tamCasillaX*k); i=i+tamCasillaX){
            for (float j=y-(tamCasillaY*k); j<y+(tamCasillaY*k); j=j+tamCasillaY){
                if (i>=xMin && i<=xMax && j>=yMin && j<=yMax){
                    //typename std::list<T>::iterator it;
                    cas = obtenerCasilla(i,j);
                    cont+=cas->puntos.size();
                }
            }
        }
        if (cont>0){
            p=k+1;
            break;
        }
    }
        
        for (float i=x-(tamCasillaX); i<x+(tamCasillaX); i+=tamCasillaX){
            for (float j=y-(tamCasillaY); j<y+(tamCasillaY); j=j+tamCasillaY){
                if (i>=xMin && i<=xMax && j>=yMin && j<=yMax){
                    typename std::list<T>::iterator it;
                    cas = obtenerCasilla(i,j);

                    for (it=cas->puntos.begin();it!=cas->puntos.end();it++){
                        double d=sqrt(pow((*it).getX()-x,2)+pow((*it).getY()-y,2));
                        if (d<distancia){
                            cercano=*it;
                            distancia=d;
                        }
                    }
                }
            }
        }         
 
    return cercano;
}

template <class T>
unsigned MallaRegular<T>::maxElementosPorCelda(){
    int num=0,maximo=0;    
   
    for (float i=xMin; i<xMax; i+=tamCasillaX){
        for (float j=yMin; j<yMax; j=j+tamCasillaY){
            Casilla<T> *c = obtenerCasilla(i,j);
            num=c->numPuntosCasilla();
            if (num>maximo) 
                maximo=num;
            }                   
    }
    return maximo;
}

template <class T>
bool MallaRegular<T>::fueraAmbito(float x, float y){ //ToDo: comprobar que funciona
    Casilla<T>* cas;
    for(unsigned i=x-tamCasillaX;i<x+tamCasillaX;i+=tamCasillaX){
        for(unsigned j=y-tamCasillaY;j<y+tamCasillaY;j+=tamCasillaY){
            
            if( (i<=xMax && i>=xMin) && (j<=yMax && j>=yMin) ){
                *cas=obtenerCasilla(i,j);
                if(cas->puntos.size()){
                    typename std::list<T>::iterator ite;
                    for (ite=cas->puntos.begin();ite!= cas->puntos.end();++ite){
                         if ((*ite).getX()>=x-tamCasillaX && (*ite).getX()<=x+tamCasillaX
                                 && (*ite).getY()>=y-tamCasillaY && (*ite).getY()<=y+tamCasillaY)
                                return false;
                    }
                }
            }
        }
    }
    return true;
}

template <class T>
float MallaRegular<T>::mediaElementosPorCelda(){
    float media= (float)numElementos()/(numDivX*numDivY);
    return media;
}

//virtual MallaRegular<T>::~MallaRegular(){}

#endif /* MALLAREGULAR_H */

