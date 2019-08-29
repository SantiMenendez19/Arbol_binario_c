#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//ESTRUCTURA DE UN ARBOL//
typedef struct
{
    int dato;
}t_dato;

typedef struct s_nodo
{
    t_dato info;
    struct s_nodo *izq;
    struct s_nodo *der;
}t_nodo;

typedef t_nodo* t_arbol;

void mostrar_info(t_dato info);
void crear_arbol(t_arbol *pa);
int procesar_preorden(const t_arbol *pa);
int procesar_posorden(const t_arbol *pa);
int procesar_inorden(const t_arbol *pa);
int insertar_busquedaI(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2));
int insertar_busquedaR(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2));
int comparar(const void *dato1,const void *dato2);
int guardarArbolB(const t_arbol *pa,FILE *arch);
int recuperarArbolB(t_arbol *pa,FILE *arch);
int contarArbol(const t_arbol *pa);
int contarHojas(const t_arbol *pa);
int contarNodosInt(const t_arbol *pa);
int alturaArbol(const t_arbol *pa);
int eliminarHojas(t_arbol *pa);
int eliminarArbol(t_arbol *pa);
float promedioHojas(t_arbol *pa);
int contarNodosNivel(t_arbol *pa,int nivel);
int contarNodosPares(t_arbol *pa);
t_arbol * buscarNodo(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2));
t_arbol * buscarMenor(t_arbol *pa);
t_arbol * buscarMayor(t_arbol *pa);
int eliminarNodo(t_arbol *pa,t_dato *pd,int (*cmp)(const void *dato1,const void *dato2));
int eliminarRaiz(t_arbol *pa);
int arbolCompleto(t_arbol *pa);
int esCompleto(t_arbol *pa, int h);
int arbolBalanceado(t_arbol *pa);
int esBalanceado(t_arbol *pa, int h);
void arbol_grafico(t_arbol *pa);
void pintar_arbol(t_arbol *pa,int cont,int nivel);
#endif // HEADER_H_INCLUDED
