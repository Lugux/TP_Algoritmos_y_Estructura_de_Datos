#include "socios.h"

int leerSocioCSV(FILE *pf, tSocio *socio)
{
    char linea[256];

    char nacimiento[11];
    char afiliacion[11];
    char ultimaCuota[11];
    char baja[11];

    if(!fgets(linea,sizeof(linea),pf))
        return 0;

    sscanf(linea,
           "%ld,%60[^,],%60[^,],%10[^,],%c,%10[^,],%10[^,],%10[^,],%c,%10[^\n]",
           &socio->dni,
           socio->apellido,
           socio->nombre,
           nacimiento,
           &socio->sexo,
           afiliacion,
           socio->categoria,
           ultimaCuota,
           &socio->estado,
           baja);

    socio->nacimiento = pasarFecha(nacimiento);
    socio->afiliacion = pasarFecha(afiliacion);
    socio->ultimaCuotaPaga = pasarFecha(ultimaCuota);
    socio->baja = pasarFecha(baja);

    return 1;
}

int grabarSocioDAT(FILE *pf, const tSocio* socio)
{
    return fwrite(socio, sizeof(tSocio), 1, pf);
}

int cargarArchivoSocios()
{
    tSocio socio;

    FILE *fpCSV = fopen("socios.csv", "rt");
    if(fpCSV == NULL)
    {
        printf("No se pudo abrir el CSV");
        return 0;
    }

    FILE *fpDAT = fopen("socios.dat", "wb");
    if(fpDAT == NULL)
    {
        printf("No se pudo crear el DAT");
        fclose(fpCSV);
        return 0;
    }

    while(leerSocioCSV(fpCSV, &socio))
    {
        grabarSocioDAT(fpDAT, &socio);
    }

    fclose(fpCSV);
    fclose(fpDAT);

    return 1;
}
