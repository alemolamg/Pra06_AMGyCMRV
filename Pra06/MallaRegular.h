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



template <class T>
class MallaRegular;
    
template <class T>
class Casilla{
    std::list<T> puntos;
    friend class MallaRegular<T>;
    public:
        Casilla(): puntos(){};
        Casilla(const Casilla& orig): puntos(orig.puntos){};
        ~Casilla();
        
        
};        
        
template <class T>
class MallaRegular {  
    float xMin,xMax,yMin,yMax, tamCasX, tamCasY; //ToDo: editar para no ser igual
    Casilla<T> *obtenerCasilla(float x, float y);
    std::vector<std::vector<Casilla<T> > >mallaR;
    unsigned numElementosTotales;
    
public:
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY, float tamCasillaX, float tamCasillay);
    MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY); // Calcula un tamaño para X e Y automaticamente
    MallaRegular(const MallaRegular& orig);
    
    
    ///-------Sin Terminar -------------///
    virtual ~MallaRegular();
    
    void insertarDato(float x,float y, const T &dato);
    T* buscarDato(float x,float y, const T &dato);
    bool borrarDato(float x,float y, const T &dato);
    
    unsigned numElementos();
    T buscarCercano (float x, float y);
    bool fueraAmbito(float x, float y);
    unsigned maxElementosPorCelda();
    float mediaElementosPorCelda();
       
private:
    
    
};


MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY, float tamCasillaX, float tamCasillay):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY), tamCasX(tamCasillaX),tamCasY(tamCasillay){};


MallaRegular<T>::MallaRegular(float minimoX, float maximoX, float minimoY, float maximoY):
    xMin(minimoX), xMax(maximoX), yMin(minimoY), yMax(maximoY),
        tamCasX(xMax/(xMax-xMin)), tamCasY(yMax/(yMax-yMin)){}
    
MallaRegular<T>::MallaRegular(const MallaRegular& orig): xMin(orig.xMin), xMax(orig.xMax), yMin(orig.yMin), yMax(orig.yMax),
        tamCasX(orig.tamCasX),tamCasY(orig.tamCasY){};

T MallaRegular<T>::buscarDato(float x, float y, const T& dato){
    Casilla<T> *posC = obtenerCasilla(x,y);
    return *posC;
}


Casilla<T>* MallaRegular<T>::obtenerCasilla(float x, float y){
    
}


#endif /* MALLAREGULAR_H */

