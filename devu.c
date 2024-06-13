#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t expLog(uint64_t n, uint64_t p, uint64_t mod) {
    if(n > mod) n %= mod;
    if(p == 0) return 1;
    if((p & 1) == 0) return expLog(n * n, p >> 1, mod) % mod;
    else return (n * expLog(n * n, p >> 1, mod)) % mod;
}

uint64_t solve(uint64_t n1, uint64_t k1, uint64_t n2, uint64_t k2, uint64_t n) {
    uint64_t a = expLog(n1, k1, n);
    uint64_t b = expLog(n2, k2, n);
    return expLog(a, b, n);
}

int main() {
    uint64_t n1 = 0, n2 = 0, k1 = 0, k2 = 0;
    uint64_t n = 0;
    uint16_t t = 0;
    scanf("%hu", &t);
    for(uint16_t i=0;i<t;i++) {
        scanf("%lu %lu %lu %lu %lu", &n1, &k1, &n2, &k2, &n);
        printf("%lu\n", solve(n1, k1, n2, k2, n));
    }
    return 0;
}