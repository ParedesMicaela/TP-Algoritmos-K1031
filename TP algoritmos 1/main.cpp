#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <cstring>
#include <fstream>

using namespace std;

struct poliza
{
    char nropoliza[10];
    char dni[10];
    char nombre[20];
    char apellido [20];
    bool cuota;
    char cuo[3];
    char patente[15];
    char acti[3];
    bool activa;
    int cantincidentes;
    int cant2020;
};

struct incidente
{
    char codigoincidente[10];
    char fecha[20];
    char dniasegurado[20];
    char dniotroconductor [20];
    char nropoliza[10];
    char calle[10];
    char altura[10];
};

struct NodoListaPoliza
{
    poliza info;
    NodoListaPoliza*sgte;
};

bool cargarpoliza ()
{
    FILE*f;
    poliza p;
    if(f=fopen("Asegurados.BAK","ab"))
    {
        cout << "Ingrese nro de poliza:" << endl;
        cin >>  p.nropoliza;
        cout << "Ingrese DNI:" << endl;
        cin >> p.dni;
        cout << "Ingrese nombre:" << endl;
        cin >> p.nombre;
        cout << "Ingrese apellido:" << endl;
        cin >> p.apellido;
        cout << "Ingrese si la cuota esta al dia:" << endl;
        cin >> p.cuo;
        if (strcmp("si", p.cuo)==0 || strcmp("SI", p.cuo)==0 ){
            p.cuota=true;
        } else{
        p.cuota=false;
        }
       cout << "Ingrese patente del auto:" << endl;
        cin >> p.patente;
        cout << "Ingrese si esta activa:" << endl;
        cin >> p.acti;
        if (strcmp("si", p.acti)==0 || strcmp("SI", p.acti)==0 )
            {
            p.activa=true;
            }else{
            p.activa=false;
            }
        cout << "Ingrese cantidad de incidentes:" << endl;
        cin >> p.cantincidentes;
        fwrite(&p, sizeof(poliza),1,f);
        fclose(f);
        return true;
    }else
    {
        cout << "El archivo no se puede abrir." << endl;
    }
    return false;
}

int sumar2020 (char ruta[],poliza &p,char nro[10])
{
    int encontrado=0;
    FILE*f;
    if(f=fopen(ruta,"rb+"))
    {
        while(!encontrado && fread(&p,sizeof(poliza),1,f))
        {
            if(strcmp(p.nropoliza,nro)==0)
            {
                encontrado=1;
                p.cant2020=p.cant2020+1;
                fseek(f,(-1)*sizeof(poliza),SEEK_CUR);
                fwrite(&p,sizeof(poliza),1,f);
            }
        }
        fclose(f);
    }
    return 0;
}

int actualizar (char ruta[],poliza &p,char nro[10])
{
    int encontrado=0;
    FILE*f;
    if(f=fopen(ruta,"rb+"))
    {
        while(!encontrado && fread(&p,sizeof(poliza),1,f))
        {
            if(strcmp(p.nropoliza,nro)==0)
            {
                encontrado=1;
                p.cantincidentes=p.cantincidentes+1;
                fseek(f,(-1)*sizeof(poliza),SEEK_CUR);
                fwrite(&p,sizeof(poliza),1,f);
            }
        }
        fclose(f);
    }
    return 0;
}

int cargarincidente()
{
    FILE*f;
    incidente i;
    poliza p;
    if(f=fopen("procesados.BAK","ab"))
    {
        cout << "Ingrese el codigo de incidente:" << endl;
        cin >>  i.codigoincidente;
        cout << "Ingrese nro de poliza:" << endl;
        cin >> i.nropoliza;
        cout << "Ingrese la fecha y hora:" << endl;
        cin >> i.fecha;
        if(strncmp(i.fecha,"2020",4)==0)
        {
            sumar2020("Asegurados.BAK",p,i.nropoliza);
        }
        cout << "Ingrese dni del asegurado:" << endl;
        cin >> i.dniasegurado;
        cout << "Ingrese dni del otro conductor:" << endl;
        cin >> i.dniotroconductor;
        cout << "Ingrese la calle:" << endl;
        cin >> i.calle;
        cout << "Ingrese la altura:" << endl;
        cin >> i.altura;
        fwrite(&i,sizeof(incidente),1,f);
        fclose(f);
        actualizar("Asegurados.BAK",p,i.nropoliza);
        return true;
    }else
    {
        cout << "El archivo no se puede abrir." << endl;
    }
    return false;
}

int levantarpolizas ()
{
    FILE *f;
    poliza p;
    if(f=fopen("Asegurados.BAK","rb"))
    {
        while(fread(&p,sizeof(poliza),1,f))
        {
            cout << "******* Poliza Asegurado *******" << endl;
            cout << "Nro.Poliza " << p.nropoliza << endl;
            cout << "DNI: " << p.dni << endl;
            cout << "Nombre: " << p.nombre << endl;
            cout << "Apellido: " << p.apellido << endl;
            cout << "CuotaAlDia: " << p.cuo << endl;
            cout << "PatenteAuto: " << p.patente << endl;
            cout << "Activa: " << p.acti << endl;
            cout << "Cdad.Incidentes: " << p.cantincidentes << endl;
            cout << " " << endl;
        }
        fclose(f);
        return 1;
    }
    return 0;
}

int levantarincidentes ()
{
    FILE *f;
    incidente i;
    if(f=fopen("procesados.BAK","rb"))
    {
        while(fread(&i,sizeof(incidente),1,f))
        {
            cout << "******* "<<i.codigoincidente<< "*******" << endl;
            cout << "Nro.Poliza " << i.nropoliza << endl;
            cout << "DNI asegurado: " << i.dniasegurado << endl;
            cout << "DNI del otro conductor: " << i.dniotroconductor << endl;
            cout << "Fecha y hora: " << i.fecha << endl;
            cout << "Calle: " << i.calle << endl;
            cout << "Altura: " << i.altura << endl;
            cout << " " << endl;
        }
        fclose(f);
        return 1;
    }
    return 0;
}

int desactivar (char ruta[],poliza &p,char nro[10])
{
    int encontrado=0;
    FILE*f;
    if(f=fopen(ruta,"rb+"))
    {
        while(!encontrado && fread(&p,sizeof(poliza),1,f))
        {
            if(strcmp(p.nropoliza,nro)==0)
            {
                encontrado=1;
                strcpy(p.acti,"no");
                p.activa=1;
                fseek(f,(-1)*sizeof(poliza),SEEK_CUR);
                fwrite(&p,sizeof(poliza),1,f);
            }
        }
        fclose(f);
    }
    return 0;
}

bool buscarporpoliza (char ruta[],poliza &p,char nro[10])
{
    FILE*f;
    bool encontrado=false;
    if(f=fopen(ruta,"rb"))
    {
        while(fread(&p,sizeof(poliza),1,f))
        {
            if(strcmp(p.nropoliza,nro)==0)
            {
                encontrado=true;
                cout << "******* Poliza Asegurado *******" << endl;
                cout << "Nro.Poliza " << p.nropoliza << endl;
                cout << "DNI: " << p.dni << endl;
                cout << "Nombre: " << p.nombre << endl;
                cout << "Apellido: " << p.apellido << endl;
                cout << "CuotaAlDia: " << p.cuo << endl;
                cout << "PatenteAuto: " << p.patente << endl;
                cout << "Activa: " << p.acti << endl;
                cout << "Cdad.Incidentes: " << p.cantincidentes << endl;
                cout << " " << endl;
            }
        }
        fclose(f);
    }
    return encontrado;
}

bool buscarincidentes (char ruta[],incidente &i,char nro[10])
{
    FILE*f;
    bool encontrado=false;
    if(f=fopen(ruta,"rb"))
    {
        while(fread(&i,sizeof(incidente),1,f))
        {
            if(strcmp(i.nropoliza,nro)==0)
            {
                encontrado=true;
                cout << "******* "<<i.codigoincidente<< "*******" << endl;
                cout << "Nro.Poliza " << i.nropoliza << endl;
                cout << "DNI asegurado: " << i.dniasegurado << endl;
                cout << "DNI del otro conductor: " << i.dniotroconductor << endl;
                cout << "Fecha y hora: " << i.fecha << endl;
                cout << "Calle: " << i.calle << endl;
                cout << "Altura: " << i.altura << endl;
                cout << " " << endl;
            }
        }
        fclose(f);
    }
    return encontrado;
}

bool buscarpordni (char ruta[],poliza &p,char dni[10])
{
    FILE*f;
    bool encontrado=false;
    if(f=fopen(ruta,"rb"))
    {
        while(fread(&p,sizeof(poliza),1,f))
        {
            if(strcmp(p.dni,dni)==0)
            {
                cout << "******* Poliza Asegurado *******" << endl;
                cout << "Nro.Poliza " << p.nropoliza << endl;
                cout << "DNI: " << p.dni << endl;
                cout << "Nombre: " << p.nombre << endl;
                cout << "Apellido: " << p.apellido << endl;
                cout << "CuotaAlDia: " << p.cuo << endl;
                cout << "PatenteAuto: " << p.patente << endl;
                cout << "Activa: " << p.acti << endl;
                cout << "Cdad.Incidentes: " << p.cantincidentes << endl;
                cout << " " << endl;
                encontrado=true;
            }
        }
        fclose(f);
    }
    return encontrado;
}

bool crearhtml (char ruta[],poliza &p)
{
    FILE*f,*q;
    bool encontrado=false;
    ofstream archivo;
    archivo.open("salidahtml.html",ios::out);
    archivo<<"<html><body>\n";
    archivo<<"<h1>Polizas con mas de 5 incidentes en el 2020</h1>\n";
    q = fopen("salidaexcel.csv", "wt");
    fprintf(q,"Nro.Poliza;DNI;Nombre;Apellido;CuotaAlDia;PatenteAuto;Activa;Cdad.Incidentes\n");
    if(f=fopen(ruta,"rb"))
    {
        while(fread(&p,sizeof(poliza),1,f))
        {
                if(p.cant2020>5){
                archivo<<"<table border=1>\n";
                archivo<<"<h2>";
                archivo<<"<th>Nro poliza</th><th>Apellidos</th><th>Nombres</th><th>DNI</th><th> Patentes </th><th> Cantidad de incidentes </th>\n";
                archivo<<"<tr>\n";
                archivo<<"<td>";
                archivo<<p.nropoliza;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<p.apellido;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<p.nombre;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<p.dni;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<p.patente;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<p.cantincidentes;
                archivo<<"</td>";
                archivo<<"</h2>";
                archivo<<"</tr>\n";

                fprintf(q,"%s;%s;%s;%s;%s;%s;%s;%d\n",p.nropoliza,p.dni,p.nombre,p.apellido,p.cuo,p.patente,p.acti,p.cantincidentes);

                encontrado=true;
                }
        }
        archivo<<"</table>";
        archivo<<"</body>";
        archivo<<"</html>";
        archivo.close();
        fclose(q);
        fclose(f);
    }
    return encontrado;
}

void burbuja (poliza p[], int n)
{
    int i, j;
    poliza aux;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(p[j+1].cantincidentes > p[j].cantincidentes)
            {
              aux=p[j+1];
              p[j+1]=p[j];
              p[j]=aux;
                }
}


void  ordenar ()
{
    poliza c, *array;
    int tam = sizeof(poliza), totalclientes, i=0;
    ifstream in;
    ofstream out;
    in.open("Asegurados.BAK", ios::binary);
    if(in.fail())
    {
       cout << "Error al abrir el fichero" << endl;
       system("pause");
       exit(1);
    }
    out.open("ORDENADOS.bak", ios::binary);
    if(out.fail())
    {
       cout << "Error al crear el fichero" << endl;
       system("pause");
       exit(1);
    }
    in.seekg(0,ios::end);
    totalclientes=in.tellg()/tam;
    array = new poliza[totalclientes];
    if(array==NULL)
    {
       cout << "Error en la asignaci�n de memoria\n";
       system("pause");
       exit(1);
    }
    in.seekg(0);
    in.read((char *) &array[i], tam);
    while(!in.eof())
    {
         i++;
         in.read((char *) &array[i], tam);
    }
     burbuja(array,totalclientes);

      for(i=0;i<totalclientes;i++)
    {
        if(array[i].activa){
            cout << "******* Poliza Asegurado *******" << endl;
            cout << "Nro.Poliza " << array[i].nropoliza << endl;
            cout << "DNI: " << array[i].dni << endl;
            cout << "Nombre: " << array[i].nombre << endl;
            cout << "Apellido: " << array[i].apellido << endl;
            cout << "CuotaAlDia: " << array[i].cuo << endl;
            cout << "PatenteAuto: " << array[i].patente << endl;
            cout << "Activa: " << array[i].acti << endl;
            cout << "Cdad.Incidentes: " << array[i].cantincidentes << endl;
            cout << " " << endl;
            out.write((char *) &array[i], tam);
    }
    }
    in.close();
    out.close();
    delete [] array;

}

NodoListaPoliza *ListaPolizaObtenerSiguiente(NodoListaPoliza  *n)
{
    if (n)
        return n->sgte;
    else
        return NULL;
}

void ListaPolizaInsertarSiguiente (NodoListaPoliza  *&n, poliza x)
{
    NodoListaPoliza *nuevo= new NodoListaPoliza();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte= n->sgte;
        n->sgte = nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n= nuevo;
    }
    return;
}

void sobreescribirArchivo(NodoListaPoliza *&a)
{
    FILE *f;
    poliza r;
    if (f=fopen("Asegurados.BAK","r"))
    {
        while (fread(&r,sizeof(poliza),1,f)){
                if (strcmp(r.acti, "SI")==0 || strcmp(r.acti, "si")==0){
                    ListaPolizaInsertarSiguiente(a,r);
                }
        }
    }
    fclose(f);
    return;
}

void guardarPolizasArchivo(NodoListaPoliza *lp)
{
    FILE *arch_polizas;
    NodoListaPoliza *auxPol=NULL;
    if (arch_polizas= fopen("Asegurados.BAK","wb"))
    {
        auxPol= lp;
        while (auxPol)
        {
            fwrite(&(auxPol->info), sizeof(poliza),1,arch_polizas);
            auxPol= ListaPolizaObtenerSiguiente(auxPol);
        }
        fclose(arch_polizas);
    }
    else
        cout << "ERROR AL INTENTAR GRABAR ARCHIVO DE POLIZAS" << endl;
    return;
}

char menu ()
{
    char opcion;
    poliza p;
    incidente i;
    NodoListaPoliza *lPolizas=NULL;
    char nropoliza[10];
    char dni[10];
    char ruta[]="Asegurados.BAK";
    char ruta2[]="procesados.BAK";
    cout << " " << endl;
    cout << "0-Mostrar todas las cuentas guardadas en el archivo" << endl;
    cout << "1-Cargar nueva poliza" << endl;
    cout << "2-Desactivar una poliza existente" << endl;
    cout << "3-Buscar una poliza por el nro de poliza" << endl;
    cout << "4-Buscar una poliza por el dni del cliente" << endl;
    cout << "5-Listar polizas activas ordenadas descendientemente" << endl;
    cout << "6-Procesar un lote de incidentes" << endl;
    cout << "7-Mostrar lote de incidentes de una poliza" << endl;
    cout << "8-Mostrar todas las polizas que tengan mas de 5 incidentes durante todo el 2020" << endl;
    cout << "9-Finalizar jornada" << endl;
    do
        opcion=getch();
    while(!(opcion >= '0' && opcion <= '11') && (opcion != 27));
    switch(opcion)
    {
        case '0':
            levantarpolizas();
            break;
        case '1':
            if (cargarpoliza())
                cout << "El registro se ha guardado con exito" << endl;
            else
            cout << "Error al intentar abrir el archivo" << endl;
        break;
        case '2':
            cout<<"Ingrese nro de poliza a desactivar"<<endl;
            cin>>nropoliza;
            desactivar(ruta,p,nropoliza);
        break;
        case '3':
            cout<<"Ingrese el nro de poliza a buscar"<<endl;
            cin>>nropoliza;
            buscarporpoliza(ruta,p,nropoliza);
        break;
        case '4':
            cout<<"Ingrese el dni a buscar"<<endl;
            cin>>dni;
           buscarpordni(ruta,p,dni);
        break;
        case '5':
            ordenar();
        break;
        case '6':
            if (cargarincidente())
            {
                cout << "El registro se ha guardado con exito" << endl;
                levantarincidentes();
            }
            else
            cout << "Error al intentar abrir el archivo" << endl;
        break;
        case '7':
            cout<<"Ingrese  el nro de poliza para ver el lote de incidentes asociado"<<endl;
            cin>>nropoliza;
            buscarincidentes(ruta2,i,nropoliza);
        break;
        case '8':
            if(crearhtml("Asegurados.BAK",p))
               {
                   cout << "Se han creado los archivos con exito" << endl;
               }
        break;
        case '9':
            cout<<"Archivo actualizado"<<endl;
            sobreescribirArchivo(lPolizas);
            guardarPolizasArchivo(lPolizas);
            levantarpolizas();
        break;
    }
    return opcion;
}

int main()
{
    char op;
    do
        op = menu();
    while (op != 27);
  return 0;
}
