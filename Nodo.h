#ifndef ClassNodo
#define ClassNodo
//const  int cantidadDemanda=10;//cantidad de demandas  (dias)
#include "Constantes.h"
#include"ArrayDinamico.h"

class Nodo
{
public:

	Nodo(int numeroNodo, int capacidad, int indice,int *demanda,int *distancia);

	~Nodo(void);

	void Imprimir();

	int *_distancia;
private:
	int _numeroNodo;

	int _capacidad;

	int _indiceArray;

	int *_demanda;

	
};

Nodo::Nodo(int numeroNodo, int capacidad, int indice, int *demanda,int *distancia)
{
	this->_numeroNodo = numeroNodo;
	this->_capacidad = capacidad;
	this->_indiceArray = indice;
	this->_demanda = demanda;
	this->_distancia = distancia;

}


Nodo::~Nodo(void)
{
	//if(this->lstDemanda)
	//delete[] this->lstDemanda;
}

void Nodo::Imprimir()
{
	printf("******************************************************************\n");
	printf("Nodo %d\n\tCapacidad %d", this->_numeroNodo, this->_capacidad);

	//imprimir demanda
	printf("\n\tdemanda:\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\tdia %d",i+1);
	}
	printf("\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\t%d",this->_demanda[i]);
	}
	printf("\n");

	//imprimir distancia
	printf("\n\tdistancia:\n");
	for (int i = 0; i < numeroNodos+1; i++)//numeroNodo + 1 // se coloca el numero de nodos mas el deposito por eso es +1
	{
		printf("nodo %d\t",i);
	}
	printf("\n");
	for (int i = 0; i < numeroNodos+1; i++)
	{
		printf("%d\t",this->_distancia[i]);
	}
	
	printf("\n******************************************************************");
	printf("\n\n");

}



#endif
