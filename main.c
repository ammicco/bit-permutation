#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "read_file.h"
#include "bit_permutation.h"

static const uint64_t m[] = {
    0xffffffffffffffff, 
    0x00000000ffffffff, 
    0x000000000000ffff, 
    0x00000000000000ff
};

static void Usage(){
    fputs("usage: ./permutation \"file to convert\" \"bit of mask\" \"mask filename\" \"bit numbering mode\"\nexit.\n", stderr);    
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

    if(!f){
        fputs("fopen() error.\nexit.\n", stderr);
        return -1;
    }

    tf = fopen(argv[3], "r");

    if(!tf){
        fputs("fopen() error.\nexit.\n", stderr);
        return -1;
    }

    table = (int *) malloc(sizeof(int) * atoi(argv[2]));

    if(!table){
        fputs("malloc() error.\nexit.\n", stderr);
        return -1;
    }

    switch(atoi(argv[2])){
        case 64: b = read64bit(f); b &= m[0]; break;
        case 32: b = read32bit(f); b &= m[1]; break;
        case 16: b = read16bit(f); b &= m[2]; break;
        case 8:  b = read8bit(f); b &= m[3]; break;
        default: fputs("argv[2] not allowed.\eexit\n", stderr); break;
    }

    fclose(f);

    for(i = 0; i < atoi(argv[2]); i++){
        fscanf(tf, "%d", &table[i]);
    }

    fclose(tf);

    printf("source: %lu -> result: %lu\n", b, permutation(b, table, atoi(argv[2]), argv[4]));
    
    return 0;
}