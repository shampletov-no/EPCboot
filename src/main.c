
#include "api.h"

#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

//#include <stdio.h>
//#include <string.h>

#ifdef WIN32
    #include "getopt.h"
#else
    #include <unistd.h>
#endif

static void print_usage(const char* exe)
{
    printf("Usage:\n");
    printf("%s -a PORT_URL -K KEY\n", exe);
    printf("For set cryptographic key for device.\n");
    printf("OR\n");
    printf("%s -a PORT_URL -I KEY -s SERIAL -v MAJOR.MINOR.REVISION\n", exe);
    printf("For set serial number of device and it's hardware version.\n");
    printf("OR\n");
    printf("%s -a PORT_URL -F FILE\n", exe);
    printf("For set new firmware\n");
    printf("OR\n");
    printf("%s -h", exe);
}

static int check_url(const char* url)
{
    if (url == NULL)
    {
        printf("You mast specify device URL.\n");
        return 0;
    }

    return 1;
}

static int fw_update(const char *url, const char *path)
{
    int res = 0;
    uint8_t *buf = NULL;
    int count = 0;
    int len = 0;
    FILE *f = NULL;

    if (path == NULL)
    {
        fprintf(stderr, "You mast specify firmware file.\n");
        return -1;
    }

#ifdef WIN32
    res = fopen_s(&f, path, "rb");
#else
    f = fopen(path, "rb");
    if (f == NULL) res = errno;
#endif
    if (res)
    {
        fprintf(stderr, "Can't open file %s %d. Exit.\n", path, res);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    len =  ftell(f);
    fseek(f, 0, 0);

    buf = (unsigned char*)calloc(len, 1);
    if (buf == NULL)
    {
        fprintf(stderr, "To less memory! Exit.\n");
        fclose(f);
        exit(1);
    }

    while (!feof(f) && count < len)
    {
        count += fread(buf + count, 1, len - count , f);
        if (ferror(f))
        {
            fprintf(stderr, "Can't read data.\n");
            fclose(f);
            free(buf);
            exit(1);
        }
    }

    res = urpc_firmware_update(url, buf, len);
    if (res == 0) fprintf(stderr, "Ok\n");
    else fprintf(stderr, "Fail\n");

    if (buf) free(buf);
    if (f) fclose(f);
    return res;
}


static void begin_log (char state, char* url, char* first, char* second)
{
    time_t sec = time(NULL);
    fprintf(stderr, "\n%sepcboot 0.2.1 %c %s\n", ctime(&sec), state, url);
    fprintf(stderr, "%s\n", first);
    if(state == 'I') fprintf(stderr, "%s\n", second);
}


int main(int argc, char** argv) {
    int opt = 0;
    int res = -1;
    char state = 0;

    char *filename = NULL;
    char *key      = NULL;
    char *url      = NULL;
    char *serial   = NULL;
    char *hard     = NULL;

    while ((opt = getopt(argc, argv, "K:I:F:s:v:a:h")) != -1) {
        switch (opt) {
            case 'K':
                key = optarg;
                state = 'K';
                break;

            case 'I':
                key = optarg;
                state = 'I';
                break;

            case 'F':
                filename = optarg;
                state = 'F';
                break;

            case 'a':
                url = optarg;
                break;

            case 's':
                serial = optarg;
                break;

            case 'v':
                hard = optarg;
                break;

            case '?':
            case 'h':
            default :;
        }
    }

    switch (state)
    {
        case 0:
            print_usage(argv[0]);
        break;

        case 'K':
            if (!check_url(url)) break;
            begin_log('K', url, key, NULL);
            res = urpc_write_key(url, key);
        break;

        case 'I':
            if (!check_url(url)) break;
            begin_log('I', url, serial, hard);
            res = urpc_write_ident(url, key, (unsigned int)atoi(serial), hard);
        break;

        case 'F':
            if (!check_url(url)) break;
            begin_log('F', url, filename, NULL);
            res = fw_update(url, filename);
        break;
    }

    return res;
}

