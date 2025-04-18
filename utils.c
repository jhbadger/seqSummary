#include <string.h>
#include <ctype.h>
#include "utils.h"

/* compute gc content of sequence */
double gc(char *seq, int raw) {
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

/* get first word of string */
char* get_first_word(char* str) {
  if (str == NULL || str[0] == '\0') {
    return ""; // Return empty string for NULL or empty input
  }

  char* start = str;
  char* end = str;

  // Skip leading whitespace
  while (isspace(*end)) {
    end++;
  }

  // Find the end of the first word
  while (end[0] != '\0' && !isspace(end[0])) {
    end++;
  }

  // Null-terminate the first word
  *end = '\0';

  return start;
}