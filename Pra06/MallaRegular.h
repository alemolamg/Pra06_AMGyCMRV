/* 
 * File:   MallaRegular.h
 * Author: Alemol
 * Created on 3 de diciembre de 2019, 12:26
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

#include <list>
#include <inttypes.h>
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
        ~Casilla();
        unsigned numCasillas(){return puntos.size();};
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
               
//        typename std::list<T>::iterator begin(){
//            return puntos.begin();
//        }
//        
//        typename std::list<T>::iterator end(){
//            return puntos.end();
//        }
};        
        
template <class T>
class MallaRegular {  
    float xMin,xMax,yMin,yMax, tamCasillaX, tamCasillaY,tamLogico; 
    Casilla<T> *obtenerCasilla(float x, float y);
    std::vector<std::vector<Casilla<T> > >mallaR;
    unsigned numElementosTotales;
    
public:
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY, float tamCasillaX, float tamCasillay);
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY); // Calcula un tamaño para X e Y automaticamente
    MallaRegular(const MallaRegular& orig);
    
    
    ///-------Sin Terminar -------------///
    virtual ~MallaRegular();
    
    void insertar(float x,float y, const T &dato);
    T* buscar(float x,float y, const T &dato);
    bool borrar(float x,float y, const T &dato);
    
    unsigned numElementos();
    T buscarCercano (float x, float y);
    bool fueraAmbito(float x, float y);
    unsigned maxElementosPorCelda();
    float mediaElementosPorCelda();
       
private:
    
    
};

template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY, float tamCasillaX, float tamCasillay):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY), tamCasillaX(tamCasillaX),tamCasillaY(tamCasillay),tamLogico(0){};

    
template <class T>
MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),tamLogico(0),
        tamCasillaX(xMax/(xMax-xMin)), tamCasillaY(yMax/(yMax-yMin)){}

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
    int numX=(x-xMin)/tamCasillaX;
    int numY=(y-yMin)/tamCasillaY;
    return &mallaR[numX][numY];
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


#endif /* MALLAREGULAR_H */

