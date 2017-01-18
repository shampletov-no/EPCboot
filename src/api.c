#include "common.h"
#include "api.h"
#include "platform.h"
#include "bootloader.h"
#include "commands.h"

#if defined(__cplusplus)
extern "C"
{
#endif

enum { SLEEP_TIMEOUT = 5000,
       DATA_SEGM_LEN = 128,
       KEY_LEN = 32};

static int legacy = 0;

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


static int key_parse(const char *key, uint8_t *rkey)
{
  if (key == NULL || rkey == NULL)
  {
    fprintf(stderr, "EPCboot: Key parse map error.\n");
    return -1;
  }

  int i = 0;
  char s[3] = {0, 0, 0};

  memset(rkey, 0, KEY_LEN);

  for (i = 0; i < KEY_LEN; i++)
  {
    memset(s, 0, 3);
    memcpy(s, key + 2 * i, 2);
    if (s[0] == 0 || s[1] == 0)
    {
      fprintf(stderr, "EPCboot: Key length less that 256. Error.\n");
      return -1;
    }
    rkey[i] = (uint8_t) strtol(s, NULL, 16);
  }

  return 0;
}


static int check_url_form(const char* url)
{
  if (url == NULL || strlen(url) < 6)
  {
    fprintf(stderr, "EPCboot: empty device url.\n");
    return -1;
  }

  return 0;
}


static device_t update_open(const char *name)
{
  device_t id;

  if (check_url_form(name) == -1)
  {
    return device_undefined;
  }

  id = open_device(name);
  if (id == device_undefined)
  {
    fprintf(stderr, "EPCboot: Can't open device %s\n", name);
	if(strncmp(name, "com:", 4) != 0 && strncmp(name, "emu:", 4) != 0)
		fprintf(stderr, "You write uncorrect device URL. You mast put 'com:' or 'emu:' at begin of url.\n");
    return device_undefined;
  }

  msec_sleep(SLEEP_TIMEOUT);

  if (reboot_to_bootloader(id) != result_ok)
  {
    legacy = 1;
    if (update_firmware(id) != result_ok)
    {
      fprintf(stderr, "EPCboot: Reboot error.\n");
      close_device(&id);
      return device_undefined;
    }
  }

  if (close_device(&id) != result_ok)
  {
    fprintf(stderr, "EPCboot: Close device error.\n");
    return device_undefined;
  }

  msec_sleep(SLEEP_TIMEOUT);

  id = open_device(name);
  if (id == device_undefined)
  {
    fprintf(stderr, "EPCboot: Open device %s error.\n", name);
  }

  return id;
}


result_t URPC_CALLCONV urpc_firmware_update(const char* name, const uint8_t* data, int len) {
  device_t id;
  in_start_session_t st_input;
  out_start_session_t st_output;
  in_end_session_t en_input;
  out_end_session_t en_output;
  size_t dim = 0;
  size_t i = 0;
  write_data_t wd;
  int res = 0;

  int cntr_len = 0;

  memset(&st_input, 0, sizeof(st_input));
  memset(&st_output.reserved, 0, sizeof(st_output.reserved));
  st_output.Result = 0;
  memset(&en_input, 0, sizeof(en_input));
  memset(&en_output.reserved, 0, sizeof(en_output.reserved));
  en_output.Result = 0;

  if (len % DATA_SEGM_LEN == 0) 
  {
    dim = len / DATA_SEGM_LEN;
  }
  else 
  {
    fprintf(stderr, "Data is not correct: data_len=%d segm_len=%d, is not divisible.\n");
    return result_error;
  }

  id = update_open(name);
  if (id == device_undefined) return result_error;

  if ((res=start_session(id, &st_input, &st_output)) != result_ok)
  {
    fprintf(stderr, "EPCboot: Start sesion error %d.\n", res);
    close_device(&id);
    return result_error;
  }

  fprintf(stderr, "EPCboot: start session Result = %d\n", st_output.Result);

  for (i = 0; i < dim; i++) 
  {
    memset(&(wd.Data), 0, DATA_SEGM_LEN);
    memcpy(&(wd.Data), data + i * DATA_SEGM_LEN, DATA_SEGM_LEN);
    cntr_len += DATA_SEGM_LEN;
    if (write_data(id, &wd) != result_ok) 
    {
      fprintf(stderr, "EPCboot:  %d data segment wrote fail.");
      end_session(id, &en_input, &en_output);
      close_device(&id);
      return result_error;
    }
  }

  fprintf(stderr, "EPCboot: firmware correctly wrote. %d\n",  len);

  if (end_session(id, &en_input, &en_output) != result_ok) return result_error;
  fprintf(stderr, "EPCboot: end session Result = %d\n", en_output.Result);

  if (close_device(&id) != result_ok) return result_error;
  return result_ok;
}


result_t URPC_CALLCONV urpc_write_key(const char* name, const char* key)
{
  device_t id;
  in_write_key_t in;
  out_write_key_t out;
  init_random_t irnd;
  result_t res;

  id = update_open(name);
  if (id == device_undefined) return result_error;

  memset((void*)(&in), 0, sizeof(in));
  memset((void*)(&out), 0, sizeof(out));
  memset((void*)(&irnd), 0, sizeof(irnd));

  if (key_parse(key, in.Key) != 0) return result_error;

  //irnd -- use random keys.
  res = init_random(id, &irnd);
  if (res != result_ok)
  {
    fprintf(stderr, "Can't init random. %d", res);
    return res;
  }

  encrypted_key(&irnd, &in);

  printf("Please wait 1-2 min.\n");
  res = write_key(id, &in, &out);
  if (res != result_ok) return res;
  printf("Ok\n");

  res = close_device(&id);
  if ( res!= result_ok) return res;

  return result_ok;
}


result_t URPC_CALLCONV urpc_write_ident(const char* name, const char* key, unsigned int serial, char* hard_id)
{
  device_t id;
  result_t res;
  set_serial_number_t ssn;
  get_identity_information_t out;
  get_serial_number_t legacy_sn_out;
  char* s;
  in_write_key_t key_struct;
  init_random_t irnd;

  id = update_open(name);
  if (id == device_undefined) return result_error;

  memset((void*)(&ssn), 0, sizeof(ssn));
  memset((void*)(&irnd), 0, sizeof(irnd));
  memset((void*)(&key_struct), 0, sizeof(key_struct));

  if (key_parse(key, key_struct.Key) != 0) return result_error;

  //irnd -- use random keys.
  res = init_random(id, &irnd);
  if (res != result_ok)
  {
    fprintf(stderr, "Can't init random. %d", res);
        return res;
  }

  encrypted_key(&irnd, &key_struct);

  memcpy(ssn.Key, key_struct.Key, WKEY_SIZE);
  ssn.SerialNumber = serial;

  char *next;

#ifdef WIN32
  s = strtok_s(hard_id, ".", &next);
  ssn.HardwareMajor = (uint8_t)atoi(s);
  s = strtok_s(next, ".", &next);
  ssn.HardwareMinor = (uint8_t)atoi(s);
  s = strtok_s(next, ".", &next);
  ssn.HardwareBugfix = (uint16_t)atoi(s);
#else
  s = strtok_r(hard_id, ".", &next);
  ssn.HardwareMajor = (uint8_t)atoi(s);
  s = strtok_r(next, ".", &next);
  ssn.HardwareMinor = (uint8_t)atoi(s);
  s = strtok_r(next, ".", &next);
  ssn.HardwareBugfix = (uint16_t)atoi(s);
#endif

  res = set_serial_number(id, &ssn);
  if (res != result_ok)
  {
    fprintf(stderr, "EPCBoot: Can't set ident information to device. set_serial_number() return %d\n", res);
    return res;
  }


  if (legacy)
  {
	  printf("Use legacy.\n");
	  memset((void*)(&legacy_sn_out), 0, sizeof(legacy_sn_out));
	  res = get_serial_number(id, &legacy_sn_out);
	  if ( res != result_ok)
	  {
		  fprintf(stderr, "EPCBoot: Can't get_serial_number(), return %d", res);
		  return res;
	  }

	  if (legacy_sn_out.SerialNumber == ssn.SerialNumber)
	  {
		  fprintf(stderr, "Identy information was wrote correctly.\n");
		  return result_ok;
	  }
	  else
	  {
		  fprintf(stderr, "ERROR: try write %d   %d.%d.%d    Read %d\n",
			  ssn.SerialNumber, ssn.HardwareMajor, ssn.HardwareMinor, ssn.HardwareBugfix,
			  legacy_sn_out.SerialNumber);
		  return result_error;
	  }
  }
  else
  {
    memset((void*)(&out), 0, sizeof(out));
    res = get_identity_information(id, &out);
    if (res != result_ok)
    {
      fprintf(stderr, "EPCBoot: Can't get ident information from device. get_identity_information() return %d\n", res);
      return res;
    }

    if (out.HardwareMajor == ssn.HardwareMajor  &&
    out.HardwareMinor == ssn.HardwareMinor  &&
    out.HardwareBugfix == ssn.HardwareBugfix &&
    out.SerialNumber == ssn.SerialNumber)
    {
		fprintf(stderr, "Identy information was wrote correctly.\n");
		return result_ok;
    }
	else
	{
		fprintf(stderr, "ERROR: try write %d   %d.%d.%d    Read %d   %d.%d.%d\n",
			ssn.SerialNumber, ssn.HardwareMajor, ssn.HardwareMinor, ssn.HardwareBugfix,
			out.SerialNumber, out.HardwareMajor, out.HardwareMinor, out.HardwareBugfix);
		return result_error;
	}
  }

  return result_ok;
}

#if defined(__cplusplus)
};
#endif

