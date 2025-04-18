#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "loadfasta.h"
#include "utils.h"

// Function to display usage information
void usage (char *name);

int
main (int argc, char **argv)
{
  int tot = 0; // Flag to indicate whether to calculate total statistics
  unsigned long  tlen = 0; // Total length of sequences (used for total statistics)
  unsigned long maxlen = 0; // Maximum sequence length (used for total statistics)
  unsigned long minlen = 0; // Minimum sequence length (used for total statistics)
  unsigned long meanlen; // Mean sequence length (used for total statistics)
  double tgc = 0; // Total GC content (used for total statistics)
  char *arg; // Temporary variable to hold command-line arguments
  char *infilename = NULL; // Pointer to the input FASTA filename

  // Check if the correct number of arguments are provided
  if (argc < 3)                        // need at least FASTA file 
    usage (argv[0]);

  // Process command-line arguments
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (strstr (arg, "-i") != NULL) {
      // Found the input filename argument
      infilename = argv[i+1];
    }
    else if (strstr (arg, "-t") != NULL) {
      // Found the total statistics flag
      tot = 1;
    }
  }

  // If an input filename was provided, process the FASTA file
  if (infilename != NULL) {
    // Load the FASTA file into a struct
    struct fasta_file *seqs = load_fasta(infilename);

    // Iterate through each sequence in the FASTA file
    for(int i = 0; i < seqs->n_contigs; i++) {
      // If the -t flag was not used, print sequence information
      if (!tot) {
        printf("%10s\t%7lu\t(GC %3.2f%%)\n", get_first_word(seqs->name[i]),
               strlen(seqs->seq[i]), 100*gc(seqs->seq[i], 0)); // Print name, length, and GC content
      }
      // If the -t flag was used, calculate total statistics
      else {
        tlen += strlen(seqs->seq[i]); // Add sequence length to total length
        tgc += gc(seqs->seq[i], 1); // Add GC content to total GC content
        // Update minimum sequence length
        if (minlen >  strlen(seqs->seq[i]) || minlen == 0) {
          minlen =  strlen(seqs->seq[i]);
        }
        // Update maximum sequence length
        if (strlen(seqs->seq[i]) > maxlen) {
          maxlen = strlen(seqs->seq[i]);
        }
      }
    }

    // If the -t flag was used, print total statistics
    if (tot) {
      tgc = tgc / tlen; // Calculate mean GC content
      meanlen = tlen / seqs->n_contigs; // Calculate mean sequence length
      printf("%6d contigs\tminlen: %-7lu\tmaxlen: %-7lu\tmeanlen: %-7lu\t(GC %3.2f%%)\n",
             seqs->n_contigs, minlen, maxlen, meanlen, 100*tgc); // Print total statistics
    }

    // Free the memory allocated for the FASTA file
    del_fasta(seqs);
  }

  exit (0); // Exit the program
}

/* display usage information */

void
usage (char *name)
{
  fprintf (stderr, "Usage: %s [options] -i fasta-file\n", name);
  fprintf (stderr, "valid options:\n");
  fprintf (stderr, "     -t create total of sequence statistics\n");
  exit (1); // Exit with an error code
}