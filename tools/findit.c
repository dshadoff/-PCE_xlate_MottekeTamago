/*****************************************************************************/
/* template.c                                                                */
/* Template for coding decoder modules for TMod2                             */
/* (c) 2000 Jay                                                              */
/*****************************************************************************/
#include "stdio.h"

#define MATCH_SIZE	3

FILE * inp;
unsigned char buff[937984];
unsigned char srch[] = { 0xa0, 0xaf, 0x9a };

int main(int argc, char * argv[])
{
int i, j, c, len, diff, dummy, match;

   inp = fopen("track2.bin", "rb");

   if (inp == NULL) {
      printf("failed to open\n");
      exit(1);
   }

   i = 0;
   dummy = 0;

   while (!feof(inp))
   {
      dummy = fread(&buff[i++], 1, 1, inp);
   }

   len = i;
   printf("size of file = %ld\n\n", len);

   for (i = 0; i < len; i++)
   {
      diff = buff[i] - srch[0];

      match = 1;

      for (j = 0; j < MATCH_SIZE; j++)
      {
         if (diff != (buff[i+j] - srch[j]) )
         {
            match = 0;
            break;
         }
      }

      if (match == 1)
      {
         printf("match at %6.6x, diff = %2.2x\n", i, diff);
      }
   }
}
