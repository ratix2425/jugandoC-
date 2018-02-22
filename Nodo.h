#ifndef ClassNodo
#define ClassNodo
//const  int cantidadDemanda=10;//cantidad de demandas  (dias)
#include "Constantes.h"
#include"ArrayDinamico.h"

class Nodo
{
private:
	int *_distancia;

	int _numeroNodo;

	int _capacidad;

	int _indiceArray;

	int *_demanda;

	int *_inventario;

	char *_nombre;

public:

	Nodo(int numeroNodo, char *nombre, int capacidad, int indice,int *demanda,int *distancia, int *inventario);

	~Nodo(void);

	void Imprimir();

	int NumeroNodo();

	int GetDemanda(int nDia);

	int GetCantidadRecoger(int nDia);

	int GetDistancia(int nodo);

	int GetInventario(int nDia);

	char *GetNombre();

};

Nodo::Nodo(int numeroNodo, char *nombre, int capacidad, int indice, int *demanda,int *distancia, int *inventario)
{
	this->_numeroNodo = numeroNodo;
	this->_capacidad = capacidad;
	this->_indiceArray = indice;
	this->_demanda = demanda;
	this->_distancia = distancia;
	this->_inventario = inventario;
	this->_nombre= nombre;

}

Nodo::~Nodo(void)
{
	//if(this->_demanda)
	//	delete[] this->_demanda;
}

void Nodo::Imprimir()
{
	printf("******************************************************************\n");
	printf("Nodo %d: %s\n\tCapacidad %d",this->_numeroNodo, this->_nombre, this->_capacidad);

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

	printf("\n");
	//imprimir inventario
	printf("\n\tInventario:\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\tdia %d",i+1);
	}
	printf("\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\t%d",this->_inventario[i]);
	}

	printf("\n");
	//imprimir Cantidad Recoger
	printf("\n\tCantidad Recoger:\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\tdia %d",i+1);
	}
	printf("\n\t");
	for (int i = 0; i < numeroDias; i++)
	{
		printf("\t%d",this->GetCantidadRecoger(i));
	}

	printf("\n******************************************************************");
	printf("\n\n");

}

int Nodo::NumeroNodo()
{
	return this->_numeroNodo;
}

int Nodo::GetDemanda(int nDia)
{
	return this->_demanda[nDia];
}

int Nodo::GetCantidadRecoger(int nDia)
{
	int inventarioAnterior=0;

	if(nDia>0)//si no es el primer dia, se trae el inventario del dia anterior
	{
		inventarioAnterior=this->_inventario[nDia-1];
	}
	//cantidad a recoger es lo que hay en inventario + demanda - inventario del dia anterior.
	return this->_inventario[nDia]+this->GetDemanda(nDia)-inventarioAnterior;
}

int Nodo::GetDistancia(int nodo)
{
	return this->_distancia[nodo];
}

int Nodo::GetInventario(int nodo)
{
	return this->_inventario[nodo];
}

char *Nodo::GetNombre()
{

	return this->_nombre;
}
#endif
