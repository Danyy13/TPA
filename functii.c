#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// https://infoarena.ro/problema/functii

#define INPUT_FILE "functii.in"
#define OUTPUT_FILE "functii.out"
#define PRIM 30103 

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

uint64_t expLog(uint64_t n, uint64_t p) {
    // if(n < 0) return expLog(1 / n, -p); // p este unsigned
    if(n > PRIM) n %= PRIM;
    if(p == 0) return 1;
    if((p & 1) == 0) return expLog(n * n, p >> 1) % PRIM;
    if((p & 1) == 1) return (n * expLog(n * n, p >> 1)) % PRIM;
}

int main() {
    uint64_t prim = PRIM;
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

    fscanf(in, "%lu %lu", &a, &b);
    uint64_t power = expLog(2, b) - 2;
    uint64_t comb = combinari(a, b, prim);
    // printf("power: %lu\ncomb: %lu\n", power, comb);
    fprintf(out, "%lu\n", power * comb);

    fclose(in);
    fclose(out);
    return 0;
}