/* 
 * File:   THashCliente.h
 * Author: Alemol
 * Created on 19 de noviembre de 2019, 11:43
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include "Cliente.h"
//#include "EcoCityMoto.h"
#include <vector>
#include <iostream>
#include "Cliente.h"
#define limite 30

//#define limite 20

enum EstadoCaja {VACIA,OCUPADA,DISPONIBLE};

//class Cliente;

class THashCliente {
private:
    //friend class Entrada;
    class Entrada{
    public:
        unsigned long clave;
        std::string dni;
        EstadoCaja marca;
        Cliente cliDatos;
        //-----Funciones----//
        Entrada(): marca(VACIA),clave(0),dni(""),cliDatos(Cliente()){}
        ~Entrada(){};
    };
    
    unsigned long tamFisico;
    unsigned long tamLogico;
    unsigned long totalColisiones;
    unsigned long maxCol;
    unsigned long primo;// Primo usado para la tabla=tam
    int selecHash=1;
    std::vector<Entrada> tabla;
    
    //--------Funciones--------//
    unsigned long calcPrimo(unsigned long& tam);
    unsigned long calcPrimoMenor(unsigned long& primer);
    unsigned long hash1(unsigned long& clave, int intento); 
    
    
    
public:
    
    inline unsigned long djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;
        return hash;
    }
    //-----Funciones--THash--------//
    THashCliente(unsigned long tamTabla=20);
    THashCliente(const THashCliente& orig); 
    virtual ~THashCliente();

    void redispersar (); //ToDo: revisar que funciona correctamente redispersar
    unsigned int numClientes();
    bool esprimo(unsigned long& n);
    
    bool insertar(const std::string& dni,Cliente& cli);
    bool buscar (string &dni, Cliente* &cli);
    bool borrar(std::string& dni);
    
    
    //---Funciones-Extra----//
    unsigned int maxColisiones();
    bool insertarEnNueva(vector<Entrada>& nuevo, const std::string& dni,Cliente *cli, int posicion);
    float promedioColisiones();
    float factorCarga();
    unsigned int tamaTabla();
    vector<string> getVectorDNI();
    void setTamLogico(unsigned long tamLogico);
    void setSelecHash(int selecHash);
    //int getSelecHash() const;
    

};
#endif /* THASHCLIENTE_H */