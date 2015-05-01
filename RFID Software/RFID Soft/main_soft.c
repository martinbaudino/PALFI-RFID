#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define SALIR 0

void mandarUSART(int, char*, int);
int initComunicacion(void);
int Create_Thread_Port(int *);
long Read_Port(int fd,char *,int);

int usart=0;

struct comunicacion{
    char start;
    char length;
    char CMD1;
    char CMD2;
    char PB1;
    char TXbits;
    char TXdata;
    char PB2;
    char RXbytes;
    int LRC;
}data;

void load(void)
{///////////{31}{36}{36}{30}{35}{30}{38}{33}{32}{30}{31}{30}{31}{36}
    ///////////1 6 6 0 50 8 3201016 PEPE
        data.start=0x01;
        data.length=0x06;
        data.CMD1=0x06;
        data.CMD2=0;//sin bytes
        //data.PB1=0x19;//0x32;
        data.PB1=0x32;
        data.TXbits=0x08;
        //data.TXdata=0x20;//0x7D;//=
        data.TXdata=0x7D;
        data.PB2=0x00;
        data.RXbytes=0x0A;
        data.LRC=0;
}

char bytes[10];

char calcular_LRC(int length){

    static int lrc=0,i=0;

    for(i=0; i< length; i++)
        lrc^=bytes[i];

        return lrc;
}

void mandarDatosEstadoActual(){
    int i;
    char buffer[128];
/*

010606320820000A10
{30}{31}{30}{36}{30}{36}{33}{32}{30}{38}{32}{30}{30}{30}{30}{41}{31}{30}

010606320820000A10

//01060632%.2X082000
//010606320820000a10
/////////CON D 010606500832001016
///////////////////16605083201016
*/
    sprintf(buffer, "%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X",data.start,data.length,data.CMD1,data.PB1,data.TXbits,data.TXdata,data.PB2,data.RXbytes,data.LRC);
    for(i=0; buffer[i]!=0;i++);

    while(i<64){
        buffer[i]=0;
        i++;
    }
    mandarUSART(usart, buffer, strlen(buffer));
}

extern char hayDato;
extern char *strRecibido;

void analizarDatoRecibido(){
    if(!hayDato) return;
    hayDato=0;

    char dato[5];
    int i;

    for(i=0;i<5;i++) dato[i]=0;

    i=0;
    //while(strRecibido[i]!='-'){
    //        dato[i]=strRecibido[i];
    //        i++;
    //}

    //datos.peso=atoi(dato);

    printf("%s", strRecibido);
    getchar();

    /*
    Tendria que recibir algo como esto:
    010B007E01000000000020D7C94A

    01
    0B
    00
    7E

    01000000000020D7C94A

    */
}


int main(int argc, char **argv)
{
    int j=0;
    char opcion='1';

    load();//cargo los datos en la estructura

    bytes[0]=data.length;
    bytes[1]=data.CMD1;
    bytes[2]=data.PB1;
    bytes[3]=data.TXbits;
    bytes[4]=data.TXdata;
    bytes[5]=data.PB2;
    bytes[6]=data.RXbytes;

    for(j=0;j<7;j++)
    printf("\nByte[%d]=%X",j,bytes[j]);

    data.LRC=calcular_LRC(data.length+1);

    printf("\nLRC: %X \n",data.LRC);

    //*************************************************************************

    usart=initComunicacion();
    Create_Thread_Port(&usart);

    if(hayDato==1) hayDato=0;
    do{
            // system("cls");
            printf("MENU\n");
            //opcion=getchar(); // esto va a recibir el enter también
            opcion='2';
            analizarDatoRecibido();

            switch(opcion)
            {
                case '1':   system("cls");

                            printf("INGRESE LAS VARIABLES DE LA FORMULA\n");


                            break;

                case '2':   system("cls");

                            mandarDatosEstadoActual();
                            //opcion='4';

                            break;

                case '3':   opcion=SALIR; break;
                case '4':   break;
            }
            getchar();

        } while(opcion!=SALIR);




    return 0;
}
