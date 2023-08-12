/*
 * main.c
 *
 *  Created on: Sep 9, 2022
 *      Author: hp
 */
# include "STD_TYPES.h"
# include "DIO_interface.h"
# include "LCD_interface.h"
# include "KPD_interface.h"
# include "KPD_config.h"

# include <util/delay.h>




int main ()
{
	/*----------------------------------------------------------LCD--------------------------------------------------------------------------------*/
		DIO_VidSetPortDirection(Port_D,0b11100000); // LCD CMD Pins  : Port_D {7,6,5--->OutPut} RS,RW,E respectively only
		DIO_VidSetPortDirection(Port_C,0b11111111); // LCD DATA Pins : Port_C {7,6,5,4,3,2,1,0--->OutPut}
	//---------------------------------------------------------------------------------------------------------------------------------------------
	/*----------------------------------------------------------KPD--------------------------------------------------------------------------------*/
		DIO_VidSetPortDirection(Port_A,0b00001111); // KPD Pins      : Port_A {7,6,5,4-->Input} R4,R3,R2,R1 | {3,2,1,0-->Output} C1,C2,C3,C4 (Gnd)
		DIO_VidSetPortValue(Port_A,0b11110000);     // Pullup Reseistors activation for KPD Input pins : R4,R3,R2,R1
	//---------------------------------------------------------------------------------------------------------------------------------------------
	/*---------------------------------------------------DC Motor,LEDs,Buzzer----------------------------------------------------------------------*/
													// DC Motor Pins : Port_B {3,2,1,0-->Output} AntiClockwise<-Pin1,Pin2   ,  Clockwise<-Pin1,Pin0
		DIO_VidSetPortDirection(Port_B,0b11111111); // LEDs Pins     : Port_B {6(Green),5(Yellow),4(Red)-->Output}
		                                            // Buzzer Pins   : Port_B {7-->Output}
	//---------------------------------------------------------------------------------------------------------------------------------------------

		u8 x=0,y,start,button,HOURS,Hours,MINUTES,Minutes,SECONDS,Seconds;
		s8 i,j,k,l,m,n;

		u8 Date_Arr[10]={'0','0','/','0','0','/','0','0','0','0'};
		u8 YPos_ArrD[8]={0,1,3,4,6,7,8,9};

		u8 Watch_Arr[11]={'0','0',':','0','0',':','0','0',' ','_','_'};
		u8 YPos_ArrT[8]={0,1,3,4,6,7,9,10};

		LCD_VidDisplayClear();
		LCD_VidInit();

		LCD_VidSendString("   WELCOME To");
		LCD_VidGotoXY(1,1);
		LCD_VidSendString(" DigitalWatch");
		_delay_ms(1000);

		LCD_VidDisplayClear();

		LCD_VidSendString("Date:00/00/0000");
		LCD_VidGotoXY(1,5);
		LCD_VidSendData('^');

		y=0;

		while (1)
		{
			button=KPD_u8GetPressedKey();
			if (button!=101)
			{
				if (button=='R')
				{
					_delay_ms(100);
					if (y<7)
					{
						LCD_VidGotoXY(1,5+YPos_ArrD[y]);
						LCD_VidSendData(' ');

						y++;
						LCD_VidGotoXY(1,5+YPos_ArrD[y]);
						LCD_VidSendData('^');
					}


				}
				else if (button=='L')
				{
					_delay_ms(100);
					if (y>0)
					{
						LCD_VidGotoXY(1,5+YPos_ArrD[y]);
						LCD_VidSendData(' ');

						y--;
						LCD_VidGotoXY(1,5+YPos_ArrD[y]);
						LCD_VidSendData('^');
					}

				}
				else if (button=='S')
				{
					LCD_VidGotoXY(1,5+YPos_ArrD[y]);
					LCD_VidSendData(' ');

					break;
				}
				else
				{
					LCD_VidGotoXY(0,5+YPos_ArrD[y]);
					Date_Arr[YPos_ArrD[y]]=button;
					LCD_VidSendData(Date_Arr[YPos_ArrD[y]]);
					LCD_VidGotoXY(1,5+YPos_ArrD[y]);
					LCD_VidSendData('^');

				}

			}//if

		}//While

		LCD_VidDisplayClear();
		LCD_VidSendString("Time:00:00:00 __");
		LCD_VidGotoXY(1,5);
		LCD_VidSendData('^');
		y=0;

		while (1)
		{
			button=KPD_u8GetPressedKey();
			if (button!=101)
			{
				if (button=='R')
				{
					_delay_ms(100);
					if (y<7)
					{
						LCD_VidGotoXY(1,5+YPos_ArrT[y]);
						LCD_VidSendData(' ');

						y++;
						LCD_VidGotoXY(1,5+YPos_ArrT[y]);
						LCD_VidSendData('^');
					}


				}
				else if (button=='L')
				{
					_delay_ms(100);
					if (y>0)
					{
						LCD_VidGotoXY(1,5+YPos_ArrT[y]);
						LCD_VidSendData(' ');

						y--;
						LCD_VidGotoXY(1,5+YPos_ArrT[y]);
						LCD_VidSendData('^');
					}

				}
				else if (button=='S')
				{
					LCD_VidGotoXY(1,5+YPos_ArrT[y]);
					LCD_VidSendData(' ');

					break;
				}
				else
				{
					LCD_VidGotoXY(0,5+YPos_ArrT[y]);
					Watch_Arr[YPos_ArrT[y]]=button;
					LCD_VidSendData(Watch_Arr[YPos_ArrT[y]]);
					LCD_VidGotoXY(1,5+YPos_ArrT[y]);
					LCD_VidSendData('^');

				}

			}//if

		}//While

		LCD_VidDisplayClear();
		LCD_VidSendString("Date:");
		LCD_VidSendString(Date_Arr);
		LCD_VidGotoXY(1,0);
		LCD_VidSendString("Time:");
		LCD_VidSendString(Watch_Arr);

		u8 I=(Watch_Arr[0]-48),J=(Watch_Arr[1]-48),K=(Watch_Arr[3]-48),L=(Watch_Arr[4]-48),M=(Watch_Arr[6]-48),N=(Watch_Arr[7]-48),P=1,f=0;
u8 Days=(Date_Arr[0]-48)*10+(Date_Arr[1]-48),Mounth=(Date_Arr[3]-48)*10+(Date_Arr[4]-48);
u32 Year=(Date_Arr[6]-48)*1000+(Date_Arr[7]-48)*100+(Date_Arr[8]-48)*10+(Date_Arr[9]-48);
u8 E,FLAG=0;

		while(1)
		{
			for (i=I;i<=1;i++)
			{
				LCD_VidGotoXY(1,5);
				LCD_VidSendNumber(i);

				if(i==0)
				{
					E=9;
				}
				else if (i==1 && FLAG==0)
				{
					E=2;
					FLAG=1;
				}
				else if (i==1 && FLAG==1)
				{
					J=0;
					E=2;
				}

				for (j=J;j<=E;j++)
				{
					LCD_VidGotoXY(1,6);
					LCD_VidSendNumber(j);
					for (k=K;k<=5;k++)
					{
						LCD_VidGotoXY(1,8);
						LCD_VidSendNumber(k);
						for (l=L;l<=9;l++)
						{
							LCD_VidGotoXY(1,9);
							LCD_VidSendNumber(l);
							for (m=M;m<=5;m++)
							{
								LCD_VidGotoXY(1,11);
								LCD_VidSendNumber(m);
								for (n=N;n<=9;n++)
								{
									LCD_VidGotoXY(1,12);
									LCD_VidSendNumber(n);
									_delay_ms(1000);
									if (i==0&&j==9&&k==5&&l==9&&m==5&&n==9)
									{
										break;
									}

									else if (i==1&&j==1&&k==5&&l==9&&m==5&&n==9)
									{
										if (Watch_Arr[9]=='A')
										{
											Watch_Arr[9]='P';
											LCD_VidGotoXY(1,14);
											LCD_VidSendData(Watch_Arr[9]);
											P++;

										}
										else
										{
											Watch_Arr[9]='A';
											LCD_VidGotoXY(1,14);
											LCD_VidSendData(Watch_Arr[9]);
											P++;

											if (Days<30)
											{
												if (Days<=8 && Mounth<=12)
												{
													LCD_VidGotoXY(0,6);
												}
												else
												{
													LCD_VidGotoXY(0,5);
												}
												Days++;
												LCD_VidSendNumber(Days);
											}
											else if (Days>=30 && Mounth<12 )
											{
												LCD_VidGotoXY(0,5);
												LCD_VidSendData('0');
												Days=1;
												LCD_VidSendNumber(Days);
												if (Mounth<=8)
												{
													LCD_VidGotoXY(0,9);
												}
												else
												{
													LCD_VidGotoXY(0,8);
												}
												Mounth++;
												LCD_VidSendNumber(Mounth);
											}
											else if (Days>=30 && Mounth>=12 )
											{
												LCD_VidGotoXY(0,5);
												LCD_VidSendData('0');
												Days=1;
												LCD_VidSendNumber(Days);
												LCD_VidGotoXY(0,8);

												LCD_VidSendData('0');
												Mounth=1;
												LCD_VidSendNumber(Mounth);

												Year++;
												LCD_VidGotoXY(0,11);
												LCD_VidSendNumber(Year);
											}

										}

									}

								/* N=?------>N=9 */

								}//N=9
								N=0;

							/* M=?------>M=5 */

							}//M=5,N=9
							M=0;
							N=0;

						/* L=?------>L=9 */

						}//L=9,M=5,N=9
						L=0;
						M=0;
						N=0;

					/* K=?-1------>K=5 */

					}//K=5,L=9,M=5,N=9
					K=0;
					L=0;
					M=0;
					N=0;

				/* J=?-1------>J=2 */

				}//J=2,K=5,L=9,M=5,N=9
					J=0;
					K=0;
					L=0;
					M=0;
					N=0;


			/* I=?-1------>I=1 */


			}//I=1,J=2,K=5,L=9,M=5,N=9
//---------------------------------------------------------------------------------------------
					I=0;
					J=1;
					K=0;
					L=0;
					M=0;
					N=0;

					//FLAG=0;




		}




}//Main
