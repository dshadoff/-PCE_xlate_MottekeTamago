/*****************************************************************************/
/* uncompress.c                                                              */
/* uncompress <track2> <hex offset> <image> <hex offset>                     */
/*****************************************************************************/

#include "stdio.h"


FILE * inp1;
FILE * inp2;
long int offset1, offset2;
long int offset1a, offset2a;

unsigned char buff1[1000000];
unsigned char buff2[1000000];


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
      dummy = fread(&buff2[i++], 1, 1, inp2);
   }

   len2 = i - 1;
   printf("size of file %s = %ld\n\n", argv[3], len2);


   offset1 = atohex(argv[2]);
   offset2 = atohex(argv[4]);

/* read through 128 sprites @ output of 0x80 bytes for each sprite */

   offset1a = offset1;
   offset2a = offset2;

   octetcount = 0;

   while (offset2a < offset2 + (256 * 0x80))
   {
      inpbit = buff1[offset1a];
      if ((octetcount & 15) == 0)
      {
         printf("input file pos = %6.6x, output file pos = %6.6x, input bitmap = %2.2x\n", offset1a, offset2a, inpbit);
         octetcount = 0;
      }


      printf("   %2.2x :", inpbit);

      bitcount = 0;
      errorcount = 0;
      for (i = 0; i < 8; i++)
      {
         if (inpbit & (0x80 >> i))
	 {
            printf(" %2.2x", buff1[offset1a + bitcount + 1]);
	    if (buff2[offset2a + i] != buff1[offset1a + bitcount + 1])
	    {
               printf("*");
               errorcount++;
	    }
            bitcount++;
	 }
	 else
	 {
            printf("   ");
	    if (buff2[offset2a + i] != buff2[offset2a + i - 2])
	    {
               printf("*");
               errorcount++;
	    }
	 }
      }
      if (errorcount > 0) {
         printf(" -- ERROR\n       ");
      } else {
         printf("\n       ");
      }

      for (i=0; i < 8; i++)
      {
         printf(" %2.2x", buff2[offset2a + i]);
      }
      printf("\n\n");

      offset2a += 8;
      offset1a += bitcount + 1;

      octetcount++;
   }
}

