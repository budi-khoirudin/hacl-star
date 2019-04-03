#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "Hacl_Chacha20Poly1305.h"

uint8_t
aead_plaintext[114] =
    {
      0x4c,      0x61,      0x64,      0x69,      0x65,      0x73,      0x20,      0x61,
      0x6e,      0x64,      0x20,      0x47,      0x65,      0x6e,      0x74,      0x6c,
      0x65,      0x6d,      0x65,      0x6e,      0x20,      0x6f,      0x66,      0x20,
      0x74,      0x68,      0x65,      0x20,      0x63,      0x6c,      0x61,      0x73,
      0x73,      0x20,      0x6f,      0x66,      0x20,      0x27,      0x39,      0x39,
      0x3a,      0x20,      0x49,      0x66,      0x20,      0x49,      0x20,      0x63,
      0x6f,      0x75,      0x6c,      0x64,      0x20,      0x6f,      0x66,      0x66,
      0x65,      0x72,      0x20,      0x79,      0x6f,      0x75,      0x20,      0x6f,
      0x6e,      0x6c,      0x79,      0x20,      0x6f,      0x6e,      0x65,      0x20,
      0x74,      0x69,      0x70,      0x20,      0x66,      0x6f,      0x72,      0x20,
      0x74,      0x68,      0x65,      0x20,      0x66,      0x75,      0x74,      0x75,
      0x72,      0x65,      0x2c,      0x20,      0x73,      0x75,      0x6e,      0x73,
      0x63,      0x72,      0x65,      0x65,      0x6e,      0x20,      0x77,      0x6f,
      0x75,      0x6c,      0x64,      0x20,      0x62,      0x65,      0x20,      0x69,
      0x74,      0x2e
    };

uint8_t aead_nonce[12] = {0x07,0x00,0x00,0x00,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47};

uint8_t aead_key[32] = {
    	0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
	0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f
};

uint8_t aead_aad[12] = {
        0x50,0x51,0x52,0x53,0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7
};

uint8_t aead_ciphertext[114] = {
        0xd3,0x1a,0x8d,0x34,0x64,0x8e,0x60,0xdb,0x7b,0x86,0xaf,0xbc,0x53,0xef,0x7e,0xc2,
	0xa4,0xad,0xed,0x51,0x29,0x6e,0x08,0xfe,0xa9,0xe2,0xb5,0xa7,0x36,0xee,0x62,0xd6,
	0x3d,0xbe,0xa4,0x5e,0x8c,0xa9,0x67,0x12,0x82,0xfa,0xfb,0x69,0xda,0x92,0x72,0x8b,
	0x1a,0x71,0xde,0x0a,0x9e,0x06,0x0b,0x29,0x05,0xd6,0xa5,0xb6,0x7e,0xcd,0x3b,0x36,
	0x92,0xdd,0xbd,0x7f,0x2d,0x77,0x8b,0x8c,0x98,0x03,0xae,0xe3,0x28,0x09,0x1b,0x58,
	0xfa,0xb3,0x24,0xe4,0xfa,0xd6,0x75,0x94,0x55,0x85,0x80,0x8b,0x48,0x31,0xd7,0xbc,
	0x3f,0xf4,0xde,0xf0,0x8e,0x4b,0x7a,0x9d,0xe5,0x76,0xd2,0x65,0x86,0xce,0xc6,0x4b,
	0x61,0x16
};

uint8_t aead_mac[16] = {
        0x1a,0xe1,0x0b,0x59,0x4f,0x09,0xe2,0x6a,0x7e,0x90,0x2e,0xcb,0xd0,0x60,0x06,0x91

};


void
aead_encrypt(
  uint8_t *k,
  uint8_t *n1,
  uint32_t aadlen,
  uint8_t *aad,
  uint32_t mlen,
  uint8_t *m,
  uint8_t *cipher,
  uint8_t *mac
);

uint32_t
aead_decrypt(
  uint8_t *k,
  uint8_t *n1,
  uint32_t aadlen,
  uint8_t *aad,
  uint32_t mlen,
  uint8_t *m,
  uint8_t *cipher,
  uint8_t *mac
);

int main(){
  int res;
  uint8_t plaintext[114];
  memset(plaintext, 0, 114 * sizeof plaintext[0]);
  uint8_t ciphertext[114];
  memset(ciphertext, 0, 114 * sizeof ciphertext[0]);
  uint8_t mac[16];
  memset(mac, 0, 16 * sizeof mac[0]);

  printf("Testing HACL* Hacl_Chacha20Poly1305\n");
  aead_encrypt(aead_key, aead_nonce, 12, aead_aad, 114, aead_plaintext, ciphertext, mac);
  res = memcmp(ciphertext, aead_ciphertext, 114 * sizeof (uint8_t));
  if (res != 0){
    printf("AEAD (Chacha20) failed on RFC test of size 114\n.");
  }
  res = memcmp(mac, aead_mac, 16 * sizeof (uint8_t));
  if (res != 0){
    printf("AEAD (Poly1305) failed on RFC test of size 114\n.");
  }

  res = aead_decrypt(aead_key, aead_nonce, 12, aead_aad, 114, plaintext, aead_ciphertext, aead_mac);
  if (res != 0){
    printf("AEAD Decrypt (Chacha20/Poly1305) failed on RFC test of size 114\n.");
  }
  res = memcmp(plaintext, aead_plaintext, 114 * sizeof (uint8_t));
  if (res != 0){
    printf("AEAD Decrypt (Chacha20/Poly1305) failed on RFC test of size 114\n.");
  }
  if (res == 0){
    printf("\nSuccess !\n");
  } else {
    printf("\nFailure !\n");
  }
}
