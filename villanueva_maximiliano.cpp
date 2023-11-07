#include <iostream>
#include <cstring>
using namespace std;

#include"parcial2.h"

class ArchivoNuevoPunto1{

private:
//int numeroProveedor;
//int provincia;

char codigoCliente[5];
char nombre[30];
float importe;

public:

    const char* getCodigoCliente() { return codigoCliente; }
    const char *getNombre(){return nombre;}
    float getImporte() { return importe; }

    void setCodigoCliente(const char *n){strcpy(codigoCliente,n);}
    void setNombre(const char *n){strcpy(nombre,n);}
    void setImporte(float im){importe=im;}


    void Mostrar(){
    cout<<"Codigo de Cliente: "<<getCodigoCliente()<<endl;
    cout<<"Nombre: "<<getNombre()<<endl;
    cout<<"Importe"<<getImporte()<<endl;
}


    bool grabarRegistro(){
    FILE *p;
    p = fopen("ArchivoNuevoPunto1.dat", "ab");
    if (p == NULL)
    {
        return false;
    }
    bool escribio = fwrite(this, sizeof(ArchivoNuevoPunto1), 1, p);
    fclose(p);
    return escribio;
    }

    void LimpiarArchivo(){
FILE *p;
ArchivoNuevoPunto1 ClassM;

p=fopen("ArchivoNuevoPunto1.dat","wb");
if(p==NULL){
    cout<<"ERROR de ARCHIVO"<<endl;
    system("pause");
}

fclose(p);
}

void MostrarArchivo(){
ArchivoNuevoPunto1 ClassM;
FILE *p;

p=fopen("ArchivoNuevoPunto1.dat","rb");
if(p==NULL){
    cout<<"ERROR de ARCHIVO"<<endl;
    system("pause");
}

while(fread(&ClassM,sizeof (ArchivoNuevoPunto1),1,p)==1){
ClassM.Mostrar();
cout<<endl;
}
fclose(p);
}

//SOBRACARGA DE OPERADORES

    bool operator<(float tamanio) {
        if(this->importe > tamanio) {
            return true;
        } else {
            return false;
        }
    }



    operator float() const {
        return this->importe;
    }

//CONSTRUCTORES

ArchivoNuevoPunto1(float imp) : importe(imp) {}
ArchivoNuevoPunto1(){}



    // bool operator<(const Venta &obj) {
    //     if(this->importe < obj.importe) {
    //         return true;
    //     } else {
    //         return false;
    //     }
    // }
};

void Punto1();
void Punto2();
void Punto3();
void Punto4();

int main(){

Punto1();


	cout<<endl;
	system("pause");
    return 0;
}

void Punto1(){

    ArchivoNuevoPunto1 objAN;

    Venta obtV;
    ArchivoVentas ARv("ventas.dat");
    
    int tam1;
    tam1 = ARv.contarRegistros();


    Cliente obtC;
    ArchivoClientes ARc("clientes.dat");



    int tam2;
    tam2 = ARc.contarRegistros();


    for(int x=0; x<tam1; x++){
        bool bandera = false;

        if((obtV.getEstado()==true)&&(obtV.getImporte()<15000)){

            for(int y=0; y<tam2; y++){
                
                if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0)) && (obtC.getEstado() == true)){
                    bandera = true;
                }

            }

        }

        if (bandera == true)
        {
            objAN.setCodigoCliente(obtC.getCodigoCliente());
            objAN.setImporte(obtV.getImporte());
            objAN.setNombre(obtC.getNombre());
            if(objAN.grabarRegistro()){}//cout<<"Perfeto PA"<<endl;}
        }

    }
    objAN.MostrarArchivo();


    //objAN.LimpiarArchivo();

}

void Punto2(){

    ArchivoNuevoPunto1 objAN;

    Venta obtV;
    ArchivoVentas ARv("Ventas.dat");
    
    int tam1;
    tam1 = ARv.contarRegistros();

    Cliente obtC;
    ArchivoClientes ARc("clientes.dat");

    int tam2;
    tam2 = ARc.contarRegistros();

    int cont=0;

    char **VecCodigoCliente = new char*[tam2];
    int *vecImporte = new int[tam1];
    char **vecNombre = new char*[tam2];


    for(int x=0; x<tam1; x++){
        bool bandera = false;

        if((obtV.getEstado()==true)&&(obtV.getImporte()<15000)){

            for(int y=0; y<tam2; y++){
                
                if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0)) && (obtC.getEstado() == true)){
                    bandera = true;
                }

            }

        }

        if (bandera == true)
        {

            objAN.setCodigoCliente(obtC.getCodigoCliente());
            objAN.setImporte(obtV.getImporte());
            objAN.setNombre(obtC.getNombre());
            if(objAN.grabarRegistro()){}//cout<<"Perfeto PA"<<endl;}

            VecCodigoCliente[cont] = new char[30];   // Asignar memoria para cada VecCodigoCliente[cont]
            strcpy(VecCodigoCliente[cont], obtC.getCodigoCliente());

            vecImporte[cont] = obtV.getImporte();
            
            vecNombre[cont] = new char[30];
            strcpy(vecNombre[cont], obtC.getNombre());

            cont++;
        }

    }

    //objAN.MostrarArchivo();
    //objAN.LimpiarArchivo();

//Mostrar Vector

cout<<cont<<endl;

    for(int i=0; i<cont; i++){
        cout<<"Codigo de Cliente: "<<VecCodigoCliente[i]<<endl;
        cout<<"Importe: "<<vecImporte[i]<<endl;
        cout<<"Nombre: "<<vecNombre[i]<<endl;
    }

//LIBERAR MEMORIA DINAMICA

for(int i=0; i<cont; i++){
delete [] VecCodigoCliente[i];
delete [] vecNombre[i];
}

delete vecImporte;

}

void Punto3(){

    ArchivoNuevoPunto1 objAN;

    Venta obtV;
    ArchivoVentas ARv("Ventas.dat");
    
    int tam1;
    tam1 = ARv.contarRegistros();


    Cliente obtC;
    ArchivoClientes ARc("clientes.dat");



    int tam2;
    tam2 = ARc.contarRegistros();

    for(int x=0; x<tam1; x++){
        bool bandera = false;

        ArchivoNuevoPunto1 ObjArP3(obtV.getImporte());

        if((obtV.getEstado()==true)&&(ObjArP3<15000)){

            for(int y=0; y<tam2; y++){
                
                if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0)) && (obtC.getEstado() == true)){
                    bandera = true;
                }

            }

        }

        if (bandera == true)
        {
            objAN.setCodigoCliente(obtC.getCodigoCliente());
            objAN.setImporte(ObjArP3);
            objAN.setNombre(obtC.getNombre());
            if(objAN.grabarRegistro()){}//cout<<"Perfeto PA"<<endl;}
        }

    }
    objAN.MostrarArchivo();
    

    objAN.LimpiarArchivo();

}

void Punto4(){

}



























