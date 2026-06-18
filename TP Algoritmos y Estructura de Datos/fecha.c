#include "fecha.h"

const int dias_meses[2][12]={
    {31,28,31,30,31,30,31,31,30,31,30,31},
    {31,29,31,30,31,30,31,31,30,31,30,31}};

int esBisiesto(tFecha* f)
{
    return (f->anio%4==0 && f->anio%100!=0) || (f->anio%400==0);
}

int fechaValida(tFecha* f)
{
    return (f->mes > 0 &&  f->mes < 13) && (f->dia > 0 && f->dia <= dias_meses[esBisiesto(f)][f->mes-1])  ;
}

tFecha pasarFecha(const char* s)
{
    tFecha f = {0,0,0};

    if(!s || *s == '\0')
        return f;

    sscanf(s,"%d/%d/%d", &f.dia, &f.mes, &f.anio);

    return f;
}
