#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void preEjecucion(){
	printf("TODO Ejecutar los metodos pre ejecución\n");
}
void postEjecucion(){
	printf("TODO Ejecutar los metodos post ejecución\n");
}

int menuPrincipal(){
	printf("1 - Ingreso\n");
	printf("2 - Salir\n");
}

int menuIngreso(char usuario[30],char password[8]){
	printf("Usuario: \n");
	scanf("%s",usuario);
	printf("Password: \n");
}

int menuOperaciones(){
	printf("1 - Sucursales\n");
	printf("2 - Cuentas\n");
	printf("3 - Nueva Sucursal\n");
	printf("4 - Baja Sucursal\n");
	printf("5 - Nueva cuenta\n");
	printf("6 - Baja cuenta\n");
	printf("7 - Actualizar Saldos\n");
	printf("8 - Deudores\n");
	printf("9 - Volver al menú anterior.\n");
}
void sucursales(){
	printf("TODO Listar Sucursales\n");
}
void cuentas(){
	printf("TODO Listar Cuentas\n");	
}
void nuevaSucursal(){
	printf("TODO Nueva Sucursal\n");	
}
void bajaSucursal(){
	printf("TODO Baja Sucursal\n");		
}
void nuevaCuenta(){
	printf("TODO Nueva Cuenta\n");
}
void bajaCuenta(){
	printf("TODO baja Cuenta\n");
}
void actualizarSaldos(){
	printf("TODO actualizar saldos\n");
}
void deudores(){
	printf("TODO listar deudores\n");
}

void opcionInvalida(){
	printf("Debe eligir una opción válida\n");
}
void wait(int time){	 
  unsigned int time_to_sleep = time; // sleep 2 seconds
  #ifdef _WIN32
  	Sleep(time*1000);
  #else
  	/*solo unix*/
 	 while(time_to_sleep){
 	 	time_to_sleep = sleep(time_to_sleep);	
 	 }
  #endif

     
}

void login(char usuario[30],char password[8]){
	printf("\nTODO Hacer login\n");
	printf("\nBienvenido %s\n\n",usuario);
}

int leerOpcion(int opcion){
	scanf("%d",&opcion);
	return opcion;
}

int main(){

	char usuario[30];
	char password[8];
	int opcion;
	do{
		menuPrincipal();
		opcion = leerOpcion(opcion);
		switch(opcion){
			case 1 : 
				menuIngreso(usuario,password);
				login(usuario,password);
				do{
					menuOperaciones();
					opcion = leerOpcion(opcion);
					switch(opcion){
						case 1 : 
							sucursales();
							wait(2);
							break;
						case 2 : 
							cuentas();
							wait(2);
							break;
						case 3 : 
							nuevaSucursal();
							wait(2);
							break;
						case 4 : 
							bajaSucursal();
							wait(2);
							break;
						case 5 :
							nuevaCuenta();
							wait(2);
							break;
						case 6 : 
							bajaCuenta();
							wait(2);
							break;
						case 7 : 
							actualizarSaldos();
							wait(2);
							break;
						case 8: 
							deudores();
							wait(2);
							break;
						case 9:
							//No se hace nada por el momento
							break;
						default:
							opcionInvalida();
							break;
					}
					
				}while(opcion != 9);

				break;
			case 2 :
				printf("Gracias!!!\n");
				break;
			default:
				break;
		}

	}while(opcion != 2);
	
	return 0;
}