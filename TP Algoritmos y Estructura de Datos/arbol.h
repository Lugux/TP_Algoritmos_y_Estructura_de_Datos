#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MINIMO(X,Y) ((X)<(Y)?(X):(Y))

typedef struct sNodo
{
    void* info;
    size_t tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
}tNodo;

typedef tNodo* tArbol;

int cmp(const void* dato1, const void* dato2);
void crear_arbol(tArbol* pa);
int insertar_ordenado_arbol(tArbol* pa, const void* dato, size_t tamDato, int (*cmp)(const void*, const void*));
void recorrer_en_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro);
void recorrer_pre_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro);
void recorrer_pos_orden(tArbol* pa, void (*accion)(void*, size_t, void*), void* parametro);
int contar_nodos_arbol(const tArbol* pa);
int altura_arbol(const tArbol* pa);
int contar_nodos_hasta_nivel(const tArbol* pa, int n);
int es_completo_hasta_nivel(const tArbol* pa, int n);
int es_balanceado(const tArbol* pa);
tNodo* cargar_arbol_balanceado(FILE* pf, int li, int ls, size_t tamInfo);
int cargar_arbol_desde_archivo(tArbol* pa, char* nombreArchivo, size_t tamRegistro);


#endif // ARBOL_H_INCLUDED
