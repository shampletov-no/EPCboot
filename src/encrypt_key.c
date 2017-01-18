#include "bootloader.h"
#include <string.h>
#include "aes.h"

const int AES_BLOCK_SIZE = 16;

static void memxor(void* dest, const void* src, uint16_t n)
{
	while(n--)
	{
		*((uint8_t*)dest) ^= *((uint8_t*)src);
		dest = (uint8_t*)dest +1;
		src  = (uint8_t*)src  +1;
	}
}

result_t encrypted_key(init_random_t *irnd, in_write_key_t *key)
{
	uint8_t cyph_key[WKEY_SIZE];
	uint8_t enc_iv[AES_BLOCK_SIZE];
	uint8_t irnd_key[AES_BLOCK_SIZE];

	memcpy(cyph_key, key->Key, WKEY_SIZE);

	for (int i=0; i<AES_BLOCK_SIZE; i++) // assumes irnd.key size equals AES_BLOCK_SIZE and equals 16
		irnd_key[i] = irnd->Key[i];

	// Preshared IV
	memcpy(enc_iv, "m2c(Knd9YE 2-q;~", AES_BLOCK_SIZE);

	// Simulate two rounds of AES-CBC with our AES-ECB
	memxor(enc_iv, key->Key, AES_BLOCK_SIZE);
	AES128_ECB_encrypt(enc_iv, irnd_key, cyph_key);

	uint8_t interm[AES_BLOCK_SIZE];
	memcpy(interm, cyph_key, AES_BLOCK_SIZE);

	memxor(interm, key->Key + AES_BLOCK_SIZE, AES_BLOCK_SIZE);
	AES128_ECB_encrypt(interm, irnd_key, cyph_key+AES_BLOCK_SIZE);

	memcpy(key->Key, cyph_key, WKEY_SIZE);
	return result_ok;
}


