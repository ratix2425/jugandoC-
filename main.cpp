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
	ArrayDinamico<int> lstDistancia(11,11);//Creamos una matriz distancia de 11 x 11
	ArrayDinamico<int> lstDemanda(2,10);//Matriz de demanda 2 x 10
	ArrayDinamico<int> lstCapacidadAlmacenamiento(1,10); // matriz de almacenamiento de 1 x 10


	//Llenar Valores para la Distancia
	//asignar los valores 
	int indice=0;
	for (int y = 0; y<lstDistancia.lengthY; y++)
	{
		for (int x = 0; x<lstDistancia.lengthX; x++)
		{

			lstDistancia.AsignarDistancia(x,y,distancia[indice++]);
		}
	}

	//Llenar Valores para la demanda
	//asignar los valores 
	indice=0;
	for (int y = 0; y<lstDemanda.lengthY; y++)
	{
		for (int x = 0; x<lstDemanda.lengthX;  x++)
		{
			lstDemanda.AsignarDistancia(x,y,demanda[indice++]);
		}
	}

	//Llenar Valores para la capacidad
	//asignar los valores 
	indice = 0;
	for (int y = 0;y< lstCapacidadAlmacenamiento.lengthY ; y++)
	{
		for (int x = 0; x<lstCapacidadAlmacenamiento.lengthX; x++)
		{

			lstCapacidadAlmacenamiento.AsignarDistancia(x,y,capacidad[indice++]);
		}
	}

	//imprimir
	printf("distancia\n");
	lstDistancia.Imprimir("%d");


	//imprimir Demanda
	printf("Demanda\n");
	lstDemanda.Imprimir("%d");

	//imprimir Capacidad Almacenamiento
	printf("Capacidad Almacenamiento\n");
	lstCapacidadAlmacenamiento.Imprimir("%d");



	//Creacion de los Nodos
	Tabla<Nodo> lstNodo;


	//Insertar Todos a la tabla
	for (int i = 0; i < 5; i++)
	{
		Nodo nodo;
		lstNodo.Insertar(nodo);
	}

	//Realizando Test, para poder acceder a los nodos de la tabla y poder modificarlos
	Nodo nodo1;
	nodo1.capacidad=5;
	indice = lstNodo.Insertar(nodo1);
	lstNodo.Get(indice)->capacidad=4;
	printf("%d",lstNodo.Get(indice)->capacidad);
	printf("%d",nodo1.capacidad);


	printf("\n%d",capacidadVehiculo);


	getchar();

	return;
}