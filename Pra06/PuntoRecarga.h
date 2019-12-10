
/* File:   PuntoRecarga.h
 * Author: Cayetano
 * Created on 3 de diciembre de 2019, 12:27
 */

#ifndef PUNTORECARGA_H
#define PUNTORECARGA_H

#include "UTM.h"

//Prueba para que se suba a github//
class PuntoRecarga {
public:
    PuntoRecarga(std::string _id="",double lat=0,double lon=0):
        id(_id),posicion(UTM(lat,lon)){};
        
    PuntoRecarga(const PuntoRecarga& orig):
        id(orig.id),posicion(orig.posicion){};
    
    
    virtual ~PuntoRecarga(){
    };
    
    PuntoRecarga& operator=(const PuntoRecarga& orig){
    if (this!=&orig){
        id=orig.id;
        posicion=orig.posicion;
    }
    return *this;
}


    std::string GetId() const {
        return id;
    }

    double getX() const{
        return posicion.latitud;
    }
    
    double getY() const{
        return posicion.longitud;
    }
private:
    std::string id;
    UTM posicion;
};
#endif /* PUNTORECARGA_H */

