#include "arbol.h"

int cmp(const void* dato1, const void* dato2)
{
    int* n1=(int*)dato1;
    int* n2=(int*)dato2;
    return (*n1)-(*n2);
}

void crear_arbol(tArbol* pa)
{
    (*pa)=NULL;
}

int insertar_ordenado_arbol(tArbol* pa, const void* dato, size_t tamDato, int (*cmp)(const void*, const void*))
{
    tNodo* nue;

    while(*pa)
    {
        if(cmp(dato,(*pa)->info)>0)
            pa=&(*pa)->der;
        else if(cmp(dato,(*pa)->info)<0)
            pa=&(*pa)->izq;
        else
            return 0;
    }

    nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return 0;
    nue->info=malloc(tamDato);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info,dato,tamDato);
    nue->tamInfo=tamDato;

    nue->der=nue->izq=NULL;
    (*pa)=nue;

    return 1;
}

void recorrer_en_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro)
{
    if(!(*pa))
        return;
    recorrer_en_orden(&(*pa)->izq, accion, parametro);
    accion((*pa)->info,(*pa)->tamInfo,parametro);
    recorrer_en_orden(&(*pa)->der, accion, parametro);
}

void recorrer_pre_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro)
{
    if(!(*pa))
        return;
    accion((*pa)->info,(*pa)->tamInfo,parametro);
    recorrer_pre_orden(&(*pa)->izq, accion, parametro);
    recorrer_pre_orden(&(*pa)->der, accion, parametro);
}

void recorrer_pos_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro)
{
    if(!(*pa))
        return;
    recorrer_pos_orden(&(*pa)->izq, accion, parametro);
    recorrer_pos_orden(&(*pa)->der, accion, parametro);
    accion((*pa)->info,(*pa)->tamInfo,parametro);
}

int contar_nodos_arbol(const tArbol* pa)
{
    if(!(*pa))
        return 0;
    return contar_nodos_arbol(&(*pa)->izq)+1+contar_nodos_arbol(&(*pa)->der);
}

int altura_arbol(const tArbol* pa)
{
    if(!(*pa))
        return 0;
    unsigned h1=altura_arbol(&(*pa)->izq);
    unsigned h2=altura_arbol(&(*pa)->der);
    return ( h1 > h2 ? h1 : h2 ) + 1;
}

int contar_nodos_hasta_nivel(const tArbol* pa, int n)
{
    if(!(*pa))
        return 0;
    if(n==0)
        return 1;

    return contar_nodos_hasta_nivel(&(*pa)->izq, n-1) + contar_nodos_hasta_nivel(&(*pa)->der, n-1) + 1;
}

int es_completo_hasta_nivel(const tArbol* pa, int n)
{
    if(!(*pa))
        return 0;
    if(n==0)
        return 1;

    return es_completo_hasta_nivel(&(*pa)->izq,n-1) && es_completo_hasta_nivel(&(*pa)->der,n-1);
}

int es_balanceado(const tArbol* pa)
{
    int h=altura_arbol(pa);

    if(h<=2)
        return 1;

    return es_completo_hasta_nivel(pa,h-2);
}

/// int cargarDatosOrdRed(tArbol* pa, void*,

tNodo* cargar_arbol_balanceado(FILE* pf, int li, int ls, size_t tamInfo)    /// ¡¡¡ sirve para archivos que el un (1) tamInfo equivale a un registro !!!
{
    if(li>ls)
        return NULL;
    int media=(li+ls)/2;    // MEDIA guarda el promedio o la media matemática

    fseek(pf,media*tamInfo,SEEK_SET);   /// el puntero de archivo se va a parar en el medio de este

    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return NULL;
    nue->info=malloc(tamInfo);
    if(!nue->info)
    {
        free(nue);
        return NULL;
    }
    nue->der=nue->izq=NULL;
    if(fread(nue->info,tamInfo,1,pf))
    {
        nue->izq=cargar_arbol_balanceado(pf,li,media-1,tamInfo);    // Raíz en el medio y acorta espacios hacia la izquierda, moviendo ls.
        nue->der=cargar_arbol_balanceado(pf,media+1,ls,tamInfo);    // Lo mismo, pero hacia la derecha (mayores), moviendo li.

        return nue;
    }
    else
    {
        free(nue->info);
        free(nue);
        return NULL;
    }
}

int cargar_arbol_desde_archivo(tArbol* pa, char* nombreArchivo, size_t tamRegistro)
{
    FILE* pf=fopen(nombreArchivo,"rb");
    if(!pf)
        return 0;
    fseek(pf,0L,SEEK_END);

    int cantRegistros=ftell(pf)/tamRegistro;
    int li=0;
    int ls=cantRegistros-1;

    fseek(pf,0L,SEEK_SET);

    (*pa)=cargar_arbol_balanceado(pf,li,ls,tamRegistro);

    fclose(pf);
    return 1;
}
