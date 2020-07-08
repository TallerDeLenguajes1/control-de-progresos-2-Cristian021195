#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



typedef struct TDocumento{
	int CantidadDePaginas;
	char *TipoDeDocumento;
	int Volumen;	
}TDocumento;

typedef struct Tnodo{
	TDocumento Documento;
	struct Tnodo *Siguiente;
}Tnodo;

char TipoDeDocumento[2][12] = {"INTERNO","PUBLICO"};
#define CantDocumentos 10
/*					42
 * crear lista null
 * 3 listas de documentos
 * crear documento
 * crearNodo
 * insertar nodo a lista
 * quitar nodo de lista
 * distribuye documentos*/
Tnodo * crearListaVacia();
TDocumento CrearDocumento(int _CantidadDePaginas, char *_TipoDeDocumento, int _Volumen);
Tnodo * CrearNodo(TDocumento Tdoc);
void InsertarNodoALaLista(Tnodo **Lista, Tnodo *Nodo);
Tnodo * QuitarNodoDeLaLista(Tnodo **Lista);
void DistribuyeDocumentos(Tnodo **ListaPrincipal, Tnodo **ListaPPublico, Tnodo **ListaPInterno);
int ContarCantDeNodos(Tnodo *Lista);
void mostrarContenido(Tnodo *Lista);

int main(){
	Tnodo *ListaPrincipal = crearListaVacia();
	Tnodo *ListaPInterno = crearListaVacia();
	Tnodo *ListaPPublico = crearListaVacia();
	TDocumento dAux;
	Tnodo *NNodo;
	srand(time(0));
	
	for(int i = 0; i<CantDocumentos; i++){
		//CrearDocumento
		dAux = CrearDocumento((rand() %500) + 1, TipoDeDocumento[rand() %2], (rand() %10) +1);
		//printf("%s\n", dAux.TipoDeDocumento);
		
		//crearNodo
		NNodo = CrearNodo(dAux);
		//printf("%s\n", NNodo->Documento.TipoDeDocumento);
		//insertar a la lista
		InsertarNodoALaLista(&ListaPrincipal, NNodo);
	}
	
	DistribuyeDocumentos(&ListaPrincipal, &ListaPPublico, &ListaPInterno);//COMO ES PUNTERO DOBLE.
	printf("\nTOTAL: %d", ContarCantDeNodos(ListaPrincipal));
	printf("\nPUBLICO: %d", ContarCantDeNodos(ListaPPublico));
	printf("\nINTERNO: %d \n -------------- \n ", ContarCantDeNodos(ListaPInterno));
	
	mostrarContenido(ListaPPublico);
	mostrarContenido(ListaPInterno);
	//lista test
	
return 0;
}
void mostrarContenido(Tnodo *Lista){
	while(Lista != NULL){
		printf("TIPO: %s\n", Lista->Documento.TipoDeDocumento);
		printf("PAGINAS: %d\n", Lista->Documento.CantidadDePaginas);
		printf("VOLUMEN: %d\n", Lista->Documento.Volumen);
		Lista = Lista->Siguiente;
	}
}
int ContarCantDeNodos(Tnodo *Lista){//puntero simple. no es doble porque no queremos modificar lo que hay dentro de c nodo
	
	int contador=0;
	while(Lista != NULL){
		contador++;
		Lista = Lista->Siguiente;
	}
	return contador;
}
void DistribuyeDocumentos(Tnodo **ListaPrincipal, Tnodo **ListaPPublico, Tnodo **ListaPInterno){
	Tnodo *Aux;
	while(*ListaPrincipal){
		//obtener el nodo de la cabecera
		Aux = QuitarNodoDeLaLista(ListaPrincipal);
		//comparar el campo
		if(strcmp(Aux->Documento.TipoDeDocumento, TipoDeDocumento[0]) == 0){
			InsertarNodoALaLista(ListaPInterno, Aux);
		}else{
			InsertarNodoALaLista(ListaPPublico, Aux);
		}
	}
}
Tnodo * QuitarNodoDeLaLista(Tnodo **Lista){//saca un nodo de la lista en particular, y devuelve el nodo para que trabajemos.
	Tnodo *Aux = *Lista;// A aux lo hace apuntar a &lista como es un puntero doble solo nos interesa recorrerlo, por eso el *lista
	if(*Lista != NULL){
		//*Lista = (*Lista)->Siguiente;
		*Lista = (*Lista)->Siguiente;
		Aux->Siguiente = NULL;//a cada nodo retirado, lo dejamos apuntando a null como uno independiente
	}return Aux;
	
}
void InsertarNodoALaLista(Tnodo **Lista, Tnodo *Nodo){
	Nodo->Siguiente = *Lista;
	*Lista = Nodo;
}

Tnodo * CrearNodo(TDocumento Tdoc){//es diferente a la que vimos porque creamos los nodos todos apuntando a null y luego los unimos no pertenecen a ninguna lista.
	Tnodo * aux = (Tnodo *)malloc(sizeof(Tnodo));
	aux->Documento.CantidadDePaginas = Tdoc.CantidadDePaginas;
	aux->Documento.TipoDeDocumento = Tdoc.TipoDeDocumento;
	aux->Documento.Volumen = Tdoc.Volumen;
	aux->Siguiente = NULL;
	
	return aux;
}
TDocumento CrearDocumento(int _CantidadDePaginas, char *_TipoDeDocumento, int _Volumen){
	TDocumento dAux;
	dAux.CantidadDePaginas = _CantidadDePaginas;
	dAux.TipoDeDocumento = _TipoDeDocumento;
	dAux.Volumen = _Volumen;
	
	return dAux;
}


Tnodo * crearListaVacia(){
	return NULL;
}
