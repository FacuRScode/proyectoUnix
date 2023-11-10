#include<iostream>
#include <string.h>
#include "Sistema.hpp"
using namespace std;

int main (int argc, char *argv[]) {
	Sistema sistemaDir = new sistema;
	sistemaDir->puenteDirectorio = new directorio;
	Cadena textoRecibido = new char[255];
	Cadena entrada = new char[16];
	Cadena ent = new char [16];
	char cadaEnt[100][100];
	Cadena divisor=new char [16];
	divisor = " ";
	int cant = 0;

	
	
	Sistema raiz = new sistema;
	raiz->puenteDirectorio = new directorio;
	raiz->puenteDirectorio->nombreDirectorio = "RAIZ";
	raiz->puenteDirectorio->siguienteDirectorio = NULL;
	raiz->puenteDirectorio->hijoDirectorio = NULL;
	raiz->puenteDirectorio->siguienteDirectorioArchivo = NULL;
	
	sistemaDir = raiz;
	Sistema sistemaDirCopia = new sistema;
	sistemaDirCopia->puenteDirectorio = new directorio;
	sistemaDirCopia->puenteRaiz = new directorio;
	sistemaDirCopia->puenteDirectorio = raiz->puenteDirectorio;
	sistemaDirCopia->puenteRaiz = raiz->puenteDirectorio;
	
	
	strcpy(ent, "");
	strcpy(textoRecibido, "");
	do {
		
		cant = 0;
		gets(entrada);
		ent = strtok(entrada, divisor);
		while(ent != NULL)
		{
			strcpy(cadaEnt[cant], ent);
			if(strcmp(cadaEnt[0], "iff") == 0)
			{
				if(cant >= 2)
				{
					strcat(textoRecibido, ent);
					strcat(textoRecibido, " ");
				}
			}
			cant++;
			ent = strtok(NULL, divisor);
		}
		
		minuscula(cadaEnt[0]);
		if(strcmp("dir", cadaEnt[0]) == 0)
		{
			if(strcmp("/s", cadaEnt[1]) == 0)
			{
				dir(sistemaDirCopia, "/s");
				strcpy(cadaEnt[1],"");
			}
			else
			{
				dir(sistemaDirCopia, rutaActual(sistemaDirCopia));
			}
		}
		
		
		
		if(strcmp("createfile", cadaEnt[0]) == 0)
		{
			if(strcmp(cadaEnt[1], "") == 0)
			{
				printf("Escribio mal el comando debe ingresar el nombre del archivo\n");
			}
			else
			{
				createFile(sistemaDirCopia,  cadaEnt[1]);
			}
		}
		minuscula(cadaEnt[0]);
		if(strcmp("delete", cadaEnt[0]) == 0)
		{
			Delete(sistemaDirCopia,  cadaEnt[1]);
		}
		
		if(strcmp("attrib", cadaEnt[0]) == 0)
		{
			attrib(sistemaDirCopia, cadaEnt[1], cadaEnt[2]);
		}
		
		if(strcmp("iff", cadaEnt[0]) == 0)
		{
			int longitud = strlen(textoRecibido);
			if (longitud >= 2 && textoRecibido[0] == '"' && textoRecibido[longitud - 2] == '"') {
				for (int i = 1; i < longitud - 1; i++) {
					textoRecibido[i - 1] = textoRecibido[i];
				}
				textoRecibido[longitud - 3] = '\0';
			}
			IFF(sistemaDirCopia, cadaEnt[1], textoRecibido);
			strcpy(textoRecibido, "");
		}
		
		if(strcmp("type", cadaEnt[0]) == 0)
		{
			type(sistemaDirCopia, cadaEnt[1]);
		}
		
		if(strcmp("mkdir", cadaEnt[0]) == 0)
		{
			mkdir(sistemaDirCopia, cadaEnt[1]);
		}
		
		if(strcmp("rmdir", cadaEnt[0]) == 0)
		{
			rmdir(sistemaDirCopia, cadaEnt[1]);
		}
		if(strcmp("move", cadaEnt[0]) == 0)
		{
			move(sistemaDirCopia, cadaEnt[1], cadaEnt[2]);
		}
		if(strcmp("destruirsistema", cadaEnt[0]) == 0)
		{
			destruirSistema(sistemaDirCopia);
			raiz->puenteDirectorio->siguienteDirectorio = NULL;
			raiz->puenteDirectorio->hijoDirectorio = NULL;
			raiz->puenteDirectorio->siguienteDirectorioArchivo = NULL;

			
		}
		
		
		
		
		if(strcmp("ayuda", cadaEnt[0]) == 0)
		{
			cout<<"Comandos disponibles: "<<endl;
			cout<<"dir"<<endl;
			cout<<"createfile"<<endl;
			cout<<"delete"<<endl;
			cout<<"attrib"<<endl;
			cout<<"iff"<<endl;
			cout<<"type"<<endl;
			cout<<"ayuda"<<endl;
			cout<<"salir"<<endl;
			cout<<""<<endl;
			cout<<"Puede escribirlos en mayuscula o minusculas"<<endl;
		}
		
		if(strcmp("cd", cadaEnt[0]) == 0)
		{
			if(strcmp("raiz", cadaEnt[1]) == 0)
			{
				sistemaDirCopia->puenteDirectorio = sistemaDir->puenteDirectorio;
				cd(sistemaDirCopia, cadaEnt[1]);
			}
			else
			{
				cd(sistemaDirCopia, cadaEnt[1]);
			}
		}
		else if(strcmp("cd..", cadaEnt[0])== 0)
		{
			cd(sistemaDirCopia, cadaEnt[0]);
			sistemaDirCopia->puenteRaiz = raiz->puenteDirectorio;
		}
		
		if(strcmp("salir", cadaEnt[0]) == 0)
		{
			return 0;
		}
		
	} while (cadaEnt[0] != "salir");
	
	
	
	return 0;
}
