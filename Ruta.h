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

	static Tabla<Ruta> *GenerarRuta(Tabla<Nodo> &lstNodo);

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
	printf("\tdia %d",this->_nDia+1);
	printf("\tTotal Carga: %d", this->TotalDemanda());
	printf("\tNodos: ");
	for(int i=0;i<this->nodos.lenght;i++)
	{
		printf("%d,",this->nodos.Get(i)->NumeroNodo());
	}
	

};



Tabla<Ruta> *Ruta::GenerarRuta(Tabla<Nodo> &lstNodo)
{
	Tabla<Ruta> *lstRutatmp = new Tabla<Ruta>();
	for(int dia =0;dia<numeroDias;dia++)
	{
		Tabla<Nodo> lstTmpNodo;
		lstTmpNodo.Insertar(lstNodo);

		int numeroRuta=0;

		Ruta *rut= new Ruta(++numeroRuta,dia);//insertar primera ruta
		lstRutatmp->Insertar(rut);
		do
		{
			int indice = random(0,lstTmpNodo.lenght-1);//obtener un nodo al azar
			if(
				rut->TotalDemanda()+lstTmpNodo.Get(indice)->GetDemanda(dia)<=capacidadVehiculo//si la total de la demanda de la ruta + la demanda del nodo, no supera la capacidad del vehiculo
				&& rut->nodos.lenght<maxNodoRuta //la cantidad de nodos por ruta no supere maxNodoRuta
				)
			{
				rut->nodos.Insertar(lstTmpNodo.Get(indice));//insertamos a la ruta
				lstTmpNodo.Remover(lstTmpNodo.Get(indice));//quitamos de la lista
			}
			else
			{
				//creamos nueva Ruta
				rut = new Ruta(++numeroRuta,dia);
				//insertar al listado de rutas
				lstRutatmp->Insertar(rut);
				rut->nodos.Insertar(lstTmpNodo.Get(indice));//insertamos a la ruta
				lstTmpNodo.Remover(lstTmpNodo.Get(indice));//quitamos de la lista
			}
		}
		while(lstTmpNodo.lenght>0);//se debe repetir, hasta que no queden nodos sin rutas
	}
	return lstRutatmp;
}

#endif