/* 
 * File:   Moto.cpp
 * Author: Cayetano
 * Created on 28 de octubre de 2019, 9:10
 */

#include <iostream>
#include "Moto.h"
#include "Cliente.h"

Moto::Moto(tipoEstado _status,string _id,double _dlat,double _dlon ):
    status(_status),id(_id),posicion(_dlat,_dlon),usadoPor(nullptr),porcentajeBateria((rand()%100)+1)
{
}

Moto::Moto(const Moto& orig):
    status(orig.status),id(orig.id),posicion(orig.posicion),
        usadoPor(orig.usadoPor),porcentajeBateria(orig.porcentajeBateria){
}

Moto::~Moto() {
}

bool Moto::operator==(const Moto& orig) {
    return id==orig.id;
}

bool Moto::operator>(Moto& orig) const {
    return id>orig.id;
}

bool Moto::operator<( Moto &orig)const{
    return id<orig.id;
}
Moto& Moto::operator=(const Moto& orig) {
    if(this!=&orig){
        status=orig.status;
        id=orig.id;
        posicion=orig.posicion;
        usadoPor=orig.usadoPor;
        porcentajeBateria=orig.porcentajeBateria;
    }
    return *this;
}

void Moto::seActiva(Cliente *cli){
    usadoPor=cli;
    status = Activo;
    //darAviso();
}
void Moto::seDesactiva(){
    status=Bloqueado;
    //this->darAviso();
    usadoPor=0;
}

UTM Moto::getPosicion() const {
    return posicion;
}

tipoEstado Moto::getStatus() const {
    return status;
}

string Moto::getId() const {
    return id;
}

void Moto::setPorcentajeBateria(float porcentajeBateria) {
    this->porcentajeBateria = porcentajeBateria;
}

float Moto::getPorcentajeBateria() const {
    return porcentajeBateria;
}

void Moto::setStatus(tipoEstado status) {
    //Cambiar status para verificar los diferentes medios
    this->status = status;
}

void Moto::setPosicion(UTM posicion) {
    this->posicion = posicion;
}

void Moto::darAviso(){
    switch(status){
        case 0: usadoPor->mostrarMensaje("Bloqueada");break;
        case 1: usadoPor->mostrarMensaje("Activada");break;
        case 2: usadoPor->mostrarMensaje("SinBateria");break;
        case 3: usadoPor->mostrarMensaje("Rota");break;
        case 4: usadoPor->mostrarMensaje("Recargando");break; 
               
    }
}
    
void Moto::Recargar(PuntoRecarga *cargando){
    RealizarCarga=cargando;
}
    
void Moto::terminarRecarga(){
    RealizarCarga=0;
};
