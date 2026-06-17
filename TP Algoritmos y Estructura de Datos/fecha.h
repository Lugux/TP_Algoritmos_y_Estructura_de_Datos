#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned dia;
    unsigned mes;
    int anio;
}tFecha;

int esBisiesto(tFecha* f);
int fechaValida(tFecha* f);

#endif // FECHA_H_INCLUDED
