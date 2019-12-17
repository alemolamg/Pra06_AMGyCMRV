/* 
 * File:   Cliente.cpp
 * Author: Alemol
 * Created on 26 de septiembre de 2019, 11:29
 */
#include "Cliente.h"
#include "EcoCityMoto.h"
#include <cmath>
#include <iostream>
Cliente::Cliente(const Cliente& orig):
        dni(orig.dni),pass(orig.pass), nombre(orig.nombre),display(""),
        direccion(orig.direccion),rutas(orig.rutas), acceso(orig.acceso),posicion(orig.posicion){}

bool Cliente::operator<(  Cliente& otro)const {
    return dni<otro.dni;
}

bool Cliente::operator== ( const Cliente &otro) {
    return dni==otro.dni;
}

Cliente& Cliente:: operator=(const Cliente &orig) {
    if(this!=&orig){
        nombre=orig.nombre;
        dni=orig.dni;
        pass=orig.pass;
        direccion=orig.direccion;
        posicion=orig.posicion;
        rutas=orig.rutas;
        acceso=orig.acceso;
        display=orig.display;
    }
    return *this;
}

std::string Cliente::GetDireccion() const {
    return direccion;
}

std::string Cliente::GetNombre() const {
    return nombre;
}

std::string Cliente::GetPass() const {
    return pass;
}

std::string Cliente::GetDni() const {
    return dni;
}

UTM Cliente::getPosicion() const {
    return posicion;
}

std::list<Itinerario> Cliente::getRutas() const {
    return rutas;
}

double Cliente::distancia(const Cliente& otro) {
    return sqrt(pow((otro.posicion.GetLatitud()-posicion.GetLatitud()),2)+pow((otro.posicion.GetLongitud()-posicion.GetLongitud()),2));
}

UTM Cliente::creaUTMAleatorio(const UTM &min,const UTM &max) {
    //int cont=0;
        double iniY,iniZ;
        srand(time(NULL));
            int x=rand()%(10000),xx=rand()%(10000); 
            double y=(float) x/1000, z=(float) xx/1000;
            y=y*(max.GetLatitud()-min.GetLatitud())+min.GetLatitud();
            z=z*(max.GetLongitud()-min.GetLongitud())+min.GetLongitud();
                iniY=y;
                iniZ=z;        
        return  UTM(iniY,iniZ);
        
}

void Cliente::crearItinerario(int num, int idUltimo, UTM min, UTM max) {
    // pagina: https://blog.martincruz.me/2012/09/obtener-numeros-aleatorios-en-c-rand.html
    srand(time(NULL));
    vector<Moto*> motosVector;
    //num= num+rand()%8;
    
    for(int i=0; i<num;i++){
    //Calcula la Fecha aleatoria
    
        int mes=1+rand()%(13-1);
        int dia=1;
        int anio=2019+rand()%(11-1);
        if(mes==2){
            dia=1+rand()%(29-1);
        }else 
            if(mes==4||mes==6||mes==9||mes==11){
                dia=1+rand()%(31-1);
            }else
                dia=1+rand()%(32-1);
    
        Fecha fecha(dia,mes,anio);
    
        //Calcula UTM aleatorios dentro del rango
                
        //UTM iniNuevo=creaUTMAleatorio(min,max); 
        UTM finNuevo=creaUTMAleatorio(min,max);
    
        //generamos el id         
        ++idUltimo;
    
        //vamos a añadir el itinerario
        int minNuevo=1+rand();  //generamos minutos aleatorios
        Moto *m=buscarMotoCercana();
        motosVector.push_back(m);
        m->seActiva(this);
    
        Itinerario it2(idUltimo,posicion,finNuevo,fecha,minNuevo,m);
        m->setPosicion(finNuevo);
        rutas.push_back(it2);
        
        //std::cout<<"Mat moto:" << (m->getId()) <<" pos moto:"<< (m->getPosicion().latitud)<<m->getPosicion().longitud << std::endl;
         
    } 
    
    for(int i=0;i<num;i++){
        motosVector[i]->seDesactiva();
        //cout<<"Moto "<<i<<" Desactivada \n";
    }
};


 bool Cliente::operator >( Cliente &otro) const{
     return dni>otro.dni;
 }
 Moto* Cliente::buscarMotoCercana(){
     Moto* m=acceso->LocMotoCercana(posicion);
     return m;
 };
 
 void Cliente::desbloquearMoto(Moto* m){
     Fecha fecha;
     acceso->desbloqueaMoto(m,this);
     UTM inicio=m->getPosicion();
     int y=37000+rand()%(1000), z=3000+rand()%(1000);
     double yy=y/1000,zz=z/1000;
        UTM fin(yy,zz);

     int min = 0;
     rutas.push_back(Itinerario(fecha,inicio,fin,acceso->GetIdUltimo(),min,m));
 };
 
 void Cliente::terminarTrayecto(){ 
     list<Itinerario>::iterator i=rutas.end();
     i--;
        Fecha f1= i->GetFecha(); 
        Fecha f2;    
         
        int bateria=rand()%(int)i->GetVehiculo()->getPorcentajeBateria();
        if(bateria<=15){
            bool alemol=motoSinBateria(i);           
        };
        
        int minutos= (f2.verHora()*60 + f2.verMin())- (f1.verHora()*60 + f1.verMin()); 
        i->SetMinutos(minutos);
        
        i->GetVehiculo()->setStatus(Bloqueado);
        i->GetVehiculo()->darAviso();//se desactiva tambien en la otra función
        
        i->GetVehiculo()->seDesactiva(); //bloquea la moto y la desvincula del cliente

 }
 
 std::ostream& operator<<(std::ostream& out, const Cliente& f){
        return out << f.GetDni() ;
    }
 Itinerario& Cliente::UltimoItinerario() {
     list<Itinerario>::iterator i=rutas.end();
     return *--i;
     //return *rutas.rbegin();
     //return (rutas.end())-1; 
}
 
void Cliente::cargaItinerario(const Itinerario& iti) {
    rutas.push_back(iti);
}

std::string Cliente::getDisplay() const {
    cout<<display<<std::endl;
    return display;
}

void Cliente::setRutas(list<Itinerario> rutaNueva) {
    this->rutas=rutaNueva;
}

void Cliente::mostrarMensaje(string texto){
    display=texto;
    std::cout<<display<<std::endl;
};


Moto* Cliente::getMiMoto() {
    list<Itinerario>::iterator i=rutas.end();
    i--;
    return i->GetVehiculo();
}




void Cliente::decrementapunto(){
    if(puntos>0){
        puntos--;
    }
}
    void Cliente::aumentapunto(){
        if(puntos<10){
            puntos++;
        }
    }
    
    void Cliente::RecargarMoto(PuntoRecarga &Punto_Recarga){
        getMiMoto()->Recargar(&Punto_Recarga);
        getMiMoto()->setStatus(Recargando); // no pasa el valor correcto
        getMiMoto()->darAviso();
        getDisplay();                       //esto para que sirve??
        getMiMoto()->setPorcentajeBateria(100);
        getMiMoto()->terminarRecarga();
        getMiMoto()->setStatus(Bloqueado);
        
        getMiMoto()->darAviso();    // no pasa el valor correcto
//        getDisplay();               //esto para que sirve??
//        getMiMoto()->seDesactiva();
        
    }
    
     PuntoRecarga Cliente::puntoRecargaMasCercano(){
        return acceso->puntoRecargaCercano(*this);
}
     
void Cliente::datosPuntoRecarga(PuntoRecarga* puntoR) {
    cout<<"El punto recarga num: "<<puntoR->GetId()<<
            ", se encuentra en la posicion: ("<<
            puntoR->getX()<<","<<puntoR->getY()<<")"<<endl;
}

bool Cliente::motoSinBateria(list<Itinerario>::iterator i) {
    
    //a) busca el punto cercano
    i->GetVehiculo()->setStatus(SinBateria);
    i->GetVehiculo()->darAviso();
    
    //b) y c) recarga la moto
    PuntoRecarga prc=(puntoRecargaMasCercano()); //ToDo: no encuentra el punto recarga
    cout<<"El punto recarga num: "<<prc.GetId()<<
            ", se encuentra en la posicion: ("<<
            prc.getX()<<","<<prc.getY()<<")"<<endl;
    //datosPuntoRecarga(&prc);
    RecargarMoto(prc); 
                
    //d) //ToDo: dudas sobre la 3
    return true;
}

