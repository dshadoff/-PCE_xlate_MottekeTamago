/*****************************************************************************/
/* sprite1.c                                                                 */
/*****************************************************************************/
#include "stdio.h"

/*
#define ARRAY_X		16
#define ARRAY_Y		16
*/

#define ARRAY_X		128
#define ARRAY_Y		32

FILE * inp;
FILE * img;
FILE * out;
unsigned char buff[1000000];
unsigned array[ARRAY_X * ARRAY_Y + 1];



/*
putsprite(long int offset, int x, int y)
{
   unsigned int x1, y1, temp, temp1, temp2, temp3, temp4, temp5;

   for (y1 = 0; y1 < 16; y1++)
   {
      temp1 = (buff[offset + (y1*2) + 0x01] << 8) | buff[offset + (y1*2) + 0x00];
      temp2 = (buff[offset + (y1*2) + 0x21] << 8) | buff[offset + (y1*2) + 0x20];
      temp3 = (buff[offset + (y1*2) + 0x41] << 8) | buff[offset + (y1*2) + 0x40];
      temp4 = (buff[offset + (y1*2) + 0x61] << 8) | buff[offset + (y1*2) + 0x60];

*
      printf("%4x\n",temp1);
      printf("%4x\n",temp2);
      printf("%4x\n",temp3);
      printf("%4x\n\n",temp4);
*

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
*/

putsprite(long int offset, int x, int y)
{
   unsigned int x1, y1, temp, temp1, temp2, temp3, temp4, temp5;

   for (y1 = 0; y1 < 16; y1++)
   {
      temp1 = 0;
      temp2 = 0;
      temp3 = 0;
      temp4 = 0;

      for (x1 = 0; x1 < 16; x1++)
      {

	 temp = 0x8000 >> x1;

         temp5 = array[((y+y1) * ARRAY_X) + (x+x1)];

	 temp1 |= (temp5 & 8) ? temp : 0;
	 temp2 |= (temp5 & 4) ? temp : 0;
	 temp3 |= (temp5 & 2) ? temp : 0;
	 temp4 |= (temp5 & 1) ? temp : 0;
      }

      buff[offset + (y1*2) + 0x00] = temp1 & 0xff;
      buff[offset + (y1*2) + 0x01] = temp1 >> 8;
      buff[offset + (y1*2) + 0x20] = temp2 & 0xff;
      buff[offset + (y1*2) + 0x21] = temp2 >> 8;
      buff[offset + (y1*2) + 0x40] = temp3 & 0xff;
      buff[offset + (y1*2) + 0x41] = temp3 >> 8;
      buff[offset + (y1*2) + 0x60] = temp4 & 0xff;
      buff[offset + (y1*2) + 0x61] = temp4 >> 8;
   }
}


int main(int argc, char * argv[])
{
int i, j, x, y, c, len, diff, dummy, match;
int startat;
char fname[40];
char ch;

   strcpy(fname, argv[1]);
   fname[strlen(fname)-3] = 'n';
   fname[strlen(fname)-2] = 'e';
   fname[strlen(fname)-1] = 'w';

   inp = fopen(argv[1], "rb");
   img = fopen(argv[2], "rb");
   out = fopen(fname, "wb");

   if (inp == NULL) {
      printf("failed to open %s\n", argv[1]);
      exit(1);
   }

   if (img == NULL) {
      printf("failed to open %s\n", argv[2]);
      exit(1);
   }

   if (out == NULL) {
      printf("failed to open %s\n", fname);
      exit(1);
   }


   i = 0;
   dummy = 0;

   while (!feof(inp))
   {
      dummy = fread(&buff[i++], 1, 1, inp);
   }

   len = i-1;
   printf("size of file = %ld\n\n", len);


   x = 0;
   y = 0;
   while (!feof(img))
   {
      dummy = fread(&ch, 1, 1, img);
      if (ch == '\n') {
         y++;
	 x = 0;
	 continue;
      }
      array[(y * ARRAY_X) + x] = ch - '0';
      x++;
   }

   putsprite(0x12558,  0,  0);
   putsprite(0x125d8, 16,  0);
   putsprite(0x12658,  0, 16);
   putsprite(0x126d8, 16, 16);
   putsprite(0x12758, 64,  0);
   putsprite(0x127d8, 80,  0);
   putsprite(0x12858, 64, 16);
   putsprite(0x128d8, 80, 16);
   putsprite(0x12d58, 32,  0);
   putsprite(0x12dd8, 48,  0);
   putsprite(0x12e58, 32, 16);
   putsprite(0x12ed8, 48, 16);
   putsprite(0x12f58, 96,  0);
   putsprite(0x12fd8,112,  0);
   putsprite(0x13058, 96, 16);
   putsprite(0x130d8,112, 16);

   for (i = 0; i < ARRAY_Y; i++)
   {
      for (j = 0; j < ARRAY_X; j++)
      {
         printf("%c", (array[ ((i * ARRAY_X) + j) ] + '0') );
      }
      printf("\n");
   }

   for (i = 0; i < len; i++)
   {
      fputc(buff[i], out);
   }

   fclose(out);
   fclose(img);
   fclose(inp);

}
