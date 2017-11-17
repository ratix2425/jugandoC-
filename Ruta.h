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

	int TotalCantidadRecoger();

	int TotalDistancia();

	void Imprimir();

	static Tabla<Tabla<Ruta>> *GenerarRuta(Tabla<Nodo> &lstNodo);

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

	for(int i=0;i<nodos.GetLength();i++)
	{
		total = total+nodos.Get(i)->GetDemanda(_nDia);
	}
	return total;
}

int Ruta::TotalDistancia()
{
	int total = 0;

	for(int i=0;i<nodos.GetLength();i++)
	{
		if(i==nodos.GetLength()-1)//si es el ultimo nodo, se calcula la distancia que tiene ese nodo, con el indice 0, o nodo principal
		{
			total = total+nodos.Get(i)->GetDistancia(0);
		}
		else
		{
			total = total+nodos.Get(i)->GetDistancia(nodos.Get(i+1)->NumeroNodo());//calcula la distancia del nodo actual, con el nodo siguiente de la lista
		}
	}
	return total;
}

int Ruta::TotalCantidadRecoger()
{
	int total = 0;

	for(int i=0;i<nodos.GetLength();i++)
	{
		total = total+nodos.Get(i)->GetCantidadRecoger(_nDia);
	}
	return total;
}

void Ruta::Imprimir()
{
	printf("\nN ruta %d",this->_numeroRuta);
	printf("\tdia %d",this->_nDia+1);
	printf("\tTC: %d", this->TotalDemanda());
	printf("\tTCR: %d", this->TotalCantidadRecoger());
	printf("\tTD: %d", this->TotalDistancia());
	printf("\tNodos: ");
	for(int i=0;i<this->nodos.GetLength();i++)
	{
		printf("%d,",this->nodos.Get(i)->NumeroNodo());
	}
};



Tabla<Tabla<Ruta>> *Ruta::GenerarRuta(Tabla<Nodo> &lstNodo)
{
	Tabla<Tabla<Ruta>> *lstRutatmpGeneral = new Tabla<Tabla<Ruta>>();//un listado de tabla de rutas, por dias
	Tabla<Ruta> *lstRutatmp;//puntero temporal donde se va a almacenar todas las rutas por dias

	for(int dia =0;dia<numeroDias;dia++)//recorrer todos los dias
	{
		lstRutatmp = new Tabla<Ruta>();//puntero temporal donde se va a almacenar todas las rutas

		lstRutatmpGeneral->Insertar(lstRutatmp);
		Tabla<Nodo> lstTmpNodo;
		lstTmpNodo.Insertar(lstNodo);//guardamos todos los nodos en un listado temporal,para ir sacando de este listado todos los nodos que se van asignando a una ruta

		int numeroRuta=0;

		Ruta *rut= new Ruta(++numeroRuta,dia);//insertar primera ruta
		lstRutatmp->Insertar(rut);//insertar la ruta al listado de Rutas temporal
		do
		{
			int indice = random(0,lstTmpNodo.GetLength()-1);//obtener un nodo al azar

			//si el nodo no tiene inventario para este dia, no se agrega a ninguna ruta
			if(lstTmpNodo.Get(indice)->GetCantidadRecoger(dia)<=0)
			{
				lstTmpNodo.Remover(lstTmpNodo.Get(indice));//quitamos de la lista
				continue;
			}
			if(
				rut->TotalCantidadRecoger()+lstTmpNodo.Get(indice)->GetCantidadRecoger(dia)<=capacidadVehiculo//si la total cantidadRecoger de la ruta + la demanda del nodo, no supera la capacidad del vehiculo
				&& rut->nodos.GetLength()<maxNodoRuta //la cantidad de nodos por ruta no supere maxNodoRuta
				)
			{
				rut->nodos.Insertar(lstTmpNodo.Get(indice));//insertamos a la ruta
				lstTmpNodo.Remover(lstTmpNodo.Get(indice));//quitamos de la lista
			}

			else
			{
				//si hay un nodo que puede agregar a alguna ruta existente, se adiciona y no se crea nueva ruta
				bool existe = false;

				for (int i = 0; i < lstRutatmp->GetLength(); i++)
				{
					if(lstRutatmp->Get(i)->nodos.GetLength()<maxNodoRuta && lstRutatmp->Get(i)->GetDia()==dia)//OJO: para poder agregar el nodo a la ruta, deben ser del mismo dia
					{
						if(lstRutatmp->Get(i)->TotalCantidadRecoger()+ lstTmpNodo.Get(indice)->GetCantidadRecoger(dia)<=capacidadVehiculo)
						{
							lstRutatmp->Get(i)->nodos.Insertar(lstTmpNodo.Get(indice));
							lstTmpNodo.Remover(lstTmpNodo.Get(indice));
							existe = true;
							break;
						}
					}
				}


				if(!existe)//si no se encontro una ruta, para agregarlo, se adiciona una nueva
				{
					//creamos nueva Ruta
					rut = new Ruta(++numeroRuta,dia);
					//insertar al listado de rutas
					lstRutatmp->Insertar(rut);
					rut->nodos.Insertar(lstTmpNodo.Get(indice));//insertamos a la ruta
					lstTmpNodo.Remover(lstTmpNodo.Get(indice));//quitamos de la lista
				}
			}
		}
		while(lstTmpNodo.GetLength()>0);//se debe repetir, hasta que no queden nodos sin rutas
	}
	return lstRutatmpGeneral;
}

#endif