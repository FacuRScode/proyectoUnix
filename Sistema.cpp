#include<iostream>
#include<stdio.h>
#include "Sistema.hpp"
#include <string.h>
//Laboratorio1

TipoRet IFF(Sistema & dirActual, Cadena nombreArchivoRecibido, Cadena textoArchivo)
{
	Archivo aux = NULL;
	aux = dirActual->puenteDirectorio->siguienteDirectorioArchivo;
	while(aux!=NULL)
	{
		if(strcmp(aux->nombreArchivo, nombreArchivoRecibido) == 0)
		{
			
			if(aux->lectura == true && aux->escritura == true)
			{
				if(strlen(aux->texto) + strlen(textoArchivo) <= MAX_TEXT)
				{
					strcat(textoArchivo, aux->texto);
					strcpy(aux->texto, textoArchivo);
					return OK;
				}
				else
				{
					printf("El texto es mayor al soportado por el archivo\n");
					return ERROR;
				}
				
			}
			else
			{
				printf("El archivo es solo tiene permisos de lectura\n");
				return ERROR;
			}
			
		}
		aux = aux->siguienteArchivo;
	}
	if(aux == NULL)
	{
		printf("El nombre del archivo que ingreso no existe en este directorio\n");
		return ERROR;
	}
	return OK;
}

TipoRet createFile(Sistema &raiz, Cadena nombre) {
	Directorio dRaiz = raiz->puenteDirectorio;
	
	if (strlen(nombre) > MAX_NOM) {
		printf("El nombre del archivo debe contener hasta 15 caracteres\n");
		return ERROR;
	}
	
	Archivo archivoExistente = dRaiz->siguienteDirectorioArchivo;
	while (archivoExistente != NULL) {
		if (strcmp(archivoExistente->nombreArchivo, nombre) == 0) {
			printf("Ya existe un archivo con ese nombre en este directorio\n");
			return ERROR;
		}
		archivoExistente = archivoExistente->siguienteArchivo;
	}
	
	Archivo archivoNuevo = new archivo;
	archivoNuevo->nombreArchivo = new char[MAX_NOM + 1];
	strcpy(archivoNuevo->nombreArchivo, nombre);
	archivoNuevo->texto = new char[MAX_TEXT + 1];
	strcpy(archivoNuevo->texto, "");
	archivoNuevo->Tipo = ARCHIVO;
	archivoNuevo->escritura = true;
	archivoNuevo->lectura = true;
	archivoNuevo->siguienteArchivo = NULL;
	
	if (dRaiz->siguienteDirectorioArchivo == NULL) {
		dRaiz->siguienteDirectorioArchivo = archivoNuevo;
	} else {
		Archivo auxArchivo = dRaiz->siguienteDirectorioArchivo;
		while (auxArchivo->siguienteArchivo != NULL) {
			auxArchivo = auxArchivo->siguienteArchivo;
		}
		auxArchivo->siguienteArchivo = archivoNuevo;
	}
	
	return OK;
}

TipoRet attrib(Sistema& raiz, Cadena archivo, Cadena atributo)
{
	Directorio dirActual = raiz->puenteDirectorio;
	Archivo auxArchivo = dirActual->siguienteDirectorioArchivo;
	
	if(auxArchivo == NULL)
	{
		printf("No hay arhivos en este directorio\n");
		return ERROR;
	}
	
	while (auxArchivo != NULL && strcmp(auxArchivo->nombreArchivo, archivo) != 0) {
		auxArchivo = auxArchivo->siguienteArchivo;
	}
	
	if (auxArchivo == NULL) {
		printf("Ese archivo no existe en este directorio\n");
		return ERROR;
	}
	
	
	if(strcmp(atributo, "+w") == 0)
	{
		if(auxArchivo->escritura == false)
		{
			auxArchivo->escritura = true;
			return OK;
		} else {
			return OK;
		}
	}
	
	if(strcmp(atributo, "-w") == 0)
	{
		if(auxArchivo->escritura == true)
		{
			auxArchivo->escritura = false;
			return OK;
		} else {
			return OK;
		}
	}
	return OK;
}



TipoRet type(Sistema & raiz, Cadena archivo)
{
	Directorio dirActual = raiz->puenteDirectorio;
	Archivo auxArchivo = dirActual->siguienteDirectorioArchivo;
	
	if (auxArchivo == NULL) {
		printf("Ese archivo no existe en este directorio\n");
		return ERROR;
	}
	
	while (auxArchivo != NULL && strcmp(auxArchivo->nombreArchivo, archivo) != 0) {
		auxArchivo = auxArchivo->siguienteArchivo;
	}
	
	if (auxArchivo == NULL) 
	{
		printf("Ese archivo no existe en este directorio\n");
		return ERROR;
	}
	
	
	if (strcmp(auxArchivo->texto, "") == 0) {
		printf("El archivo no tiene contenido\n");
		return OK;
	} else {
		printf("%s\n",auxArchivo->texto);
		return OK;
	}
	return OK;
}

TipoRet Delete (Sistema & dirActual, Cadena nombreArchivoRecibido)
{
	Archivo aux = NULL;
	Archivo borrar = NULL;
	aux = dirActual->puenteDirectorio->siguienteDirectorioArchivo;
	if(aux == NULL)
	{
		printf("El nombre del archivo que ingreso no existe en este directorio\n");
		return ERROR;
	}
	if(strcmp(aux->nombreArchivo, nombreArchivoRecibido) == 0)
	{
		if(aux->lectura == true && aux->escritura == true)
		{
			dirActual->puenteDirectorio->siguienteDirectorioArchivo = dirActual->puenteDirectorio->siguienteDirectorioArchivo->siguienteArchivo;
			delete aux;
			return OK;
		}
		else
		{
			printf("El archivo solo tiene permisos de lectura\n");
			return ERROR;
		}
	}
	while(aux->siguienteArchivo != NULL)
	{
		
		if(strcmp(aux->siguienteArchivo->nombreArchivo, nombreArchivoRecibido) == 0)
		{
			if(aux->siguienteArchivo->lectura == true && aux->siguienteArchivo->escritura == true)
			{
				borrar = aux->siguienteArchivo;
				aux->siguienteArchivo = borrar->siguienteArchivo;
				delete borrar;
				return OK;
			}
			else
			{
				printf("El archivo es solo tiene permisos de lectura\n");
				return ERROR;
			}
		}
		aux = aux->siguienteArchivo;
	}
	if(aux->siguienteArchivo == NULL)
	{
		printf("El nombre del archivo que ingreso no existe en este directorio\n");
		return ERROR;
	}
	return OK;
}

TipoRet dir(Sistema & dirActual, Cadena direccionActual)
{
	
	Sistema copia = NULL;
	Archivo archivos = NULL;
	Archivo aux = NULL;
	Directorio auxDir = NULL;
	aux = dirActual->puenteDirectorio->siguienteDirectorioArchivo;
	auxDir = dirActual->puenteDirectorio->hijoDirectorio;
	int parar = 0;
	pilaPalabra pil = NULL;
	pilaPalabra auxPila = NULL;
	if(strcmp(direccionActual, "/s") == 0)
	{
		dirRecursivo(dirActual->puenteDirectorio,pil, auxPila, archivos);
	}
	else
	{
		puts(direccionActual);
		if(aux == NULL && auxDir == NULL)
		{
			printf("No hay archivos ni directorios\n");
			return OK;
		}
		copia = new sistema;
		copia->puenteArchivo = new archivo;
		copia->puenteDirectorio = new directorio;
		copia->puenteArchivo->siguienteArchivo = NULL;
		copia->puenteDirectorio->siguienteDirectorio = NULL;
		Archivo anterior = NULL;
		Directorio anteriorDir = NULL;
		while(aux != NULL)
		{
			parar = 0;
			Archivo a = new archivo;
			a->nombreArchivo = new char[MAX_NOM + 1];
			strcpy(a->nombreArchivo, aux->nombreArchivo);
			a->texto = new char[MAX_TEXT + 1];
			strcpy(a->texto, aux->texto);
			a->Tipo = aux->Tipo;
			a->escritura = aux->escritura;
			a->lectura = aux->lectura;
			a->siguienteArchivo = NULL;
			
			if(copia->puenteArchivo->siguienteArchivo == NULL)
			{
				copia->puenteArchivo->siguienteArchivo = a; 
			}
			else
			{
				if(strcmp(a->nombreArchivo, copia->puenteArchivo->siguienteArchivo->nombreArchivo) < 0) 
				{
					a->siguienteArchivo = copia->puenteArchivo->siguienteArchivo;
					copia->puenteArchivo->siguienteArchivo = a;
				}
				else if(strcmp(a->nombreArchivo, copia->puenteArchivo->siguienteArchivo->nombreArchivo) > 0)
				{
					anterior = copia->puenteArchivo->siguienteArchivo;
					while(parar <= 0)
					{
						while(anterior->siguienteArchivo && strcmp(a->nombreArchivo, anterior->siguienteArchivo->nombreArchivo) > 0)
						{
							anterior = anterior->siguienteArchivo;
						}
						if(anterior->siguienteArchivo == NULL)
						{
							a->siguienteArchivo = anterior->siguienteArchivo;
							anterior->siguienteArchivo = a;
							parar = 1;
						}
						else
						{
							if(strcmp(a->nombreArchivo, anterior->siguienteArchivo->nombreArchivo) > 0) 
							{
								anterior = anterior->siguienteArchivo;
							}
							else if(strcmp(a->nombreArchivo, anterior->siguienteArchivo->nombreArchivo) < 0)
							{
								a->siguienteArchivo = anterior->siguienteArchivo;
								anterior->siguienteArchivo = a;
								parar = 1;
							}
						}
					}
				}
			}
			aux = aux->siguienteArchivo;
		}
		
		while(copia->puenteArchivo->siguienteArchivo != NULL)
		{
			if(copia->puenteArchivo->siguienteArchivo->lectura == true && copia->puenteArchivo->siguienteArchivo->escritura == true)
			{
				printf("%s     %s\n", copia->puenteArchivo->siguienteArchivo->nombreArchivo, "Lectura/Escritura");
			}
			else
			{
				if(copia->puenteArchivo->siguienteArchivo->lectura == true)
				{
					printf("%s     %s\n", copia->puenteArchivo->siguienteArchivo->nombreArchivo, "Lectura");
				}
				if(copia->puenteArchivo->siguienteArchivo->escritura == true)
				{
					printf("%s     %s\n", copia->puenteArchivo->siguienteArchivo->nombreArchivo, "Escritura");
				}
			}
			copia->puenteArchivo->siguienteArchivo = copia->puenteArchivo->siguienteArchivo->siguienteArchivo;
		}
		
		while(auxDir != NULL)
		{
			parar = 0;
			Directorio d = new directorio;
			d->nombreDirectorio = new char[MAX_NOM + 1];
			strcpy(d->nombreDirectorio, auxDir->nombreDirectorio);
			d->siguienteDirectorio = NULL;
			
			if(copia->puenteDirectorio->siguienteDirectorio == NULL)
			{
				copia->puenteDirectorio->siguienteDirectorio = d; 
			}
			else
			{
				if(strcmp(d->nombreDirectorio, copia->puenteDirectorio->siguienteDirectorio->nombreDirectorio) < 0) 
				{
					d->siguienteDirectorio = copia->puenteDirectorio->siguienteDirectorio;
					copia->puenteDirectorio->siguienteDirectorio = d;
				}
				else if(strcmp(d->nombreDirectorio, copia->puenteDirectorio->siguienteDirectorio->nombreDirectorio) > 0)
				{
					anteriorDir = copia->puenteDirectorio->siguienteDirectorio;
					while(parar <= 0)
					{
						while(anteriorDir->siguienteDirectorio && strcmp(d->nombreDirectorio, anteriorDir->siguienteDirectorio->nombreDirectorio) > 0)
						{
							anteriorDir = anteriorDir->siguienteDirectorio;
						}
						if(anteriorDir->siguienteDirectorio == NULL)
						{
							d->siguienteDirectorio = anteriorDir->siguienteDirectorio;
							anteriorDir->siguienteDirectorio = d;
							parar = 1;
						}
						else
						{
							if(strcmp(d->nombreDirectorio, anteriorDir->siguienteDirectorio->nombreDirectorio) > 0) 
							{
								anteriorDir = anteriorDir->siguienteDirectorio;
							}
							else if(strcmp(d->nombreDirectorio, anteriorDir->siguienteDirectorio->nombreDirectorio) < 0)
							{
								d->siguienteDirectorio = anteriorDir->siguienteDirectorio;
								anteriorDir->siguienteDirectorio = d;
								parar = 1;
							}
						}
					}
				}
			}
			auxDir = auxDir->siguienteDirectorio;
		}
		
		while(copia->puenteDirectorio->siguienteDirectorio != NULL)
		{
			printf("%s\n", copia->puenteDirectorio->siguienteDirectorio->nombreDirectorio);
			copia->puenteDirectorio->siguienteDirectorio = copia->puenteDirectorio->siguienteDirectorio->siguienteDirectorio;
		}
	}
	return OK;
}
void dirRecursivo(Directorio arbol, pilaPalabra pil, pilaPalabra auxPila, Archivo archivos)
{
	Cadena barra = new char[10];
	strcpy(barra, "/");
	Cadena ruta = new char[255];
	strcpy(ruta, "");
	if(arbol == NULL) return;
	if(strcmp(arbol->nombreDirectorio, "RAIZ") == 0)
	{
		Cadena RAIZ = new char[10];
		strcpy(RAIZ, "RAIZ");
		apilarPalabra(pil, crearNodoPalabra(RAIZ));
		puts(cimaPalabra(pil)->palabra);
	}
	else
	{
		apilarPalabra(pil,crearNodoPalabra(strcat(barra, arbol->nombreDirectorio)));
		while(pil != NULL)
		{
			apilarPalabra(auxPila, desapilarPalabra(pil));
		}
		while(auxPila != NULL)
		{
			apilarPalabra(pil, desapilarPalabra(auxPila));
			strcat(ruta, cimaPalabra(pil)->palabra);
		}
		puts(ruta);
	}
	archivos = arbol->siguienteDirectorioArchivo;
	while(archivos != NULL)
	{
		Cadena barra = new char[10];
		strcpy(barra, "/");
		Cadena ruta = new char[10];
		strcpy(ruta, "");
		apilarPalabra(pil, crearNodoPalabra(strcat(barra, archivos->nombreArchivo)));
		while(pil != NULL)
		{
			apilarPalabra(auxPila, desapilarPalabra(pil));
		}
		while(auxPila != NULL)
		{
			apilarPalabra(pil, desapilarPalabra(auxPila));
			strcat(ruta, cimaPalabra(pil)->palabra);
		}
		puts(ruta);
		archivos = archivos->siguienteArchivo;
		desapilarPalabra(pil);
	}
	
	dirRecursivo(arbol->hijoDirectorio, pil, auxPila, archivos);
	desapilarPalabra(pil);
	dirRecursivo(arbol->siguienteDirectorio, pil, auxPila, archivos);
}

//laboratorio2

TipoRet cd(Sistema &s, Cadena nombreDir)
{
	Directorio dirActual = s->puenteDirectorio;
	Directorio RAIZ = s->puenteRaiz;
	
	if(strcmp(nombreDir, "cd..") == 0)
	{
		if(dirActual == RAIZ)
		{
			printf("el directorio raiz no tiene padre\n");
		}
		else
		{
			int cant = 0;
			padreRecursivo(RAIZ, cant, dirActual);
			s->puenteDirectorio = dirActual;
		}
	}
	
	else
	{
		
		if(strcmp(nombreDir, "RAIZ") == 0)
		{
			dirActual = s->puenteDirectorio;
			return OK;
		}
		else
		{
			dirActual = dirActual->hijoDirectorio;
			if(dirActual == NULL)
			{
				printf("no existe el subdirectorio destino\n");
				return ERROR;
			}
			while(strcmp(dirActual->nombreDirectorio, nombreDir) != 0)
			{
				if(dirActual->siguienteDirectorio == NULL)
				{
					printf("no existe el subdirectorio destino\n");
					return ERROR;
				}
				dirActual = dirActual->siguienteDirectorio;
			}
			if(strcmp(dirActual->nombreDirectorio , nombreDir) == 0)
			{
				s->puenteDirectorio = dirActual;
				
			}
		}
	}
	
	return OK;
}

int padreRecursivo(Directorio arbol, int &cant, Directorio &dirActual)
{
	if(arbol == NULL) return 0;
	padreRecursivo(arbol->hijoDirectorio, cant, dirActual);
	if(cant == 1)
	{
		dirActual = arbol;
		cant++;
	}
	if(cant >1) return cant;
	if(arbol == dirActual)
	{
		cant = 1;
		return cant;
	}
	padreRecursivo(arbol->siguienteDirectorio, cant, dirActual);
	
}




TipoRet mkdir(Sistema &dirActual, Cadena nombreDirNuevo)
{
	if (strcmp(nombreDirNuevo, "RAIZ") == 0)
	{
		printf("No se puede crear un directorio llamado 'RAIZ'\n");
		return ERROR;
	}
	
	Directorio dActual = dirActual->puenteDirectorio;
	Directorio dActualHijos = dActual->hijoDirectorio;
	
	while (dActualHijos != NULL)
	{
		if(strcmp(dActualHijos->nombreDirectorio, nombreDirNuevo) == 0)
		{
			printf("No se pudo crear el nuevo directorio, ya existe uno con ese nombre en la ruta actual\n");
			return ERROR;
		}
		dActualHijos = dActualHijos->siguienteDirectorio;
	}
	
	Directorio directorioNuevo = new directorio;
	directorioNuevo->nombreDirectorio = new char[MAX_NOM +1];
	strcpy(directorioNuevo->nombreDirectorio, nombreDirNuevo);
	directorioNuevo->siguienteDirectorio = NULL;
	directorioNuevo->hijoDirectorio = NULL;
	directorioNuevo->siguienteDirectorioArchivo = NULL;
	
	
	if (dActual->hijoDirectorio == NULL) {
		dActual->hijoDirectorio = directorioNuevo;
	} else {
		Directorio dActualHijos = dActual->hijoDirectorio;
		while (dActualHijos->siguienteDirectorio != NULL) {
			dActualHijos = dActualHijos->siguienteDirectorio;
		}
		dActualHijos->siguienteDirectorio = directorioNuevo;
	}
	return OK;
}


TipoRet rmdir (Sistema &s, Cadena nombreDirectorio)
{
	Directorio dirActual = s->puenteDirectorio;
	bool primero = false;
	Directorio anterior = NULL;
	if(dirActual->hijoDirectorio == NULL)
	{
		printf("no existe el subdirectorio destino\n");
		return ERROR;
	}
	Directorio borrar = dirActual->hijoDirectorio;
	if(strcmp(borrar->nombreDirectorio, nombreDirectorio) == 0)
	{
		primero = true;
	}
	else
	{
		while(strcmp(borrar->nombreDirectorio, nombreDirectorio) != 0)
		{
			if(borrar->siguienteDirectorio == NULL)
			{
				printf("El directorio no existe en la ruta actual\n");
				return ERROR;
			}
			if(strcmp(borrar->siguienteDirectorio->nombreDirectorio, nombreDirectorio) == 0)
			{
				anterior = borrar;
				borrar = borrar->siguienteDirectorio;
				break;
			}
			borrar = borrar->siguienteDirectorio;
		}
	}
	borrarRecursivo(borrar, borrar);
	if(primero == true)
	{
		dirActual = borrar->siguienteDirectorio;
		delete borrar;
		s->puenteDirectorio->hijoDirectorio = dirActual;
	}
	else
	{
		anterior->siguienteDirectorio = borrar->siguienteDirectorio;
		delete borrar;
	}
	return OK;
}

void borrarRecursivo(Directorio borrar, Directorio parar)
{
	
	if(borrar == NULL) return;
	borrarRecursivo(borrar->hijoDirectorio, parar);
	if(borrar == parar)
	{
		return;
	}
	if(borrar->hijoDirectorio != NULL)
	{
		delete borrar->hijoDirectorio;
		if(borrar->siguienteDirectorio != NULL)
		{
			borrarRecursivo(borrar->siguienteDirectorio, parar);
		}
		else
		{
			return;
		}
	}
	else
	{
		if(borrar->siguienteDirectorio != NULL)
		{
			borrarRecursivo(borrar->siguienteDirectorio, parar);
			delete borrar->siguienteDirectorio;
			return;
		}
		else
		{
			return;
		}
	}
}

TipoRet move(Sistema &dirActual, Cadena nombreCosaMover, Cadena rutaDestino)
{
	Directorio RAIZ = dirActual->puenteRaiz;
	Directorio dActual = dirActual->puenteDirectorio;
	Directorio existeDir = NULL;
	pilaPalabra pil = NULL;
	pilaPalabra auxPil = NULL;
	Cadena rActual = new char[50];
	rActual = rutaActual(dirActual);
	if (strcmp(rActual, rutaDestino) == 0) {
		printf("No se puede mover un directorio o archivo al directorio actual\n");
		return ERROR;
	}
	Directorio dirEncontrado = NULL;
	Directorio dirBuscado = dActual->hijoDirectorio;
	while (dirBuscado != NULL) {
		if (strcmp(dirBuscado->nombreDirectorio, nombreCosaMover) == 0) {
			dirEncontrado = dirBuscado;
			break;
		}
		dirBuscado = dirBuscado->siguienteDirectorio;
	}
	Archivo archivoEncontrado = NULL;
	Archivo archivoBuscado = dActual->siguienteDirectorioArchivo;
	if (dirEncontrado == NULL) {
		while (archivoBuscado != NULL) {
			if (strcmp(archivoBuscado->nombreArchivo, nombreCosaMover) == 0) {
				archivoEncontrado = archivoBuscado;
				break;
			}
			archivoBuscado = archivoBuscado->siguienteArchivo;
		}
	}
	if (dirBuscado == NULL && archivoBuscado == NULL) {
		printf("No existe un directorio o archivo con el nombre ingresado en el directorio actual\n");
		return ERROR;
	}
	
	existeDirRecursivo(RAIZ, existeDir, rutaDestino, pil, auxPil);
	if(existeDir == NULL)
	{
		printf("El directorio destino no existe\n");
		return ERROR;
	}
	
	
	char matriz1[100][100];
	char matriz2[100][100];
	int cant1 = 0;
	int cant2 = 0;
	bool adentro = false;
	Directorio dirDestino = existeDir;
	Cadena directorioDestinoCopia = new char[MAX_NOM + 1];
	strcpy(directorioDestinoCopia, rutaDestino);
	
	strcat(rActual,"/");
	Cadena nombreDirActual = strtok(rActual, "/");
	while (nombreDirActual != NULL) {
		strcpy(matriz1[cant1], nombreDirActual);
		nombreDirActual = strtok(NULL, "/");
		cant1++;
	} 
	Cadena nombreDir = strtok(directorioDestinoCopia, "/");
	while(nombreDir != NULL)
	{
		strcpy(matriz2[cant2], nombreDir);
		nombreDir = strtok(NULL, "/");
		cant2++;
	}
	if(cant1 > cant2)
	{
		
	}
	else
	{
		for (int i = 0; i<cant1; i++)
		{
			if(strcmp(matriz1[i], matriz2[i]) == 0)
			{
				adentro = true;
			}
			else
			{
				adentro = false;
				break;
			}
		}
	}
	if(adentro == true)
	{
		printf("No puede mover el directorio/archivo a la rama de su directorio actual\n");
		return ERROR;
	}
	
	if (dirBuscado != NULL) {
		Directorio dirDestinoCopia = dirDestino;
		if (strcmp(rutaDestino,"RAIZ")!=0 ) {

			
			if (dirDestinoCopia->hijoDirectorio == NULL) {
				dirDestinoCopia->hijoDirectorio = dirBuscado;
			} else {
				Directorio hijosDirDestinoCopia = dirDestinoCopia->hijoDirectorio;
				if (strcmp(hijosDirDestinoCopia->nombreDirectorio,dirBuscado->nombreDirectorio) == 0)
				{

					dirDestinoCopia->hijoDirectorio->siguienteDirectorioArchivo = dirBuscado->siguienteDirectorioArchivo;
					dirDestinoCopia->hijoDirectorio->hijoDirectorio = dirBuscado->hijoDirectorio;
				} else {
					while(hijosDirDestinoCopia->siguienteDirectorio != NULL && strcmp(hijosDirDestinoCopia->nombreDirectorio,dirBuscado->nombreDirectorio) != 0)
					{
						hijosDirDestinoCopia = hijosDirDestinoCopia->siguienteDirectorio;
					}
					if (strcmp(hijosDirDestinoCopia->nombreDirectorio,dirBuscado->nombreDirectorio) == 0){
						
						hijosDirDestinoCopia->hijoDirectorio = dirBuscado->hijoDirectorio;
						hijosDirDestinoCopia->siguienteDirectorioArchivo = dirBuscado->siguienteDirectorioArchivo;
					} else {
						hijosDirDestinoCopia->siguienteDirectorio = dirBuscado;
					}
				}
			}
		} 
		else {
			Directorio hijoRaiz = dirDestino->hijoDirectorio;
			while (hijoRaiz->siguienteDirectorio!= NULL) {
				hijoRaiz = hijoRaiz->siguienteDirectorio;
			}
			hijoRaiz->siguienteDirectorio= dirBuscado;
		}
		Directorio hijosActualCopia = dActual->hijoDirectorio;
		if (hijosActualCopia == dirBuscado)
		{
			dActual->hijoDirectorio = dirBuscado->siguienteDirectorio;
		} else {
			while(hijosActualCopia->siguienteDirectorio != dirBuscado)
			{
				hijosActualCopia = hijosActualCopia->siguienteDirectorio;
			}
			hijosActualCopia->siguienteDirectorio = dirBuscado->siguienteDirectorio;
			dirBuscado->siguienteDirectorio = NULL;
		}
	}
	else if (archivoBuscado != NULL) {
		Archivo archivoDestinoCopia = dirDestino->siguienteDirectorioArchivo;
		
		if (archivoDestinoCopia == NULL){
			archivoDestinoCopia->siguienteArchivo = archivoBuscado;
		} else {
			while (archivoDestinoCopia->siguienteArchivo != NULL && strcmp(archivoDestinoCopia->nombreArchivo, archivoBuscado->nombreArchivo) != 0) {
				archivoDestinoCopia = archivoDestinoCopia->siguienteArchivo;
			}
			if (strcmp(archivoDestinoCopia->nombreArchivo,archivoBuscado->nombreArchivo) == 0){
				
				archivoDestinoCopia->texto = archivoBuscado->texto;
				archivoDestinoCopia->escritura = archivoBuscado->escritura;
				archivoDestinoCopia->lectura = archivoBuscado->lectura;
			} else {
				archivoDestinoCopia->siguienteArchivo = archivoBuscado;
			}
		}
		
		
		if (dActual != NULL) {
			Archivo archivoActualCopia = dActual->siguienteDirectorioArchivo;
			if (archivoActualCopia == archivoBuscado) {
				dActual->siguienteDirectorioArchivo = archivoBuscado->siguienteArchivo;
				archivoBuscado->siguienteArchivo = NULL;
				return OK;
			}
			else {
				while (archivoActualCopia->siguienteArchivo != archivoBuscado) {
					archivoActualCopia = archivoActualCopia->siguienteArchivo;
				}
				archivoActualCopia->siguienteArchivo = archivoBuscado->siguienteArchivo;
				archivoBuscado->siguienteArchivo = NULL;
			}
		}
	}
	
	return OK;
}


void existeDirRecursivo(Directorio RAIZ, Directorio &existeDir, Cadena rutaDestino, pilaPalabra &pil, pilaPalabra &auxPila)
{
	Cadena barra = new char[10];
	strcpy(barra, "/");
	Cadena ruta = new char[255];
	strcpy(ruta, "");
	if (RAIZ == NULL || existeDir != NULL) return;
	
	if(strcmp(RAIZ->nombreDirectorio, "RAIZ") == 0)
	{
		Cadena RAIZ = new char[10];
		strcpy(RAIZ, "RAIZ");
		apilarPalabra(pil, crearNodoPalabra(RAIZ));
		strcat(ruta, RAIZ);
	}
	else
	{
		apilarPalabra(pil,crearNodoPalabra(strcat(barra, RAIZ->nombreDirectorio)));
		while(pil != NULL)
		{
			apilarPalabra(auxPila, desapilarPalabra(pil));
		}
		while(auxPila != NULL)
		{
			apilarPalabra(pil, desapilarPalabra(auxPila));
			strcat(ruta, cimaPalabra(pil)->palabra);
		}
		
	}
	if(strcmp(rutaDestino, ruta) == 0)
	{
		existeDir = RAIZ;
		return;
	}
	existeDirRecursivo(RAIZ->hijoDirectorio, existeDir, rutaDestino, pil, auxPila);
	desapilarPalabra(pil);
	existeDirRecursivo(RAIZ->siguienteDirectorio, existeDir, rutaDestino, pil, auxPila);
}

TipoRet destruirSistema(Sistema &raizSistema) {
	if (raizSistema != NULL) {
		destruirSistemaRecursivo(raizSistema->puenteDirectorio);
		
		delete[] raizSistema->puenteDirectorio->nombreDirectorio;
		raizSistema->puenteDirectorio->nombreDirectorio = NULL;
		raizSistema->puenteDirectorio->hijoDirectorio = NULL;
		raizSistema->puenteDirectorio->siguienteDirectorio = NULL;
		raizSistema->puenteDirectorio->siguienteDirectorioArchivo = NULL;
		delete raizSistema->puenteDirectorio;
		raizSistema->puenteDirectorio = NULL;
		
		delete[] raizSistema->puenteArchivo;
		raizSistema->puenteArchivo->nombreArchivo == NULL;
		raizSistema->puenteArchivo->texto == NULL;
		raizSistema->puenteArchivo = NULL;
		
		delete[] raizSistema->puenteRaiz;
		delete raizSistema;
		
		raizSistema = NULL;
		return OK;
	}
	return ERROR;
}
void destruirSistemaRecursivo(Directorio dir) {
	if (dir != NULL) {
		Archivo archivo = dir->siguienteDirectorioArchivo;
		while (archivo != NULL) {
			Archivo siguienteArchivo = archivo->siguienteArchivo;
			delete[] archivo->nombreArchivo;
			archivo->nombreArchivo = NULL;
			delete[] archivo->texto;
			archivo->texto = NULL;
			archivo->siguienteArchivo = NULL;
			delete archivo;
			archivo = siguienteArchivo;
		}
		
		Directorio subDirectorio = dir->hijoDirectorio;
		while (subDirectorio != NULL) {
			destruirSistemaRecursivo(subDirectorio);
			Directorio siguienteDirectorio = subDirectorio->siguienteDirectorio;
			delete[] subDirectorio->nombreDirectorio;
			subDirectorio->nombreDirectorio = NULL;
			subDirectorio->hijoDirectorio = NULL;
			subDirectorio->siguienteDirectorioArchivo = NULL;
			subDirectorio->siguienteDirectorio = NULL;
			delete subDirectorio;
			subDirectorio = siguienteDirectorio;
		} 
		Directorio directorioHermano = dir->siguienteDirectorio;
		while (directorioHermano != NULL) {
			destruirSistemaRecursivo(directorioHermano);
			Directorio siguienteDirectorio = directorioHermano->siguienteDirectorio;
			delete[] directorioHermano->nombreDirectorio;
			directorioHermano->nombreDirectorio = NULL;
			directorioHermano->hijoDirectorio = NULL;
			directorioHermano->siguienteDirectorioArchivo = NULL;
			directorioHermano = siguienteDirectorio;
			delete directorioHermano;
			directorioHermano = siguienteDirectorio;
		}
	}
}
// Auxiliares, las auxiliares recursivas estan con su funcion original
Cadena rutaActual(Sistema dirActual)
{
	Cadena ruta = new char[255];
	strcpy(ruta, "");
	Directorio aux = new directorio;
	aux = dirActual->puenteRaiz;
	bool encontrado = false;
	pilaPalabra pil = NULL;
	pilaPalabra auxPila = NULL;
	inOrden(aux, encontrado, dirActual->puenteDirectorio, pil);
	
	while(pil != NULL)
	{
		apilarPalabra(auxPila, desapilarPalabra(pil));
	}
	while(auxPila != NULL)
	{
		apilarPalabra(pil, desapilarPalabra(auxPila));
		strcat(ruta, cimaPalabra(pil)->palabra);
	}
	
	return ruta;
}

bool inOrden(Directorio arbol, bool encontrado, Directorio dirActual, pilaPalabra& pil)
{
	Cadena barra = new char[10];
	strcpy(barra, "/");
	if (arbol == NULL || encontrado == true) return encontrado;
	
	if(strcmp(arbol->nombreDirectorio, "RAIZ") == 0)
	{
		Cadena RAIZ = new char[10];
		
		strcpy(RAIZ, "RAIZ");
		apilarPalabra(pil, crearNodoPalabra(RAIZ));
		
	}
	else
	{
		apilarPalabra(pil, crearNodoPalabra(strcat(barra, arbol->nombreDirectorio)));
		
	}
	if(arbol == dirActual)
	{
		encontrado = true;
		return encontrado;
	}
	
	if(inOrden(arbol->hijoDirectorio, encontrado, dirActual, pil) == true)
	{
		encontrado = true;
		return encontrado;
	}
	desapilarPalabra(pil);
	
	if(inOrden(arbol->siguienteDirectorio, encontrado, dirActual, pil) == true)
	{
		encontrado = true;
		return encontrado;
	}
}

void minuscula(Cadena entrada) {
	int longitud = strlen(entrada);
	
	for (int i = 0; i < longitud; i++) {
		if (entrada[i] >= 'A' && entrada[i] <= 'Z') {
			entrada[i] = entrada[i] + ('a' - 'A');
		}
	}
}

pilaPalabra crearNodoPalabra(Cadena palabra)
{
	pilaPalabra aux=new nodoPilaPalabra;
	if (aux)
	{
		aux->palabra=palabra;
		aux->siguiente=NULL;
		return aux;
	}
	return aux;
}

void apilarPalabra(pilaPalabra &pilaL,pilaPalabra aux)
{
	aux->siguiente = pilaL;
	pilaL = aux;
}

pilaPalabra cimaPalabra(pilaPalabra palabra)
{
	return (palabra);
}

pilaPalabra desapilarPalabra(pilaPalabra &p)
{
	pilaPalabra aux, dev=new nodoPilaPalabra;
	aux=p;
	if(!p) return NULL;
	dev->palabra=p->palabra;
	dev->siguiente=NULL;
	p=p->siguiente;
	delete(aux);
	return dev;
}
