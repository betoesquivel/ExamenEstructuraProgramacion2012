/*
 * =====================================================================================
 *
 *       Filename:  listaDoblementeEncadenadaCircular.cpp
 *
 *    Description:  contiene implementacion y prueba de mi lista doblemente encadenada circular
 *    con un metodo para meter y sacar. 
 *
 *        Version:  1.0
 *        Created:  12/08/2013 04:41:51 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jose Alberto Esquivel Patino (), 
 *   Organization:  ITESM Campus Monterrey
 *
 * =====================================================================================
 */
#include <iostream>
using namespace std;

template <class T>
class NodoPilaDEC
{ 
	public:
		T info;
		NodoPilaDEC<T> *frente;
		NodoPilaDEC<T> *atras;
		NodoPilaDEC() {frente = atras = NULL;}
		NodoPilaDEC(T dato) {info = dato; frente = atras = NULL;}
};

template <class T>
class PilaDEC
{
	private:
		NodoPilaDEC<T>* TOPE;
		int tamanio; 
	public: 
		PilaDEC(){TOPE = NULL; tamanio = 0;}
		PilaDEC(T dato){TOPE = new NodoPilaDEC<T>(dato); tamanio = 1;}
		bool meter(T dato);
		bool sacar();
		int tam() { return tamanio; } 
		bool vacia() { return (TOPE==NULL); } 
		NodoPilaDEC<T>* tope(){ return TOPE; }
		~PilaDEC(){
			while(TOPE!=NULL){
				sacar();
			}
		}
};

template <class T>
bool PilaDEC<T>::meter(T dato)
{
	NodoPilaDEC<T> *nuevo = new NodoPilaDEC<T>(dato);
	if (nuevo==NULL) {
		return false; 
	}
	if (TOPE!=NULL) {
		nuevo->frente = TOPE->frente;
		nuevo->atras = TOPE;
		TOPE->frente = nuevo;

		TOPE = nuevo;
		TOPE->frente->atras = TOPE; 
	} else {
		TOPE = nuevo;
		TOPE->frente = TOPE->atras = TOPE;
	}
	tamanio+=1; 
	return true; 
}

template <class T>
bool PilaDEC<T>::sacar()
{
	if(TOPE==NULL){
		return false; 
	}else {
		NodoPilaDEC<T> *aux = TOPE; 
		
		if (TOPE->atras != TOPE) {
			TOPE = TOPE->atras; 
			TOPE->frente = aux->frente;
			TOPE->frente->atras = TOPE;

		}else {
			TOPE = NULL;
		}
		delete aux; 
		tamanio-=1;
		return true; 
	}
}

template <class T>
class dobleFila
{
	private:
		PilaDEC<T> frente;
		PilaDEC<T> atras;
	public:
		dobleFila(){};
		bool meterfrente(T dato) {return frente.meter(dato);}
		bool meteratras(T dato) {return atras.meter(dato);}
		bool sacarfrente();
		bool sacaratras();
		void balancearAtras();
		void balancearFrente();
		bool vacia(){ return (frente.vacia() && atras.vacia()); }
		NodoPilaDEC<T>* verFrente(){return frente.tope();}
		NodoPilaDEC<T>* verAtras(){return atras.tope();}
};

template <class T>
bool dobleFila<T>::sacarfrente() 
{
	bool exito;
	if(frente.vacia() && !atras.vacia()){
		// cout<<"Balanceo frente." <<endl;
		balancearFrente();
	}
	exito = frente.sacar();
	if(frente.vacia() && !atras.vacia()){
		// cout<<"Balanceo frente despues de sacar." <<endl;
		balancearFrente();
	}

	return exito;
}

template <class T>
bool dobleFila<T>::sacaratras() 
{
	bool exito;
	if(atras.vacia() && !frente.vacia()){
		balancearAtras();
	}
	exito = atras.sacar();
	if(atras.vacia() && !frente.vacia()){
		balancearAtras();
	}

	return exito;
}

template <class T>
void dobleFila<T>::balancearAtras(){
	//cuando la pila de atras esta vacia y la de en frente no.
	int contador = 0;
	PilaDEC<T> temp;
	int tam = frente.tam()/2;
	while (contador < tam) {
		temp.meter(frente.tope()->info);
		frente.sacar();
		contador++;		
	}

	while(!frente.vacia()){
		atras.meter(frente.tope()->info);
		frente.sacar();
	}
	while(!temp.vacia()){
		frente.meter(temp.tope()->info);
		temp.sacar();
	}
}

template <class T>
void dobleFila<T>::balancearFrente(){
	//cuando la pila de en frente esta vacia y la de atras no.
	int contador = 0;
	PilaDEC<T> temp;
	int tam = atras.tam()/2;
	while (contador < tam) {
		temp.meter(atras.tope()->info);
		atras.sacar();
		contador++;		
	}

	while(!atras.vacia()){
		frente.meter(atras.tope()->info);
		atras.sacar();
	}
	while(!temp.vacia()){
		atras.meter(temp.tope()->info);
		temp.sacar();
	}
}

int main(int argc, const char *argv[])
{
	cout<<"Hello World." <<endl;	
	// int count = 10;
	// PilaDEC<int> miPila;
	// while (count > 0) {
	// 	miPila.meter(count);
	// 	
	// 	count--;		
	// }
	// cout<<miPila.tam()<<endl;
	// count = 0;
	// while (count < 10) {
	// 	cout<<miPila.tope()->info<<endl;
	// 	miPila.sacar();	
	// 	count++;		
	// }
	dobleFila<int> miDobleFila;
	int count = 10;
	while (count > 0) {
		miDobleFila.meteratras(count);
		count--;		
	}
	count = 11;
	while (count < 20) {
		miDobleFila.meterfrente(count);
		count++;		
	}
	count = 0;
	while (count < 20) {
		cout<<miDobleFila.verFrente()->info<<endl;
		miDobleFila.sacarfrente();
		count++;		
	}
	return 0;
}
