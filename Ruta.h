#ifndef ClassRuta
#define ClassRuta


#include "Tabla.h"

class Ruta
{

private:
	int _nDia;

	int _numeroRuta;

public:

	Ruta(int numeroRuta, int nDia);

	Tabla<Nodo> nodos;

	int GetDia();

	int TotalDemanda();

	void Imprimir();
};

Ruta::Ruta(int numeroRuta, int nDia)
{
	_numeroRuta=numeroRuta;
	_nDia = nDia;
}

int Ruta::GetDia()
{
	return _nDia;
}

int Ruta::TotalDemanda()
{
	int total = 0;

	for(int i=0;i<nodos.lenght;i++)
	{
		total = total+nodos.Get(i)->GetDemanda(_nDia);
	}
	return total;
}

void Ruta::Imprimir()
{
	printf("\nN ruta %d",this->_numeroRuta);
	printf("\tdia %d",this->_nDia);
	printf("\tNodos:");
	for(int i=0;i<this->nodos.lenght;i++)
	{
		printf("%d,",this->nodos.Get(i)->NumeroNodo());
	}
	printf("\tTotal Carga: %d", this->TotalDemanda());

}
#endif