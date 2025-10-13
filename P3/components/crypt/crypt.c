#include "crypt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <esp_log.h>
#include <aes/esp_aes.h>

#include <serial_io.h>
#include <lownet.h>

void crypt_decrypt(const lownet_secure_frame_t* cipher, lownet_secure_frame_t* plain)
{
	// ...
}

void crypt_encrypt(const lownet_secure_frame_t* plain, lownet_secure_frame_t* cipher)
{
	// ...
}

// Usage: crypt_command(KEY)
// Pre:   KEY is a valid AES key or NULL
// Post:  If key == NULL encryption has been disabled
//        Else KEY has been set as the encryption key to use for
//        lownet communication.
void crypt_setkey_command(char* args)
{
	// ...
}

void crypt_test_command(char* str)
{
	if (!str)
		return;
	if (!lownet_get_key())
		{
			serial_write_line("No encryption key set!");
			return;
		}

	// Encrypts and then decrypts a string, can be used to sanity check your
	// implementation.
	lownet_secure_frame_t plain;
	lownet_secure_frame_t cipher;
	lownet_secure_frame_t back;

	memset(&plain, 0, sizeof(lownet_secure_frame_t));
	memset(&cipher, 0, sizeof(lownet_secure_frame_t));
	memset(&back, 0, sizeof(lownet_secure_frame_t));

	const uint8_t cipher_magic[2] = {0x20, 0x4e};

	memcpy(plain.magic, cipher_magic, sizeof cipher_magic);
	plain.source = lownet_get_device_id();
	plain.destination = 0xFF;
	plain.protocol = 0x02;
	plain.length = strlen(str);

	*((uint32_t*) plain.ivt) = 123456789;
	strcpy((char*) plain.payload, str);

	crypt_encrypt(&plain, &cipher);

	if (memcmp(&plain, &cipher, LOWNET_UNENCRYPTED_SIZE) != 0)
		{
			serial_write_line("Unencrypted part of frame not preserved!");
			return;
		}
	if (memcmp(&plain.ivt, &cipher.ivt, LOWNET_IVT_SIZE) != 0)
		{
			serial_write_line("IVT not preserved!");
			return;
		}

	crypt_decrypt(&cipher, &back);

	if (memcmp(&plain, &back, sizeof plain) == 0)
		{
			serial_write_line("Encrypt/Decrypt successful");
			return;
		}

	serial_write_line("Encrypt/Decrypt failed");
	char msg[200];
	snprintf(msg, sizeof msg,
					 "Unencrypted content: %s\n"
					 "IVT:                 %s\n"
					 "Encrypted content:   %s\n",
					 memcmp(&plain, &back, LOWNET_UNENCRYPTED_SIZE) == 0 ? "Same" : "Different",
					 memcmp(&plain.ivt, &back.ivt, LOWNET_IVT_SIZE) == 0 ? "Same" : "Different",
					 memcmp(&plain.protocol, &back.protocol, LOWNET_ENCRYPTED_SIZE) == 0 ? "Same" : "Different"
	);
	serial_write_line(msg);
}
