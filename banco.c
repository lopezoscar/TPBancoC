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

void cargarSucursales(nodo_Sucursal *p){
    FILE *sucursalesFile;
    printf("Leyendo Sucursales\n");

    if((sucursalesFile = fopen("Sucursales.txt","r")) == NULL ){
        printf("NO SE PUDO LEER EL ARCHIVO\n");
    }else{
        while(!feof(sucursalesFile)){
            fscanf(sucursalesFile,"%d;%39[^\n]\n",&p->cod_sucursal,p->barrio);
            //printf("%d %s \n",p->cod_sucursal,p->barrio);
            p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));

            p->succuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
            cargarCuentas(p->succuenta,p->cod_sucursal);

            p = p->sigsuc;
        }
        p->sigsuc = NULL;
    }
    fclose(sucursalesFile);
}
void cargarCuentas(nodo_Cuentas *p,int cod_suc){
    FILE *cuentas;
    printf("Leyendo Cuentas\n");

    if( (cuentas = fopen("Cuentas.txt","r")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(!feof(cuentas)){
            fscanf(cuentas,"%d;%d;%39[^\;];%9[^\;];%d\n",&p->cod_sucursal,&p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,&p->saldo);
            if(cod_suc == p->cod_sucursal){
                p->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
                //printf("%d %d %s %s\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                p = p->sigcuenta;
            }
        }
        p->sigcuenta = NULL;
        fclose(cuentas);
    }
}


void cargarClientes(nodo_Clientes *p){
    FILE *clientes;
    printf("Leyendo Clientes\n");

    if( (clientes = fopen("Clientes.txt","r")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(!feof(clientes)){
            fscanf(clientes,"%d;%d;%9[^\;];%1[^\;];%d\n",&p->cod_sucursal,&p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,&p->monto);
            p->sigclien = (nodo_Clientes*)malloc(sizeof(nodo_Clientes));
            //printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);

            p = p->sigclien;

        }
        p->sigclien = NULL;
        fclose(clientes);
    }
}

void grabarCuentas(nodo_Sucursal *s){
    printf("Grabando Cuentas\n");

    FILE *cuentas;
    if( (cuentas = fopen("Cuentas.txt","w")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        /*Por cada sucursal recorro las cuentas y hago printf*/
        while(s->sigsuc != NULL){
            nodo_Cuentas *p = s->succuenta;
            while(p->sigcuenta != NULL){
                fprintf(cuentas,"%d;%d;%s;%s;%d\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                p = p->sigcuenta;
            }
            s = s->sigsuc;
        }
        fclose(cuentas);
    }
}

void grabarSucursales(nodo_Sucursal *p){
    printf("Grabando Sucursales\n");

    FILE *sucursales;
    if( (sucursales = fopen("Sucursales.txt","w")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(p->sigsuc != NULL){
            fprintf(sucursales,"%d;%s\n",p->cod_sucursal,p->barrio);
            p = p->sigsuc;
        }
        fclose(sucursales);
    }

}

void grabarClientes(nodo_Clientes *p){
    printf("Grabando Clientes\n");

    FILE *clientes;
    if( (clientes = fopen("Clientes.txt","w")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(p->sigclien != NULL){
            //printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);
            fprintf(clientes,"%d;%d;%s;%s;%d\n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);
            p = p->sigclien;
        }
        fclose(clientes);
    }
}



void mostrarLista(nodo_Clientes *registro){
    if(registro->sigclien != NULL){
        printf("Sucursal %d\n",registro->cod_sucursal);
        mostrarLista(registro->sigclien);
    }
}

void preEjecucion(nodo_Clientes *listaClientesToFill,nodo_Cuentas *listaCuentasToFill,nodo_Sucursal *listaSucursalesToFill){
	srand(time(NULL));//Setea la semilla para que el rand sea realmente random

    cargarClientes(listaClientesToFill);
    //cargarCuentas(listaCuentasToFill);
    cargarSucursales(listaSucursalesToFill);

    //mostrarLista(listaClientes);

    //no incluye el ; pero despues hay que incluir
    //fscanf(sucursales,"$%d;%39[^\;];%9[;];%d\n",&cod,barrio):

    //fscanf("","%d;%d;%9[^;];%1[^;];%d\n");
}


void postEjecucion(nodo_Clientes *listaClientes,nodo_Cuentas *listaCuentas,nodo_Sucursal *listaSucursales){
	grabarClientes(listaClientes);
	grabarSucursales(listaSucursales);
	grabarCuentas(listaSucursales);
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
void sucursales(nodo_Sucursal *p){
	while(p->sigsuc != NULL){
        printf("%d - %s\n",p->cod_sucursal,p->barrio);
        p = p->sigsuc;
	}
}

nodo_Sucursal* buscarSucursal(nodo_Sucursal *s){
    int suc;
    printf("Ingrese numero de sucursal \n");
    scanf("%d",&suc);

    while(s->sigsuc != NULL && s->cod_sucursal != suc){
        s = s->sigsuc;
    }
    if(s->cod_sucursal == suc){
        return s;
    }
    return NULL;
}

nodo_Cuentas* bajaCuenta(nodo_Cuentas *p){

    printf("Ingrese el numero de cuenta a eliminar\n");
    int nroCuenta;
    scanf("%d",&nroCuenta);

    nodo_Cuentas *cabecera = p;
    nodo_Cuentas *aux;

    if(nroCuenta == p->nro_cuenta){
        aux = p->sigcuenta;
        free(p);
        printf("Se elimino la cuenta %d \n",p->nro_cuenta);
        return aux;
    }else{
        printf("Nro cuenta a eliminar %d \n",p->nro_cuenta);
        while(p->nro_cuenta != nroCuenta && p->sigcuenta != NULL){
            printf("Nro cuenta %d \n",p->nro_cuenta);
            aux = p;
            p = p->sigcuenta;
        };
        if(p->sigcuenta != NULL){
            aux->sigcuenta = p->sigcuenta;
            free(p);
            printf("Se elimino la cuenta %d \n",p->nro_cuenta);
        }else{
            printf("No se encuentra el nro de cuenta \n");
        }
    }
    return cabecera;
}

void cuentas(nodo_Sucursal *s){
    s = buscarSucursal(s);
    if(s != NULL){
        printf("Sucursal %d \n",s->barrio);
        nodo_Cuentas *p = s->succuenta;

        while(p->sigcuenta != NULL){
            printf("%d %d %s %s\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
            p = p->sigcuenta;
        }
    }else{
        printf("No existe la sucursal \n");
    }

}
void nuevaSucursal(nodo_Sucursal *p){
    nodo_Sucursal *aux;
	while(p->sigsuc != NULL){
        aux = p;
        p = p->sigsuc;
	}
    p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));
	p->cod_sucursal = (aux->cod_sucursal)+1;
	printf("Ingrese Barrio \n");
	fflush(stdin);
    scanf("%39[^\n]",p->barrio);//Es con %s porque tiene un limite
    printf("Sucursal Nº %d %s agregada correctamente\n",p->cod_sucursal,p->barrio);
}

void bajaSucursal(nodo_Sucursal *p){
    printf("Ingrese el sucursal\n");
    int nroSuc;
    scanf("%d",&nroSuc);

    nodo_Sucursal *cabecera = p;
    nodo_Sucursal *aux;

    if(nroSuc == p->cod_sucursal){
        aux = p->sigsuc;

        nodo_Cuentas *auxC = p->succuenta;
        nodo_Cuentas *prev;
        while(auxC->sigcuenta != NULL){
            prev = auxC->sigcuenta;
            free(auxC);
            auxC = prev;
        }

        free(p);
        printf("Se elimino la sucursal %d \n",p->cod_sucursal);
        return aux;
    }else{
        printf("Nro sucursal a eliminar %d \n",p->cod_sucursal);
        while(p->cod_sucursal != nroSuc && p->sigsuc != NULL){
            printf("Nro sucursal %d \n",p->cod_sucursal);
            aux = p;
            p = p->sigsuc;
        };
        if(p->sigsuc != NULL){
            aux->sigsuc = p->sigsuc;

            printf("Cuenta P %d\n",p->succuenta->nro_cuenta);
            nodo_Cuentas *auxC = p->succuenta;
            nodo_Cuentas *prev;
            while(auxC->sigcuenta != NULL){
                prev = auxC->sigcuenta;
                free(auxC);
                auxC = prev;
            }

            free(p);
            printf("Se elimino la sucursal %d \n",nroSuc);
        }else{
            printf("No se encuentra el nro de sucursal \n");
        }
    }
    return cabecera;



}
void nuevaCuenta(nodo_Sucursal* s){
    s = buscarSucursal(s);

    nodo_Cuentas* n = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
    n->cod_sucursal = s->cod_sucursal;

    printf("Ingrese nombre_apellido \n");
    scanf("%s",n->nombreyapellido);

    n->saldo = 0;

    printf("Ingrese tipo de cuenta \n");
    scanf("%s",n->tipo_de_cuenta);

    nodo_Cuentas *r = s->succuenta;

    nodo_Cuentas* ultimaCuenta;
    while(r->sigcuenta != NULL){
        ultimaCuenta = r;
        r = r->sigcuenta;
    }

    n->nro_cuenta = ultimaCuenta->nro_cuenta+1;
    r->sigcuenta = n;

    printf("Se ha ingresado la cuenta nro %d \n",n->nro_cuenta);
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
    listaCuentas = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));

    nodo_Sucursal *listaSucursales;
    listaSucursales = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));

    //Multilistas
    //listaSucursales->succuenta = listaCuentas;

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
							sucursales(listaSucursales);
							wait();
							break;
						case 2 :
							cuentas(listaSucursales);
							wait();
							break;
						case 3 :
							nuevaSucursal(listaSucursales);
							wait();
							break;
						case 4 :
							bajaSucursal(listaSucursales);
							sucursales(listaSucursales);
							wait();
							break;
						case 5 :
							nuevaCuenta(listaSucursales);
							wait();
							break;
						case 6 : {
						    nodo_Sucursal* suc = buscarSucursal(listaSucursales);
                            suc->succuenta = bajaCuenta(suc->succuenta);
							wait();
							break;
						}
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
