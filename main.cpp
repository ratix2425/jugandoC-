#include <stdio.h>
#include "Constantes.h"
#include "ArrayDinamico.h"
#include "Tabla.h"
#include "Nodo.h"



void main()
{

	//datos para llenar la tabla distancia
	int distancia[]={0,10,5,9,8,7,
		10,0,6,3,9,12,
		5,6,0,2,4,8,
		9,3,2,0,2,1,
		8,9,4,2,0,10,
		7,12,8,1,10,0};
	//datos para llenar la tabla demanda
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

	//datos para llenar la tabla capacidad
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
	ArrayDinamico<int> lstDistancia(6,6);//Creamos una matriz distancia de 5 X 5
	ArrayDinamico<int> lstDemanda(2,10);//Matriz de demanda 5 X 5
	ArrayDinamico<int> lstCapacidadAlmacenamiento(1,10);


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