#include <stdio.h>

#ifndef ClassArrayDinamico
#define ClassArrayDinamico
template <class T>
class ArrayDinamico
{
private:

	T **lstDistancia;//puntero donde va a quedar almacenado el array de las distancias

public:

	int lengthX;//tamaño del array
	int lengthY;
	//Constructor
	ArrayDinamico(int cantidadX,int cantidadY);
	//Retornar Valor de la matriz
	int Get(int origen, int destino);//traer valor del array

	//obtener los valores del listado para Y
	T* GetListY(int origen) { return lstDistancia[origen]; }

	//Asignar valor a la matriz
	void Set(int origen, int destino, T valor);//asignar valor del array

	//Imprimir Matriz
	void Imprimir(const char* formato);


	//destructor
	~ArrayDinamico(void)
	{
		for(int i = 0; i < lengthY; i++){
			delete[] this->lstDistancia[i];
		}
		delete[] this->lstDistancia;
	}
};

//Constructor
template <class T>
ArrayDinamico<T>::ArrayDinamico(int cantidadX,int cantidadY)//se crea un array de [cantidad][cantidad]
{
	this->lengthX = cantidadX;
	this->lengthY = cantidadY;

	this->lstDistancia = new T*[cantidadY];

	for(int i = 0; i < cantidadY; i++){
		this->lstDistancia[i] = new T[cantidadX]; 
	}
}

template <class T>
int ArrayDinamico<T>::Get(int origen, int destino)
{
	return this->lstDistancia[origen][destino];
}

template <class T>
void ArrayDinamico<T>::Set(int x, int y, T valor)//asignar valor del array
{
	if(x>=this->lengthX || y>=this->lengthY)
	{
		throw "asignar un valor mayor al tamaño de la distancia";
	}

	this->lstDistancia[y][x]=valor;
}

template <class T>
void ArrayDinamico<T>::Imprimir(const char* formato)
{
	//cabecera
	printf("\t");
	for (int i = 0; i < this->lengthX; i++)
	{
		printf("%d\t",i);
	}
	printf("\n");


	for (int y = 0; y < this->lengthY; y++)
	{
		printf("%d\t",y);//imprimir row
		for(int x=0;x<this->lengthX;x++)
		{
			printf(formato,lstDistancia[y][x]);//imprimir columna
			printf("\t");
		}
		printf("\n");
	}

}
#endif