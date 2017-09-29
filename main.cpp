#include <stdio.h>
#include "Constantes.h"
#include "ArrayDinamico.h"
#include "Tabla.h"
#include "Nodo.h"



void main()
{

	//datos para llenar la tabla distancia  (nodo x nodo)
	int distancia[]={0,230,250,320,150,230,452,420,230,320,250,
		230,0,25,65,47,85,25,14,36,96,85,
		250,25,0,4,68,5,21,23,5,69,54,
		320,65,4,0,7,9,5,47,52,32,1,
		150,47,68,7,0,5,96,3,56,21,12,
		230,85,5,9,5,0,2,4,6,8,96,
		452,25,21,5,96,2,0,85,41,52,32,
		420,14,23,47,3,4,85,0,14,25,74,
		230,36,5,52,56,6,41,14,0,8,10,
		320,96,69,32,21,8,52,25,8,0,4,
		250,85,54,1,12,96,32,74,10,4,0
	};
	//datos para llenar la tabla demanda  = (nodo x dias)
	int demanda[]=  {3,7,
		8,4,
		4,5,
		10,10,
		3,5,
		4,6,
		8,4,
		3,7,
		2,2,
		1,4};

	//datos para llenar la tabla capacidad (nodo)
	int capacidad[]={10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10,
		10};

	//Contenedor de los datos
	ArrayDinamico<int> lstDistancia(numeroNodos+1,numeroNodos+1);//Creamos una matriz distancia de numeroNodos+1  X numeroNodos+1--    mas 1 por que estamos sumando el deposito
	ArrayDinamico<int> lstDemanda(numeroDias,numeroNodos);//Matriz de demanda 2 x numero de Nodos
	ArrayDinamico<int> lstCapacidadAlmacenamiento(1,numeroNodos); // matriz de almacenamiento de 1 x numero de Nodos

	//Creacion de los Nodos
	Tabla<Nodo> lstNodo;

	//Llenar Valores para la Distancia
	//asignar los valores 
	int indice=0;
	for (int y = 0; y<lstDistancia.lengthY; y++)
	{
		for (int x = 0; x<lstDistancia.lengthX; x++)
		{

			lstDistancia.Set(x,y,distancia[indice++]);
		}
	}

	//Llenar Valores para la demanda
	//asignar los valores 
	indice=0;
	for (int y = 0; y<lstDemanda.lengthY; y++)
	{
		for (int x = 0; x<lstDemanda.lengthX;  x++)
		{
			lstDemanda.Set(x,y,demanda[indice++]);
		}
	}

	//Llenar Valores para la capacidad
	//asignar los valores 
	indice = 0;
	for (int y = 0;y< lstCapacidadAlmacenamiento.lengthY ; y++)
	{
		for (int x = 0; x<lstCapacidadAlmacenamiento.lengthX; x++)
		{

			lstCapacidadAlmacenamiento.Set(x,y,capacidad[indice++]);
		}
	}



	//Insertar Nodos a la Tabla
	for (int i = 1; i <= numeroNodos; i++)
	{
		//i-1 por que el valor del nodo1, esta en el indice 0, del nodo2 esta en el indice 1, nodo3 en indice 2 ...
		Nodo *nodo =new Nodo(i,lstCapacidadAlmacenamiento.Get(i-1,0),i-1, lstDemanda.GetListY(i-1),lstDistancia.GetListY(i-1));
		lstNodo.Insertar(nodo);
	}



	printf("\nCapacidad de Vehiculo : %d\n", capacidadVehiculo);
	printf("\nN de Nodos : %d\n", numeroNodos);
	printf("\nN de Dias : %d\n", numeroDias);

	//imprimir
	printf("\n\ndistancia\n");
	lstDistancia.Imprimir("%d");


	//imprimir Demanda
	printf("\nDemanda\n");
	lstDemanda.Imprimir("%d");

	//imprimir Capacidad Almacenamiento
	printf("\nCapacidad Almacenamiento\n");
	lstCapacidadAlmacenamiento.Imprimir("%d");

	printf("\n\nMostrar Nodos\n");
	for (int i = 0; i < lstNodo.lenght; i++)
	{
		lstNodo.Get(i)->Imprimir();
	}

	getchar();

	return;
}