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
    int i, bit_num = atoi(argv[2]);
    uint64_t *b;

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

    table = (int *) malloc(sizeof(int) * bit_num);

    if(!table){
        fputs("malloc() error.\nexit.\n", stderr);
        return -1;
    }

    if(bit_num != 64 && bit_num != 32 && bit_num != 16 && bit_num != 8){
        fputs("argv[2] not allowed.\eexit\n", stderr);
        return -1;
    }

    b = (uint64_t *) readbit(f, bit_num);

    switch(bit_num){
        case 64: *(b) &= m[0]; break;
        case 32: *(b) &= m[1]; break;
        case 16: *(b) &= m[2]; break;
        case 8:  *(b) &= m[3]; break;
        default: fputs("argv[2] not allowed.\eexit\n", stderr); break;
    }

    fclose(f);

    for(i = 0; i < bit_num; i++){
        fscanf(tf, "%d", &table[i]);
    }

    fclose(tf);

    printf("source: %lu -> result: %lu\n", *(b), permutation(*(b), table, bit_num, argv[4]));
    
    return 0;
}