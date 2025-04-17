/*
 * loadfasta by Stephen Cohen <cohen.1107@osu.edu>
 * Released under CC0 1.0 Universal - see LICENSE
 */

#ifndef FASTA_H
#define FASTA_H

struct fasta_file {
	int n_contigs;
	char *data;
	char **name;
	char **seq;
};

extern struct fasta_file	*load_fasta(char *file);
extern void			 del_fasta(struct fasta_file *fasta);

#endif
