#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "bit_permutation.h"

static const uint64_t m[] = {
    0xffffffffffffffff, 
    0xffffffff, 
    0xffff, 
    0xff
};

static void Usage(){
    fputs("usage: ./permutation \"file to convert\" \"bit of mask\" \"mask filename\" \"bit numbering mode\".\nexit.\n", stderr);    
}

int main(int argc, char **argv){
    FILE *f, *tf; 
    int *table;
    int i;
    uint64_t b = 0;

    if(argc < 4){
        Usage();
        return -1;
    }

    f = fopen(argv[1], "rb");
    tf = fopen(argv[3], "r");
    table = (int *) malloc(sizeof(int) * atoi(argv[2]));

    fread(&b, sizeof(uint64_t), 1, f);
    fclose(f);

    switch(atoi(argv[2])){
        case 64: b &= m[0]; break;
        case 32: b &= m[1]; break;
        case 16: b &= m[2]; break;
        case 8:  b &= m[3]; break;
    }

    printf("%c\n", (char) b);

    for(i = 0; i < atoi(argv[2]); i++){
        fscanf(tf, "%d", &table[i]);
    }

    printf("source: %lu -> result: %lu\n", b, permutation(b, table, atoi(argv[2]), argv[4]));
    
    return 0;
}