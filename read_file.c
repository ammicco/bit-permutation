#include "read_file.h"

uint8_t read8bit(FILE *f){
    int i;
    uint8_t tmp = 0; 
    
    if(!f){
        return -1;
    }

    fread(&tmp, 1, 1, f);

    return tmp;
}

uint16_t read16bit(FILE *f){
    int i, len;
    uint16_t tmp = 0; 
    uint16_t r = 0;
    
    if(!f){
        return -1;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(len < 2){
        return read8bit(f);
    }

    for(i = 1; i <= 2; i++){
        fread(&r, 1, 1, f);
        tmp |= (r << (16 - (i * 8)));
    }

    return tmp;
}

uint32_t read32bit(FILE *f){
    int i, len;
    uint32_t tmp = 0; 
    uint32_t r = 0;
    
    if(!f){
        return -1;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(len < 4){
        return read16bit(f);
    }

    for(i = 1; i <= 4; i++){
        fread(&r, 1, 1, f);
        tmp |= (r << (32 - (i * 8)));
    }

    return tmp;
}

uint64_t read64bit(FILE *f){
    int i, len;
    uint64_t tmp = 0; 
    uint64_t r = 0;
    
    if(!f){
        return -1;
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if(len < 8){
        return read32bit(f);
    }

    for(i = 1; i <= 8; i++){
        fread(&r, 1, 1, f);
        tmp |= (r << (64 - (i * 8)));
    }

    return tmp;
}