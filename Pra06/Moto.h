/* 
 * File:   Moto.h
 * Author: Cayetano
 * Created on 27 de octubre de 2019, 12:10
 */

#ifndef MOTO_H
#define MOTO_H
#include <string>
#include "UTM.h"
#include "PuntoRecarga.h"

using namespace std;
class Cliente; 

enum tipoEstado{Bloqueado,Activo,SinBateria,Rota,Recargando};


class Moto {
public:
    Moto(tipoEstado status=Bloqueado,string _id="",double dlat=37.1,double dlon=3.1 );
    Moto(const Moto& orig);
    virtual ~Moto();
    
    bool operator==( const Moto &orig);
    bool operator<(Moto &orig)const;
    bool operator >(Moto &orig) const;
    Moto& operator=(const Moto &orig);
    
    void seActiva(Cliente *cli);
    
    void seDesactiva();
    
    UTM getPosicion() const;
    
    tipoEstado getStatus() const;
    
    string getId() const;
    void setPorcentajeBateria(float porcentajeBateria);
    float getPorcentajeBateria() const;
    void setStatus(tipoEstado status);
    void setPosicion(UTM posicion);
    void darAviso();
    void Recargar(PuntoRecarga *cargando);
    void terminarRecarga();
    
    
private:
    std::string id;
    tipoEstado status;
    Cliente  *usadoPor; 
    UTM posicion;
    float porcentajeBateria;
    PuntoRecarga *RealizarCarga;
   
};

#endif /* MOTO_H */

