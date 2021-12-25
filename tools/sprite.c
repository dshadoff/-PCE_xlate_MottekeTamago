/*****************************************************************************/
/* sprite.c                                                                  */
/*****************************************************************************/
#include "stdio.h"

/*
#define ARRAY_X		16
#define ARRAY_Y		16
*/

#define ARRAY_X		128
#define ARRAY_Y		32

FILE * inp;
unsigned char buff[1000000];
unsigned array[ARRAY_X * ARRAY_Y + 1];

getsprite(long int offset, int x, int y)
{
   unsigned int x1, y1, temp, temp1, temp2, temp3, temp4, temp5;

   for (y1 = 0; y1 < 16; y1++)
   {
      temp1 = (buff[offset + (y1*2) + 0x01] << 8) | buff[offset + (y1*2) + 0x00];
      temp2 = (buff[offset + (y1*2) + 0x21] << 8) | buff[offset + (y1*2) + 0x20];
      temp3 = (buff[offset + (y1*2) + 0x41] << 8) | buff[offset + (y1*2) + 0x40];
      temp4 = (buff[offset + (y1*2) + 0x61] << 8) | buff[offset + (y1*2) + 0x60];

/*
      printf("%4x\n",temp1);
      printf("%4x\n",temp2);
      printf("%4x\n",temp3);
      printf("%4x\n\n",temp4);
*/

      for (x1 = 0; x1 < 16; x1++)
      {
	 temp = 0x8000 >> x1;

	 temp5  = 0;
	 temp5 |= (temp & temp1) ? 8:0;
	 temp5 |= (temp & temp2) ? 4:0;
	 temp5 |= (temp & temp3) ? 2:0;
	 temp5 |= (temp & temp4) ? 1:0;

         array[((y+y1) * ARRAY_X) + (x+x1)] = temp5;
      }
   }
}

int main(int argc, char * argv[])
{
int i, j, c, len, diff, dummy, match;
int startat;

   inp = fopen(argv[1], "rb");

   if (inp == NULL) {
      printf("failed to open %s\n", argv[1]);
      exit(1);
   }

   i = 0;
   dummy = 0;

   while (!feof(inp))
   {
      dummy = fread(&buff[i++], 1, 1, inp);
   }

   len = i - 1;
   printf("size of file = %ld\n\n", len);

   for (i=0; i < ARRAY_X * ARRAY_Y; i++) {
      array[i] = 0;
   }

   getsprite(0x12558,  0,  0);

   getsprite(0x125d8, 16,  0);
   getsprite(0x12658,  0, 16);
   getsprite(0x126d8, 16, 16);
   getsprite(0x12758, 64,  0);
   getsprite(0x127d8, 80,  0);
   getsprite(0x12858, 64, 16);
   getsprite(0x128d8, 80, 16);
   getsprite(0x12d58, 32,  0);
   getsprite(0x12dd8, 48,  0);
   getsprite(0x12e58, 32, 16);
   getsprite(0x12ed8, 48, 16);
   getsprite(0x12f58, 96,  0);
   getsprite(0x12fd8,112,  0);
   getsprite(0x13058, 96, 16);
   getsprite(0x130d8,112, 16);


   for (i = 0; i < ARRAY_Y; i++)
   {
      for (j = 0; j < ARRAY_X; j++)
      {
         printf("%c", (array[ ((i * ARRAY_X) + j) ] + '0') );
      }
      printf("\n");
   }
}
