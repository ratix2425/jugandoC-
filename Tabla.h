#ifndef ClassTabla
#define ClassTabla

template <class T>
class Tabla {
public:
	int lenght;

	Tabla(void);
	~Tabla();
	//Inserta Nuevo Clase y retorna el indice donde se inserta el registro
	int Insertar(T &row);//Insertar por referencia
	int Insertar(T *row);//Insertar por Puntero
	void Remover(T *row);
	void Remover(int nElem);
	//traer objeto, con el indice
	T *Get(int indice);
private:
	//Array de punteros
	T **_pT;

};

// Definición:
template <class T>
Tabla<T>::Tabla(void) {
	this->lenght = 0;
}

template <class T>
Tabla<T>::~Tabla() {
	delete[] _pT;
}

template <class T>
int Tabla<T>::Insertar(T &row) {//Referencia de Memoria
	return this->Insertar(&row);//Inserto Con el puntero -> esta llamando a Tabla<T>::Insertar(T *row)
}


template <class T>
int Tabla<T>::Insertar(T *row) {
	
	int indice = lenght;
	T **newA= new T*[lenght+1];

	for (int i = 0; i < lenght; i++)
	{
		newA[i]=_pT[i];
	}
	newA[indice]=row;
	lenght++;

	delete[] _pT;//borrar el array anterior

	_pT= newA;//Asignar nueva ubicacion de memoria de los Array
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
		return &*_pT[indice];
}
#endif