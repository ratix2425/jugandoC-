#ifndef ValoresConstantes

#define ValoresConstantes
#define capacidadVehiculo 15
#define numeroNodos  10
#define numeroDias 2
#define maxNodoRuta 4
#define tiempoEjecucion 1 //en segundos
#define tiempoEjecucionIntercambioNodos 1 //en segundos
#define minimoNodoIntercambioRutas 3

//Funcion General
int random(int inicio, int final)
{
	return rand()%(final-inicio+1)+inicio;
}


#endif
