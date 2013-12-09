//Jose Alberto Esquivel Patino A01139626
//Estructura de Datos
//Examen 2
//Ing. Roman Martinez
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TAMDEFAULT 100  

//Implementaci�n del nivel f�sico de un ABB
template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
		bool converso;
public:
		ABB() { raiz = NULL; converso = false; }
		ABB(bool es_converso) { raiz = NULL; converso = es_converso; }
		NodoArbol<T>* getRaiz() { return raiz; } 
		void inserta (T dato);
		void despliega() { inorden(raiz); }
		int cuenta () { return contar(raiz); }
		int altura () { return niveles(raiz); }
		double promedioComparaciones (NodoArbol<T>* raiz, int comparaciones, int nodos);
		int sumaComparacionesCorreccion (NodoArbol<T>* raiz, int comparaciones);
		int contarNodosConDosHijos(NodoArbol<T>* inicial);	
		bool masDe30PorcientoNodosConDosHijos() { return ( contarNodosConDosHijos(raiz)*1.0/contar(raiz) > .3 ); } 
		bool busqueda (T dato);
		~ABB() { libera(raiz); }
};

template <class T>
double ABB<T>::promedioComparaciones (NodoArbol<T>* raiz, int comparaciones, int nodos)
{
	if (raiz != NULL) {
		return (
			 1.0*comparaciones/nodos 
			 + promedioComparaciones(raiz->izq, comparaciones+1, nodos)
			 + promedioComparaciones(raiz->der, comparaciones+1, nodos)
		);
	}else{
		return 0.0;
	}
}

template <class T>
int ABB<T>::sumaComparacionesCorreccion (NodoArbol<T>* raiz, int comparaciones)
{
	if (raiz != NULL) {
		return (
			 comparaciones 
			 + sumaComparacionesCorreccion(raiz->izq, comparaciones+1)
			 + sumaComparacionesCorreccion(raiz->der, comparaciones+1)
		);
	}else{
		return 0;
	}
}

template <class T>
int ABB<T>::contarNodosConDosHijos(NodoArbol<T>* inicial)
{
	if (inicial != NULL) {
		if (inicial->der != NULL && inicial->izq != NULL) {
			return 1+contarNodosConDosHijos(inicial->der)+contarNodosConDosHijos(inicial->izq);
		} else {
			return 0+contarNodosConDosHijos(inicial->der)+contarNodosConDosHijos(inicial->izq);
		}
	} else{
		return 0;
	}
}

template <class T>
void libera (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void inorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		inorden(raiz->izq);
		cout << raiz->info <<" ";
		inorden(raiz->der);
	}
}

template <class T>
void inordenconverso (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		inordenconverso(raiz->izq);
		cout << raiz->info <<" ";
		inordenconverso(raiz->der);
	}
}

template <class T>
void preorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		cout << raiz->info <<" ";
		preorden(raiz->izq);
		preorden(raiz->der);
	}
}

template <class T>
void preordenconverso (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		cout << raiz->info <<" ";
		preordenconverso(raiz->der);
		preordenconverso(raiz->izq);
	}
}

template <class T>
void posorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		posorden(raiz->izq);
		posorden(raiz->der);
		cout << raiz->info <<" ";
	}
}

template <class T>
void posordenconverso (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		posordenconverso(raiz->der);
		posordenconverso(raiz->izq);
		cout << raiz->info <<" ";
	}
}

template <class T>
int contar (NodoArbol<T>* raiz)
{
	if (raiz == NULL)
		return 0;
	return(1+contar(raiz->izq)+contar(raiz->der));
}

template <class T>
int niveles (NodoArbol<T>* raiz)
{
	int altizq, altder;
	if (raiz == NULL)  return 0;
	altizq = niveles(raiz->izq);
	altder = niveles(raiz->der);
	return(1 + (altizq>altder? altizq : altder));
}

template <class T>
void ABB<T>::inserta (T valor)
{
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		if (converso) {
			actual=(actual->info<valor? actual->izq: actual->der);
		}else{
			actual=(actual->info>valor? actual->izq: actual->der);
		}
	}
	if (anterior==NULL){
		raiz = NuevoNodo;
	}else{
		if (converso) {
			if (anterior->info < valor)
				anterior->izq = NuevoNodo;
			else
				anterior->der = NuevoNodo;

		}else{
			if (anterior->info > valor)
				anterior->izq = NuevoNodo;
			else
				anterior->der = NuevoNodo;
		}
	}
}

template <class T>
bool ABB<T>::busqueda (T valor)
{
	NodoArbol<T> *aux = raiz; 
	int comparaciones = 1;
	while(aux != NULL && aux->info!=valor){
		if(converso){
			if(aux->info < valor){
				aux = aux->izq;
			}else{
				aux = aux->der;
			}
		}else{
			if(aux->info > valor){
				aux = aux->izq;
			}else{
				aux = aux->der;
			}

		}
		comparaciones++;
	}
	if(aux==NULL){
		cout<<"Tomaron "<<comparaciones<<" comparaciones para averiguar que el dato "<<valor<< " no existe en el arbol."<<endl;
		return false;
	}else{
		cout<<"Tomaron "<<comparaciones<<" comparaciones para encontrar el dato "<<valor<<"."<<endl;
		return true;
	}
}

// Implementaci�n del nivel f�sico de una Tabla de Hash

template <class T>
class tablaHash
{
private:
	ABB<T> *tabla;
	int cantidad;
	int TAM; 
	
public:
	tablaHash() {cantidad = 0; TAM = TAMDEFAULT; tabla = new ABB<T>[TAM];}
	tablaHash(int tamanio) {cantidad = 0; TAM = tamanio; tabla = new ABB<T>[TAM];}
	void inserta (T dato);
	void inserta2 (T dato);
	void despliega ();
	double promedioComparaciones ();
	double promedioComparacionesCorreccion ();
	double promedioComparacionesListaSecuencial ();
	double eficienciaBucketsConDosHijos ();
};

template <class T>
void tablaHash<T>::inserta (T dato)
{
	int posicion = dato / 100 % TAM;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
void tablaHash<T>::inserta2 (T dato)
{
	int posicion = 0;
	posicion = dato%10 + dato/10%10 + dato/100%10 + dato/1000%10 + dato/10000%10 + dato/100000%10;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
double tablaHash<T>::promedioComparaciones()
{
	int indice = 0, contador = 0;
	double tempPromedioBucket = 0, suma = 0;
	while (indice < TAM) {
		tempPromedioBucket = 0;
		if(tabla[indice].cuenta() != 0 ){
			tempPromedioBucket = tabla[indice].promedioComparaciones(tabla[indice].getRaiz(), 1, tabla[indice].cuenta());
			suma += tempPromedioBucket;
			contador++;
		}
		indice++;
	}
	return suma/contador;
}

template <class T>
double tablaHash<T>::promedioComparacionesCorreccion()
{
	int indice = 0;
	double tempPromedioBucket = 0, suma = 0;
	while (indice < TAM) {
		tempPromedioBucket = 0;
		if(tabla[indice].cuenta() != 0 ){
			tempPromedioBucket = tabla[indice].sumaComparacionesCorreccion(tabla[indice].getRaiz(), 1);
			suma += tempPromedioBucket;
		}
		indice++;
	}
	return suma/cantidad;
}

template <class T>
void tablaHash<T>::despliega()
{
	cout << "Cantidad de datos: "<<cantidad<<"\n";
	for (int i = 0; i < TAM; i++)
	{
   	   cout << "Posicion "<<i<<": "<<tabla[i].cuenta()<<" datos en "<<tabla[i].altura()<<" niveles ";
	   tabla[i].despliega();
	   cout << "\n";
	}
}

template <class T>
double tablaHash<T>::promedioComparacionesListaSecuencial()
{
	int indice = 0, contador = 0;
	double tempPromedioBucket = 0, suma = 0;
	while (indice < TAM) {
		tempPromedioBucket = 0;
		if(tabla[indice].cuenta() != 0 ){
			int indiceLista = tabla[indice].cuenta();
			int temp = indiceLista;
			while(temp>0){
				tempPromedioBucket += temp;	
				temp--;
			}
			tempPromedioBucket /= indiceLista;
			suma += tempPromedioBucket;
			contador++;
		}
		indice++;
	}
	return suma/contador;
}

template <class T>
double tablaHash<T>::eficienciaBucketsConDosHijos ()
{
	int i = 0, suma = 0, bucketsLlenos = 0;
	while (i < TAM) {
		if(tabla[i].cuenta()>0){
			if (tabla[i].masDe30PorcientoNodosConDosHijos()) {
				suma+=1;
			}
			bucketsLlenos+=1; 
		}
		i++;		
	}
	cout<<" Estos son los buckets con mas de 30 porciento de sus nodos con dos hijos: : " << suma<<endl;
	cout<<" Estos son los buckets llenos: " << bucketsLlenos<<endl;
	cout<<" Este es el tamanio de la tabla: " << TAM<<endl;
	return (suma*1.0/bucketsLlenos);
}

// Implemetaci�n del programa de aplicaci�n
int main()
{
	ifstream arch;
	string nomarch;
	int dato;
	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;

	arch.open(nomarch.c_str());

	// ABB<int> arbolNormal;
	// ABB<int> arbolConverso(true);
	tablaHash<int> tabla;
	tablaHash<int> tabla2;
	while (!arch.eof())
	{
		
		//es para evitar leer lineas en blanco
		if (arch >> dato) {
			// aqui se inserta el dato en la estructura de datos que se desee.
			// arbolNormal.inserta(dato);
			// arbolConverso.inserta(dato);
			tabla.inserta(dato);
			// tabla2.inserta2(dato);
		}
	}
	arch.close();
	// cin>>nomarch;
	
	//PROBLEMA 3 y 4 =============================
	cout<<"Esta es la tabla Hash 1"<<endl;	
	tabla.despliega();
	cout<<"Promedio de comparaciones: "<<tabla.promedioComparaciones()<<endl;
	cout<<"Promedio de comparaciones correccion: "<<tabla.promedioComparacionesCorreccion()<<endl;
	cout<<"Promedio de comparaciones lista secuencial: "<<tabla.promedioComparacionesListaSecuencial()<<endl;

	cout<<" Eficiencia de un bucket con 2 hijos: "<<endl;
	cout<<tabla.eficienciaBucketsConDosHijos()<<endl;

	// cout<<"Esta es la tabla Hash 2"<<endl;	
	// tabla2.despliega();
	// cout<<"Promedio de comparaciones: "<<tabla2.promedioComparaciones()<<endl;
	//PROBLEMA 1 y 2 =============================
	// cout<<"ARBOL NORMAL"<<endl;
	// arbolNormal.despliega();
	// cout<<endl;
	// 
	// cout<<"ARBOL CONVERSO"<<endl;
	// arbolConverso.despliega();
	// cout<<endl;

	// cout<<"ARBOL NORMAL"<<endl;
	// cout<<"La altura del arbol normal es de: "<<arbolNormal.altura()<<endl;
	// cout<<"La raiz del arbol normal es: "<<arbolNormal.getRaiz()->info<<endl;
	// arbolNormal.busqueda(143012);

	// cout<<"\nRecorrido inorden: ";
	// inorden(arbolNormal.getRaiz());
	// cout<<"\nRecorrido preorden: ";
	// preorden(arbolNormal.getRaiz());
	// cout<<"\nRecorrido posorden: ";
	// posorden(arbolNormal.getRaiz());
	// cout<<endl;
	// cout<<endl;

	// cout<<"Promedio de comparaciones en arbol normal: ";
	// cout<<arbolNormal.promedioComparaciones(arbolNormal.getRaiz(), 1, arbolNormal.cuenta())<<endl;
	// cout<<endl;

	// cout<<"ARBOL CONVERSO"<<endl;
	// cout<<"La altura del arbol converso es de: "<<arbolConverso.altura()<<endl;
	// cout<<"La raiz del arbol converso es: "<<arbolConverso.getRaiz()->info<<endl;
	// arbolConverso.busqueda(143012);

	// cout<<"\nRecorrido inorden: ";
	// inorden(arbolConverso.getRaiz());
	// cout<<"\nRecorrido preorden: ";
	// preorden(arbolConverso.getRaiz());
	// cout<<"\nRecorrido posorden: ";
	// posorden(arbolConverso.getRaiz());
	// cout<<"\nRecorrido preorden converso: ";
	// preordenconverso(arbolConverso.getRaiz());
	// cout<<"\nRecorrido posorden converso: ";
	// posordenconverso(arbolConverso.getRaiz());
	// cout<<endl;
	// cout<<endl;

	// cout<<"Promedio de comparaciones en arbol converso: ";
	// cout<<arbolConverso.promedioComparaciones(arbolConverso.getRaiz(), 1, arbolConverso.cuenta())<<endl;
	// cout<<endl;

	return 0;
}


