#ifndef SISTEMA_H
#define SISTEMA_H

#define MAX_NOM 15
#define MAX_TEXT 55
typedef char* Cadena;
enum retorno
{
	OK, ERROR, NO_IMPLEMENTADA
};
typedef enum retorno TipoRet;
enum TipoArchivo
{
	
	DIRECTORIO,ARCHIVO
		
};
typedef enum TipoArchivo Tipo;
struct archivo 
{
	Cadena nombreArchivo = new char[MAX_NOM+1];
	Cadena texto = new char[MAX_TEXT+1];
	enum TipoArchivo Tipo;
	bool escritura = false;
	bool lectura = true;
	archivo *siguienteArchivo;
	
};
typedef archivo *Archivo;

struct directorio
{
	Cadena nombreDirectorio = new char[MAX_NOM+1];
	directorio *siguienteDirectorio;
	directorio *hijoDirectorio;
	Archivo siguienteDirectorioArchivo;
};
typedef directorio *Directorio;
struct sistema
{
	Archivo puenteArchivo;
	Directorio puenteRaiz;
	Directorio puenteDirectorio;
};
typedef sistema *Sistema;

//---------------------------------Pilas-----------------------------------------------
struct nodoPilaPalabra{
	Cadena palabra;
	nodoPilaPalabra *siguiente;
};

typedef nodoPilaPalabra *pilaPalabra;

void menu();
pilaPalabra crearNodoPalabra(Cadena);
void apilarPalabra(pilaPalabra &, pilaPalabra);
pilaPalabra cimaPalabra(pilaPalabra);
pilaPalabra desapilarPalabra(pilaPalabra&);


//--------------------------------------------------------------------------------

Cadena rutaActual(Sistema);
TipoRet dir(Sistema &, Cadena);
TipoRet Delete(Sistema &, Cadena);
TipoRet IFF(Sistema &, Cadena, Cadena);
TipoRet createFile(Sistema &, Cadena );
TipoRet attrib(Sistema& , Cadena , Cadena);
TipoRet type(Sistema & , Cadena);
void minuscula(Cadena);
TipoRet cd(Sistema &, Cadena);
bool inOrden(Directorio, bool, Directorio, pilaPalabra&);
TipoRet mkdir(Sistema &, Cadena );
TipoRet rmdir (Sistema &, Cadena );
void borrarRecursivo(Directorio, Directorio);
int padreRecursivo(Directorio, int&, Directorio&);
void dirRecursivo(Directorio, pilaPalabra, pilaPalabra, Archivo);
void existeDirRecursivo(Directorio, Directorio&, Cadena, pilaPalabra&, pilaPalabra&);
TipoRet destruirSistema(Sistema &);
void destruirSistemaRecursivo(Directorio);
TipoRet move(Sistema & , Cadena, Cadena);
#endif
