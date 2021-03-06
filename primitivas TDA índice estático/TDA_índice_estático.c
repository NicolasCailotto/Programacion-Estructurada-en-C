#include "TDA_índice_estático.h"

#include<stdio.h>
#include<stdlib.h>

unsigned indicador=TAM;

void ind_crear(t_indice *ind)
    {
    ind->tope=0;
    }

int ind_insertar(t_indice *ind,const t_reg_indice *reg_ind)
    {
    if(ind->tope==TAM)
        return INDICE_LLENO;
    if(ind->tope!=0)
        {
        unsigned pos=0;
        while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni)
            pos++;
        if(ind->registro[pos].dni==reg_ind->dni)
            return DUPLICADO;
        t_reg_indice aux1,aux2;
        aux1=ind->registro[pos];
        ind->registro[pos]=*reg_ind;
        pos++;
        while(pos<ind->tope)
            {
            aux2=ind->registro[pos];
            ind->registro[pos]=aux1;
            aux1=aux2;
            pos++;
            }
        ind->registro[pos]=aux1;
        }
    else
        ind->registro[ind->tope]=*reg_ind;
    ind->tope++;
    return OK;
    }

int ind_eliminar(t_indice *ind,t_reg_indice *reg_ind)
    {
    if(ind->tope==0)
        return INDICE_VACIO;
    unsigned pos=0;
    while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni)
        pos++;
    if(pos==ind->tope||ind->registro[pos].dni!=reg_ind->dni)
        return NO_ENCONTRADO;
    while(pos<ind->tope)
        {
        ind->registro[pos]=ind->registro[pos+1];
        pos++;
        }
    ind->tope--;
    return OK;
    }

int ind_buscar(const t_indice *ind,t_reg_indice *reg_ind)
    {
    if(ind->tope==0)
        return INDICE_VACIO;
    unsigned pos=0;
    while(pos<ind->tope&&ind->registro[pos].dni<reg_ind->dni)
        pos++;
    if(pos<ind->tope&&ind->registro[pos].dni!=reg_ind->dni)
        return NO_ENCONTRADO;
    *reg_ind=ind->registro[pos];
    return OK;
    }

int ind_cargar(t_indice *ind,const char *path)
    {
    FILE *pf;
    pf=fopen(path,"rb");
    if(!pf)
        return ARCHIVO_CORRUPTO;
    unsigned pos=0;
    fread(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
    while(!feof(pf))
        {
        pos++;
        fread(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
        }
    fclose(pf);
    ind->tope=pos;
    return OK;
    }

int ind_grabar(const t_indice *ind,const char *path)
    {
    if(ind->tope==0)
        return INDICE_VACIO;
    FILE *pf;
    pf=fopen(path,"wb");
    if(!pf)
        return ARCHIVO_CORRUPTO;
    unsigned pos=0;
    while(pos<ind->tope)
        {
        fwrite(&ind->registro[pos],sizeof(t_reg_indice),1,pf);
        pos++;
        }
    fclose(pf);
    return OK;
    }

void ind_vaciar(t_indice *ind)
    {
    ind->tope=0;
    }

int ind_primero(t_indice *ind,t_reg_indice *reg_ind)
    {
    if(ind->tope==0)
        return INDICE_VACIO;
    extern unsigned indicador;
    indicador=0;
    *reg_ind=ind->registro[indicador];
    return OK;
    }

int ind_siguiente(t_indice *ind,t_reg_indice *reg_ind)
    {
    if(ind->tope==0)
        return INDICE_VACIO;
    extern unsigned indicador;
    if(indicador==TAM)
        return NO_ENCONTRADO;
    if(indicador+1==ind->tope)
        return NO_ENCONTRADO;
    indicador++;
    *reg_ind=ind->registro[indicador];
    return OK;
    }

int ind_fin(t_indice *ind)
    {
    extern unsigned indicador;
    if(indicador+1==ind->tope)
        return OK;
    return NO_ENCONTRADO;
    }

void ind_liberar(t_indice *indice)
    {
    ///Esta primitiva no aplica a la implementación estática del TDA índice
    }
