#include <stdio.h>
#include <stdlib.h>

const uint8_t S_box1[4][16] = {
    {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
};

const uint8_t S_box2[4][16] = {
    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
};

const uint8_t S_box3[4][16] = {
    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
};

const uint8_t S_box4[4][16] = {
    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
};

const uint8_t S_box5[4][16] = {
    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
};

const uint8_t S_box6[4][16] = {
    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
  	{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
  	{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
  	{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
};

const uint8_t S_box7[4][16] = {
    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
  	{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
  	{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
  	{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
};

const uint8_t S_box8[4][16] = {
    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
  	{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
  	{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
  	{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
};

const uint8_t E[48] = {31, 0, 1, 2, 3, 4,
                       3, 4, 5, 6, 7, 8,
                       7, 8, 9, 10, 11, 12,
                       11, 12, 13, 14, 15, 16,
                       15, 16, 17, 18, 19, 20,
                       19, 20, 21, 22, 23, 24,
                       23, 24, 25, 26, 27, 28,
                       27, 28, 29, 30, 31, 0};

const uint8_t P[32] = {15, 6, 19, 20, 28, 11, 27, 16,
                       0, 14, 22, 25, 4, 17, 30, 9,
                       1, 7, 23, 13, 31, 26, 2, 8,
                       18, 12, 29, 5, 21, 10, 3, 24};

void fFunction(uint8_t rightHalve[], uint8_t subKey[6]);
void copy_bit(uint8_t source[], uint8_t dest[], uint16_t source_bit, uint16_t dest_bit);

int main(int argc, char** argv)
{
    uint8_t key_guess[6];
    FILE* left_right_last = fopen("pre-fp_text", "r");
    FILE* fFunction_out = fopen("fFunction_output_text", "w");

    uint8_t right_array[10000][4];
    uint8_t left_array[10000][4];

    uint32_t right;
    uint32_t left;
    uint32_t i, j, h;

    for(i = 0; (fscanf(left_right_last, "%uX\t%uX", &left, &right) != EOF) && i < 10000; ++i)
    {
        left_array[i][0] = (left & 0xFF000000) >> 24;
        left_array[i][1] = (left & 0x00FF0000) >> 16;
        left_array[i][2] = (left & 0x0000FF00) >> 8;
        left_array[i][3] = (left & 0x000000FF);

        right_array[i][0] = (right & 0xFF000000) >> 24;
        right_array[i][1] = (right & 0x00FF0000) >> 16;
        right_array[i][2] = (right & 0x0000FF00) >> 8;
        right_array[i][3] = (right & 0x000000FF);
    }
    for(i = 0; i < 10000; ++i)
    {
        for(j = 0; j < 64; ++j)
        {
            for(h = 0; h < 6; ++h)
            {
                key_guess[h] = j;
            }
            fFunction(right_array[i], key_guess);
            fprintf(fFunction_out, "%02X%02X%02X%02X, ", right_array[i][0], right_array[i][1], right_array[i][2], right_array[i][3]);
            printf("%02X%02X%02X%02X, ", right_array[i][0], right_array[i][1], right_array[i][2], right_array[i][3]);
        }
        printf("\r\n");
    }

    return 0;
}

void fFunction(uint8_t rightHalve[], uint8_t subKey[6]){

    uint8_t rightHalveE[6] = {0};
    uint8_t rowBits = 0;
    uint8_t colBits = 0;
    uint8_t post_Sbox_R[4] = {0};
    
    uint32_t i;

    //Send rightHalve to E permutation
    for(i = 0; i < 48; i++){
        copy_bit(rightHalve, rightHalveE, E[i], i);   
    }

    //XOR subKey with output of E
    for(i = 0; i < 6; i++){
        rightHalveE[i] = rightHalveE[i] ^ subKey[i];
    }

    //printf("E: %02x%02x %02x%02x %02x%02x\n", rightHalveE[0], rightHalveE[1], rightHalveE[2], 
    //        rightHalveE[3], rightHalveE[4], rightHalveE[5]);

    //Send output of XOR into Switch Boxes
    //------------------------------------------------------------------------
    // 1111 1111 | 1111 1111 | 1111 1111 | 1111 1111 | 1111 1111 | 1111 1111
    // ^      ^         ^        ^         ^      ^         ^        ^      
    // 0      6         4        2         0      6         4        2
    //------------------------------------------------------------------------
    //*************
    //  Sbox1
    //*************
    rowBits = (rightHalveE[0] & 0x80) >> 6;
    rowBits |= (rightHalveE[0] & 0x04) >> 2;

    colBits = (rightHalveE[0] & 0x78) >> 3;

    post_Sbox_R[0] = (S_box1[rowBits][colBits] << 4);
    //*************
    //  Sbox2
    //*************
    rowBits = (rightHalveE[0] & 0x02);
    rowBits |= (rightHalveE[1] & 0x10) >> 4;

    colBits = (rightHalveE[0] & 0x01) << 3;
    colBits |= (rightHalveE[1] & 0xE0) >> 5;

    post_Sbox_R[0] |= S_box2[rowBits][colBits];
    //printf("Sbox1&2: %02x \n", post_Sbox_R[0]);
    //*************
    //  Sbox3
    //*************
    rowBits = (rightHalveE[1] & 0x08) >> 2;
    rowBits |= (rightHalveE[2] & 0x40) >> 6;

    colBits = (rightHalveE[1] & 0x07) << 1;
    colBits |= (rightHalveE[2] & 0x80) >> 7;

    post_Sbox_R[1] = (S_box3[rowBits][colBits] << 4);
    //*************
    //  Sbox4
    //*************
    rowBits = (rightHalveE[2] & 0x20) >> 4;
    rowBits |= (rightHalveE[2] & 0x01);

    colBits = (rightHalveE[2] & 0x1E) >> 1;

    post_Sbox_R[1] |= S_box4[rowBits][colBits];
    //printf("Sbox3&4: %02x \n", post_Sbox_R[1]);
    //*************
    //  Sbox5
    //*************
    rowBits = (rightHalveE[3] & 0x80) >> 6;
    rowBits |= (rightHalveE[3] & 0x04) >> 2;

    colBits = (rightHalveE[3] & 0x78) >> 3;

    post_Sbox_R[2] = (S_box5[rowBits][colBits] << 4);
    //*************
    //  Sbox6
    //*************
    rowBits = (rightHalveE[3] & 0x02);
    rowBits |= (rightHalveE[4] & 0x10) >> 4;

    colBits = (rightHalveE[3] & 0x01) << 3;
    colBits |= (rightHalveE[4] & 0xE0) >> 5;

    post_Sbox_R[2] |= S_box6[rowBits][colBits];
    //printf("Sbox5&6: %02x \n", post_Sbox_R[2]);
    //*************
    //  Sbox7
    //*************
    rowBits = (rightHalveE[4] & 0x08) >> 2;
    rowBits |= (rightHalveE[5] & 0x40) >> 6;

    colBits = (rightHalveE[4] & 0x07) << 1;
    colBits |= (rightHalveE[5] & 0x80) >> 7;

    post_Sbox_R[3] = (S_box7[rowBits][colBits] << 4);
    //*************
    //  Sbox8
    //*************
    rowBits = (rightHalveE[5] & 0x20) >> 4;
    rowBits |= (rightHalveE[5] & 0x01);

    colBits = (rightHalveE[5] & 0x1E) >> 1;

    post_Sbox_R[3] |= S_box8[rowBits][colBits];
    //printf("Sbox7&8: %02x \n", post_Sbox_R[3]);

    //Send output of Switch Boxes into P permutation
    for(i = 0; i < 32; i++){
      copy_bit(post_Sbox_R, rightHalve, P[i], i); 
    }

    //printf("P: %02x%02x %02x%02x\n", rightHalve[0], rightHalve[1], rightHalve[2], 
    //        rightHalve[3]);

    //End of Function

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
