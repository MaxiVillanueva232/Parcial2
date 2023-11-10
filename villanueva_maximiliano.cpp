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
    cout<<"Importe: "<<getImporte()<<endl;
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
    bool operator<(int tamanio) {
        if(this->importe < tamanio) {
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

/////////////////////////
void aPunto1();
void aPunto2();
void aPunto3();
/////////////////////////
void bPunto1();
void bPunto2();
void bPunto3();
/////////////////////////
void PonerCeroVector(int vec[],int tam);
void MostrarVector(int vec[],int tam);
/////////////////////////

int main(){

    Cliente objC;
    Tour obtT;
    Venta objV;
    Guia obtG;

    // objC.MostrarArchivo();
    // obtT.MostrarArchivo();
    // objV.MostrarArchivo();
    // obtG.MostrarArchivo();

    cout<<"aPunto1"<<endl;
    aPunto1();
    cout<<"aPunto3"<<endl;
    aPunto3();


	cout<<endl;
	system("pause");
    return 0;
}

/////////////////////////////////////////////////////////////////////////
void aPunto1(){

    ArchivoNuevoPunto1 objAN;

    ArchivoClientes ARc("clientes.dat");
    Cliente obtC;

    int tam1;
    tam1 = ARc.contarRegistros();

    int *acumVec = new int[tam1];

    PonerCeroVector(acumVec,tam1);
    
    ArchivoVentas ARv("ventas.dat");
    Venta obtV;

    int tam2;
    tam2 = ARv.contarRegistros();

    for(int x=0; x<tam1; x++){
        obtC = ARc.leerRegistro(x);

            if((obtC.getEstado()==true)){

                for(int y=0; y<tam2; y++){

                    obtV = ARv.leerRegistro(y);

                    if((obtV.getEstado()==true)&&(obtV.getImporte()<15000)){

                        if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0))){
                            acumVec[x]=acumVec[x]+obtV.getImporte();
                        }

                    }

                }
            }


    }

//CARGAR y MOSTRAR ARCHIVOS
for(int x=0; x<tam1; x++){
    obtC = ARc.leerRegistro(x);

    if(acumVec[x]>0){
        objAN.setCodigoCliente(obtC.getCodigoCliente());
        objAN.setNombre(obtC.getNombre());
        objAN.setImporte(acumVec[x]);
        if(objAN.grabarRegistro()){}//cout<<"Perfeto PA"<<endl;}
    }


}
    objAN.MostrarArchivo();
    objAN.LimpiarArchivo();



    delete acumVec;

}

void aPunto2(){

    ArchivoNuevoPunto1 objAN;

    ArchivoClientes ARc("clientes.dat");
    Cliente obtC;

    int tam1;
    tam1 = ARc.contarRegistros();

    char **VecCodigoCliente = new char*[tam1];
    char **vecNombre = new char*[tam1];
    int *vecImporte = new int[tam1];

    PonerCeroVector(vecImporte,tam1);
    
    ArchivoVentas ARv("ventas.dat");
    Venta obtV;

    int tam2;
    tam2 = ARv.contarRegistros();

    for(int x=0; x<tam1; x++){
        obtC = ARc.leerRegistro(x);

            if((obtC.getEstado()==true)){

                for(int y=0; y<tam2; y++){

                    obtV = ARv.leerRegistro(y);

                    if((obtV.getEstado()==true)&&(obtV.getImporte()<15000)){

                        if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0))){
                            VecCodigoCliente[x] = new char[30];   // Asignar memoria para cada VecCodigoCliente[cont]
                            strcpy(VecCodigoCliente[x],obtC.getCodigoCliente());

                            vecImporte[x]=vecImporte[x]+obtV.getImporte();

                            vecNombre[x] = new char[30];   // Asignar memoria para cada VecCodigoCliente[cont]
                            strcpy(vecNombre[x],obtC.getNombre());
                        }

                    }

                }
            }


    }



//CARGAR y MOSTRAR ARCHIVOS
for(int x=0; x<tam1; x++){


    if(vecImporte[x]>0){

        cout<<"Codigo de Cliente: "<<VecCodigoCliente[x]<<endl;
        cout<<"Nombre: "<<vecNombre[x]<<endl;
        cout<<"Importe: "<<vecImporte[x]<<endl;
    }



    delete vecImporte;

}
}

void aPunto3(){

    ArchivoNuevoPunto1 objAN;

    ArchivoClientes ARc("clientes.dat");
    Cliente obtC;

    int tam1;
    tam1 = ARc.contarRegistros();

    int *acumVec = new int[tam1];

    PonerCeroVector(acumVec,tam1);
    
    ArchivoVentas ARv("ventas.dat");
    Venta obtV;

    int tam2;
    tam2 = ARv.contarRegistros();

    for(int x=0; x<tam1; x++){
        obtC = ARc.leerRegistro(x);

            if((obtC.getEstado()==true)){

                for(int y=0; y<tam2; y++){

                    obtV = ARv.leerRegistro(y);
                    ArchivoNuevoPunto1 ObjArP3(obtV.getImporte());


                    if((obtV.getEstado()==true)&&(ObjArP3<15000)){

                        if(((strcmp(obtV.getNumeroDeCliente(), obtC.getCodigoCliente()) == 0))){
                            acumVec[x]=acumVec[x]+obtV.getImporte();
                        }

                    }

                }
            }


    }

//CARGAR y MOSTRAR ARCHIVOS
for(int x=0; x<tam1; x++){
    obtC = ARc.leerRegistro(x);

    if(acumVec[x]>0){
        objAN.setCodigoCliente(obtC.getCodigoCliente());
        objAN.setNombre(obtC.getNombre());
        objAN.setImporte(acumVec[x]);
        if(objAN.grabarRegistro()){}//cout<<"Perfeto PA"<<endl;}
    }


}
    objAN.MostrarArchivo();
    objAN.LimpiarArchivo();



    delete acumVec;

}

/////////////////////////////////////////////////////////////////////////
void bPunto1(){

}

void bPunto2(){

}

void bPunto3(){

}

/////////////////////////////////////////////////////////////////////////






void PonerCeroVector(int vec[],int tam){
    for(int i=0; i<tam; i++){
        vec[i]=0;
    }
}

void MostrarVector(int vec[],int tam){
    for(int i=0; i<tam; i++){
        cout<<vec[i]<<endl;
    }
}


















