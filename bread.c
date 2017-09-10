#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char **argv)
{
  int sflag = 0;
  int index;
  int c;

  //For argc loop that returns error if args fail strtol()
  int argcIndex = 1;
  int argcLoop;

  opterr = 0;
  while ((c = getopt (argc, argv, "s")) != -1)
    switch (c)
      {
      case 's':
        sflag = 1;
        if (argc != 7) {
          fprintf(stderr, "You need to use 5 arguments with the -s option, see `man bread`\n");
          return 1;
        }
        argcIndex++;
        break;
      case '?':
        if (isprint (optopt))
	  // Isprint will print if it gets an unknown option that can be printed
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
	  // This one prints if it is a unicode character and prints the code
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

  // Taking care of the case that the user inputs the wrong amount of arguments.
  if (sflag == 0 && argc != 4) {
    // Checking that it has the proper amount of arguments.
    fprintf(stderr, "You need 3 arguments for bread, see `man bread`\n");
    return 1;
  }

  int vars[argc - 2];
  int varsIndex = 0;
  for (int i = argcIndex; i < argc; i++) {
    // Initializing a pointer variable
    char *ptr;
    // Taking argv[i] and putting it in the address of ptr in base 10
    long argument = strtol(argv[i], &ptr, 10);

    if (strlen(ptr) > 0) {
      // Letting the user know they can only use numbers as arguments.
      fprintf(stderr, "You can only use numbers as arguments. Try without: %s\n", ptr);
      return 1;
    }
    vars[varsIndex] = argument; varsIndex++;
  }

  //vars = [starter weight, starter hydration, final hydration goal, total flour goal, desired salt content]
  if (sflag) {
    //percent of starter that is water (100 percent hydration "vars[1]" is 50% water)
    float waterPercent = (float)vars[1]/100/((float)vars[1]/100 + 1);
    float starterWater = (float)vars[0] * waterPercent;
    //starter flour must be the opposite percentage of water
    float starterFlour = (float)vars[0] * (1 - waterPercent);
    //total flour - starterFlour
    float addFlour = (float)vars[3] - starterFlour;
    //total flour goal * final hydration goal - starterWater
    float addWater = (float)vars[3] * ((float)vars[2]/100) - starterWater;
    //desire salt content/100 * the total flour goal
    float addSalt = (float)vars[4] / 100 * (float)vars[3];
    printf("\n\tAdd (%f) grams of Flour\n\tAdd (%f) grams of water\n\tAdd (%f) grams of salt\n\n",
      addFlour, addWater, addSalt);
  //vars = [final hydration goal, total flour goal, desired salt content]
  } else if (!sflag) {
    float useFlour = (float)vars[1];
    float useWater = (float)vars[0] * useFlour;
    float useSalt = (float)vars[2]/100 * useFlour;

    printf("\n\tAdd (%f) grams of flour\n\tAdd (%f) grams of water\n\tAdd (%f) grams of salt\n\n",
      useFlour, useWater, useSalt);
  }
  return 0;
}
