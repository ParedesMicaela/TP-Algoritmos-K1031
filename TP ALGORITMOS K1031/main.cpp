#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <cstring>
#include <fstream>

#define RUTA "Asegurados.BAK"
#define RUTA2 "procesados.BAK"
using namespace std;

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

struct nodoincidente
{
    incidente info;
    nodoincidente*sgte;
};

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

struct nodopoliza
{
    poliza info;
    nodopoliza*sgte;
    nodoincidente*sublista=NULL;;
};


void insertarsiguienteincidente (nodoincidente *&n, incidente x)
{
    nodoincidente*nuevo= new nodoincidente();
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte=n->sgte;
        n->sgte =nuevo;
    }
    else
    {
        nuevo->sgte= n;
        n=nuevo;
    }

    return;
}

void insertarsiguientepoliza (nodopoliza *&n, poliza x)
{
    nodopoliza*nuevo= new nodopoliza();
    nuevo->sublista=NULL;
    nuevo->info=x;
    if (n!=NULL)
    {
        nuevo->sgte=n->sgte;
        n->sgte=nuevo;
    }
    else
    {
        nuevo->sgte=n;
        n= nuevo;
    }

    return;
}

void borrarsiguienteincidente(nodoincidente *n)
{
    nodoincidente*aborrar=n->sgte;
    nodoincidente*sgteaborrar;
    if (aborrar)
        sgteaborrar=aborrar->sgte;
    else
        sgteaborrar=NULL;
    n->sgte=sgteaborrar;
    delete aborrar;
    return;
}

nodopoliza *anteriorpoliza (nodopoliza*raiz,nodopoliza*anterior)
{
    nodopoliza*p=NULL;
    if(raiz!=anterior)
    {
        p=raiz;
        while(p&&(p->sgte!=anterior))
        {
            p=p->sgte;
        }
        return p;
    }else
    {
        return NULL;
    }

}

nodopoliza *obtenersiguientepoliza (nodopoliza*p)
{
    if(p)
    {
        return p->sgte;
    }else
    {
        return NULL;
    }
}

nodoincidente *obtenersiguienteincidente (nodoincidente*p)
{
    if(p)
    {
        return p->sgte;
    }else
    {
        return NULL;
    }
}

nodopoliza *obtenerultimapoliza(nodopoliza*p)
{
    if (p)
    {
        while (p->sgte)
        {
            p=p->sgte;
        }
    }
    return p;

}

nodoincidente *obtenerultimoincidente(nodoincidente*p)
{
    if (p)
    {
        while (p->sgte)
        {
            p=p->sgte;
        }
    }
    return p;
}

void insertaralfinalpoliza(nodopoliza*&lista, poliza x)
{
    nodopoliza*aux;
    aux=obtenerultimapoliza(lista);
    if (aux)
    {
        insertarsiguientepoliza(aux,x);
    }
    else
    {
        insertarsiguientepoliza(lista,x);
    }
    return;
}

void insertaralfinalincidente(nodoincidente*&lista, incidente x)
{
    nodoincidente*aux;
    aux=obtenerultimoincidente(lista);
    if (aux)
    {
        insertarsiguienteincidente(aux,x);
    }
    else
    {
        insertarsiguienteincidente(lista,x);
    }
    return;
}

void borrarlistaincidente(nodoincidente*&lista)
{
    nodoincidente*anterior;
    nodoincidente*paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux=lista;
        while (paux && paux->sgte)
        {
            anterior=paux;
            paux=paux->sgte;
        }
        if (paux)
        {
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista=NULL;
        }
    }
    return;
}

void borrarlistapoliza(nodopoliza*&lista)
{
    nodopoliza*anterior;
    nodopoliza*paux;
    while (lista!=NULL)
    {
        anterior=NULL;
        paux=lista;
        while (paux && paux->sgte)
        {
            anterior=paux;
            paux=paux->sgte;
        }
        if (paux)
        {
            borrarlistaincidente(paux->sublista);
            delete paux;
            if (anterior!=NULL)
                anterior->sgte=NULL;
            else
                lista=NULL;
        }
    }
    return;
}

void mostrarbuscado (nodopoliza*lista,char dni[])
{
    while(lista)
    {
        if(strcmp(lista->info.dni,dni)==0){
            cout << "******* Poliza Asegurado *******" << endl;
            cout << "Nro.Poliza " << lista->info.nropoliza << endl;
            cout << "DNI: " << lista->info.dni << endl;
            cout << "Nombre: " << lista->info.nombre << endl;
            cout << "Apellido: " << lista->info.apellido << endl;
            cout << "CuotaAlDia: " << lista->info.cuo << endl;
            cout << "PatenteAuto: " << lista->info.patente << endl;
            cout << "Activa: " << lista->info.acti << endl;
            cout << "Cdad.Incidentes: " << lista->info.cantincidentes << endl;
            cout << " " << endl;
        }
        lista = lista->sgte;
    }
}

void listarincidentes(nodoincidente*lista)
{
    while (lista)
    {
            cout << "------ "<<lista->info.codigoincidente<< " ------" << endl;
            cout << "Nro.Poliza " << lista->info.nropoliza << endl;
            cout << "DNI asegurado: " << lista->info.dniasegurado << endl;
            cout << "DNI del otro conductor: " << lista->info.dniotroconductor << endl;
            cout << "Fecha y hora: " << lista->info.fecha << endl;
            cout << "Calle: " << lista->info.calle << endl;
            cout << "Altura: " << lista->info.altura << endl;
            cout << " " << endl;
        lista = lista->sgte;
    }
}

void mostrarlistapolizas(nodopoliza*lista)
{
    while (lista)
    {
            cout << "******* Poliza Asegurado *******" << endl;
            cout << "Nro.Poliza " << lista->info.nropoliza << endl;
            cout << "DNI: " << lista->info.dni << endl;
            cout << "Nombre: " << lista->info.nombre << endl;
            cout << "Apellido: " << lista->info.apellido << endl;
            cout << "CuotaAlDia: " << lista->info.cuo << endl;
            cout << "PatenteAuto: " << lista->info.patente << endl;
            cout << "Activa: " << lista->info.acti << endl;
            cout << "Cdad.Incidentes: " << lista->info.cantincidentes << endl;
            cout << " " << endl;
        if (lista->sublista)
        {
                listarincidentes(lista->sublista);
        }
        else
            cout << "El cliente no tuvo incidentes" << endl  << endl;
        lista = lista->sgte;
    }
}

nodopoliza*buscarnro(nodopoliza*raiz, char nro[])
{
    while (raiz && (strcmp(raiz->info.nropoliza,nro)))
    {
        raiz=raiz->sgte;
    }
    return raiz;
}

nodopoliza*buscarpordni(nodopoliza*raiz, char dni[])
{
    while (raiz && (strcmp(raiz->info.dni,dni)))
    {
        raiz=raiz->sgte;
    }
    return raiz;
}

nodopoliza*sumar2020(nodopoliza*&raiz,char dni[])
{
    nodopoliza*p=raiz;
    bool encontrado=false;
    while (p)
    {
        if(strcmp(p->info.dni,dni)==0)
        {
            encontrado=true;
            p->info.cant2020=p->info.cant2020+1;
        }
        p=p->sgte;
    }
    return p;
}

nodopoliza*desactivar(nodopoliza*&raiz,char nro[])
{
    nodopoliza*p=raiz;
    bool encontrado=false;
    while (!encontrado && p)
    {
        if(strcmp(p->info.nropoliza,nro)==0)
        {
            p->info.activa=1;
            strcpy(p->info.acti,"no");
            encontrado=true;
        }
        p=p->sgte;
    }
    return p;
}

nodopoliza*actualizar (nodopoliza*&raiz,char dni[])
{
    nodopoliza*p=raiz;
    bool encontrado=false;
        while(p)
        {
            if(strcmp(p->info.dni,dni)==0)
            {
                encontrado=true;
                p->info.cantincidentes=p->info.cantincidentes+1;
            }
            p=p->sgte;
    }
    return p;
}

void listarpolizasordenadas(nodopoliza *lista)
{
    while (lista)
    {
        if(lista->info.activa==0)
        {
            cout << "******* Poliza Asegurado *******" << endl;
            cout << "Nro.Poliza " << lista->info.nropoliza << endl;
            cout << "DNI: " << lista->info.dni << endl;
            cout << "Nombre: " << lista->info.nombre << endl;
            cout << "Apellido: " << lista->info.apellido << endl;
            cout << "CuotaAlDia: " << lista->info.cuo << endl;
            cout << "PatenteAuto: " << lista->info.patente << endl;
            cout << "Activa: " << lista->info.acti << endl;
            cout << "Cdad.Incidentes: " << lista->info.cantincidentes << endl;
            cout << " " << endl;
        }
        lista=obtenersiguientepoliza(lista);
    }
}

void cargararchivo()
{
    FILE *f;
    f=fopen(RUTA,"wb");
    poliza p;
    if (f)
    {
    strcpy(p.nropoliza,"012");
    strcpy(p.dni,"456789");
    strcpy(p.nombre,"Agustin");
    strcpy(p.apellido,"Trepin");
    p.cuota=1;
    strcpy(p.patente,"K4353");
    p.activa=0;
    strcpy(p.acti,"si");
    p.cantincidentes=6;
    p.cant2020=6;
    fwrite(&p,sizeof(poliza),1,f);

    strcpy(p.nropoliza,"016");
    strcpy(p.dni,"123456");
    strcpy(p.nombre,"Hugo");
    strcpy(p.apellido,"Rodriguez");
    p.cuota=1;
    strcpy(p.patente,"J2434");
    p.activa=0;
    strcpy(p.acti,"no");
    p.cantincidentes=3;
    p.cant2020=3;
    fwrite(&p,sizeof(poliza),1,f);

    strcpy(p.nropoliza,"015");
    strcpy(p.dni,"987654");
    strcpy(p.nombre,"Monica");
    strcpy(p.apellido,"Trejo");
    p.cuota=1;
    strcpy(p.patente,"L4389");
    p.activa=0;
    strcpy(p.acti,"si");
    p.cantincidentes=1;
    p.cant2020=0;
    fwrite(&p,sizeof(poliza),1,f);

    strcpy(p.nropoliza,"018");
    strcpy(p.dni,"232849");
    strcpy(p.nombre,"Angeles");
    strcpy(p.apellido,"Avalos");
    p.cuota=1;
    strcpy(p.patente,"F1129");
    p.activa=1;
    strcpy(p.acti,"si");
    p.cantincidentes=4;
    p.cant2020=0;
    fwrite(&p,sizeof(poliza),1,f);

    strcpy(p.nropoliza,"014");
    strcpy(p.dni,"987654");
    strcpy(p.nombre,"Monica");
    strcpy(p.apellido,"Trejo");
    p.cuota=1;
    strcpy(p.patente,"L4389");
    p.activa=0;
    strcpy(p.acti,"si");
    p.cantincidentes=2;
    p.cant2020=1;
    fwrite(&p,sizeof(poliza),1,f);
    fclose(f);
    }
    else
        cout << "Error: no se pudo crear el archivo" << endl;
    return;
}

void cargararchivoincidente()
{
    FILE*f;
    incidente i;
    if(f=fopen("procesados.BAK","wb"))
    {
    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"892823");
    strcpy(i.codigoincidente,"001");
    strcpy(i.fecha,"2020100621:08");
    strcpy(i.altura,"6678");
    strcpy(i.calle,"Capdevila");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"014");
    strcpy(i.dniasegurado,"987654");
    strcpy(i.dniotroconductor,"892384");
    strcpy(i.codigoincidente,"002");
    strcpy(i.fecha,"2020122318:23");
    strcpy(i.altura,"7728");
    strcpy(i.calle,"Alberdi");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"016");
    strcpy(i.dniasegurado,"123456");
    strcpy(i.dniotroconductor,"545452");
    strcpy(i.codigoincidente,"021");
    strcpy(i.fecha,"2020112521:23");
    strcpy(i.altura,"4456");
    strcpy(i.calle,"Humbold");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"018");
    strcpy(i.dniasegurado,"232849");
    strcpy(i.dniotroconductor,"535676");
    strcpy(i.codigoincidente,"004");
    strcpy(i.fecha,"2009100619:56");
    strcpy(i.altura,"2389");
    strcpy(i.calle,"Callao");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"877994");
    strcpy(i.codigoincidente,"005");
    strcpy(i.fecha,"2020100619:34");
    strcpy(i.altura,"3298");
    strcpy(i.calle,"Draco");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"014");
    strcpy(i.dniasegurado,"987654");
    strcpy(i.dniotroconductor,"545326");
    strcpy(i.codigoincidente,"006");
    strcpy(i.fecha,"2009110620:13");
    strcpy(i.altura,"2345");
    strcpy(i.calle,"Corrientes");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"188913");
    strcpy(i.codigoincidente,"007");
    strcpy(i.fecha,"2020110619:45");
    strcpy(i.altura,"3893");
    strcpy(i.calle,"Cuba");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"018");
    strcpy(i.dniasegurado,"232849");
    strcpy(i.dniotroconductor,"111343");
    strcpy(i.codigoincidente,"008");
    strcpy(i.fecha,"2019100919:56");
    strcpy(i.altura,"8893");
    strcpy(i.calle,"Humbold");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"318773");
    strcpy(i.codigoincidente,"009");
    strcpy(i.fecha,"2020081119:25");
    strcpy(i.altura,"2568");
    strcpy(i.calle,"Conde");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"987654");
    strcpy(i.codigoincidente,"010");
    strcpy(i.fecha,"2020081119:35");
    strcpy(i.altura,"3499");
    strcpy(i.calle,"Rivadavia");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"016");
    strcpy(i.dniasegurado,"123456");
    strcpy(i.dniotroconductor,"778892");
    strcpy(i.codigoincidente,"019");
    strcpy(i.fecha,"202012291116:39");
    strcpy(i.altura,"5431");
    strcpy(i.calle,"Thames");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"016");
    strcpy(i.dniasegurado,"123456");
    strcpy(i.dniotroconductor,"324535");
    strcpy(i.codigoincidente,"011");
    strcpy(i.fecha,"2020070516:16");
    strcpy(i.altura,"4567");
    strcpy(i.calle,"Lacroze");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"012");
    strcpy(i.dniasegurado,"456789");
    strcpy(i.dniotroconductor,"324579");
    strcpy(i.codigoincidente,"012");
    strcpy(i.fecha,"2020112819:12");
    strcpy(i.altura,"4345");
    strcpy(i.calle,"Larrea");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"018");
    strcpy(i.dniasegurado,"232849");
    strcpy(i.dniotroconductor,"565321");
    strcpy(i.codigoincidente,"113");
    strcpy(i.fecha,"2017121911:32");
    strcpy(i.altura,"8786");
    strcpy(i.calle,"Mosconi");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"018");
    strcpy(i.dniasegurado,"232849");
    strcpy(i.dniotroconductor,"876522");
    strcpy(i.codigoincidente,"014");
    strcpy(i.fecha,"2018080415:29");
    strcpy(i.altura,"7865");
    strcpy(i.calle,"Ibera");
    fwrite(&i,sizeof(incidente),1,f);

    strcpy(i.nropoliza,"015");
    strcpy(i.dniasegurado,"987654");
    strcpy(i.dniotroconductor,"423521");
    strcpy(i.codigoincidente,"020");
    strcpy(i.fecha,"2017061218:09");
    strcpy(i.altura,"4355");
    strcpy(i.calle,"Sucre");
    fwrite(&i,sizeof(incidente),1,f);
    fclose(f);
    }
    else
        cout << "Error: no se pudo crear el archivo" << endl;
    return;
}

void levantararchivos(nodopoliza *&a)
{
    FILE*f;
    poliza r;
    incidente m;
    if (f=fopen(RUTA,"r"))
    {
        while (fread(&r,sizeof(poliza),1,f))
            insertarsiguientepoliza(a,r);
        fclose(f);
    }
    if (f=fopen(RUTA2,"r"))
    {
        while (fread(&m,sizeof(incidente),1,f))
        {
            nodopoliza*aux= buscarnro(a, m.nropoliza);
            if (aux)
                insertarsiguienteincidente(aux->sublista,m);
        }
        fclose(f);
    }

    return;
}

void mostrarpoliza(poliza p)
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
        return;
}

void guardarPolizasArchivo(nodopoliza *lp)
{
    FILE *arch_polizas;
    FILE *arch_incidentes;
    nodopoliza *auxP=NULL;
    nodoincidente *auxI=NULL;
    if (arch_polizas= fopen(RUTA,"wb"))
    {
        if (arch_incidentes= fopen(RUTA2,"wb"))
        {
            auxP= lp;
            while (auxP)
            {
                if(auxP->info.activa==0){
                fwrite(&(auxP->info), sizeof(poliza),1,arch_polizas);
                auxI= auxP->sublista;
                while(auxI)
                {
                    fwrite(&(auxI->info), sizeof(incidente),1,arch_incidentes);
                    auxI= obtenersiguienteincidente(auxI);
                }
                }
                auxP= obtenersiguientepoliza(auxP);
            }
            fclose(arch_incidentes);
        }
        else
            cout << "ERROR AL INTENTAR GRABAR ARCHIVO DE INCIDENTES" << endl;
        fclose(arch_polizas);
    }
    else
        cout << "ERROR AL INTENTAR GRABAR ARCHIVO DE POLIZAS" << endl;
    return;
}

int contarnodo (nodopoliza*lista)
{
    int cont=0;
    while(lista)
    {
        cont++;
        lista=obtenersiguientepoliza(lista);
    }
    return cont;
}

void burbuja(nodopoliza*&lista)
{
    int n,i,j;
    nodopoliza *aux;
    nodopoliza *anterior;
    nodopoliza *proximo;
    bool inter;
    n= contarnodo(lista);
    for (i=0;i<=n-2;i++)
    {
        aux= lista;
        for (j=0;j<=n-2-i;j++)
        {
            if (aux->sgte->info.cantincidentes < aux->info.cantincidentes)
            {
                inter= true;
                if (aux==lista)
                {
                    lista= aux->sgte;
                    proximo= lista->sgte;
                    lista->sgte=aux;
                    aux->sgte=proximo;
                }
                else
                {
                    anterior=anteriorpoliza(lista,aux);
                    proximo=aux->sgte;
                    anterior->sgte= proximo;
                    aux->sgte= proximo->sgte;
                    proximo->sgte= aux;
                }
            }
            else
                inter=false;
            if (!inter)
            {
                aux= aux->sgte;
            }
        }
    }
    return;
}

bool crearhtml (nodopoliza*n)
{
    FILE*f,*q;
    nodopoliza*lista=NULL;
    lista=n;
    bool encontrado=false;
    ofstream archivo;
    archivo.open("salidahtml.html",ios::out);
    archivo<<"<html><body>\n";
    archivo<<"<h1>Polizas con mas de 5 incidentes en el 2020</h1>\n";
    q = fopen("salidaexcel.csv", "wt");
    fprintf(q,"Nro.Poliza;DNI;Nombre;Apellido;CuotaAlDia;Patente\n");
    while(lista)
    {
        if(lista->info.cant2020>5)
        {
                archivo<<"<table border=1>\n";
                archivo<<"<h2>";
                archivo<<"<th> Nro poliza </th><th> Apellido </th><th> Nombre </th><th> DNI </th><th> Patente </th>\n";
                archivo<<"<tr>\n";
                archivo<<"<td>";
                archivo<<lista->info.nropoliza;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<lista->info.apellido;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<lista->info.nombre;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<lista->info.dni;
                archivo<<"</td>";
                archivo<<"<td>";
                archivo<<lista->info.patente;
                archivo<<"</td>";
                archivo<<"</h2>";
                archivo<<"</tr>\n";
                fprintf(q,"%s;%s;%s;%s;%s;%s;%s;%d\n",lista->info.nropoliza,lista->info.dni,lista->info.nombre,lista->info.apellido,lista->info.cuo,lista->info.patente,lista->info.acti,lista->info.cantincidentes);
                encontrado=true;
        }
        lista=lista->sgte;
    }
        archivo<<"</table>";
        archivo<<"</body>";
        archivo<<"</html>";
        archivo.close();
        fclose(q);
    return encontrado;
}

void otroconductor (nodopoliza*&n,char dniotro [],char nroincidente [], char fecha[], char dniasegurado[],char altura[],char calle[])
{
    nodopoliza*p=NULL;
    nodopoliza*lista=NULL;
    lista=n;
    incidente i;
    strcpy(i.dniasegurado,dniotro);
    strcpy(i.codigoincidente,nroincidente);
    strcpy(i.fecha,fecha);
    strcpy(i.altura,altura);
    strcpy(i.calle,calle);
    strcpy(i.dniotroconductor,dniasegurado);
    p=buscarpordni(lista,i.dniasegurado);
    if(p)
    {
        strcpy(i.nropoliza,p->info.nropoliza);
        actualizar(lista,i.dniasegurado);
        if(strncmp(i.fecha,"2020",4)==0)
        {
            sumar2020(lista,i.dniasegurado);
        }
        insertaralfinalincidente(p->sublista,i);
    }
}

char mostrarmenu()
{
    cout << "Ingrese una opcion: " << endl;
    cout << "0-Levantar archivos" << endl;
    cout << "1-Cargar una nueva poliza" << endl;
    cout << "2-Desactivar una poliza" << endl;
    cout << "3-Buscar una poliza y sus incidentes por numero de poliza" << endl;
    cout << "4-Buscar una poliza por el dni del asegurado" << endl;
    cout << "5-Listar todas las polizas activas ordenadas por cantidad de incidentes" << endl;
    cout << "6-Procesar incidente" << endl;
    cout << "7-Mostrar las polizas que tengan mas de 5 incidentes durante todo el 2020" << endl;
    cout << "8-Mostrar todas las polizas y sus incidentes relacionados" << endl;
    cout << "9-Finalizar jornada" << endl;

    char opcion;
    do
    {
       opcion=getch();
    } while (!(opcion >= '0' && opcion <= '11') && (opcion != 27));
    return opcion;
}

int main()
{
    nodopoliza*listapolizas=NULL;
    nodoincidente*listaincidentes=NULL;
    nodopoliza*x=NULL;
    nodopoliza*r=NULL;
    levantararchivos(listapolizas);
    char elegida;
    char nro[10];
    char dni[10];
    do
    {
        elegida= mostrarmenu();
        switch (elegida)
        {
            case '0':
                borrarlistapoliza(listapolizas);
                cargararchivo();
                cargararchivoincidente();
                levantararchivos(listapolizas);
                cout << "" << endl;
                cout << "Archivos levantados correctamente" << endl;
                cout << "" << endl;
            break;
            case '1':
                poliza p;
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
                    p.cuota=0;
                } else{
                p.cuota=1;
                }
                cout << "Ingrese patente del auto:" << endl;
                cin >> p.patente;
                cout << "Ingrese si esta activa:" << endl;
                cin >> p.acti;
                if (strcmp("si", p.acti)==0 || strcmp("SI", p.acti)==0 )
                    {
                p.activa=0;
                    }else{
                    p.activa=1;
                    }
                cout << "Ingrese cantidad de incidentes:" << endl;
                cin >> p.cantincidentes;
                insertaralfinalpoliza(listapolizas,p);
                cout << "Poliza cargada con exito" << endl;
            break;
            case '2':
                cout<<"Ingrese nro de poliza a desactivar"<<endl;
                cin>>nro;
                desactivar(listapolizas,nro);
            break;
            case '3':
                cout<<"Ingrese nro de poliza a buscar"<<endl;
                cin>>nro;
                x=buscarnro(listapolizas,nro);
                if(x){
                mostrarpoliza(x->info);
                listarincidentes(x->sublista);
                }
                else
                cout<<"Error: poliza inexistente"<<endl;
            break;
            case '4':
                cout<<"Ingrese el dni del cliente a buscar"<<endl;
                cin>>dni;
                mostrarbuscado(listapolizas,dni);
            break;
            case '5':
                burbuja(listapolizas);
                listarpolizasordenadas(listapolizas);
            break;
            case '6':
                cout << "Ingrese nro de poliza:" << endl;
                cin >> nro;
                x=buscarnro(listapolizas,nro);
                if(x){
                incidente i;
                strcpy(i.nropoliza,nro);
                cout << "Ingrese el codigo de incidente:" << endl;
                cin >>  i.codigoincidente;
                cout << "Ingrese la fecha y hora:" << endl;
                cin >> i.fecha;
                cout << "Ingrese dni del asegurado:" << endl;
                cin >> i.dniasegurado;
                cout << "Ingrese dni del otro conductor:" << endl;
                cin >> i.dniotroconductor;
                if(strncmp(i.fecha,"2020",4)==0)
                {
                    sumar2020(listapolizas,i.dniasegurado);
                }
                cout << "Ingrese la calle:" << endl;
                cin >> i.calle;
                cout << "Ingrese la altura:" << endl;
                cin >> i.altura;
                actualizar(listapolizas,i.dniasegurado);
                r=buscarpordni(listapolizas,i.dniotroconductor);
                if(r)
                {
                    otroconductor(listapolizas,i.dniotroconductor,i.codigoincidente,i.fecha,i.dniasegurado,i.altura,i.calle);
                }
                insertaralfinalincidente(x->sublista,i);
                cout<<"Incidente cargado con exito"<<endl;
                }
            break;
            case '7':
                crearhtml(listapolizas);
                cout << "" << endl;
                cout <<"Archivos creados correctamente" << endl;
                cout <<"" << endl;
            break;
            case '8':
                mostrarlistapolizas(listapolizas);
            break;
            case '9':
                cout << "" << endl;
                cout<<"Archivo actualizado"<<endl;
                cout << "" << endl;
                guardarPolizasArchivo(listapolizas);
                borrarlistapoliza(listapolizas);
                levantararchivos(listapolizas);
            break;
        }
    } while (elegida!=27);
    return 0;
}
