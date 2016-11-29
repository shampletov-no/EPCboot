#include "common.h"
#include "api.h"
#include "platform.h"
#include "util.h"
#include "bootloader.h"

#include <string.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C"
{
#endif

enum { SLEEP_TIMEOUT = 2000,
       DATA_SEGM_LEN = 128};

static void print_buf(uint8_t* buf, int bufsize) 
{
  int i = 0;
  printf("%d\t", bufsize);
  for (i = 0; i < bufsize; i++)
  {
    printf("%x ", buf[i]);
  }
  printf("\n");
}

result_t URPC_CALLCONV urpc_firmware_update(const char* name, const uint8_t* data, int len, int old_dev_flag) {
  device_t id;
  in_start_session_t st_input;
  out_start_session_t st_output;
  in_end_session_t en_input;
  out_end_session_t en_output;
  size_t dim = 0;
  size_t i = 0;
  write_data_t wd;

  int cntr_len = 0;

  memset(&st_input, 0, sizeof(st_input));
  memset(&st_output.reserved, 0, sizeof(st_output.reserved));
  st_output.Result = 0;
  memset(&en_input, 0, sizeof(en_input));
  memset(&en_output.reserved, 0, sizeof(en_output.reserved));
  en_output.Result = 0;

  fprintf(stderr, "booloader.dll version 0.0.1\n");

  if (len % DATA_SEGM_LEN == 0) 
  {
    dim = len / DATA_SEGM_LEN;
  }
  else 
  {
    fprintf(stderr, "Data is not correct: data_len=%d segm_len=%d, is not divisible.\n");
    return result_error;
  }

  fprintf(stderr, "data length = %d, segm num = %d\n", len, dim);

  id = open_device(name);
  if (id == device_undefined) 
  {
    fprintf(stderr, "booloader.dll: Can't open device %s\n", name);
    return result_error;
  }

  if (old_dev_flag) 
  {
    if (update_firmware(id) != result_ok) 
    {
      fprintf(stderr, "booloader.dll: Reboot error\n");
      close_device(&id);
      return result_error;
    }
  } 
  else 
  {
    if (reboot_to_bootloader(id) != result_ok) 
    {
       fprintf(stderr, "booloader.dll: Reboot error\n");
       close_device(&id);
       return result_error;
    }
  }

  if (close_device(&id) != result_ok) 
  {
    fprintf(stderr, "booloader.dll: Close device (1) error\n");
    return result_error;
  }
  msec_sleep(SLEEP_TIMEOUT);

  id = open_device(name);
  if (id == device_undefined) 
  {
    fprintf(stderr, "booloader.dll: Open device error\n");
    return result_error;
  }

  if (start_session(id, &st_input, &st_output) != result_ok) 
  {
    fprintf(stderr, "booloader.dll: Start sesion error\n");
    close_device(&id);
    return result_error;
  }

  fprintf(stderr, "booloader.dll: start session Result = %d\n", st_output.Result);

  for (i = 0; i < dim; i++) 
  {
    memset(&(wd.Data), 0, DATA_SEGM_LEN);
    memcpy(&(wd.Data), data + i * DATA_SEGM_LEN, DATA_SEGM_LEN);
    cntr_len += DATA_SEGM_LEN;
    if (write_data(id, &wd) != result_ok) 
    {
      fprintf(stderr, "booloader.dll:  %d data segment write fail.");
      end_session(id, &en_input, &en_output);
      close_device(&id);
      return result_error;
    }
  }

  fprintf(stderr, "booloader.dll: Ok!! %d  %d\n", cntr_len, len);

  if (end_session(id, &en_input, &en_output) != result_ok) return result_error;
  fprintf(stderr, "booloader.dll: end session Result = %d\n", en_output.Result);

  if (close_device(&id) != result_ok) return result_error;
  return result_ok;
}

#if defined(__cplusplus)
};
#endif

