/* 
 * File:   MallaRegular.h
 * Author: Alemol
 * Created on 3 de diciembre de 2019, 12:26
 */

#ifndef MALLAREGULAR_H
#define MALLAREGULAR_H

#include <list>



template <class T>
class MallaRegular;
    
template <class T>
class Casilla{
    std::list<T> puntos;
    friend class MallaRegular<T>;
    public:
        Casilla(): puntos(){};
};        
        
template <class T>
class MallaRegular {  
    float xMin,xMax,yMin,yMax;
    
    
public:
    MallaRegular();
    MallaRegular(const MallaRegular& orig);
    virtual ~MallaRegular();
    
    void insertarDato(float x,float y, const T &dato);
    T* buscarDato(float x,float y, const T &dato);
    bool borrarDato(float x,float y, const T &dato);
    
    
    
private:
    
    
    

};

#endif /* MALLAREGULAR_H */

