#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DIV 1999999973
#define INPUT_FILE "lgput.in"
#define OUTPUT_FILE "lgput.out"

uint64_t expLog(uint64_t n, uint64_t p) {
    // if(n < 0) return expLog(1 / n, -p); // p este unsigned
    if(n > DIV) n %= DIV;
    if(p == 0) return 1;
    if((p & 1) == 0) return expLog(n * n, p >> 1) % DIV;
    if((p & 1) == 1) return (n * expLog(n * n, p >> 1)) % DIV;
}

int main() {
    uint64_t n = 0, p = 0;
    FILE *in = NULL, *out = NULL;

    if((in = fopen(INPUT_FILE, "r")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier intrare\n");
        exit(-1);
    }

    if((out = fopen(OUTPUT_FILE, "w")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier iesire\n");
        exit(-1);
    }

    fscanf(in, "%lu %lu", &n, &p);
    fprintf(out, "%lu\n", expLog(n, p) % DIV);
    // printf("%lu %lu\n", n, p);

    fclose(in);
    fclose(out);
    return 0;
}