#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://infoarena.ro/problema/jap2

#define INPUT_FILE "jap2.in"
#define OUTPUT_FILE "jap2.out"

uint32_t inversModularEuclidExtins(uint64_t a, uint32_t prim) {
    uint64_t r = 0, c = 0, y = 0;
    int64_t y0 = 0, y1 = 1;
    uint64_t aux = prim;
    while(a != 0) {
        r = prim % a;
        c = prim / a;
        prim = a;
        a = r;
        y = y0 - c * y1;
        y0 = y1;
        y1 = y;
    }
    while(y0 < 0) {
        y0 += aux;
    }
    return y0;
}

uint64_t inmultireConsecutiva(uint64_t start, uint64_t end) {
    uint64_t number = 1;
    for(uint64_t i=start;i<=end;i++) number *= i;
    return number;
}

uint64_t factorial(uint64_t number) {
    if(number == 0 || number == 1) return 1;
    return inmultireConsecutiva(2, number);
}

uint64_t combinari(uint64_t a, uint64_t b, uint32_t prim) {
    // b! se va reduce complet din formula de combinari => formula va fi
    // ((b + 1)(b + 2)...a) / (a - b)!
    // astfel, cu cat b este mai mare cu atat avem mai putin de calculat

    if(b < a / 2) b = a - b; // C(a, b) == C(a, a - b)

    if(a == b && a == 0) return 1; // C(n, n) = 1 ; C(n, 0) = 1
    
    uint64_t upper = inmultireConsecutiva(b + 1, a) % prim; // aflam numaratorul modulo prim
    // printf("upper0: %lu ", inmultireConsecutiva(b + 1, a) % prim);
    // printf("upper: %lu ", upper);

    uint64_t lower = factorial(a - b) % prim; // aflam numitorul modulo prim
    // printf("lower: %lu ", lower);

    uint64_t invers = inversModularEuclidExtins(lower, prim); // aflam inversul modular pentru numarator
    // invers * lower == 1 (mod prim)
    // printf("invers: %lu \n", invers);

    return (invers * upper) % prim;
}

int main() {
    uint32_t prim = 0, questions = 0;
    uint64_t a = 0, b = 0;
    FILE *in = NULL, *out = NULL;

    if((in = fopen(INPUT_FILE, "r")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier intrare\n");
        exit(-1);
    }

    if((out = fopen(OUTPUT_FILE, "w")) == NULL) {
        fprintf(stderr, "Eroare la deschidere fisier iesire\n");
        exit(-1);
    }

    fscanf(in, "%u %u", &prim, &questions);
    for(uint32_t i=0;i<questions;i++) {
        fscanf(in, "%lu %lu", &a, &b);
        fprintf(out, "%lu\n", combinari(a, b, prim));
    }

    fclose(in);
    fclose(out);
    return 0;
}