/*****************************************************************************/
/* compress.c                                                                */
/* compress <track2> <hex offset> <image> <hex_off_start> <hex_off_finish>   */
/*****************************************************************************/

#include "stdio.h"


FILE * inp1;
FILE * inp2;
long int offset1, offset2;
long int offset1a, offset2a;
long int offset3;

unsigned char buff1[1000000];
unsigned char buff2[1000000];
unsigned char array[10];


int atohex(char * str)
{
int hex, i;

   hex = 0;

   for (i = 0; i < strlen(str); i++)
   {
      hex *= 16;

      if (str[i] <= '9')
      {
         hex += (str[i] - '0');
      }
      else if (str[i] <= 'F')
      {
         hex += (str[i] - 'A') + 10;
      }
      else if (str[i] <= 'f')
      {
         hex += (str[i] - 'a') + 10;
      }
      else
         hex = 0;
   }

   return (hex);
}


int main(int argc, char * argv[])
{
int i, j, c, len1, len2, diff, dummy, match;
int startat, inpbit, bitcount, octetcount, errorcount;

   inp1 = fopen(argv[1], "rb");
   inp2 = fopen(argv[3], "rb");

   if (inp1 == NULL) {
      printf("failed to open %s\n", argv[1]);
      exit(1);
   }

   if (inp2 == NULL) {
      printf("failed to open %s\n", argv[3]);
      exit(1);
   }

   i = 0;
   dummy = 0;

   while (!feof(inp1)) {
      dummy = fread( &buff1[i++], 1, 1, inp1);
   }

   len1 = i - 1;
   printf("size of file %s = %ld\n\n", argv[1], len1);


   i = 0;
   dummy = 0;

   while (!feof(inp2)) {
      dummy = fread( &buff2[i++], 1, 1, inp2);
   }

   len2 = i - 1;
   printf("size of file %s = %ld\n\n", argv[3], len2);

   offset1 = atohex(argv[2]);
   offset2 = atohex(argv[4]);
   offset3 = atohex(argv[5]);

/* read through 128 sprites @ output of 0x80 bytes for each sprite */

   offset1a = offset1;
   offset2a = offset2;

   octetcount = 0;

   while (offset2a < offset3)
   {
      printf("input file pos = %6.6x, output file pos = %6.6x, input bitmap = %2.2x\n", offset1a, offset2a, inpbit);

      for (i = 0; i < 16; i++)
      {
	 buff2[offset2a + i] = buff1[offset1a + i];
      }

      offset2a += 32;
      offset1a += 32;
   }

   fclose(inp1);
   fclose(inp2);

   inp2 = fopen(argv[3], "wb");

   if (inp2 == NULL) {
      printf("failed to open %s\n", argv[3]);
      exit(1);
   }

   for (i = 0; i < len2; i++)
   {
      fputc(buff2[i], inp2);
   }

   fclose(inp2);
}

