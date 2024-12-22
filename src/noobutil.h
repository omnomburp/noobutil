#ifndef NOOB_UTIL_H
#define NOOB_UTIL_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* encode_to_base64_string(const char* input) {
	int str_size = strlen(input);

	int padding = str_size % 3;

	if (padding != 0) {
		padding = 3 - padding;
	}

	char* output = (char*)malloc((str_size + padding + 1) * sizeof(char));
	char* output_ptr = output;

	for (size_t i = 0; i < str_size; i += 3) {
		uint8_t byte1 = input[i];
		uint8_t byte2 = (i + 1 < str_size) ? input[i + 1] : 0;
		uint8_t byte3 = (i + 2 < str_size) ? input[i + 2] : 0;

		uint8_t bits1 = (byte1 >> 2) & 0x3F;
		uint8_t bits2 = (byte1 << 4 | byte2 >> 4) & 0x3F;
		uint8_t bits3 = (byte2 << 2 | byte3 >> 6) & 0x3F;
		uint8_t bits4 = byte3 & 0x3F;

		*output_ptr++ = base64_table[bits1];
		*output_ptr++ = base64_table[bits2];

		if (i + 1 < str_size) {
			*output_ptr++ = base64_table[bits3];
			if (i + 2 < str_size) {
				*output_ptr++ = base64_table[bits4];
			}
		} 
		
	}

	for (size_t j = 0; j < padding; ++j) {
		*output_ptr++ = '=';
	}

	*output_ptr = '\0';

	return output;
}

int get_base64_index(const char c) {
	if (c == '=')
		return 0;
    for (size_t i = 0; i < 64; ++i) {
        if (base64_table[i] == c) {
            return i;
        }
    }
    return 0;
}

char* decode_from_base64_string(const char* input) {
	int str_size = strlen(input);

	char* output = (char*)malloc(((str_size * 3) / 4) + 1);
	char* output_ptr = output;

	for (size_t i = 0; i < str_size; i += 4) {
		uint8_t bits1 = get_base64_index(input[i]);
		uint8_t bits2 = (i + 1 < str_size) ? get_base64_index(input[i + 1]) : 0;
		uint8_t bits3 = (i + 2 < str_size) ? get_base64_index(input[i + 2]) : 0;
		uint8_t bits4 = (i + 3 < str_size) ? get_base64_index(input[i + 3]) : 0;

		uint8_t byte1 = (bits1 << 2) | (bits2 >> 4);
		uint8_t byte2 = (bits2 << 4) | (bits3 >> 2);
		uint8_t byte3 = (bits3 << 6) | bits4;

		*output_ptr++ = byte1;
		if (i + 1 < str_size) {
			*output_ptr++ = byte2;
			if ((i + 2 < str_size) && (i + 3 < str_size)) {
				*output_ptr++ = byte3;
			}
		}
	}

	*output_ptr = '\0';

	return output;
}

#endif