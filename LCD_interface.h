/***************************************************************************************************************************************************************************************/
/************************************************* SWE     : LCD DRIVER              *************************************************************************************************************/
/************************************************* BY      : Youssef Ayman           *************************************************************************************************************/
/************************************************* Date    : 27Aug20                 *************************************************************************************************************/
/************************************************* Version : v1.0                    *************************************************************************************************************/
/***************************************************************************************************************************************************************************************/


# ifndef LCD_INTERFACE_H
# define LCD_INTERFACE_H





/*    */

void LCD_VidSendCmd (u8 Copy_u8Cmd);

/*   */

void LCD_VidSendData (u8 Copy_u8Data); 


/*   */

void LCD_VidInit (void);


/*   */

void LCD_VidDisplayClear (void);

/*   */

void LCD_VidSendNumber (u32 Copy_u32Number);



/*   */

void LCD_VidGotoXY (u8 Copy_u8X , u8 Copy_u8Y);


/*   */


void LCD_VidCompleteInSecondLineInString (u8 *pu8String);


void LCD_VidSendString (u8 *pu8String);

/*   */

void LCD_VidSendSpecialChar (u8 *Patern,u8 Patrn_num,u8 Copy_u8Xpos,u8 Copy_u8Ypos);

/*   */

void LCD_VidSendValue (u32 Copy_u8Value);









#endif
