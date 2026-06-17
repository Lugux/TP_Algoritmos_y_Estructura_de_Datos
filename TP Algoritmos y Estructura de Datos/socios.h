#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#include "fecha.h"

typedef struct
{
    long dni;
    char apellido[60];
    char nombre[60];
    tFecha nacimiento;
    char sexo;
    tFecha afliciacion;
    char categoria[10];
    tFecha ultimaCuotaPaga;
    char estado;
    tFecha baja;
}tSocio;

#endif // SOCIOS_H_INCLUDED
