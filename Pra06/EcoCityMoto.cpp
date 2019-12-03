/* 
 * File:   EcoCityMoto.cpp
 * Author: Alemol
 * 
 * Created on 28 de octubre de 2019, 11:38
 */
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "EcoCityMoto.h"

EcoCityMoto::EcoCityMoto(const string& fileClientes, const string& fileMotos,unsigned long tamTabla,int funcionHash):
    idUltimo(0), clientes(tamTabla), motos(){
    cargarMotos(fileMotos);
    cargarClientes(fileClientes,funcionHash);
}

EcoCityMoto::EcoCityMoto(const EcoCityMoto& orig):
    idUltimo(orig.idUltimo),motos(orig.motos),clientes(orig.clientes){}


EcoCityMoto::~EcoCityMoto() {
    
    guardarClientesItinerarios("prueba.txt");
    std::cout<<"Guardado archivo correctamente"<<std::endl;
}


void EcoCityMoto::cargarMotos(string fileNameMotos){ 

    ifstream fe;               
    string linea;                   
    int total = 0;                 
    
    int destado;
    double dlat, dlon;
    string matricula, latitud, longitud,estado;
    tipoEstado tipo;


    fe.open(fileNameMotos);
    
    if(fe.good()){
        
        getline(fe, linea); //lee la primera, que es informativa
        getline(fe, linea);     //Toma una línea del fichero
        while(!fe.eof()){            
            stringstream ss;               
            if(linea!=""){
                ++total;
            }            
  
            if(total>=1){                
                
                ss << linea;
                
                //Leemos Matricula
                getline(ss,matricula,';');    //El carácter ; se lee y se elimina de ss
                
                //Leemos estado moto
                getline(ss,estado,';');          
                // Leemos estado
                destado = stoi(estado);
                switch (destado){
                    case 0: tipo=Bloqueado; break;
                    case 1: tipo=Activo; break;
                    case 2: tipo=SinBateria; break;
                    case 3: tipo=Rota; break;
                }
                //Leemos la latitud y longitud
                getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss

                dlat = stod(latitud);       //tranforma en double
                dlon = stod(longitud);      //tranforma en double
                
                //con todos los atributos leídos, se crea la moto
                Moto moto(tipo, matricula, dlat, dlon);
                motos.push_back(moto);
                
                //comprobacion lectura
               //std::cout << moto.getId() << ";" << moto.getPosicion().latitud <<std::endl;            
            }              
            getline(fe, linea);     //Toma una línea del fichero
        }    
        cout<<"Total de motos en el fichero: " << total <<endl;
        fe.close();     
        
    }else{
        cerr<<"No se puede abrir el fichero"<<endl;
    }
    cout<<"cargadas Motos Correctamente" << endl;
}

void EcoCityMoto::cargarClientes(const string &fileNameClientes,int funHash){
    ifstream fe;                    //Flujo de entrada
    string tipofichero,linea;       //Cada línea tiene un clienete
    int total = 0;                  //Contador de líneas o clientes
    
    //Variables auxiliares para almacenar los valores leídos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon; 

    //Asociamos el flujo al fichero 
    fe.open(fileNameClientes);
    
    if(fe.good()){
        double maxLon=-9999999, maxLat=-9999999, minLon=9999999, minLat=9999999;
        //Mientras no se haya llegado al final del fichero
        stringstream ss1;
        getline(fe, linea); // quitamos la primera línea
        ss1 << linea;
        //Leemos clave de fichero
        getline(ss1,tipofichero,';');       
        if (tipofichero=="1"){
            
            getline(fe, linea);     //Toma una línea del fichero
            while(!fe.eof()){            
                stringstream ss;        //Stream que trabaja sobre buffer interno         
                if(linea!=""){
                    ++total;
                }            
                if(total>=1){                
                    //Inicializamos el contenido de ss
                    ss << linea;
                    //Leemos el NIF
                    getline(ss,dni,';');            //El carácter ; se lee y se elimina de ss
                    //Leemos el pass
                    getline(ss,pass,';');           //El caráter ; se lee y se elimina de ss
                    //Leemos el nombre
                    getline(ss,nombre,';');         //El caráter ; se lee y se elimina de ss
                    //Leemos la dirección
                    getline(ss,direccion,';');      //El caráter ; se lee y se elimina de ss
                    //Leemos la latitud y longitud
                    getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                    getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss
                    dlat = stod(latitud);
                    dlon = stod(longitud);
                    //calculamos Latitud y longitud max y min
                    if (dlon>maxLon)
                        maxLon=dlon;
                    else
                        if (dlon<minLon)
                            minLon=dlon;

                    if (dlat>maxLat)
                        maxLat=dlat;
                    else
                        if (dlat<minLat)
                            minLat=dlat;
                    //con todos los atributos leídos, se crea el cliente
                    Cliente client (dni, nombre, pass, direccion,dlat, dlon, this);
                    clientes.setSelecHash(funHash);
                    bool funciona=clientes.insertar(dni,client);
                    if (!funciona)
                        std::cout <<"No insertado"<<std::endl;
//                    else
//                        std::cout << client.GetDni() << ";" << client.GetNombre() <<std::endl;            
                }              
                getline(fe, linea);     //Toma una línea del fichero
            }
            
            int numItiAlt= 1+rand()%10;
            crearItinerarios(numItiAlt,UTM(minLat,minLon),UTM(maxLat,maxLon));
        }else{
            getline(fe, linea);     //Toma una línea del fichero
            while(!fe.eof()){            
                stringstream ss;        //Stream que trabaja sobre buffer interno         
                if(linea!=""){
                    ++total;
                }            
                if(total>=1){                
                    //Inicializamos el contenido de ss
                    ss << linea;
                    //Leemos el NIF
                    getline(ss,dni,';');            //El carácter ; se lee y se elimina de ss
                    //Leemos el pass
                    getline(ss,pass,';');           //El caráter ; se lee y se elimina de ss
                    //Leemos el nombre
                    getline(ss,nombre,';');         //El caráter ; se lee y se elimina de ss
                    //Leemos la dirección
                    getline(ss,direccion,';');      //El caráter ; se lee y se elimina de ss
                    //Leemos la latitud y longitud
                    getline(ss,latitud,';');        //El caráter ; se lee y se elimina de ss
                    getline(ss,longitud,';');       //El caráter ; se lee y se elimina de ss
                    dlat = stod(latitud);
                    dlon = stod(longitud);
                    
                    //con todos los atributos leídos, se crea el cliente
                    Cliente client (dni, nombre, pass, direccion,dlat, dlon, this);
                    clientes.insertar(dni,client); 
                    bool inserto=clientes.insertar(dni,client);
                    if (!inserto){
                        std::cout << "No insertado" ;                       
                    }
                    
                    Cliente *pClient=0;
                    clientes.buscar(dni,pClient);
                    string nIti,mot;
                    int id,dia,mes,anio,hora,min,minutos;
                    float iniLat,finLat,iniLon,finLon;
                    getline(ss,nIti,';');               
              
                    for (int i=0; i<stoi(nIti); i++){
                        getline(fe, linea);
                        stringstream ss3;
                        ss3 << linea;
                        ss3 >> id; ss3.ignore(1);
                        ss3 >> iniLat; ss3.ignore(1);
                        ss3 >> iniLon; ss3.ignore(1);
                        ss3 >> finLat; ss3.ignore(1);
                        ss3 >> finLon; ss3.ignore(1);
                        ss3 >> dia; ss3.ignore(1);
                        ss3 >> mes; ss3.ignore(1);
                        ss3 >> anio; ss3.ignore(1);
                        ss3 >> hora; ss3.ignore(1);
                        ss3 >> min; ss3.ignore(1);
                        ss3 >> minutos; ss3.ignore(1);
                        ss3 >> mot;
                        //vector<Moto>::iterator itMoto=find(motos.begin(),motos.end(),mot);
                        vector<Moto>::iterator itMoto=motos.begin();
                        while (itMoto!=motos.end()){
                            if ((*(itMoto)).getId()==mot){                             
                                break;
                            }
                            itMoto++;
                        }
                        Itinerario iti(id,UTM(iniLat,iniLon),UTM(finLat,finLon),Fecha(dia,mes,anio,hora,min),minutos,&(*itMoto));;
                        pClient->cargaItinerario(iti);
                    }                                                        
                }              
                getline(fe, linea);     //Toma una línea del fichero
            }
        }
        std::cout<<"Total de clientes en el fichero: " << total <<endl;
        std::cout << "Tamaño tablaHash: " << clientes.tamaTabla() << std::endl;
        std::cout << "Factor de Carga tablaHash: " << clientes.factorCarga() << std::endl;
        std::cout << "Maximo de Colisiones en la tablaHash: " << clientes.maxColisiones() << std::endl;
        std::cout << "Promedio de Colisiones en la tablaHash: " << clientes.promedioColisiones() << std::endl;
               
        fe.close(); //Cerramos el flujo de entrada }else{
        //std::cerr<<"No se puede abrir el fichero"<<endl;
    }    
}

    
unsigned EcoCityMoto::GetIdUltimo() const{
        return idUltimo;
}

void EcoCityMoto::SetIdUltimo(unsigned nuevoIdUltimo){
    idUltimo=nuevoIdUltimo;
}


Cliente* EcoCityMoto::buscarCliente(string dni){//ToDo: Cambiar al final de la hash
    Cliente *elCliente;
    bool encontrado=false;
    encontrado=clientes.buscar(dni,elCliente);
    //it=clientes.find(dni);
    if(encontrado)
        return elCliente;
        
    throw std::invalid_argument("No esta este cliente");
}


vector<Moto>& EcoCityMoto::getMotos(){
    return motos;
}

void EcoCityMoto::desbloqueaMoto(Moto* moto, Cliente* cli) {
    moto->seActiva(cli);
    ++idUltimo;
}

Moto* EcoCityMoto::LocMotoCercana(UTM& ubicacion) {
    Moto *MotoCer=0;
    double dist=999999999, x;
    for (int i=0; i<motos.size()-1;i++)                  
        if (motos[i].getStatus()==Bloqueado){ 
            x=ubicacion.distancia(motos[i].getPosicion());   //distancia en UTM 
            if (x<dist){
                dist=x;
                MotoCer=&motos[i];
            }                        
        }
    return MotoCer;
}

void EcoCityMoto::crearItinerarios(int num, const UTM& min, const UTM& max) {
    vector<string> vectorClientes= clientes.getVectorDNI();
    Cliente *aux;
    int i=0;
    while (i<vectorClientes.size()) {
    //while (i<clientes.getVectorDNI().size()) {
        bool encon=clientes.buscar(vectorClientes[i],aux); //ToDo: cambiar a variable interna
        if (encon){
        aux->crearItinerario (num,idUltimo,min,max);
        idUltimo=idUltimo+num;
        }else 
            cout<<"Cliente no encontrado: "<<vectorClientes[i]<< endl;
        ++i;
    }
}

vector<string> EcoCityMoto::getVecDNICli() {
    return clientes.getVectorDNI();
}


bool EcoCityMoto::proPracticaClientes() {
    bool caye=true;
    cout<<"Esta practica ha sido realizada por:";
    if (caye)
        cout<<"Cayetano y Alemol"<<std::endl;
    return caye;
}

void EcoCityMoto::guardarClientesItinerarios(const string& fileName) {
    ofstream fs;                   
    fs.open(fileName,ofstream::trunc);
    
    
    if(fs.good()){
        vector<string> vecCli=getVecDNICli();
        Cliente* pclient;
        fs << "NIF;clave;nomape;dirección;latitud;longitud;nIti" << endl;
        int i=0; 
        while (i<vecCli.size()){            
            bool p=clientes.buscar(vecCli[i],pclient);
            list<Itinerario> r=pclient->getRutas();
            list<Itinerario>::iterator it2=r.begin();
            fs << pclient->GetDni() <<";"<< pclient->GetPass() <<";"<< pclient->GetNombre() <<";"<<
                  pclient->GetDireccion() <<";"<< pclient->getPosicion().GetLatitud() <<";"<<
                  pclient->getPosicion().GetLongitud() <<";"<< pclient->getRutas().size() << endl;
            while (it2!=r.end()){
                fs << it2->GetId() <<";"<< it2->GetInicio().GetLatitud() <<";"<<
                   it2->GetInicio().GetLongitud() <<";"<< it2->GetFin().GetLatitud() <<";"<<
                   it2->GetFin().GetLongitud() <<";"<< it2->GetFecha().verDia() <<";"<<
                   it2->GetFecha().verMes() <<";"<< it2->GetFecha().verAnio() <<";"<<
                   it2->GetFecha().verHora() <<";"<< it2->GetFecha().verMin() <<";"<< 
                   it2->GetMinutos() <<";"<< it2->GetVehiculo()->getId() << endl;
                it2++;
            }
            i++;            
        }    
        fs.close(); //Cerramos el flujo de entrada         
    }else{
        std::cerr<<"No se puede crear el fichero"<<endl;
    } 
}

bool EcoCityMoto::nuevoCliente(Cliente& nuevoCli) {
    std::string clave=nuevoCli.GetDni();
    return (clientes.insertar(clave,nuevoCli));
}

bool EcoCityMoto::eliminarCliente(std::string borrameid) {
    return clientes.borrar(borrameid);
    
}

vector<Moto*> EcoCityMoto::localizaMotosSinBateria() {
    vector<Moto*> vecMotos;
        for (int i=0; i<motos.size(); i++)
            if (motos[i].getPorcentajeBateria()<15)
                vecMotos.push_back(&motos[i]);
        return vecMotos;
}

void EcoCityMoto::redispersarClientes() {//ToDo: Borrar couts
    cout << " Factor de Carga primero: " << clientes.factorCarga() << endl;
    clientes.redispersar();
    cout << " Factor de Carga Despues: " << clientes.factorCarga() << endl;
}

void EcoCityMoto::borraTodosLosClientes(unsigned long borraTodosEstos){
    vector<string> vectorDeClientes=getVecDNICli();
    unsigned long cliBorrados=0;
    for(cliBorrados=0;cliBorrados<borraTodosEstos;cliBorrados++){
        clientes.borrar(vectorDeClientes[cliBorrados]); //ToDo: mandar un dni
    }
    clientes.setTamLogico(clientes.numClientes()-cliBorrados);
    cout<<"Todos los clientes han sido eliminados, "<<
            "Tam nuevo es: "<< clientes.numClientes()<<std::endl;
}