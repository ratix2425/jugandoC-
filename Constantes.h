#ifndef ValoresConstantes

#define ValoresConstantes
#define capacidadVehiculo 15
#define numeroNodos  10
#define numeroDias 2
#define maxNodoRuta 4
#define tiempoEjecucion 300 //en segundos


//Funcion General
int random(int inicio, int final)
{
	return rand()%(final-inicio+1)+inicio;
}
#endif
