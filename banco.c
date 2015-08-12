#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preEjecucion(){
	srand(time(NULL));//Setea la semilla para que el rand sea realmente random
}
void postEjecucion(){
	printf("TODO Ejecutar los metodos post ejecución\n");
}

int menuPrincipal(){
	printf("1 - Ingreso\n");
	printf("2 - Salir\n");
}

int menuIngreso(char usuario[30]){
	printf("Usuario: \n");
	scanf("%s",usuario);

	int maxIntentos = 3;

	int intentos = 0;
	int secuencia[4];

	printf("Escriba la siguiente clave sin guiones ni espacios y en minúscula: \n");

	int c;
	int i;
	for(i = 0; i < 4; i++){
		c = rand()%26+97;//Calculo random de letras desde a minuscula
		putchar(c);
		putchar(' ');
		secuencia[i] = c;
	}
	putchar('\n');


	int in, cont = 0;
	
	do{
		fflush(stdin);//Limpio ingreso por teclado
		in = getchar();

		while(in != '\n'){
			if(secuencia[cont] == in){
				cont++;
			}
			in = getchar();
		}

		if(cont == 4){
			printf("\nBienvenido %s!!! \n\n",usuario);
		
		}else if(intentos > 0 && intentos < maxIntentos){
			printf("Clave Incorrecta. Intente nuevamente\n");
			intentos++;
		}else{
			intentos++;
		}
		
	}while(intentos <= maxIntentos && cont < 4);//Corta si hay mas de n intentos o si coincidieron todas las letras
	
	if(intentos > maxIntentos){
		printf("Ha alcanzado el máximo de intentos. Se cerrará la aplicación. Gracias \n");
		exit(0);
	}

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
void wait(){
    system("pause");
}


int leerOpcion(int opcion){
	scanf("%d",&opcion);
	return opcion;
}

int main(){
	preEjecucion();

	char usuario[30];
	
	int opcion;
	do{
		menuPrincipal();
		opcion = leerOpcion(opcion);
		switch(opcion){
			case 1 :
				menuIngreso(usuario);
				do{
					menuOperaciones();
					opcion = leerOpcion(opcion);
					switch(opcion){
						case 1 :
							sucursales();
							wait();
							break;
						case 2 :
							cuentas();
							wait();
							break;
						case 3 :
							nuevaSucursal();
							wait();
							break;
						case 4 :
							bajaSucursal();
							wait();
							break;
						case 5 :
							nuevaCuenta();
							wait();
							break;
						case 6 :
							bajaCuenta();
							wait();
							break;
						case 7 :
							actualizarSaldos();
							wait();
							break;
						case 8:
							deudores();
							wait();
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
