#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#include "fecha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    long dni;
    char apellido[61];
    char nombre[61];
    tFecha nacimiento;
    char sexo;
    tFecha afiliacion;
    char categoria[11];
    tFecha ultimaCuotaPaga;
    char estado;
    tFecha baja;
}tSocio;

int leerSocioCSV(FILE *pf, tSocio* socio);
int grabarSocioDAT(FILE *pf, const tSocio* socio);
int cargarArchivoSocios();


#endif // SOCIOS_H_INCLUDED
