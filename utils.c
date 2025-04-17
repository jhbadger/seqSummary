#include <string.h>
#include "utils.h"

/* compute gc content of sequence */
float gc(char *seq, int raw) {
    float gc = 0.0;
    for(int i = 0; i<strlen(seq); i++) {
        if (seq[i] == 'G' || seq[i] == 'g' ||
            seq[i] == 'C' || seq[i] == 'c') {
            gc += 1;
        }
    }
    if (raw != 1) {
        gc = gc/strlen(seq);
    }
    return gc;
}