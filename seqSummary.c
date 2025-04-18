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
  unsigned long  tlen = 0;
  unsigned long maxlen = 0;
  unsigned long minlen = 0;
  unsigned long meanlen;
  double tgc = 0;
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
    for(int i = 0; i < seqs->n_contigs; i++) {
      if (!tot) {
        printf("%10s\t%7lu\t(GC %3.2f%%)\n", get_first_word(seqs->name[i]), 
               strlen(seqs->seq[i]), 100*gc(seqs->seq[i], 0));
      }
      else {
        tlen += strlen(seqs->seq[i]);
        tgc += gc(seqs->seq[i], 1);
        if (minlen <  strlen(seqs->seq[i]) || minlen == 0) {
          minlen =  strlen(seqs->seq[i]);
        }
        if (strlen(seqs->seq[i]) > maxlen) {
          maxlen = strlen(seqs->seq[i]); 
        }
      }
    }
    if (tot) {
      tgc = tgc / tlen;
      meanlen = tlen / seqs->n_contigs;
      printf("%6d contigs\tminlen: %-7lu\tmaxlen: %-7lu\tmeanlen: %-7lu\t(GC %3.2f%%)\n",
             seqs->n_contigs, minlen, maxlen, meanlen, 100*tgc);

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
