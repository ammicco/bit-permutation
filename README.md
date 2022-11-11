This C program implements a simple bit permutation.
 - Save a value in a file, of 8, 16, 32 or 64 bit. 
 - Save a bit order table in another file. 
 - From CLI you compile, than use: ./main "file with bit value" "number of bit" "file with table" "bit counting mode"

The bit counting mode can be "msb" or "lsb" that indicates: 
 - Most signifincant bit, for example:

    **counting**: &nbsp;&emsp; 0 1 2 3 4 5 6 7

    **bit string**: &emsp;     0 0 0 1 0 0 1 1
 - Less significant bit, for example: 

    **counting**: &nbsp;&emsp; 7 6 5 4 3 2 1 0
 
    **bit string**: &emsp;     0 0 0 1 0 0 1 1

An example: 
``` bash
echo 4 > file # 4 == 00000100
echo 0 1 2 3 4 6 5 7 > order_table

./main ./file 8 ./order_table "msb"
 source: 4 -> result: 2 # the order swap 6th bit and 5th bit, so result == 00000010 
```

Here you can find the standard bit order table: 
MSB:   
``` c
int msb_mask64[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,
    24,25,26,27,28,29,30,31,
    32,33,34,35,36,37,38,39,
    40,41,42,43,44,45,46,47,
    48,49,50,51,52,53,54,55,
    56,57,58,59,60,61,62,63
};

int msb_mask32[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10,11,12,13,14,15,
    16,17,18,19,20,21,22,23,
    24,25,26,27,28,29,30,31
}

int msb_mask16[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10,11,12,13,14,15
}

int msb_mask8[] = {
    0, 1, 2, 3, 4, 5, 6, 7
}
```
LSB
```c
int lsb_mask64[] = {
    63,62,61,60,59,58,57,56,
    55,54,53,52,51,50,49,48,
    47,46,45,44,43,42,41,40,
    39,38,37,36,35,34,33,32,
    31,30,29,28,27,26,25,24,
    23,22,21,20,19,18,17,16,
    15,14,13,12,11,10,9, 8,
    7, 6, 5, 4, 3, 2, 1, 0
}

int lsb_mask32[] = {
    31,30,29,28,27,26,25,24,
    23,22,21,20,19,18,17,16,
    15,14,13,12,11,10,9, 8,
    7, 6, 5, 4, 3, 2, 1, 0
}

int lsb_mask16[] = {
    15,14,13,12,11,10,9, 8,
    7, 6, 5, 4, 3, 2, 1, 0
}

int lsb_mask8[] = {
    7, 6, 5, 4, 3, 2, 1, 0
}
```