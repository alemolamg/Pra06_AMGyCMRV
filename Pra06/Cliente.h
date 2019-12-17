/* File:   Cliente.h
 * Author: Cayetano
 * Created on 20 de septiembre de 2019, 17:17
 */  
#ifndef CLIENTE_H
#define	CLIENTE_H
#include <string>
#include <list>
#include "UTM.h"
#include "Itinerario.h"

class EcoCityMoto;    

class Cliente {
  
    std::string dni;
    std::string pass;
    std::string nombre;
    std::string direccion;
    UTM posicion;
    std::list<Itinerario> rutas;
    EcoCityMoto *acceso;
    std::string display;
    int puntos;
    
public:
    
    Cliente(string _dni,string _nombre="", string _pass="", string _direccion="", double _latitud=0.0, double _longitud=0.0, EcoCityMoto *_ecoC=0,int _puntos=0):
    dni(_dni), pass(_pass), nombre(_nombre), direccion (_direccion),acceso(_ecoC),rutas() ,posicion (_latitud, _longitud),puntos(_puntos){}
    Cliente(): nombre(""), dni(""), pass(""), rutas(), acceso(0), direccion(""),display(" ") ,posicion(UTM(0.0,0.0)),puntos(rand()%10){};
    Cliente(const Cliente& orig);
    
    
    
    double distancia(const Cliente &otro);
    void crearItinerario(int num,int idUltimo,UTM min, UTM max);
    UTM creaUTMAleatorio(const UTM &min,const UTM &max);

    ~Cliente(){};
    
    bool operator >( Cliente &otro)const;
    bool operator< (  Cliente &otro)const;
    bool operator== ( const Cliente &otro);
    Cliente& operator=(const Cliente &orig);
    
    Moto* buscarMotoCercana();
    void desbloquearMoto(Moto* m);
    void terminarTrayecto();
    bool motoSinBateria(list<Itinerario>::iterator i);
    
    Itinerario& UltimoItinerario() ;
    
    std::string GetDireccion() const;
    std::string GetNombre() const;
    std::string GetPass() const;
    std::string GetDni() const;
    UTM getPosicion() const;
    std::list<Itinerario> getRutas() const;
    void setRutas(list<Itinerario> rutaNueva);
    
    void cargaItinerario(const Itinerario &iti);
    std::string getDisplay() const;
    
    void mostrarMensaje(string texto);
    Moto* getMiMoto();
    void decrementapunto();
    void aumentapunto();
    void RecargarMoto(PuntoRecarga &Punto_Recarga);
    PuntoRecarga puntoRecargaMasCercano();
    void datosPuntoRecarga(PuntoRecarga* puntoR);
    int getPuntos() const;
    
    
    
};

std::ostream& operator<<(std::ostream& out, const Cliente& f);

#endif /* CLIENTE_H */

