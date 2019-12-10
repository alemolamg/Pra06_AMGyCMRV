/* File:   EcoCityMoto.h
 * Author: Alemol
 * Created on 28 de octubre de 2019, 11:38
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "THashCliente.h"
#include <vector>
#include "Moto.h"
#include "Cliente.h"
#include "PuntoRecarga.h"
#include "MallaRegular.h"

using namespace std;

class EcoCityMoto {
private:
    unsigned idUltimo;
    vector <Moto> motos;
    THashCliente clientes;
    vector<string> dniClientes;
    MallaRegular<PuntoRecarga> recargaPuntos;
    
    //---FUNCIONES----------//
    void cargarMotos(string fileNameMotos);
    void cargarClientes(const string &fileNameClientes,int funHash);
    void crearItinerarios(int num,const UTM &min,const UTM &max);
    void GuardarMotosItinerarios(const string& file); //ToDo: hacer, no está hecho nada
    void guardarClientesItinerarios(const string &fileName);   
//    THashCliente& getClientes();
    bool nuevoCliente(Cliente& nuevoCli);
    vector<string> getVecDNICli();
    
    
public:
    EcoCityMoto(const string &fileClientes="prueba.txt",const string &fileMotos="motos.txt",unsigned long tamTabla=10000,int funcionHash=0);
    EcoCityMoto(const EcoCityMoto& orig);
    
    unsigned GetIdUltimo() const;
    void SetIdUltimo(unsigned nuevoIdUltimo);
    
    vector<Moto*> localizaMotosSinBateria();
    Moto* LocMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);   
    
//    bool nuevoCliente(Cliente& nuevoCli);
    Cliente* buscarCliente(string dni);

    vector<Moto>& getMotos();
    bool eliminarCliente(std::string borrameid);
    bool proPracticaClientes();
    void borraTodosLosClientes(unsigned long borraTodosEstos=1000);
//    vector<string> getVecDNICli();
    void redispersarClientes();
    PuntoRecarga puntoRecargaCercano (Cliente &cli);
    virtual ~EcoCityMoto();
    
    ///------Sin Terminar--------//
       
};

#endif /* ECOCITYMOTO_H */