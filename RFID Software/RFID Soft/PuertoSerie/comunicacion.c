#define __WINDOWS_COM__
#define ENABLE_SERIAL_PORT_EVENT

#include "com/serial.h"
DCB OldConf;
char *strRecibido;
char hayDato=0;

void SERIAL_PORT_EVENT(HANDLE * hPort)
{
    char c[64];
    Read_Port(*hPort,c,64);

    strRecibido=c;
    printf("Recibido= %s\n",c);
    hayDato=1;
}

void strupper(char *str) {
    while (*str) {
        if ((*str >= 'a' ) && (*str <= 'z')) *str -= ('a'-'A');
        str++;
    }
}


void limpiarBuffer(char *cad, int cantidad){
    int i=0;
    for(i=0; i<cantidad; i++){
        cad[i]='\0';
    }
}

int commandSalir(char str[16]){
    int i=0;
    char strSalir[]="salir";
    while(str[i]==strSalir[i] && str[i]!='\0' && strSalir[i]!='\0'){i++;}
    return (i==strlen(strSalir) && strlen(strSalir)==strlen(str)) ? TRUE : FALSE;
}

void mostrarPuertosDisponibles(){
    int i;
    char puerto[7]="COM1";
    HANDLE fd;

    printf("Puertos disponibles:\n");
    for(i=0; i<500; i++){
        sprintf(puerto, "COM%d", i);
        fd=Open_Port(puerto);
        if(((int)fd)!=-1){
            strupper(puerto);
            printf("- %s\n", puerto);
            Close_Port(fd);
        }
    }
}

HANDLE ingresarPuerto(){
    HANDLE fd;
    char puerto[7]="COM2";

    do{
        printf("\nIngresar puerto (COMx):");
        scanf("%s", puerto);
        fd=Open_Port(puerto);               // Abre el puerto serie
                                        // fd=Open_Port("/dev/ttyS0");

        if((int)fd==-1) printf("Error:No se puede abrir puerto: %s \n",puerto);
    }while(((int)fd)==-1);

    strupper(puerto);
    printf("%s Abierto\n", puerto);

    return fd;
}

void mandarUSART(HANDLE fd, char *str, int tam){
    Write_Port(fd,str,tam);
}

void desconectar(HANDLE fd){
    Set_Configure_Port(fd,OldConf);     // Restituyo la antigua configuración
                                        // del puerto.
    Close_Port(fd);                     // Cierro el puerto serie.
}


int initComunicacion()
{
    HANDLE fd;

    printf("Programa para enviar y recibir por puerto Serie\n");
    printf("Escribir y presionar enter para enviar\n'salir' para salir\n");
    printf("--------------------------------------------------\n");

    mostrarPuertosDisponibles();
    fd=ingresarPuerto();

    OldConf=Get_Configure_Port(fd);     // Guardo la configuración del puerto.
    Configure_Port(fd,B9600,"8N1");   // Configuro el puerto serie.

    IO_Blocking(fd,FALSE);               // Bloqueante por defecto, pero también
                                        // se puede usar:
                                        // IO_Blocking(fd,TRUE);



    return (int)fd;
}

