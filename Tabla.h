#ifndef ClassTabla
#define ClassTabla

template <class T>
class Tabla {
private:
	int lenght;
	//Array de punteros
	T **_pT;

public:
	Tabla(void);
	~Tabla();
	//Inserta Nuevo Clase y retorna el indice donde se inserta el registro
	int Insertar(T &row);//Insertar por referencia
	int Insertar(T *row);//Insertar por Puntero
	int Insertar(Tabla<T> &c);
	void Remover(T *row);
	void Remover(int nElem);

	int GetLength(){ return this->lenght;}
	//traer objeto, con el indice
	T *Get(int indice);

	int Totalizar(int (T::*metodo)());
	//al hacer un =, no llevarse la memoria, sino que copie los registros
	//Tabla<T> &operator=(Tabla<T> &c);
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
int Tabla<T>::Insertar(Tabla<T> &c) {
	int indice = lenght;
	if(this != &c) {
		if(c._pT) {
			//this->lenght=this->lenght+&c->lenght;
			//_pT= new T*[&c->lenght];

			for (int i = 0; i < c.lenght; i++)
			{
				this->Insertar(*c.Get(i));
			}
		}
		else _pT = NULL;
	}
	return indice;
}

template <class T>
void Tabla<T>::Remover(T *row){
	T **newA= new T*[lenght-1];


	for (int i = 0,x=0; i < lenght; i++)
	{
		if(_pT[i]!=row)
		{
			newA[x++]=_pT[i];
		}
	}
	lenght--;

	delete[] _pT;//borrar el array anterior

	_pT= newA;//Asignar nueva ubicacion de memoria de los Array
	newA = NULL;
}

template <class T>
void Tabla<T>::Remover(int nElem) {
	this->Remover(this->Get(nElem));
}

template <class T>
T *Tabla<T>::Get(int indice) { 
	if(indice>=lenght || indice<0)
	{
		throw "está saliendo de los índices de la Tabla";
	}
	return &*_pT[indice];
}


template <class T>
int Tabla<T>::Totalizar(int (T::*metodo)()){
	int suma = 0;
	for (int i = 0,x=0; i < lenght; i++)
	{
		suma +=(*_pT[i].*metodo)();
	}
	return suma;
}
/*
template <class T>
Tabla<T> &Tabla<T>::operator=(Tabla<T> &c) {
if(this != &c) {
delete[] _pT;
lenght=0;
if(c._pT) {
lenght=c.lenght;
_pT= new T*[c.lenght];

for (int i = 0; i < lenght; i++)
{
_pT[i]=c.Get(i);
}
}
else _pT = NULL;
}
return *this;
}*/
#endif