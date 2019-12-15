#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <csetjmp>
#include "Cliente.h"
#include "Moto.h"
#include "EcoCityMoto.h"
#include "PuntoRecarga.h"

void mostrarInformacionCliente(const Cliente *cli) {
    std::cout << "\n Cliente: " << cli->GetDni()
                <<" Cuyo nombre es: "<<cli->GetNombre()<<std::endl
                <<"El cual tiene la siguiente contraseña: "<<cli->GetPass()<<std::endl
                <<"Situado en: " << 
                cli->getPosicion().GetLatitud() << "," <<
                 cli->getPosicion().GetLongitud() << std::endl;
}

int main(){    
    unsigned long primo,numero=10000;
    float max=7, min=3;
    float tamX=max/(max-min);
    
    std::vector<int> datosPR={37,38, 3, 4, 18, 18};
    
    cout<<tamX<<std::endl;
    setlocale(LC_ALL,"es_ES.UTF8"); 
    srand(time(0));
    try{ 
        int modo=3; // modo=1-> entrenar; modo=0-> ejecutar normal; //Prueba creación de los puntos recarga

        if(modo==0){
            //int funHash=0;
            unsigned long tam[]={numero,10580};
//            std::vector<int> datosPR={37,38, 3, 4, 18, 18};
            
             //cout<<"\nCargamos el archivo con el numero: "<< tam[0]<<" funHash num: 0 " <<std::endl;
                    EcoCityMoto ecoEntrena(datosPR,"clientes_v2.csv","motos.txt",tam[0],0); //Prueba creación de los puntos recarga
//                    EcoCityMoto genPuntosRecarga();
//            for(int i=0;i<2;i++){ //Cambia el Tamaño  //comentado para pruevas
//                cout<<"\n\nCargamos con el numero "<<tam[i]<<std::endl;
//                for(int funHash=0;funHash<3;funHash++){ //Recorre las funciones hash
//                    cout<<"\nCargamos el archivo con el numero: "<< tam[i]<<" funHash num: "<<funHash+1 <<std::endl;
//                    EcoCityMoto ecoEntrena("clientes_v2.csv","motos.txt",tam[i],funHash);
//                    //cout<<"Fin del nuemro "<<tam[i]<<"\n\n";    
//                }
//             }
            cout <<"\nTERMINADO ENTRENAMIENTO\n"<<std::endl;
             
             
         }else{
            
            //1)Crear de forma aleatoria 300 puntos de recarga
            
            cout << "Creando Eco.... Comienzo de lectura de ficheros " << endl;   
            EcoCityMoto eco("clientes_v2.csv","motos.txt",numero); // Se crean en el constructor por defecto de EcoCityMoto
            
            //EcoCityMoto eco("clientes_v5.csv","motos2.txt",numero); 
            //EcoCityMoto eco("prueba.txt","motos2.txt",numero);
            
            //2) probar tamaños de malla
            //realizado en el entrenamiento
            
            //3)Añadir a todos los clientes un número de puntos aleatorio entre 1 y 10
            
            
            //4)Añadir un nuevo cliente que no exista previamente con coordenadas en Jaén.
            std::string dniCli="50617459W";
            Cliente clienteA("50617459W", "Alejandro Molero" , "antirrobo", "Universidad", 37.3, 38.4, &eco);
            eco.nuevoCliente(clienteA);
            
            //5) Localizar el cliente anterior dado su DNI y mostrar toda la información del cliente
            Cliente *pCli= eco.buscarCliente(dniCli);
            mostrarInformacionCliente(pCli);
            
            //6) Localizar la moto cercana y mostrar información
            Moto* motoCerCli =pCli->buscarMotoCercana(); 
            std::cout << "Moto mas cercana: " << motoCerCli->getId() << " situada en: " <<
            motoCerCli->getPosicion().GetLatitud() << "," << motoCerCli->getPosicion().GetLongitud() << std::endl;
            
            
            
            
            //--------PRACTICA06-------------//
                       
                        
                        
            //Realizar un itinerario con la moto localizada con duración válida para la carga de batería de la moto
            std::cout << "Comienza Ruta n: " << eco.GetIdUltimo() << std::endl;
            pCli->desbloquearMoto(motoCerCli);
            motoCerCli->darAviso(); //esto es de la parte 7;
            std::cout << "Desbloqueamos la Moto: " << motoCerCli->getId() << std::endl;
            pCli->terminarTrayecto();
            std::cout << "Fin de la Ruta: " << pCli->UltimoItinerario().GetFecha().cadena() <<
                    ", Minutos: " << pCli->UltimoItinerario().GetMinutos() <<
                    ", Id: " << pCli->UltimoItinerario().GetVehiculo()->getId() <<
                    ", Pos Fin: " << pCli->UltimoItinerario().GetFin().GetLatitud() << "<-->" <<
                    pCli->UltimoItinerario().GetFin().GetLongitud() << std::endl;
            
            // mostrar en el display estado moto
                //motoCerCli->darAviso();
                /// La función Moto::darAviso se ejecuta internamente en el Cliente::terminarTrayecto, 
                /// asi no hace falta mostrarlo desde el main, porque el cliente ya no tiene la moto
            
            // Borrar el cliente
            if(eco.eliminarCliente(clienteA.GetDni()))
                cout<<"Cliente Borrado correctamente"<<std::endl;
            else{
                cout<<"Cliente no borrado"<<std::endl;
                throw invalid_argument ("Main.cpp: parte8:: cliente no borrado");
            }
            // insertar el mismo cliente de nuevo
            bool alemol=eco.nuevoCliente(clienteA); 
            if (!alemol)
                cout<<"Cliente no añadido correctamente"<<std::endl;
            
            // Eliminar 1000 clientes y redispersar si es necesario
            eco.borraTodosLosClientes(1000); 
            eco.redispersarClientes();
            
            // volver a cargar los ficheros como en la practica 4...
            
         }

                
     //Tratamiento de errores
     }catch (ErrorFechaIncorrecta &e){
            std::cerr << "Fecha Incorrecta: " << std::endl;
     }catch (std::runtime_error &e){ //std::ifstream::failure &e){
            std::cerr << "Excepcion en fichero: " << e.what() << std::endl;
     }catch (std::bad_alloc &e){
            std::cerr << "No hay memoria suficiente para el objeto dinamico" << std::endl;     
     }catch (std::invalid_argument &e){
            std::cerr << e.what() << std::endl;
     } 
          
    return 0;
    
}
