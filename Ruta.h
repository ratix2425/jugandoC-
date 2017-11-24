#ifndef ClassRuta
#define ClassRuta


#include "Tabla.h"
#include "Nodo.h"
#include "Win.h"

class Ruta
{

private:
	int _nDia;

	int _numeroRuta;

public:

	Ruta(int numeroRuta, int nDia);

	~Ruta()
	{
		nodos.Clear();
	}

	Tabla<Nodo> nodos;

	int GetRuta();

	int GetDia();

	int TotalDemanda();

	int TotalCantidadRecoger();

	int TotalDistancia();

	int TotalInventario();

	void Imprimir();

	static Tabla<Tabla<Ruta>> *GenerarRuta(Tabla<Nodo> &lstNodo);

	static void IntercambioNodos(Tabla<Tabla<Ruta>> *lstRuta);
};

Ruta::Ruta(int numeroRuta, int nDia)
{
	_numeroRuta=numeroRuta;
	_nDia = nDia;
}

int Ruta::GetRuta()
{
	return _numeroRuta;
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

int Ruta::TotalCantidadRecoger()
{
	int total = 0;

	for(int i=0;i<nodos.GetLength();i++)
	{
		total = total+nodos.Get(i)->GetCantidadRecoger(_nDia);
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

int Ruta::TotalInventario()
{
	int total = 0;

	for(int i=0;i<nodos.GetLength();i++)
	{
		total = total+nodos.Get(i)->GetInventario(_nDia);
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
	printf("\tTI: %d", this->TotalInventario());
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

void Ruta::IntercambioNodos(Tabla<Tabla<Ruta>> *lstRuta)
{
	Nodo *nodoPuente;
	Tabla<Ruta> *ruta;


	Debug("\nInicia Intercambio de Nodos\n");


	int cantidadRutas=0;

	//antes de poner a correr el tiempo revisamos, si algun dia, tiene rutas con mas de minimoNodoIntercambioRutas nodos y si no tiene que no realice ninguna accion aqui
	for(int i=0;i<lstRuta->GetLength();i++)
	{
		int cantidadNodo=0;

		cantidadRutas=0;
		ruta = lstRuta->Get(i);
		for(int r=0;r<ruta->GetLength();r++)
		{
			if(ruta->Get(r)->nodos.GetLength()>=minimoNodoIntercambioRutas)
			{
				cantidadNodo++;
			}

			if(cantidadNodo>=2)//para poder intercambiar, minimo debe haber 2 nodos.
			{
				cantidadRutas++;
				break;
			}
		}

		if(cantidadRutas>=1)//si hay almenos una ruta, que tenga 2 nodos
		{
			break;
		}
	}

	if(cantidadRutas==0)
	{
		Error("\nNo existen dias, que tenga mas de 2 rutas almenos con %d Nodos",minimoNodoIntercambioRutas);
		return;
	}


	unsigned tiempoEjecutado=clock();
	int segundosEjecucion=0;
	int ultimoSegundo=0;
	do
	{

		for(int i=0;i<lstRuta->GetLength();i++)
		{
			Debug("\nDia %d",i);

			//Obtener Rutas del Dia
			Tabla<Ruta> *ruta = lstRuta->Get(i);


			//revisar si en este dia hay mas de 2 rutas que tengan 3 nodos

			int cantidadRutas=0;
			for(int r=0;r<ruta->GetLength();r++)
			{
				if(ruta->Get(r)->nodos.GetLength()>=minimoNodoIntercambioRutas)
				{
					cantidadRutas++;
				}

				if(cantidadRutas>=2)
				{
					break;
				}
			}

			//si la cantidad de rutas en el dia, no supera los 3 nodos, se pasa al siguiente dia
			if(cantidadRutas<2)//minimo debe haber 2 rutas
			{
				Error("\nNo tiene mas de %d nodos",minimoNodoIntercambioRutas);
				continue;
			}

			int indiceRuta1=-1;
			int indiceRuta2=-1;

			//Obtener indice para Ruta1, que tenga mas de minimoNodoIntercambioRutas nodos
			do
			{
				int azar = random(0,ruta->GetLength()-1);
				if(ruta->Get(azar)->nodos.GetLength()>=minimoNodoIntercambioRutas)
				{
					indiceRuta1 = azar;
				}
			}
			while (indiceRuta1<0);

			//Obtener indice para Ruta2, que tenga mas de minimoNodoIntercambioRutas nodos
			do
			{
				int azar = random(0,ruta->GetLength()-1);
				if(ruta->Get(azar)->nodos.GetLength()>=minimoNodoIntercambioRutas && indiceRuta1!=azar)
				{
					indiceRuta2 = azar;
				}

			}
			while (indiceRuta2<0);

			Debug("\nIntercambiar los siguientes rutas %d y %d", ruta->Get(indiceRuta1)->GetRuta(),  ruta->Get(indiceRuta2)->GetRuta());


			//Crea una Ruta Duplicada
			//Tabla<Ruta> *rutaDuplicada = new Tabla<Ruta>(*ruta);

			int nodoRuta1 = random(0,ruta->Get(indiceRuta1)->nodos.GetLength()-1);
			int nodoRuta3;

			do
			{
				nodoRuta3=random(0,ruta->Get(indiceRuta1)->nodos.GetLength()-1);
			}
			while (nodoRuta1==nodoRuta3);//para no escoger un nodo repetido

			int nodoRuta2 = random(0,ruta->Get(indiceRuta2)->nodos.GetLength()-1);
			int nodoRuta4;
			do
			{
				nodoRuta4=random(0,ruta->Get(indiceRuta2)->nodos.GetLength()-1);
			}
			while (nodoRuta2==nodoRuta4);//para no escoger un nodo repetido
			


			printf("\n*Actual*******************");
			ruta->Get(indiceRuta1)->Imprimir();
			ruta->Get(indiceRuta2)->Imprimir();
			int totalDistancia = ruta->Totalizar(&Ruta::TotalDistancia);
			Debug("\ntotal Distancia %d",totalDistancia);

			nodoPuente=ruta->Get(indiceRuta1)->nodos.Get(nodoRuta1);

			ruta->Get(indiceRuta1)->nodos.Set(nodoRuta1,ruta->Get(indiceRuta2)->nodos.Get(nodoRuta2));
			ruta->Get(indiceRuta2)->nodos.Set(nodoRuta2,nodoPuente);

			nodoPuente=ruta->Get(indiceRuta1)->nodos.Get(nodoRuta3);
			ruta->Get(indiceRuta1)->nodos.Set(nodoRuta3,ruta->Get(indiceRuta2)->nodos.Get(nodoRuta4));
			ruta->Get(indiceRuta2)->nodos.Set(nodoRuta4,nodoPuente);


			printf("\n*Nueva*******************");
			ruta->Get(indiceRuta1)->Imprimir();
			ruta->Get(indiceRuta2)->Imprimir();
			int totalDistanciaNueva = ruta->Totalizar(&Ruta::TotalDistancia);
			Debug("\ntotal Distancia %d",totalDistanciaNueva);


			BOOL valido = TRUE;


			//Verificar que las nuevas rutas aun respete, que no pueda superar la capacidad de vehiculo
			if(ruta->Get(indiceRuta1)->TotalCantidadRecoger()>capacidadVehiculo
				||
				ruta->Get(indiceRuta2)->TotalCantidadRecoger()>capacidadVehiculo
				)
			{
				Error("\nNo se Actualiza Ruta, la cantidad a recoger Supera la capacidad de vehiculo");
				valido=FALSE;
			}
			else if(totalDistanciaNueva>=totalDistancia)
			{
				Error("\nNo se Actualiza Ruta, La distancia Nueva es mayor a la Actual");
				valido=FALSE;
			}

			//Si no es Valido, se vuelve a dejar la ruta como estaba;
			if(!valido)
			{
				nodoPuente=ruta->Get(indiceRuta1)->nodos.Get(nodoRuta1);
				ruta->Get(indiceRuta1)->nodos.Set(nodoRuta1,ruta->Get(indiceRuta2)->nodos.Get(nodoRuta2));
				ruta->Get(indiceRuta2)->nodos.Set(nodoRuta2,nodoPuente);

				nodoPuente=ruta->Get(indiceRuta1)->nodos.Get(nodoRuta3);
				ruta->Get(indiceRuta1)->nodos.Set(nodoRuta3,ruta->Get(indiceRuta2)->nodos.Get(nodoRuta4));
				ruta->Get(indiceRuta2)->nodos.Set(nodoRuta4,nodoPuente);
			}
			else
			{
				Notice("\nSe actualiza Ruta");
			}

			printf("\n");

			//Validacion para intercambio de Nodos

			//delete rutaDuplicada;

		}
		ultimoSegundo=(int(clock()-tiempoEjecutado)/CLOCKS_PER_SEC);//evaluar cuantos segundos han corrido desde la vez que se inicio el ciclo

		if(ultimoSegundo!=segundosEjecucion)//si los segundos han cambiado
		{
			//LimpiarPantalla();
			printf("\nSegundos %d",(int(clock()-tiempoEjecutado)/CLOCKS_PER_SEC));//imprime el tiempo que lleva
			segundosEjecucion=ultimoSegundo;//actualizo los segundos que lleva ejecutando
		}
	}
	while(segundosEjecucion<=tiempoEjecucionIntercambioNodos);//realiza el ciclo hasta que llegue al tope de tiempo de ejecucion
}

//funcion puente para el intercambio
void cambio(int *x, int *y) { 
	int temp = *x;
	*x = *y;
	*y = temp;
}

//forma 1, invertir desde el ultimo indice al primero
void IntercambioNodosEntreRuta(int *arreglo,int cantidad,int sizeArray)
{
	for(int i=1;i<=cantidad;i++)
	{
		IntercambioNodosEntreRuta(arreglo,cantidad-1,sizeArray);

		if(i==cantidad)continue;//entra a la funcion intercambio, pero no necesito que realice el cambio, ni imprima valor, (es solo para que haga la llamada recursiva)
		
		cambio(&arreglo[sizeArray-i],&arreglo[sizeArray-cantidad]);

		//invertir el array, desde donde se hizo cambio
		for(int x=cantidad-1;x>1;x--)
		{
			cambio(&arreglo[sizeArray-x],&arreglo[sizeArray-(cantidad-x)]);
		}


		//imprimir
		for(int p=0;p<sizeArray;p++)
		{
			printf("%d",arreglo[p]);
		}
		printf("\n");
	}
}

/*
//forma 2, invertir desde el primer indice hasta el final
//mas facil de entender
void intercambio(int *arreglo,int cantidad,int sizeArray)
{
for(int i=1;i<=cantidad;i++)
{
intercambio(arreglo,cantidad-1,sizeArray);

if(i==cantidad)continue;//hace el intercambio pero no imprime el mismo valor
//printf("%d %d\n",i,cantidad);
cambio(&arreglo[i],&arreglo[cantidad]);

//invertir
for(int x=cantidad-1;x>1;x--)
{
cambio(&arreglo[x],&arreglo[cantidad-x]);
}

printf("\t%d%d%d%d\n",arreglo[1],arreglo[2],arreglo[3],arreglo[4]);
}
}
*/
#endif