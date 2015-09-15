#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Sucursales{
    int cod_sucursal;
    char barrio[40];
    struct Cuentas *succuenta;
    struct Sucursales *sigsuc;
} nodo_Sucursal;

typedef struct Cuentas{
    int cod_sucursal;
    int nro_cuenta;
    char nombreyapellido[40];
    char tipo_de_cuenta [10];
    int saldo;
    struct Cuentas *sigcuenta;
} nodo_Cuentas;

typedef struct Clientes{
    int cod_sucursal;
    int nro_cuenta;
    char tipo_de_cuenta [10];
    char tipo_de_movimiento[2];
    int monto;
    struct Clientes *sigclien;
} nodo_Clientes;

//void cargarSucursales(nodo_Sucursal *);
//void cargarCuentas(FILE *, nodo_Cuentas *);
//void cargarClientes(FILE *);

void cargarSucursales(FILE *sucursalesFile, nodo_Sucursal *p){
    printf("Sucursales\n");

    if((sucursalesFile = fopen("Sucursales.txt","r")) == NULL ){
        printf("NO SE PUDO LEER EL ARCHIVO\n");
    }else{
        while(!feof(sucursalesFile)){
            fscanf(sucursalesFile,"%d;%39[^\n]\n",&p->cod_sucursal,p->barrio);
            //printf("%d %s \n",p->cod_sucursal,p->barrio);
            p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));
            p = p->sigsuc;
        }
        p->sigsuc = NULL;
    }
    fclose(sucursalesFile);
}
void cargarCuentas(FILE *cuentas,nodo_Cuentas *p){
    printf("Cuentas\n");

    if( (cuentas = fopen("Cuentas.txt","r")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(!feof(cuentas)){
            fscanf(cuentas,"%d;%d;%39[^\;];%9[^\;];%d\n",&p->cod_sucursal,&p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,&p->saldo);
            p->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
            //printf("%d %d %s %s\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
            p = p->sigcuenta;
        }
        p->sigcuenta = NULL;
        fclose(cuentas);
    }
}


void cargarClientes(FILE *clientes,nodo_Clientes *p){

    printf("Clientes\n");

    if( (clientes = fopen("Clientes.txt","r")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(!feof(clientes)){
            fscanf(clientes,"%d;%d;%9[^\;];%1[^\;];%d\n",&p->cod_sucursal,&p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,&p->monto);
            p->sigclien = (nodo_Clientes*)malloc(sizeof(nodo_Clientes));
            //printf("%d %d %s %s\n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);

            p = p->sigclien;

        }
        p->sigclien = NULL;
        fclose(clientes);
    }
}

void grabarSucursales(){

}

void grabarClientes(nodo_Clientes *p){
    printf("Grabando Clientes\n");

    FILE *clientes;
    if( (clientes = fopen("Clientes.txt","w")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(p != NULL){
            fprintf(clientes,"%d;%d;%s;%s;%%d\n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);
            p = p->sigclien;
        }
        fclose(clientes);
    }
}

void grabarCuentas(){

}

void mostrarLista(nodo_Clientes *registro){
    if(registro->sigclien != NULL){
        printf("Sucursal %d\n",registro->cod_sucursal);
        mostrarLista(registro->sigclien);
    }
}

void preEjecucion(nodo_Clientes *listaClientes,nodo_Cuentas *listaCuentas,nodo_Sucursal *listaSucursales){
	srand(time(NULL));//Setea la semilla para que el rand sea realmente random

    FILE *sucursales;
    //nodo_Sucursal *listaSucursales;
    listaSucursales = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));
    cargarSucursales(sucursales,listaSucursales);

    FILE *cuentas;
    //nodo_Cuentas *listaCuentas;
    listaCuentas = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
    cargarCuentas(cuentas,listaCuentas);



    FILE *clientes;
    listaClientes = (nodo_Clientes*)malloc(sizeof(nodo_Clientes));
    cargarClientes(clientes,listaClientes);
    //mostrarLista(listaClientes);

    //no incluye el ; pero despues hay que incluir
    //fscanf(sucursales,"$%d;%39[^\;];%9[;];%d\n",&cod,barrio):

    //fscanf("","%d;%d;%9[^;];%1[^;];%d\n");
}


void postEjecucion(nodo_Clientes *listaClientes,nodo_Cuentas *listaCuentas,nodo_Sucursal *listaSucursales){
	printf("TODO Ejecutar los metodos post ejecución\n");
	grabarClientes(listaClientes);
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
    nodo_Clientes *listaClientes;
    listaClientes = (nodo_Clientes*)malloc(sizeof(nodo_Clientes));
    nodo_Cuentas  *listaCuentas;
    nodo_Sucursal *listaSucursales;
	preEjecucion(listaClientes,listaCuentas,listaSucursales);

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

    postEjecucion(listaClientes,listaCuentas,listaSucursales);
	return 0;
}
