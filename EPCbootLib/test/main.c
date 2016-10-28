
#define WIN32

#include "../src/api.h"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) 
{
	int res = 0;
	uint8_t *buf = NULL;
	int count = 0;
	int len = 0;
	int old_dev = 0;
	FILE *f = NULL;

	if (argc < 3) {
		fprintf(stderr, "Usage: %s <port url> <data path> [Old]\n", argv[0]);
		fprintf(stderr, "Old for using UPDF vs RBLD.\n");
		exit(1);
	}

	if (argc == 4) {
		if (strncmp(argv[3], "Old", 3) == 0) {
			old_dev = 1;
		}
	}

#ifdef WIN32
	res = fopen_s(&f, argv[2], "rb");
#else
	res = fopen(&f, argv[2], "rb");
#endif
	if (res) {
		fprintf(stderr, "Can't open file %d. Exit.\n", res);
		goto END;
	}

	fseek(f, 0, SEEK_END);
	len =  ftell(f);
	fseek(f, 0, 0);
	
	buf = (unsigned char*)calloc(len, 1);
	if (buf == NULL) {
		fprintf(stderr, "To less memory! Exit.\n");
		res = 1;
		goto END;
	}

	while (!feof(f) && count < len) {
		count += fread(buf + count, 1, len - count , f);
		if (ferror(f)) {
			fprintf(stderr, "Can't read data.\n");
			res = 1;
			goto END;
		}
		printf("READ TO BUF %d %d\n", len, count);
	}

	res = urpc_firmware_update(argv[1], buf, len, old_dev);
	if (res == 0) fprintf(stderr, "Ok\n");
	else fprintf(stderr, "Fail\n");

END:
	if (buf) free(buf);
	if (f) fclose(f);
	return res;
}