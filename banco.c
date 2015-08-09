#include <stdio.h>
#include <stdlib.h>

int leerOpcion(int opcion){
	scanf("%d",&opcion);
	return opcion;
}

int menuPrincipal(){
	printf("1 - Ingreso\n");
	printf("2 - Salir\n");
}

int menuIngreso(){
	printf("Usuario: \n");
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


int main(){

	int opcion;
	do{
		menuPrincipal();
		opcion = leerOpcion(opcion);
		menuOperaciones();
		opcion = leerOpcion(opcion);
		switch(opcion){
			case 1 : 
				sucursales();
				break;
			case 2 : 
				cuentas();
				break;
			case 3 : 
				nuevaSucursal();
				break;
			case 4 : 
				bajaSucursal();
				break;
			case 5 :
				nuevaCuenta();
				break;
			case 6 : 
				bajaCuenta();
				break;
			case 7 : 
				actualizarSaldos();
			case 8: 
				deudores();
			case 9:
			default:
				menuOperaciones();
				break;
		}

	}while(opcion != 0);
	

	return 0;
}