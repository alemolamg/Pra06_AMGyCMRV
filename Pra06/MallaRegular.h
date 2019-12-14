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
#include <ostream>
#include <iostream>

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
    float xMin,xMax,yMin,yMax, tamCasillaX, tamCasillaY,numDivX,numDivY; //ToDo:: gestionar numDivisiones correctamente
    Casilla<T> *obtenerCasilla(float x, float y);
    std::vector<std::vector<Casilla<T> > >mallaR;
    unsigned numElementosTotales;
    //----Funciones ---------//
    
    void setTamCasillaX(float tamCasillaX);
    void setTamCasillaY(float tamCasillaY);
    
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
    bool ajustarTamMalla(int nuevoDivD);
    
    
    unsigned getNumElementosTotales() const;
    float getTamCasillaY() const;
    float getTamCasillaX() const;
    float getYMax() const;
    float getYMin() const;
    float getXMax() const;
    float getXMin() const;
    
    
    float getNumDivY() const;
    float getNumDivX() const;
    void setNumDivY(float numDivY);
    void setNumDivX(float numDivX);
    
    ///-------Sin Terminar -----------///
    
};

template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY,float numDivisionesX,float numDivisionesY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),numDivX(numDivisionesX),numDivY(numDivisionesY),
        tamCasillaX((xMax-xMin)/numDivisionesX),tamCasillaY((yMax-yMin)/numDivisionesY),numElementosTotales(0){
    mallaR.insert(mallaR.begin(), numDivX, std::vector<Casilla<T> >(numDivY));
};

    
template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),numDivX(15),numDivY(15),
        tamCasillaX((xMax-xMin)/numDivX), tamCasillaY((yMax-yMin)/numDivY),numElementosTotales(0){
    mallaR.insert(mallaR.begin(), numDivX, std::vector<Casilla<T> >(numDivY));
}


template <class T>
MallaRegular<T>::MallaRegular(const MallaRegular& orig): xMin(orig.xMin), xMax(orig.xMax), yMin(orig.yMin), yMax(orig.yMax),
        tamCasillaX(orig.tamCasillaX),tamCasillaY(orig.tamCasillaY),numElementosTotales(orig.numElementosTotales){};

template <class T>
T* MallaRegular<T>::buscar(float x, float y, const T& dato){
    Casilla<T> *posC = obtenerCasilla(x,y);
    return *posC;
}

template <class T>
Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y){
    float numX=(x-xMin)/tamCasillaX;
    float numY=(y-yMin)/tamCasillaY;
    return &mallaR[numX][numY];
//    std::cout<<"malla insertada"<<std::endl;
}

template <class T>
void MallaRegular<T>::insertar(float x, float y, const T& dato){
    Casilla<T> *cas=obtenerCasilla(x,y);
    cas->insertarC(dato);
//    std::cout<<"nos hemos quedado en el puntoRecarga num: "<<numElementosTotales<<std::endl;
    numElementosTotales++;
}

template <class T>
bool MallaRegular<T>::borrar(float x, float y, const T& dato){
    Casilla<T> *cas=obtenerCasilla(x,y);
    if(cas->borrarC(dato)){
        numElementosTotales--;
        return true;
    }
    return false;
}

template <class T>
unsigned MallaRegular<T>::numElementos(){
    return numElementosTotales;
}

template <class T>
T MallaRegular<T>::buscarCercano(float x, float y){ 
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

template <class T>
unsigned MallaRegular<T>::getNumElementosTotales() const {
    return numElementosTotales;
}

template <class T>
void MallaRegular<T>::setTamCasillaY(float tamCasillaY) {
    this->tamCasillaY = tamCasillaY;
}

template <class T>
float MallaRegular<T>::getNumDivY() const {
    return numDivY;
}

template <class T>
float MallaRegular<T>::getNumDivX() const {
    return numDivX;
}

template <class T>
void MallaRegular<T>::setNumDivY(float numDivY) {
    this->numDivY = numDivY;
}

template <class T>
void MallaRegular<T>::setNumDivX(float numDivX) {
    this->numDivX = numDivX;
}

template <class T>
float MallaRegular<T>::getTamCasillaY() const {
    return tamCasillaY;
}

template <class T>
void MallaRegular<T>::setTamCasillaX(float tamCasillaX) {
    this->tamCasillaX = tamCasillaX;
}

template <class T>
float MallaRegular<T>::getTamCasillaX() const {
    return tamCasillaX;
}

template <class T>
float MallaRegular<T>::getYMax() const {
    return yMax;
}

template <class T>
float MallaRegular<T>::getYMin() const {
    return yMin;
}

template <class T>
float MallaRegular<T>::getXMax() const {
    return xMax;
}

template <class T>
float MallaRegular<T>::getXMin() const {
    return xMin;
}

template <class T>
bool MallaRegular<T>::ajustarTamMalla(int nuevoDivD){
//    tamCasillaX((xMax-xMin)/numDivX)
    setTamCasillaX((getXMax()- getXMin()) / getNumDivX()+nuevoDivD);
    setTamCasillaY((getYMax()- getYMin()) / getNumDivY()+nuevoDivD);
    setNumDivX(getNumDivX()+ nuevoDivD);
    setNumDivY(getNumDivY()+ nuevoDivD);
    return true;
}

#endif /* MALLAREGULAR_H */

