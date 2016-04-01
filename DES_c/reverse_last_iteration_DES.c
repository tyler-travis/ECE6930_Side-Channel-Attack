#include <stdio.h>
#include <stdlib.h>

const uint8_t IP[64] = {57, 49, 41, 33, 25, 17, 9,  1,
                        59, 51, 43, 35, 27, 19, 11, 3,
                        61, 53, 45, 37, 29, 21, 13, 5,
                        63, 55, 47, 39, 31, 23, 15, 7,
                        56, 48, 40, 32, 24, 16, 8,  0,
                        58, 50, 42, 34, 26, 18, 10, 2,
                        60, 52, 44, 36, 28, 20, 12, 4,
                        62, 54, 46, 38, 30, 22, 14, 6};

const uint8_t FP[64] = {39, 7, 47, 15, 55, 23, 63, 31,
                        38, 6, 46, 14, 54, 22, 62, 30,
                        37, 5, 45, 13, 53, 21 ,61, 29,
                        36, 4, 44, 12, 52, 20, 60, 28,
                        35, 3, 43, 11, 51, 19, 59, 27,
                        34, 2, 42, 10, 50, 18, 58, 26,
                        33, 1, 41, 9,  49, 17, 57, 25,
                        32, 0, 40, 8,  48, 16, 56, 24};

void copy_bit(uint8_t source[], uint8_t dest[], uint16_t source_bit, uint16_t dest_bit);

int main(int argc, char** argv)
{
    FILE* cipher = fopen("cipher_text", "r");
    FILE* pre_fp = fopen("pre-fp_text", "w");

    uint64_t value;

    uint8_t value_array[8] = {0};
    uint8_t result_array[8] = {0};

    uint32_t i = 0;

    while(fscanf(cipher, "%llx", &value) != EOF)
    {
        value_array[0] = (value & (unsigned long long)0xFF << 56) >> 56;
        value_array[1] = (value & (unsigned long long)0xFF << 48) >> 48;
        value_array[2] = (value & (unsigned long long)0xFF << 40) >> 40;
        value_array[3] = (value & (unsigned long long)0xFF << 32) >> 32;
        value_array[4] = (value & (unsigned long long)0xFF << 24) >> 24;
        value_array[5] = (value & (unsigned long long)0xFF << 16) >> 16;
        value_array[6] = (value & (unsigned long long)0xFF << 8) >> 8;
        value_array[7] = value & (unsigned long long)0xFF;

        for(i = 0; i < 64; ++i)
        {
            copy_bit(value_array, result_array, IP[i], i);
        }
        fprintf(pre_fp, "%02X%02X%02X%02X\t%02X%02X%02X%02X\n", 
                result_array[0], result_array[1], result_array[2], result_array[3],
                result_array[4], result_array[5], result_array[6], result_array[7]);

        printf("%02X%02X%02X%02X\t%02X%02X%02X%02X\n", 
                result_array[0], result_array[1], result_array[2], result_array[3],
                result_array[4], result_array[5], result_array[6], result_array[7]);
    }

    
    return 0;
}

void copy_bit(uint8_t source[], uint8_t dest[], uint16_t source_bit, uint16_t dest_bit)
{
    // Find which byte to look in
    uint8_t source_byte = source_bit/8;

    // Get the bit offset relative to the byte
    uint8_t source_bit_offset = 7-source_bit%8;

    // Get the data from at the byte
    uint8_t source_byte_data = source[source_byte];

    // Get what the bit is
    uint8_t source_bit_data = ((0x1 << source_bit_offset) & source_byte_data) >> source_bit_offset;

    // Find which byte to store the value in
    uint8_t dest_byte = dest_bit/8;

    // Get the bit taht we need to store the value in
    uint8_t dest_bit_offset = 7-dest_bit%8;
    
    // Get the byte data
    uint8_t dest_byte_data = dest[dest_byte];

    // mask for the bit destination
    uint8_t dest_mask;

    // the bit data for the destination
    uint8_t dest_bit_data = source_bit_data << dest_bit_offset;

    // If the the bit needs to be a 1,
    // then the final byte data just needs to be ORed
    // for it to work correctly
    if(source_bit_data == 0x1)
    {
        dest_mask = 0x0;
        dest_byte_data = dest_byte_data | (dest_mask | dest_bit_data);
    }
    // If the bit needs to be a 0, then we need to and it with a mask
    // of 0x11..0..11 where the 0 is the position where the zero needs
    // to be.
    else
    {
        dest_mask = ~(0x1 << dest_bit_offset);
        dest_byte_data = dest_byte_data & dest_mask;
    }

    // Store the data back into the array
    dest[dest_byte] = dest_byte_data;
}
