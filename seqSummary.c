#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "loadfasta.h"
#include "utils.h"

void usage (char *name);

int
main (int argc, char **argv)
{
  int tot = 0;
  char *arg;
  char *infilename;

  if (argc < 3)			/* need at least FASTA file */
    usage (argv[0]);

  /* process arguments */
  
  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (strstr (arg, "-i") != NULL) {
      infilename = argv[i+1];
    }
    else if (strstr (arg, "-t") != NULL) {
      tot = 1;
    }
  }
  if (infilename != NULL) {
    struct fasta_file *seqs = load_fasta(infilename);
    if (!tot) {
      for(int i = 0; i < seqs->n_contigs; i++) {
        printf("%10s %7lu (GC %3.2f%%)\n", seqs->name[i], strlen(seqs->seq[i]),
               100*gc(seqs->seq[i], 0));
      }
    }
    del_fasta(seqs);
  }
  exit (0);
}

/* display usage information */

void
usage (char *name)
{
  fprintf (stderr, "Usage: %s [options] -i fasta-file\n", name);
  fprintf (stderr, "valid options:\n");
  fprintf (stderr, "     -t create total of sequence statistics\n");
  exit (1);
}
