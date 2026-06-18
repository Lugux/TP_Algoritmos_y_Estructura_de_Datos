#include <stdio.h>
#include <stdlib.h>

#include "Funciones.h"
#include "socios.h"

void mostrarFecha(const tFecha* f)
{
    printf("%02d/%02d/%04d",
           f->dia,
           f->mes,
           f->anio);
}

void mostrarSocio(const tSocio* socio)
{
    printf("DNI: %ld\n", socio->dni);
    printf("Apellido: %s\n", socio->apellido);
    printf("Nombre: %s\n", socio->nombre);

    printf("Fecha de Nacimiento: ");
    mostrarFecha(&socio->nacimiento);
    printf("\n");

    printf("Sexo: %c\n", socio->sexo);

    printf("Fecha de Afiliacion: ");
    mostrarFecha(&socio->afiliacion);
    printf("\n");

    printf("Categoria: %s\n", socio->categoria);

    printf("Ultima Cuota Paga: ");
    mostrarFecha(&socio->ultimaCuotaPaga);
    printf("\n");

    printf("Estado: %c\n", socio->estado);

    printf("Fecha de Baja: ");
    mostrarFecha(&socio->baja);
    printf("\n");

    printf("----------------------------------------\n");
}

void mostrarArchivoDAT(const char* nombreArchivo)
{
    FILE* pf = fopen(nombreArchivo, "rb");
    tSocio socio;

    if(!pf)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    while(fread(&socio, sizeof(tSocio), 1, pf))
    {
        mostrarSocio(&socio);
    }

    fclose(pf);
}

int main()
{
    cargarArchivoSocios();
    mostrarArchivoDAT("socios.dat");
    return 0;
}

