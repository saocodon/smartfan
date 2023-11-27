#include "stdutils.h"
#include "nec_ir.h"
#include "dht11.h"

sbit LD7 = P1^4;
sbit RD7 = P1^5;
int I_RH,D_RH,I_Temp,D_Temp,CheckSum;
int I_Temp_C, I_Temp_D;

void delayms(int ms) {
	unsigned int i, j;
	for (i = 0; i < ms; i++)
		for (j = 0; j < 123; j++);
}

void main() {
	unsigned int i;
	uint32_t key;
	IR_RemoteInit(); // Initialize the INT0 and Timer0 for decoding the IR pulses
	while (1) {
		/* ======================= DHT11 ======================= */
		Request();	/* send start pulse */
		Response();	/* receive response */
		
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		
		if ((I_RH + D_RH + I_Temp + D_Temp) == CheckSum)
		{
			// output I_Temp to 7seg display
			I_Temp_C = I_Temp / 10;
			I_Temp_D = I_Temp % 10;
		}
		// always do
		for (i = 0; i < 125; i++) {
		    LD7 = 1; RD7 = 0; P1 |= 15;
			P1 = (P1 & (240 + I_Temp_C));
			delayms(20);
			LD7 = 0; RD7 = 1; P1 |= 15;
			P1 = (P1 & (240 + I_Temp_D));
			delayms(20);
		}
		/* ======================= REMOTE ======================= */
		key = IR_RemoteGetKey(); // Read the key press, it returns key code if key press is detected, else it returns 0
		switch (key) {
			default:
				break;
		}
	}
}