/*
 * loadfasta by Stephen Cohen <cohen.1107@osu.edu>
 * Released under CC0 1.0 Universal - see LICENSE
 * gzip support by Jonathan Badger <jhbadger@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loadfasta.h"

struct fasta_file *
load_fasta(char *file)
{
	char c;
	long file_size;
	long i = 0;
	FILE *f;
	struct fasta_file *fasta;
	int n_contigs;
	char *data = NULL;
	char **name = NULL;
	char **seq = NULL;
        char cmd[500] = "gzcat -cf \"";
        strlcat(cmd, file,  sizeof(cmd));
        strlcat(cmd, "\"",  sizeof(cmd));
	/* Find file size to figure out required buffer size */
	f = popen(cmd, "r");
        if (f == NULL) return NULL;
        while( (c=fgetc(f)) != EOF) {
          i += 1;
        }
	file_size = i;
	pclose(f);
        f = popen(cmd, "r");
	/* Allocate space for buffer and load in data byte by byte */
	data = malloc(sizeof(*data)*file_size);
	for (i = 0, n_contigs = 0; (c = fgetc(f)) != EOF; i++) {
		*(data+i) = c;
		if (c == '>') {
			n_contigs++;
			if (n_contigs == 1) {
				name = malloc(n_contigs*sizeof(*name));
				*(name+n_contigs-1) = data+i;
				seq = malloc(n_contigs*sizeof(*seq));
			} else {
				*(data+i) = '\0';
				i++;
				name = realloc(name, n_contigs*sizeof(*name));
				*(name+n_contigs-1) = data+i;
				seq = realloc(seq, n_contigs*sizeof(*seq));
			}
			while ((c = fgetc(f)) != '\n') {
				*(data+i) = c;
				i++;
			}
			*(data+i) = '\0';
			*(seq+n_contigs-1) = data+i+1;
		} else if (c == '\n') {
			i--;
		}
	}
	*(data+i) = '\0';
	data = realloc(data, (i+1)*sizeof(*data));
 	pclose(f);

 	/* Put it in a structure to return */
	fasta = malloc(sizeof(*fasta));
 	fasta->n_contigs = n_contigs;
 	/* Try to shrink the memory reserved due to newlines in the file */
	fasta->data = realloc(data, (i+1)*sizeof(*fasta->data));
	if (fasta->data == NULL) fasta->data = data;
	fasta->name = name;
	fasta->seq = seq;
	return fasta;
}


void
del_fasta(struct fasta_file *fasta)
{
	if (fasta != NULL) {
		if (fasta->name != NULL) free(fasta->name);
		if (fasta->seq != NULL) free(fasta->seq);
		if (fasta->data != NULL) free(fasta->data);
		free(fasta);
	}
}
