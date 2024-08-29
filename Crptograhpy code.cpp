#include <iostream>
#include <bitset>

using namespace std;

// Define Block and Key Sizes
const int BLOCK_SIZE = 8;  // Block size in bits
const int KEY_SIZE = 8;    // Key size in bits

// Implement a Simple Substitution Box (S-box)
const int S_BOX[16] = {
    //"0b" is prefix to denote the numbers are in binary
    0b1110, 0b0100, 0b1101, 0b0001,
    0b0010, 0b1111, 0b1011, 0b1000,
    0b0011, 0b1010, 0b0110, 0b1100,
    0b0101, 0b1001, 0b0000, 0b0111
};

int substitute(int nibble) {
    // Substitute a 4-bit nibble using the S-box
    return S_BOX[nibble];
}

// Implement a Simplified Permutation
const int PERMUTATION_TABLE[8] = {1, 5, 2, 0, 3, 7, 4, 6};

int permute(int block) {
    // Permute the 8-bit block according to the permutation table
    int permuted_block = 0;
    for (int i = 0; i < 8; i++) {
        int bit = (block >> PERMUTATION_TABLE[i]) & 1;
        permuted_block |= (bit << i);
    }
    return permuted_block;
}

// Implement a Basic Feistel Function
int feistel_function(int right_half, int key) {
    // Feistel function: XOR the right half with the key
    return right_half ^ key;
}

// Combine Components for Encryption
int encrypt(int block, int key) {
    // Split the block into two 4-bit halves
    int left_half = (block >> 4) & 0x0F;
    int right_half = block & 0x0F;

    // Apply the Feistel function to the right half
    int feistel_output = feistel_function(right_half, key);

    // XOR the Feistel output with the left half
    int new_right_half = left_half ^ feistel_output;

    // Substitute both halves
    int substituted_left = substitute(new_right_half);
    int substituted_right = substitute(right_half);

    // Combine the halves back into an 8-bit block
    int combined_block = (substituted_left << 4) | substituted_right;

    // Permute the bits in the block
    int encrypted_block = permute(combined_block);

    return encrypted_block;
}

int main() {
    // Example block and key (8 bits each)
    int block = 0b11001010;  // Example block
    int key = 0b10101100;    // Example key

    // Encrypt the block using the key
    int encrypted_block = encrypt(block, key);
    cout<<"Sample block: "<<bitset<8> (block)<<" - "<<block<<endl;
    cout<<"Sample key: "<<bitset<8>(key)<<" - "<<key<<endl;
    cout << "Encrypted Block: " << bitset<8>(encrypted_block) <<" - "<<encrypted_block<< endl;

    return 0;
}