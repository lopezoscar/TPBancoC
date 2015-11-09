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


void cargarCuentas(nodo_Cuentas *p,int cod_suc){
    FILE *cuentas;
//    printf("Leyendo Cuentas\n");
    int cod;
    int cuenta;
    char *nombre[40];
    char *tipo[2];
    int saldo;

    int contadorCuentas = 0;
    if( (cuentas = fopen("Cuentas.txt","r")) == NULL){
        printf("NO SE PUEDE LEER EL ARCHIVO\n");
    }else{
        while(!feof(cuentas)){
            fscanf(cuentas,"%d;%d;%39[^\;];%9[^\;];%d\n",&cod,&cuenta,nombre,tipo,&saldo);

            if(cod_suc == cod){
                p->cod_sucursal = cod;
                p->nro_cuenta = cuenta;
                strcpy(p->nombreyapellido,nombre);
                strcpy(p->tipo_de_cuenta,tipo);
                p->saldo = saldo;

                p->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));

                printf("%d %d %s %s %d\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                p = p->sigcuenta;
                contadorCuentas++;
            }
        }
        p->sigcuenta = NULL;
        fclose(cuentas);

        if(contadorCuentas == 0){
            printf("La sucursal %d no tiene cuentas \n",cod_suc);
        }

    }
}



void cargarSucursales(nodo_Sucursal *p){
    FILE *sucursalesFile;
//    printf("Leyendo Sucursales\n");

    if((sucursalesFile = fopen("Sucursales.txt","r")) == NULL ){
        printf("NO SE PUDO LEER EL ARCHIVO\n");
    }else{
        while(!feof(sucursalesFile)){
            fscanf(sucursalesFile,"%d;%39[^\n]\n",&p->cod_sucursal,p->barrio);
            //printf("%d %s \n",p->cod_sucursal,p->barrio);

            p->succuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
            cargarCuentas(p->succuenta,p->cod_sucursal);

            p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));

            p = p->sigsuc;
        }
        p->sigsuc = NULL;
    }
    fclose(sucursalesFile);
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
        printf("Ingresa al while SUCURSAL\n");
        while(s->sigsuc != NULL){
            nodo_Cuentas *p = s->succuenta;
            printf("Sucursal %d \n",s->cod_sucursal);
            if(p != NULL){
                while(p->sigcuenta != NULL){
                    printf("CUENTA  %d \n",p->nro_cuenta);
                    fprintf(cuentas,"%d;%d;%s;%s;%d\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                    p = p->sigcuenta;
                }
            }else{
                printf("LA SUCURSAL NO TIENE CUENTAS \n");
            }
            s = s->sigsuc;
        }
        printf("Fin grabar cuentas \n");
        fclose(cuentas);
    }
}

void grabarSucursales(nodo_Sucursal *p){
    printf("Grabando Sucursales\n");

    FILE *sucursales;
    if( (sucursales = fopen("Sucursales.txt","w")) == NULL){
        printf("NO SE PUEDE GRABAR EL ARCHIVO\n");
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
        printf("NO SE PUEDE GRABAR EL ARCHIVO\n");
    }else{
        while(p->sigclien != NULL){
            //printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);
            fprintf(clientes,"%d;%d;%s;%s;%d\n",p->cod_sucursal,p->nro_cuenta,p->tipo_de_cuenta,p->tipo_de_movimiento,p->monto);
            p = p->sigclien;
        }
        fclose(clientes);
    }
}

void grabarDeudores(nodo_Cuentas *p){
    printf("Grabando deudores \n");
    if(p->saldo > 0 || p->sigcuenta == NULL){
        printf("No hay deudores para grabar\n");
    }else{
        FILE *deudoresFILE;
        printf("Creando archivo deudores \n");
        if( (deudoresFILE = fopen("Deudores.txt","w"))== NULL){
            printf("NO SE PUEDE GRABAR EL ARCHIVO");
        }else{
            printf("While deudores \n");
            while(p->sigcuenta != NULL){
                fprintf(deudoresFILE,"%d;%d;%s;%s;%d\n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                p = p->sigcuenta;
            }
        }
        printf("Fin deudores \n");
        fclose(deudoresFILE);
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


void postEjecucion(nodo_Clientes *listaClientes,nodo_Cuentas *listaCuentas,nodo_Sucursal *listaSucursales,nodo_Cuentas *listaDeudores){
	grabarClientes(listaClientes);
	grabarSucursales(listaSucursales);
	grabarCuentas(listaSucursales);
    grabarDeudores(listaDeudores);


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
        printf("Sucursal %s \n",s->barrio);
        nodo_Cuentas *p = s->succuenta;

        if(p->sigcuenta == NULL){
            printf("La sucursal no posee cuentas\n");
        }else{
            while(p->sigcuenta != NULL){
                printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
                p = p->sigcuenta;
            }
        }
    }else{
        printf("No existe la sucursal \n");
    }

}
/*
void nuevaSucursal(nodo_Sucursal *p){
    nodo_Sucursal *aux;
	while(p->sigsuc != NULL){
        aux = p;
        p = p->sigsuc;
	}
	p->succuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
    p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));

	p->cod_sucursal = (aux->cod_sucursal)+1;

	printf("Ingrese Barrio \n");
	fflush(stdin);
    scanf("%39[^\n]",p->barrio);//Es con %s porque tiene un limite
    printf("Sucursal Nº %d %s agregada correctamente\n",p->cod_sucursal,p->barrio);
}
*/
void nuevaSucursal(nodo_Sucursal *p){
    nodo_Sucursal *aux;
	while(p->sigsuc != NULL){
        aux = p;
        p = p->sigsuc;
	}
	p->succuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
    p->sigsuc = (nodo_Sucursal*)malloc(sizeof(nodo_Sucursal));

	p->cod_sucursal = (aux->cod_sucursal)+1;

	printf("Ingrese Barrio \n");
	fflush(stdin);
    scanf("%39[^\n]",p->barrio);//Es con %s porque tiene un limite
    printf("Sucursal Nº %d %s agregada correctamente\n",p->cod_sucursal,p->barrio);
}
nodo_Sucursal* bajaSucursal(nodo_Sucursal *p){
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
        printf("Se elimino la sucursal %d \n",nroSuc);
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

            //printf("Cuenta P %d\n",p->succuenta->nro_cuenta);
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

void nuevaCuenta(nodo_Sucursal *s){
    s = buscarSucursal(s);


    nodo_Cuentas *r;
    r = s->succuenta;

    //Si es la primer cuenta
    if(r->sigcuenta == NULL){
        //s->succuenta->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
        //r = s->succuenta;

        r->cod_sucursal = s->cod_sucursal;

        printf("Ingrese nombre_apellido \n");
        scanf("%s",r->nombreyapellido);

        r->saldo = 0;

        printf("Ingrese tipo de cuenta \n");
        scanf("%s",r->tipo_de_cuenta);

        r->nro_cuenta = (s->cod_sucursal*1000)+1;
        printf("FIN IF \n");

        printf("Se ha ingresado la cuenta nro %d \n",r->nro_cuenta);

        //CLAVE Agregar el nodo aca para que siga
        //s->succuenta->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
        r->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
        r->sigcuenta->sigcuenta = NULL;

    }else{
        printf("EJECUTA WHILE \n");
        while(r->sigcuenta != NULL && r->sigcuenta->sigcuenta != NULL){
            printf("ENTRO WHILE \n");
            r = r->sigcuenta;
        }
        printf("FIN WHILE \n");
        r->sigcuenta->cod_sucursal = s->cod_sucursal;

        printf("Ingrese nombre_apellido \n");
        scanf("%s",r->sigcuenta->nombreyapellido);

        r->sigcuenta->saldo = 0;

        printf("Ingrese tipo de cuenta \n");
        scanf("%s",r->sigcuenta->tipo_de_cuenta);

        r->sigcuenta->nro_cuenta = r->nro_cuenta+1;

        /*
         * COMENTAR funcionamiento
         */


        if(r->cod_sucursal == NULL){
            r = r->sigcuenta;
            r->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
        }else{
            r->sigcuenta->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));
        }

        printf("Se ha ingresado la cuenta nro %d \n",r->sigcuenta->nro_cuenta);
    }

    /*
    nodo_Cuentas *p = s->succuenta;
    if(p->sigcuenta->sigcuenta == NULL){
        printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
    }else{
        while(p->sigcuenta != NULL){
            printf("%d %d %s %s %d \n",p->cod_sucursal,p->nro_cuenta,p->nombreyapellido,p->tipo_de_cuenta,p->saldo);
            p = p->sigcuenta;
        }
    }
    */



}


void actualizarSaldos(nodo_Clientes *c,nodo_Sucursal *s){

    /*Recorro todos los clientes*/
    while(c->sigclien != NULL){
        int suc = c->cod_sucursal;

        /*Busca sucursal*/
        while(s->sigsuc != NULL && s->cod_sucursal != suc){
            s = s->sigsuc;
        }
        /*Si encontro sucursal*/
        if(s->cod_sucursal == suc){

            printf("Encontro sucursal \n");

            nodo_Cuentas *cCuenta = s->succuenta;
            /*Se busca la cuenta del cliente*/
            while(cCuenta->sigcuenta != NULL && cCuenta->nro_cuenta != c->nro_cuenta){
                cCuenta = cCuenta->sigcuenta;
            }

            if(cCuenta->nro_cuenta == c->nro_cuenta){
                printf("Encontro cuenta\n",c->nro_cuenta);
                if(strcmp(c->tipo_de_cuenta, cCuenta->tipo_de_cuenta) == 0 ){
                    printf("MISMO TIPO DE CUENTA\n");

                    printf("Tipo de Movimiento %s\n",c->tipo_de_movimiento);


                    if(c->tipo_de_movimiento[0] =='D'){
                        printf("DEPOSITO\n");
                        cCuenta->saldo += c->monto;
                    }
                    //Extraccion
                    if(c->tipo_de_movimiento[0] == 'E'){
                        cCuenta->saldo -= c->monto;
                        printf("EXTRACCION\n");
                    }

                }else{
                    printf("NO COINCIDE EL TIPO DE CUENTA\n");
                }
            }else{
                printf("No se encontro la cuenta\n");
            }

            /*Si encontro la cuenta*/



        }else{
            printf("no existe la sucursal\n");
        }
        //Siempre se trata de aplicar los movimientos aunque no exista sucursal o cuenta en ese momento.
        c = c->sigclien;
    }
}

void deudores(nodo_Sucursal *s, nodo_Cuentas *d){
    //Recorro todas las sucursales
    while(s->sigsuc != NULL){

        nodo_Cuentas *c = s->succuenta;
        /* Por todas las cuentas */
        while(c->sigcuenta != NULL){

            if(c->saldo < 0){

                d->cod_sucursal = c->cod_sucursal;
                strcpy(d->nombreyapellido,c->nombreyapellido);
                d->nro_cuenta = c->nro_cuenta;
                d->saldo = c->saldo;
                strcpy(d->tipo_de_cuenta,c->tipo_de_cuenta);

                d->sigcuenta = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));

                d = d->sigcuenta;
            }
            c = c->sigcuenta;
        }
        s = s->sigsuc;
    }
    d->sigcuenta = NULL;
}

void mostrarDeudores(nodo_Cuentas *aux){
    if(aux->sigcuenta == NULL){
        printf("No hay deudores\n");
    }else{
        while(aux->sigcuenta != NULL){
            printf("%d %d %s %s %d \n",aux->cod_sucursal,aux->nro_cuenta,aux->nombreyapellido,aux->tipo_de_cuenta,aux->saldo);
            aux = aux->sigcuenta;
        }
    }

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

    nodo_Cuentas *listaDeudores;
    listaDeudores = (nodo_Cuentas*)malloc(sizeof(nodo_Cuentas));

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
							listaSucursales = bajaSucursal(listaSucursales);
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
							actualizarSaldos(listaClientes,listaSucursales);
							wait();
							break;
						case 8:
							deudores(listaSucursales,listaDeudores);
                            mostrarDeudores(listaDeudores);
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

    postEjecucion(listaClientes,listaCuentas,listaSucursales,listaDeudores);
	return 0;
}
