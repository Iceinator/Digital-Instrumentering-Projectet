#include "Ansi.h"

/*void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White

  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}*/

//void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  //printf("%c[%dm", ESC, background+40);
//}

//void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
 // uint8_t type = 22;             // normal text
	//if (foreground > 7) {
	//  type = 1;                // bold text
	//	foreground -= 8;
	//}
 // printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
//}//

//void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
 // printf("%c[m", ESC);
//}

//void clrscr(){
    //printf("%c[%d%c", ESC, 2, 0x4a);
//}

//void clreol(){
  //  printf("%c[%c", ESC, 0x4b);
//}

//void underline(uint8_t on){
 //   if (on==1)
 //       printf("%c[%d%c", ESC, 04, 0x6d);
//    else
 //       printf("%c[%d%c", ESC, 24, 0x6d);
//}

//void blink(uint8_t on){
 //   if (on==1)
 //       printf("%c[%d%c", ESC, 05, 0x6d);
//    else
 //       printf("%c[%d%c", ESC, 25, 0x6d);
//}
/*
void revvideo(uint8_t on){
    if (on==1)
        printf("%c[%d%c", ESC, 07, 0x6d);
    else
        printf("%c[%d%c", ESC, 27, 0x6d);
}

void gotoxy(uint8_t y, uint8_t x){
    printf("%c[%d;%d%c", ESC, y,  x, 0x66);
}

void window(uint8_t y, uint8_t x, uint16_t h, uint16_t w){
    uint16_t i;
    for (i=0; i < h; i++)
    {
        printf("%c[%d;%d%c", ESC, y+i,  x, 0x66);
        printf("%c",219);
        printf("%c[%d;%d%c", ESC, y+i,  x+w, 0x66);
        printf("%c",219);
    }

    uint16_t o;
    for (o=0; o < w; o++)
    {
        printf("%c[%d;%d%c", ESC, y,  x+o, 0x66);
        printf("%c",219);
        printf("%c[%d;%d%c", ESC, y+h,  x+o, 0x66);
        printf("%c",219);
    }

    printf("%c[%d;%d%c", ESC, y,  x, 0x66);
    printf("%c",219);
    printf("%c[%d;%d%c", ESC, y,  x+w, 0x66);
    printf("%c",219);
    printf("%c[%d;%d%c", ESC, y+h,  x, 0x66);
    printf("%c",219);
    printf("%c[%d;%d%c", ESC, y+h,  x+w, 0x66);
    printf("%c",219);}



// Menu and boss key functions:

// Design of the main menu:
void main_menu(){
clrscr(); // Clearing the screen. Useful when returning to main menu.
color(2,0); // Setting the color of the foreground and background.
blink(1); // Setting the text to not blink.
revvideo(0); // Setting the text to not reverse color.

int16_t startx = 64;

gotoxy(3, startx); // Moves the cursor to desired location.
printf("Press enter to start scan");
//Press enter to mode menu

}*/



