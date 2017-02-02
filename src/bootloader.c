#include "common.h"

#include "bootloader.h"
#include "util.h"
#include "metadata.h"
#include "platform.h"
#include "protosup.h"

#if !defined(URPC_EXPORTS)
#error URPC_EXPORTS must be defined when building a library
#endif

#if defined(__cplusplus)
extern "C" {
#endif

result_t URPC_CALLCONV reset(device_t id) {
    result_t result;
    byte out_buffer[4];
//    byte in_buffer[4];
    byte *p;
//    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "rest");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 4));
}
result_t URPC_CALLCONV write_key(device_t id, in_write_key_t* input, out_write_key_t* output) {
    result_t result;
    byte out_buffer[46];
    byte in_buffer[15];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "wkey");
    for(i=0; i<32; i++) push_uint8_t(&p, input->Key[i]);
    for(i=0; i<8; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 46)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 46, in_buffer, 15)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Result = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 15, in_buffer));
}

result_t URPC_CALLCONV start_session(device_t id, in_start_session_t* input, out_start_session_t* output) {
    result_t result;
    byte out_buffer[14];
    byte in_buffer[15];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "conn");
    for(i=0; i<8; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 14)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 14, in_buffer, 15)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Result = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 15, in_buffer));
}

result_t URPC_CALLCONV end_session(device_t id, in_end_session_t* input, out_end_session_t* output) {
    result_t result;
    byte out_buffer[14];
    byte in_buffer[15];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "disc");
    for(i=0; i<8; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 14)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 14, in_buffer, 15)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Result = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 15, in_buffer));
}
result_t URPC_CALLCONV write_data(device_t id, write_data_t* input) {
    result_t result;
    byte out_buffer[142];
//    byte in_buffer[4];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "wdat");
    for(i=0; i<128; i++) push_uint8_t(&p, input->Data[i]);
    for(i=0; i<8; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 142)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 142));
}
result_t URPC_CALLCONV get_device_information(device_t id, get_device_information_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[36];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "geti");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 36)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    for(i=0; i<4; i++) output->Manufacturer[i] = pop_uint8_t(&p);
    for(i=0; i<2; i++) output->ManufacturerId[i] = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->ProductDescription[i] = pop_uint8_t(&p);
    output->Major = pop_uint8_t(&p);
    output->Minor = pop_uint8_t(&p);
    output->Release = pop_uint16_t(&p);
    for(i=0; i<12; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 36, in_buffer));
}
result_t URPC_CALLCONV get_bootloader_version(device_t id, get_bootloader_version_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[10];
    byte *p;
//    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "gblv");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 10)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Major = pop_uint8_t(&p);
    output->Minor = pop_uint8_t(&p);
    output->Release = pop_uint16_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 10, in_buffer));
}

result_t URPC_CALLCONV has_firmware(device_t id, has_firmware_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[15];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "hasf");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 15)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Result = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 15, in_buffer));
}

result_t URPC_CALLCONV goto_firmware(device_t id, goto_firmware_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[15];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "gofw");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 15)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->Result = pop_uint8_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 15, in_buffer));
}

result_t URPC_CALLCONV init_random(device_t id, init_random_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[24];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "irnd");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 24)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    for(i=0; i<16; i++) output->Key[i] = pop_uint8_t(&p);
    for(i=0; i<2; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 24, in_buffer));
}

result_t URPC_CALLCONV set_serial_number(device_t id, set_serial_number_t* input) {
    result_t result;
    byte out_buffer[50];
//    byte in_buffer[4];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "sser");
    push_uint32_t(&p, input->SerialNumber);
    for(i=0; i<32; i++) push_uint8_t(&p, input->Key[i]);
    push_uint8_t(&p, input->HardwareMajor);
    push_uint8_t(&p, input->HardwareMinor);
    push_uint16_t(&p, input->HardwareBugfix);
    for(i=0; i<4; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 50)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 50));
}

result_t URPC_CALLCONV get_serial_number(device_t id, get_serial_number_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[10];
    byte *p;
//    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "gser");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 10)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    output->SerialNumber = pop_uint32_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 10, in_buffer));
}

result_t URPC_CALLCONV update_firmware(device_t id) {
    result_t result;
    byte out_buffer[4];
//    byte in_buffer[4];
    byte *p;
//    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "updf");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 4));
}

result_t URPC_CALLCONV get_status(device_t id, get_status_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[54];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "gets");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 54)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    for(i=0; i<48; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 54, in_buffer));
}

result_t URPC_CALLCONV get_identity_information(device_t id, get_identity_information_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[78];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "ginf");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 78)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    for(i=0; i<16; i++) output->Manufacturer[i] = pop_uint8_t(&p);
    for(i=0; i<16; i++) output->ProductName[i] = pop_uint8_t(&p);
    for(i=0; i<16; i++) output->ControllerName[i] = pop_uint8_t(&p);
    output->HardwareMajor = pop_uint8_t(&p);
    output->HardwareMinor = pop_uint8_t(&p);
    output->HardwareBugfix = pop_uint16_t(&p);
    output->BootloaderMajor = pop_uint8_t(&p);
    output->BootloaderMinor = pop_uint8_t(&p);
    output->BootloaderBugfix = pop_uint16_t(&p);
    output->FirmwareMajor = pop_uint8_t(&p);
    output->FirmwareMinor = pop_uint8_t(&p);
    output->FirmwareBugfix = pop_uint16_t(&p);
    output->SerialNumber = pop_uint32_t(&p);
    for(i=0; i<8; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 78, in_buffer));
}

result_t URPC_CALLCONV reboot_to_bootloader(device_t id) {
    result_t result;
    byte out_buffer[4];
//    byte in_buffer[4];
    byte *p;
//    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "rbld");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 4));
}

result_t URPC_CALLCONV get_dummy(device_t id, dummy_t* output) {
    result_t result;
    byte out_buffer[4];
    byte in_buffer[10];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "gdmy");
    if((result = check_out_overrun(p-out_buffer, 4)) != result_ok)
        return unlocker(id, result);
    if((result = command_checked(id, out_buffer, 4, in_buffer, 10)) != result_ok)
        return unlocker(id, result);

    // Gettings response
    p = in_buffer+4;
    for(i=0; i<4; i++) output->reserved[i] = pop_uint8_t(&p);

    return unlocker(id, check_in_overrun(id, p-in_buffer, 10, in_buffer));
}
result_t URPC_CALLCONV set_dummy(device_t id, dummy_t* input) {
    result_t result;
    byte out_buffer[10];
//    byte in_buffer[4];
    byte *p;
    unsigned int i;

    lock(id);
    // Sending request
    p = out_buffer;
    push_str(&p, "sdmy");
    for(i=0; i<4; i++) push_uint8_t(&p, input->reserved[i]);
    push_crc(&p, out_buffer, p-out_buffer);
    if((result = check_out_overrun(p-out_buffer, 10)) != result_ok)
        return unlocker(id, result);
    return unlocker(id, command_checked_echo(id, out_buffer, 10));
}

    #if defined(__cplusplus)
};
#endif
