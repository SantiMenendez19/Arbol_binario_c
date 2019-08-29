#include "header.h"
int main()
{
    int OP,num,cont;
    t_arbol arbol;
    t_arbol *aux;
    t_dato dato;
    crear_arbol(&arbol);
    while(OP!=20)
    {
        printf("Elige una opcion:\n");
        printf("1-Insertar en un arbol\n");
        printf("2-Guardar el arbol en un archivo binario\n");
        printf("3-Recuperar el arbol de un archivo binario\n");
        printf("4-Recorrer el arbol en Preorden\n");
        printf("5-Contar los nodos del arbol\n");
        printf("6-Contar las hojas del arbol\n");
        printf("7-Contar los nodos interiores del arbol\n");
        printf("8-Altura del arbol\n");
        printf("9-Eliminar Hojas del arbol\n");
        printf("10-Eliminar Arbol\n");
        printf("11-Contar nodos desde X nivel\n");
        printf("12-Contar nodos pares\n");
        printf("13-Buscar el menor del arbol\n");
        printf("14-Buscar el mayor del arbol\n");
        printf("15-Buscar el valor de un nodo en un arbol\n");
        printf("16-Eliminar nodo por teclado de un arbol\n");
        printf("17-Averiguar si el arbol es un arbol completo\n");
        printf("18-Averiguar si el arbol es un ABL\n");
        printf("19-Mostrar arbol grafico\n");
        printf("20-Salir\n");
        scanf("%d",&OP);
        system("cls");
        switch(OP)
        {
        case 1:
            do
            {
                puts("Inserte un numero:");
                scanf("%d",&dato.dato);
                insertar_busquedaR(&arbol,&dato,comparar);
                puts("Desea insertar otro numero? 1-SI 2-NO");
                scanf("%d",&OP);
            }
            while(OP==1);
            break;
        case 2:
        {
            FILE *archbin;
            archbin=fopen("arbol.bin","wb");
            guardarArbolB(&arbol,archbin);
            puts("Arbol guardado");
            fclose(archbin);
            system("pause");
            break;
        }
        case 3:
        {
            eliminarArbol(&arbol);
            FILE *archbin;
            archbin=fopen("arbol.bin","rb");
            recuperarArbolB(&arbol,archbin);
            puts("Arbol recuperado");
            fclose(archbin);
            system("pause");
            break;
        }
        case 4:
        {
            procesar_preorden(&arbol);
            printf("\n");
            system("pause");
            break;
        }
        case 5:
        {
            cont=contarArbol(&arbol);
            printf("Cantidad de Nodos del arbol: %d \n",cont);
            system("pause");
            break;
        }
        case 6:
        {
            cont=contarHojas(&arbol);
            printf("Cantidad de hojas del arbol: %d \n",cont);
            system("pause");
            break;
        }
        case 7:
        {
            cont=contarNodosInt(&arbol);
            printf("Cantidad de nodos interiores del arbol: %d \n",cont);
            system("pause");
            break;
        }
        case 8:
        {
            cont=alturaArbol(&arbol);
            printf("Altura del arbol: %d \n",cont);
            system("pause");
            break;
        }
        case 9:
        {
            cont=eliminarHojas(&arbol);
            printf("%d hojas eliminadas\n",cont);
            system("pause");
            break;
        }
        case 10:
        {
            eliminarArbol(&arbol);
            puts("Arbol eliminado");
            system("pause");
            break;
        }
        case 11:
        {
            puts("Inserta numero de nivel del arbol:");
            scanf("%d",&num);
            cont=contarNodosNivel(&arbol,num);
            printf("Cantidad de nodos desde ese nivel: %d \n",cont);
            system("pause");
            break;
        }
        case 12:
        {
            cont=contarNodosPares(&arbol);
            printf("Cantidad de nodos pares: %d \n",cont);
            system("pause");
            break;
        }
        case 13:
        {
            aux=buscarMenor(&arbol);
            printf("Menor: ");
            mostrar_info((*aux)->info);
            system("pause");
            break;
        }
        case 14:
        {
            aux=buscarMayor(&arbol);
            printf("Mayor: ");
            mostrar_info((*aux)->info);
            system("pause");
            break;
        }
        case 15:
        {
            printf("Inserta el valor del nodo a buscar:\n");
            scanf("%d",&num);
            dato.dato=num;
            aux=buscarNodo(&arbol,&dato,comparar);
            if(!aux)
                puts("No se encontro el valor");
            else
            {
                printf("Se encontro el nodo: ");
                mostrar_info((*aux)->info);
            }
            system("pause");
            break;
        }
        case 16:
        {
            printf("Inserta el valor del nodo a buscar:\n");
            scanf("%d",&num);
            dato.dato=num;
            if(eliminarNodo(&arbol,&dato,comparar))
                puts("Se elimino el nodo");
            else
                puts("El nodo no pudo ser eliminado");
            system("pause");
            break;
        }
        case 17:
        {
            arbolCompleto(&arbol)?printf("El arbol es COMPLETO\n"):printf("El arbol NO es completo\n");
            system("pause");
            break;
        }
        case 18:
        {
            arbolBalanceado(&arbol)?printf("El arbol es BALANCEADO\n"):printf("El arbol NO es BALANCEADO\n");
            system("pause");
            break;
        }
        case 19:
        {
            printf("Arbol Grafico\n");
            arbol_grafico(&arbol);
            system("pause");
            break;
        }
        case 20: //SALIDA
        {
            break;
        }
        default:
        {
            puts("Opcion incorrecta");
            system("pause");
            break;
        }
        }
        system("cls");
    }
    puts("Salida del Programa");
    return 0;
}
