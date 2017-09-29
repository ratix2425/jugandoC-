#ifndef ClassTabla
#define ClassTabla

template <class T>
class Tabla {
public:
	int lenght;

	Tabla(void);
	~Tabla();
	//Inserta Nuevo Clase y retorna el indice donde se inserta el registro
	int Insertar(T &row);
	void Remover(T *row);
	void Remover(int nElem);
	//traer objeto, con el indice
	T *Get(int indice);
private:
	//Array de punteros
	T **pT;

};

// Definición:
template <class T>
Tabla<T>::Tabla(void) {
	this->lenght = 0;
}

template <class T>
Tabla<T>::~Tabla() {
	delete[] pT;
}

template <class T>
int Tabla<T>::Insertar(T &row) {
	
	int indice = lenght;
	T **newA= new T*[lenght+1];

	for (int i = 0; i < lenght; i++)
	{
		newA[i]=pT[i];
	}
	newA[indice]=&row;
	lenght++;

	delete[] pT;//borrar el array anterior

	pT= newA;//Asignar nueva ubicacion de memoria de los Array
	newA = NULL;

	return indice;
}

template <class T>
void Tabla<T>::Remover(T *row){

}

template <class T>
void Tabla<T>::Remover(int nElem) {
	
}

template <class T>
T *Tabla<T>::Get(int indice) { 
		if(indice>=lenght || indice<0)
		{
			throw "está saliendo de los índices de la Tabla";
		}
		return &*pT[indice];
}
#endif