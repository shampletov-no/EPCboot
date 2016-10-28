#include "common.h"

#include "bootloader.h"

#include "types.h"
#include "commands.h"

#include "util.h"
#include "metadata.h"
#include "platform.h"

#include "iobuffer.h"

#include "flowparser.h"

#define PROTOCOL_VERSION_Q "0.3.0"


#if defined(__cplusplus)
extern "C"
{
#endif





typedef struct
{
    char version[16];
    settings_storage_t set;

    uint32_t serial;                      /////that's may be wrong.
} AllParamsStr;



unsigned short CRC16(const uint8_t *pbuf, unsigned short n)
{
	unsigned short crc, i, j, carry_flag, a;
	crc = 0xffff;
	for(i = 0; i < n; i++)
	{
		crc = crc ^ pbuf[i];
		for(j = 0; j < 8; j++)
		{
			a = crc;
			carry_flag = a & 0x0001;
			crc = crc >> 1;
			if ( carry_flag == 1 ) crc = crc ^ 0xa001;
		}
	}
	return crc;
}

/*
	This function is a lookup routine to get additional data length in the packet
	If command is listed in the switch placeholder - it returns corresponding data length.
	If not - it returns zero, which means that no additional data is attached.
*/

/*
static uint16_t GetReadDataSize(uint32_t Command)
{
	return Commands_GetInputSize(Command);
}

static uint16_t GetWriteDataSize(uint32_t Command)
{
	return Commands_GetOutputSize(Command);
}
            */

ssize_t read_port_virtual (device_metadata_t *metadata, void *buf, size_t amount)
{
	/*if (metadata->virtual_packet_actual + amount > metadata->virtual_packet_size)
	{
		log_error( L"Virtual packet overflow from %d to %d by %d",
				metadata->virtual_packet_actual, metadata->virtual_packet_size, amount);
		return -1;
	}
	else
	{
		memcpy( buf, metadata->virtual_scratchpad + metadata->virtual_packet_actual,
				amount );
		metadata->virtual_packet_actual += amount;

		return (ssize_t)amount;
	}*/

    IOBuffer_GetBuf(&(metadata->tx_buffer), buf, amount);

    return (ssize_t)amount;


}

ssize_t write_port_virtual (device_metadata_t *metadata, const void *buf, size_t amount)
{

/*AllParamsStr* allParams = (AllParamsStr*)metadata->virtual_state;
	size_t in_data_size = GetReadDataSize(*((uint32_t*)buf));

	 ///Process data and save response in scratchpad
	metadata->virtual_packet_actual = 0;
	metadata->virtual_packet_size = GetData(buf, in_data_size,
			metadata->virtual_scratchpad, allParams);
	if (metadata->virtual_packet_size > VIRTUAL_SCRATCHPAD_SIZE)
	{
		log_error( L"Scratchpad overflow" );
		return -1;
	}
	log_debug( L"Write virtual port in logical %d, out binary %d",
			amount, metadata->virtual_packet_size );
                                                                                */

    io_buffer_t rx_buffer;
    IOBuffer_Init(&rx_buffer);

    IOBuffer_PutBuf(&rx_buffer, buf, amount);

    AllParamsStr* all_params = (AllParamsStr*)metadata->virtual_state;

    /*if (!FlowParser_Process(&(all_params->set),&rx_buffer, &(metadata->tx_buffer))) {
        exit(11);
    }*/


    ssize_t written = IOBuffer_Size(&rx_buffer);

    FlowParser_Process(&rx_buffer, &(metadata->tx_buffer));

    return written;

}

void create_empty_state (AllParamsStr* blob, const char* serial)
{

    memset( blob, 0, sizeof(AllParamsStr) );
    strncpy( blob->version, PROTOCOL_VERSION_Q, sizeof(blob->version) );

    /* Serial */
	if (serial)
	{
		if (sscanf(serial, "%u", &blob->serial) != 1)
			serial = 0;
		log_debug( L"Setting existing serial: %u", blob->serial);
	}
}

/* Returns 1 if virtual state is incompatible with sources */
int check_state_version (AllParamsStr* blob)
{
	char file_version[sizeof(blob->version)+1] = { 0 };
	char actual_version[sizeof(blob->version)+1] = { 0 };
	char *tmp;

	strncpy( file_version, blob->version, sizeof(blob->version) );
	strncpy( actual_version, PROTOCOL_VERSION_Q, sizeof(blob->version) );

	/* cut major version */
	if ((tmp = strstr( file_version, "." )) != NULL)
		*tmp = 0;
	if ((tmp = strstr( actual_version, "." )) != NULL)
		*tmp = 0;

	return strcmp(file_version, actual_version) != 0;
}

result_t open_port_virtual (device_metadata_t *metadata, const char* virtual_path, const char* serial)
{
	FILE *file;
	AllParamsStr *blob;
	size_t flen;
	int need_create_empty_state = 1;



	if (PACKET_SIZE > VIRTUAL_SCRATCHPAD_SIZE)
	{
		log_system_error( L"not enough scratchpad size" );
		return result_error;
	}


	blob = malloc(sizeof(AllParamsStr));
	if (!blob)
	{
		log_system_error( L"cannot allocate memory" );
		return result_error;
	}

	file = fopen( virtual_path, "rb+" );
	if (file == NULL)
	{
		log_warning( L"no state file, creating" );

		/* Reopen as rw */
		file = fopen( virtual_path, "wb+" );
		if (file == NULL)
		{
			log_system_error( L"can't open virtual device %hs due to: ", virtual_path );
			free( blob );
			return result_error;
		}

	}
	else
	{
		/* Get a file size */
		if (fseek( file, 0, SEEK_END ))
		{
			fclose( file );
			free( blob );
			return result_error;
		}
		flen = (size_t)ftell( file );

		if (flen == sizeof(AllParamsStr))
		{
			/* Read a state from file */
			if (fseek( file, 0, SEEK_SET ))
			{
				fclose( file );
				free( blob );
				return result_error;
			}
			if (fread( blob, sizeof(AllParamsStr), 1, file ) != 1)
			{
				fclose( file );
				free( blob );
				return result_error;
			}

			/* Check state version */
			if (check_state_version( blob ))
			{
				log_warning( L"state file version mismatch, creating new state" );
				need_create_empty_state = 1;
			}
			else
				need_create_empty_state = 0;
		}
		else
		{
			log_warning( L"wrong virtual data file size (expected %d, got %d), creating new state", sizeof(AllParamsStr), flen );
			
			/* truncate the file */
			fclose( file );
			file = fopen( virtual_path, "wb+" );
			if (file == NULL)
			{
				log_system_error( L"can't open virtual device %hs due to: ", virtual_path );
				free( blob );
				return result_error;
			}
		}
	}

	if (need_create_empty_state)
	{
		/* Initialize an empty state */
		create_empty_state( blob, serial );
	}

    IOBuffer_Init(&(metadata->tx_buffer));

	/* save metadata */
	metadata->handle = (handle_t)rand();
	metadata->type = dtVirtual;
	metadata->virtual_state = blob;
	metadata->virtual_file = file;
	
	return result_ok;
}

result_t close_port_virtual (device_metadata_t *metadata)
{
	/* Write virtual blob back to state file */
	if (!metadata->virtual_state)
		return result_error;


	if (fseek( metadata->virtual_file, 0, SEEK_SET ) != 0 ||
			fwrite( metadata->virtual_state, sizeof(AllParamsStr), 1,
				metadata->virtual_file ) != 1)
	{
		fclose( metadata->virtual_file );
		return result_error;
	}

	/* Close a state file */
	if (fclose( metadata->virtual_file ))
	{
		log_system_error( L"error closing virtual device: " );
		return result_error;
	}

    ////IOBuffer_ReInit(&(metadata->tx_buffer))

	free( metadata->virtual_state );

	return result_ok;
}

/* vim: ts=4 shiftwidth=4 */

#if defined(__cplusplus)
extern "C"
{
#endif

#if defined(__cplusplus)
};
#endif