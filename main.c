/*
About this program:
- This program counts words.
- The specific words that will be counted are passed in as command-line
  arguments.
- The program reads words (one word per line) from standard input until EOF or
  an input line starting with a dot '.'
- The program prints out a summary of the number of times each word has
  appeared.
- Various command-line options alter the behavior of the program.

E.g., count the number of times 'cat', 'nap' or 'dog' appears.
> ./main cat nap dog
Given input:
 cat
 .
Expected output:
 Looking for 3 words
 Result:
 cat:1
 nap:0
 dog:0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smp0_tests.h"

#define LENGTH(s) (sizeof(s) / sizeof(*s))

/* Structures */
typedef struct {
  char *word;
  int counter;
} WordCountEntry;


int process_stream(WordCountEntry entries[], int entry_count)
{
  short line_count = 0;
  char buffer[30];

  /* C4: replace gets with fgets */
  while (gets(buffer)) {
    if (*buffer == '.')
      break;

    /* C5: strtok() can be used to split a line into individual tokens.
       For the separator characters we use whitespace (space and
       tab), as well as the newline character '\n'.  We could also
       trim the buffer to get rid of the newline, instead. 
       strtok returns NULL when no more tokens are available. */

    /* Compare against each entry. 
    When you implement C5, you won't be able to process the entries directly from the buffer,
    but rather from returned value of strtok. Call "man strtok" in your command line to learn more about strtok*/
    int i = 0;
    while (i < entry_count) {
      if (!strcmp(entries[i].word, buffer))
        entries[i].counter++;
      i++;
    }
    line_count++;
  }
  return line_count;
}


void print_result(WordCountEntry entries[], int entry_count)
{
    /* B5: introduce a temporary variable i and use it to count up from 0 */

    /* C2: send output to the right stream, use fprintf */
    printf("Result:\n");

    /* B5: fix this*/
    while (entry_count-- > 0) {
        printf("%s:%d\n", entries->word, entries->counter);
    }
}


void printHelp(const char *name)
{
    /* C2: send output to the right stream, use fprintf */
    printf("usage: %s [-h] <word1> ... <wordN>\n", name);
}


int main(int argc, char **argv)
{
  const char *prog_name = *argv;

  /* C3: make entries a pointer instead of an array */
  WordCountEntry entries[5];
  int entryCount = 0;

  /* C2: create a variable to store the output stream to use, stdout by default 
        Hint: use the FILE data type and understand the stdout and stderr output streams*/
  // FILE *output = ?? // Complete this stream variable definition (Note: this will not be a file)

  /* Entry point for the testrunner program */
  if (argc > 1 && !strcmp(argv[1], "-test")) {
    run_smp0_tests(argc - 1, argv + 1);
    return EXIT_SUCCESS;
  }

  /* C3: allocate (potentially) a little more memory than strictly
       necessary, thus avoiding extensive modifications to the code below. Hint: use malloc */

 /* B4: fix argv */

  while (*argv != NULL) {
    if (**argv == '-') {

      switch ((*argv)[1]) {
        /* C2: -fFILENAME switch: open FILENAME and set it as the output
             stream */

        /* B3: fix the logical flow error in the switch*/
        case 'h':
          printHelp(prog_name);
        default:
          printf("%s: Invalid option %s. Use -h for help.\n",
                 prog_name, *argv);
      }
    } else {
      /* C3: the LENGTH macro will not work anymore, since entries will be a pointer, not an array */
      if (entryCount < LENGTH(entries)) {
        entries[entryCount].word = *argv;
        entries[entryCount++].counter = 0;
      }
    }
    argv++;
  }
  if (entryCount == 0) {
    printf("%s: Please supply at least one word. Use -h for help.\n",
           prog_name);
    return EXIT_FAILURE;
  }

  /* C2: send output to the right stream */
  if (entryCount == 1) {
    printf("Looking for a single word\n");
  } else {
    printf("Looking for %d words\n", entryCount);
  }

  process_stream(entries, entryCount);
  print_result(entries, entryCount);

  // FREE MEMORY, CLOSE FILES, STREAMS, etc.

  return EXIT_SUCCESS;
}
