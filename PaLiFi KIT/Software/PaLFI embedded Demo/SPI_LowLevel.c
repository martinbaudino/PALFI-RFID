/******************************************************************************\
*           Copyright (C) 2005 Texas Instruments
*                           All Rights Reserved
*------------------------------------------------------------------------------
* FILENAME...... SPI_LowLevel.c
* DATE CREATED.. 10/21/2008
* WRITTEN BY.... J. Austen, S.Recknagel
*
*   Implementation of the Basic SPI communication from a microcontroller to the TMS37157 Frontend
*   Basic functionaly:
*       - Initialization of the SPI interface of the MSP430F2274
*       - Transmit bytes to the Frontend
*       - Receive bytes from the Frontend
*
*------------------------------------------------------------------------------
* HISTORY:
*


\******************************************************************************/
#include  "PaLFI_Transponder.h"
#include  "msp430x22x4.h"

/******************************************************************************/

unsigned char ucTX_ONLY;
extern unsigned char ucWDT_Count;

/******************************************************************************/
void MSP430_SPI_Init(void)
 /****************************************************************************************
  *
  *  Initialization of the SPI Interface
  *
  *   SPI_SIMO	  // P3.1 Output
  *   SPI_SOMI	  // P3.2 Input
  *   SPI_CLK 	  // P3.3 Output
  *   TMS_BUSY	  // P2.0 Input
  *   PUSH		  // P2.2 Output
  *   CLK_AM	  // P2.1 Input
  *
  ****************************************************************************************/
{  
  P2DIR |= CU_PUSH;							// Push Output
  P2DIR &= ~CU_BUSY;						// Busy Input
  P2DIR &= ~CLK_AM;							// CLK_AM Input	
  
  P2SEL |= CLK_AM;							// TACLK Function for CLK_AM
  
  P3OUT = 0;								
  P3SEL |= SPI_SIMO + SPI_SOMI + SPI_CLK;	// Configure Port 3 for SPI functions
     
  UCB0CTL0 |= UCMSB + UCMST + UCSYNC;       // 3-pin, 8-bit SPI mstr, MSB 1st
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x08;							// SPICLK = 2MHz/8 (About 250kHz)
  UCB0BR1 = 0;
  UCB0CTL1 |= UCSWRST;                     // **don't activate SPI yet

}


//******************************************************************************

void ErrorMode(void)
{
	WDTCTL = WDT_MRST_0_064;
	//for(;;);					// MCU restart....
}
/******************************************************************************/
void Wake_PaLFI(void)
{
  	P2OUT |= CU_PUSH;						// pess push at PaLFI, to wake up PaLFI

	while ((P2IN & CU_BUSY) == 0x00);
  	while ((P2IN & CU_BUSY) == CU_BUSY);	// wait until PaLFI is ready

  	P2OUT &= ~CU_PUSH;						// release PUSH
}

void Stop_SPI_WDT(void)
{
    WDT_HOLD();
    ucWDT_Count = 0;
    IE1 &= ~WDTIE;
}

void Wait_for_Busy_low (void)
{
  	while ((P2IN&CU_BUSY) == CU_BUSY);	// wait until busy goes low, PaLFI is ready then  
}

void Start_SPI_WDT(void)
{
    WDT_HOLD();
/*
    ucWDT_Count = 0;
    WDT_INTERVAL_MODE();                      // Start timer in interval mode
    IE1 |= WDTIE;
    _EINT();                                  // Enable interrupts
    */ //Error
}


/******************************************************************************/
unsigned char MSP430_SPI_Rx(unsigned char *RxBuffer, unsigned char size)
 /****************************************************************************************
  *
  *  Receive a telegram with the SPI Emulation
  *
  ****************************************************************************************/
{
    if(!size) return Fail;					        		// invalid data size

    size--;
	do
	{
		UCB0TXBUF = 0x00;                       // Dummy write to start SPI
	    while (!(IFG2 & UCA0TXIFG));
      	while((P2IN & CU_BUSY) == CU_BUSY);
	    while(!(P2IN & CU_BUSY));
   	  	*RxBuffer++ = UCB0RXBUF;
	}while(--size);
	
    UCB0TXBUF = 0x00;                       // Dummy write to start SPI
    while (!(IFG2 & UCB0TXIFG));
    while((P2IN & CU_BUSY) == CU_BUSY);
    *RxBuffer = UCB0RXBUF;

    return Okay;
}



/******************************************************************************/
unsigned char MSP430_SPI_Tx(unsigned char *TxBuffer, unsigned char size)
{
    if(!size) return Fail;					        	// invalid data size

    if((P2IN & CU_BUSY) == CU_BUSY) return Fail;	  	// Control Unit is not ready(Busy is high)
    if (!(IFG2 & UCA0TXIFG)) return Fail;					// MSP430 SPI Tx buffer is not ready.
	  do
    	 {
            UCB0TXBUF = *TxBuffer++;
            while (!(IFG2 & UCB0TXIFG));
            while((P2IN & CU_BUSY) == CU_BUSY);
            if (ucTX_ONLY && size == 0x01)
                ;                           			// Only transmit data to frontend then busy line stays low after last SPI byte !
            else
                while(!(P2IN & CU_BUSY));               // wait until busy goes from low to high again
	      }while(--size);
    Stop_SPI_WDT();
	  return Okay;
}






