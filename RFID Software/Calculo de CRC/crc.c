#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


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
{
        data.start=0x01;
        data.length=0x06;
        data.CMD1=0x06;
        data.CMD2=0;//sin bytes
        data.PB1=0x32;
        data.TXbits=0x08;
        data.TXdata=0x20;
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


int main(int argc, char **argv)
{
    int j=0;

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


    return 0;
}

/*
 *
 * Intentando separar otra trama
 *
 * 010D0632402100000000007F260F0A04
 *
start  01
length 0D 13 bytes
CMD1 06
PB1 32
TXbits  40
TXdata 21
PB2 00
 00
000000
7F
26
0F

RxBytes 0A
LRC 04


*/


