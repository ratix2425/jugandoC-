#ifndef ClassNodo
#define ClassNodo
//const  int cantidadDemanda=10;//cantidad de demandas  (dias)

class Nodo
{
public:

	int *lstDemanda;//puntero donde queda almacenada la  demanda para este nodo

	int capacidad;

	void Asignar(int dias)
	{
	 this->lstDemanda = new int[dias];//crear array dinamico, para almacenar la demanda
	}

	~Nodo(void)
	{
		if(this->lstDemanda)
		delete[] this->lstDemanda;
	}
};

#endif
