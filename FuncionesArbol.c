#include "header.h"

void mostrar_info(t_dato info)
{
    printf("%d ",info.dato);
}

void crear_arbol(t_arbol *pa)
{
    *pa=NULL;
}

int procesar_preorden(const t_arbol *pa)
{
    if(*pa==NULL)
        return 0; //NO HAY NADA
    mostrar_info((*pa)->info);
    procesar_preorden(&(*pa)->izq);
    procesar_preorden(&(*pa)->der);
    return 1;  // TODO BIEN
}

int procesar_posorden(const t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    procesar_posorden(&(*pa)->izq);
    procesar_posorden(&(*pa)->der);
    mostrar_info((*pa)->info);
    return 1;
}

int procesar_inorden(const t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    procesar_inorden(&(*pa)->izq);
    mostrar_info((*pa)->info);
    procesar_inorden(&(*pa)->der);
    return 1;
}

int insertar_busquedaI(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2))
{
    int comp;
    t_nodo *nue;
    while(*pa)
    {
        if((comp=(cmp(&(*pa)->info.dato,&pd->dato)))>0)
        {
            pa=&(*pa)->izq;
        }
        else if(comp<0)
        {
            pa=&(*pa)->der;
        }
        else
            return 0; //DUPLICADO
    }
    nue=(t_nodo*)malloc(sizeof(t_nodo));
    if(nue==NULL)
        return 0;
    nue->info=*pd;
    nue->izq=NULL;
    nue->der=NULL;
    *pa=nue;
    return 1;

}

int insertar_busquedaR(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2))
{
    int comp;
    if(!*pa)
    {
        *pa=(t_nodo*)malloc(sizeof(t_nodo));
        if(*pa==NULL)
            return 0; //SIN MEMORIA
        (*pa)->izq=(*pa)->der=NULL;
        (*pa)->info=*pd;
        return 1; //TODO BIEN
    }
    if((comp=cmp(&(*pa)->info.dato,&pd->dato))==0)
    {
        return 0; //DUPLICADO
    }
    if(comp>0)
        return insertar_busquedaR(&(*pa)->izq,pd,comparar);
    else
        return insertar_busquedaR(&(*pa)->der,pd,comparar);
}

int comparar(const void *dato1,const void *dato2)
{
    return *(int*)dato1-*(int*)dato2;
}

int guardarArbolB(const t_arbol *pa,FILE *arch)
{
    if(*pa==NULL)
        return 0; //NO HAY NADA
    fwrite(&(*pa)->info,sizeof(t_dato),1,arch);
    guardarArbolB(&(*pa)->izq,arch);
    guardarArbolB(&(*pa)->der,arch);
    return 1;  // TODO BIEN
}

int recuperarArbolB(t_arbol *pa,FILE *arch)
{
    t_dato reg;
    fread(&reg,sizeof(t_dato),1,arch);
    while(!feof(arch))
    {
        insertar_busquedaR(&(*pa),&reg,comparar);
        fread(&reg,sizeof(t_dato),1,arch);
    }
    return 1;
}

int contarArbol(const t_arbol *pa)
{
    int cont=0;
    if(*pa==NULL)
        return 0;
    cont+=contarArbol(&(*pa)->izq);
    cont+=contarArbol(&(*pa)->der);
    return cont+1;
}

int contarHojas(const t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    if(!(*pa)->izq && !(*pa)->der)
        return 1;
    return contarHojas(&(*pa)->izq)+contarHojas(&(*pa)->der);
}

int contarNodosInt(const t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    if(!(*pa)->izq && !(*pa)->der)
        return 0;
    return contarNodosInt(&(*pa)->izq)+contarNodosInt(&(*pa)->der)+1;
}

int alturaArbol(const t_arbol *pa)
{
    int izq,der;
    if(*pa==NULL)
        return 0;
    izq=alturaArbol(&(*pa)->izq);
    der=alturaArbol(&(*pa)->der);
    return izq<der?der+1:izq+1;
}

int eliminarHojas(t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa=NULL;
        return 1;
    }
    return eliminarHojas(&(*pa)->izq)+eliminarHojas(&(*pa)->der);
}

int eliminarArbol(t_arbol *pa)
{
    if(*pa==NULL)
        return 0;
    eliminarArbol(&(*pa)->izq);
    eliminarArbol(&(*pa)->der);
    free(*pa);
    *pa=NULL;
    return 1;
}

float promedioHojas(t_arbol *pa)
{
    //int cant=contarHojas(pa);
    return 0;
}

int contarNodosNivel(t_arbol *pa,int nivel)
{
    if(!*pa)
        return 0;
    if(nivel<=0)
        return 1+contarNodosNivel(&(*pa)->izq,nivel-1)+contarNodosNivel(&(*pa)->der,nivel-1);

    return contarNodosNivel(&(*pa)->izq,nivel-1)+contarNodosNivel(&(*pa)->der,nivel-1);
}

int contarNodosPares(t_arbol *pa)
{
    if(!*pa)
        return 0;
    if((*pa)->info.dato%2==0)
        return 1+contarNodosPares(&(*pa)->izq)+contarNodosPares(&(*pa)->der);
    return contarNodosPares(&(*pa)->izq)+contarNodosPares(&(*pa)->der);
}

t_arbol * buscarNodo(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2))
{
    if(!*pa)
        return NULL;
    if(cmp(&(*pa)->info.dato,&pd->dato)<0)
        return buscarNodo(&(*pa)->der,pd,cmp);
    else if(cmp(&(*pa)->info.dato,&pd->dato)>0)
        return buscarNodo(&(*pa)->izq,pd,cmp);
    return pa;
}

t_arbol * buscarMenor(t_arbol *pa)
{
    if(!*pa)
        return NULL;
    if(!(*pa)->izq)
        return pa;
    return buscarMenor(&(*pa)->izq);
}

t_arbol * buscarMayor(t_arbol *pa)
{
    if(!*pa)
        return NULL;
    if(!(*pa)->der)
        return pa;
    return buscarMayor(&(*pa)->der);
}

int eliminarNodo(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2))
{
    t_arbol *aux;
    aux=buscarNodo(pa,pd,cmp);
    if(!aux)
        return 0; //NO ENCONTRADO
    *pd=(*aux)->info;
    eliminarRaiz(aux);
    return 1;
}

int eliminarRaiz(t_arbol *pa)
{
    t_arbol *hoj;
    if(!(*pa)->izq && !(*pa)->der)
    {
        free(*pa);
        *pa=NULL;
        return 1;
    }
    else
    {
        hoj=buscarMayor(&(*pa)->izq);
        if(!hoj)
        {
            hoj=buscarMenor(&(*pa)->der);
            (*pa)->info=(*hoj)->info;
            eliminarRaiz(hoj);
        }
        else
        {
            (*pa)->info=(*hoj)->info;
            eliminarRaiz(hoj);
        }
    }
    return 1;
}

int arbolCompleto(t_arbol *pa)
{
    int h = alturaArbol(pa);
    return esCompleto(pa,h);
}

int esCompleto(t_arbol *pa, int h)
{
    if(*pa)
    {
        return esCompleto(&(*pa)->izq, h - 1) && esCompleto(&(*pa)->der, h - 1);
    }
    return h==0;
}

int arbolBalanceado(t_arbol *pa)
{
    int h=alturaArbol(pa);
    return esBalanceado(pa,h);
}

int esBalanceado(t_arbol *pa, int h)
{
    if(*pa)
    {
        return esBalanceado(&(*pa)->izq,h-1) && esBalanceado(&(*pa)->der,h-1);
    }
    return h<=1;
}

void arbol_grafico(t_arbol *pa)
{
    int nivel= alturaArbol(pa);
    int i;
    for(i=0; i<nivel; i++)
    {
        pintar_arbol(pa,i,nivel-i);
        printf("\n");
    }
}

void pintar_arbol(t_arbol *pa,int cont,int nivel)
{
    int i;
    if(cont==0)
    {
        for(i=0;i<nivel;i++)
            printf("    ");
        mostrar_info((*pa)->info);
    }
    else
    {
        if(*pa!=NULL)
        {
            if((*pa)->izq)
                pintar_arbol(&(*pa)->izq,cont-1,nivel);
            for(i=0;i<nivel*2;i++)
                printf("    ");
            if((*pa)->der)
                pintar_arbol(&(*pa)->der,cont-1,nivel);
        }
    }
}
