#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DIV 666013
#define INPUT_FILE "kfib.in"
#define OUTPUT_FILE "kfib.out"

#define SIZE 2

void init(uint64_t m[][SIZE]) {
    // face matricea trimisa prin parametru matricea identitate
    for(uint64_t i=0;i<SIZE;i++) {
        for(uint64_t j=0;j<SIZE;j++) {
            if(i == j) m[i][j] = 1;
            else m[i][j] = 0;
        }
    }
}

void initZ(uint64_t m[][SIZE]) {
    // face matricea trimisa prin parametru matricea Z
    m[0][0] = 0;
    m[0][1] = m[1][0] = m[1][1] = 1;
}

void afisare(uint64_t matrix[][SIZE], unsigned int size) {
    for(uint64_t i=0;i<size;i++) {
        for(uint64_t j=0;j<size;j++) {
            printf("%lu ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void multiply(uint64_t result[][SIZE], uint64_t a[][SIZE], uint64_t b[][SIZE]) {
    for(uint64_t i=0;i<SIZE;i++) {
        for(uint64_t j=0;j<SIZE;j++) {
            result[i][j] = 0;
            for(uint64_t k=0;k<SIZE;k++) {
                result[i][j] += a[i][k] * b[k][j] % DIV;
            }
        }
    }
}

void matcpy(uint64_t src[][SIZE], uint64_t dst[][SIZE]) {
    for(uint64_t i=0;i<SIZE;i++) {
        for(uint64_t j=0;j<SIZE;j++) {
            dst[i][j] = src[i][j];
        }
    }
}

uint64_t expLogMatrix(uint64_t n[][SIZE], uint64_t p) {
    if(p == 0) return 0; // n nu se modifica daca puterea este 0 din prima
    if(p == 1) return 1;

    uint64_t x[SIZE][SIZE], result[SIZE][SIZE];
    for(uint64_t i=0;i<SIZE;i++) {
        for(uint64_t j=0;j<SIZE;j++) {
            result[i][j] = 0;
        }
    }
    init(x);
    while(p > 0) {
        // afisare(x, SIZE);
        // afisare(n, SIZE);
        // putchar('\n');
        if((p & 1) == 1) {
            multiply(result, x, n);
            matcpy(result, x);
        }
        multiply(result, n, n);
        matcpy(result, n);
        p >>= 1;
        // if(x[0][1] > DIV) {
        //     for(uint64_t i=0;i<SIZE;i++) {
        //         for(uint64_t j=0;j<SIZE;j++) {
        //             x[i][j] = x[i][j] % DIV;
        //         }
        //     }
        // }
        // afisare(x, SIZE);
    }
    return x[1][1];
    // matcpy(n, x);
    // afisare(x, SIZE);
    // fprintf(out, "%lu\n", x[1][1]);
}

int main() {
    uint64_t k = 0;
    FILE *in = NULL, *out = NULL;

    if((in = fopen(INPUT_FILE, "r")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier intrare\n");
        exit(-1);
    }

    if((out = fopen(OUTPUT_FILE, "w")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier iesire\n");
        exit(-1);
    }

    fscanf(in, "%lu", &k);
    uint64_t m[SIZE][SIZE];
    initZ(m);
    if(k == 1) fprintf(out, "%u\n", 1);
    else {
        // afisare(m, SIZE);
        fprintf(out, "%lu\n", expLogMatrix(m, k - 1)); // trebuie sa il ridic pe Z la puterea i - 1
    }

    fclose(in);
    fclose(out);
    return 0;
}