

from ctypes import *
import os
import platform

# Load library

# use cdecl on unix and stdcall on windows
def project_shared_lib():
    if platform.system() == "Windows":
        return CDLL("urio.dll")
    else:
        return CDLL("liburio.so")

# Common declarations

class Result:
    Ok = 0
    Error = -1
    NotImplemented = -2
    ValueError = -3
    NoDevice = -4

# ---------------------------
# BEGIN OF GENERATED code
# ---------------------------

STATE_SECUR  =  0x3ffc0
STATE_ALARM  =  0x40
STATE_CONTROLLER_OVERHEAT  =  0x80
STATE_OUTPUT1_OVERCURRENT  =  0x100
STATE_OUTPUT2_OVERCURRENT  =  0x200
STATE_OUTPUT3_OVERCURRENT  =  0x400
STATE_OUTPUT4_OVERCURRENT  =  0x800
STATE_TOTAL_POWER_SURGE  =  0x1000
STATE_TOTAL_UNDERPOWER  =  0x2000
STATE_OUTPUT1_UNDERCURRENT  =  0x4000
STATE_OUTPUT2_UNDERCURRENT  =  0x8000
STATE_OUTPUT3_UNDERCURRENT  =  0x10000
STATE_OUTPUT4_UNDERCURRENT  =  0x20000
STATE_INPUT1_ACTIVE  =  0x1
STATE_INPUT2_ACTIVE  =  0x2
STATE_INPUT3_ACTIVE  =  0x4
STATE_INPUT4_ACTIVE  =  0x8
STATE_INPUTS_ACTIVE_BITS  =  0xf
STATE_OUTPUT1_ENABLE  =  0x1
STATE_OUTPUT2_ENABLE  =  0x2
STATE_OUTPUT3_ENABLE  =  0x4
STATE_OUTPUT4_ENABLE  =  0x8
STATE_OUTPUTS_ENABLE_BITS  =  0xf
STATE_OUTPUT1_DISABLE  =  0x1
STATE_OUTPUT2_DISABLE  =  0x2
STATE_OUTPUT3_DISABLE  =  0x4
STATE_OUTPUT4_DISABLE  =  0x8
STATE_OUTPUTS_DISABLE_BITS  =  0xf
STATE_OUTPUT1_ACTIVE  =  0x1
STATE_OUTPUT2_ACTIVE  =  0x2
STATE_OUTPUT3_ACTIVE  =  0x4
STATE_OUTPUT4_ACTIVE  =  0x8
STATE_OUTPUTS_ACTIVE_BITS  =  0xf
ALARM_OUTPUT_OVERCURRENT  =  0x2
ALARM_OUTPUT_UNDERCURRENT  =  0x4
ALARM_CONTROLLER_OVERHEAT  =  0x1
ALARM_TOTAL_POWER_SURGE  =  0x8
ALARM_TOTAL_POWER_LOW  =  0x10



class get_status_t(Structure):
    _fields_ = [
         ("CurT", c_int16),
         ("Flags", c_uint32),
         ("InputStates", c_uint32),
         ("reserved", c_uint8 * 18),
    ]

class get_identity_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_uint8 * 16),
         ("ProductName", c_uint8 * 16),
         ("ControllerName", c_uint8 * 16),
         ("HardwareMajor", c_uint8),
         ("HardwareMinor", c_uint8),
         ("HardwareBugfix", c_uint16),
         ("BootloaderMajor", c_uint8),
         ("BootloaderMinor", c_uint8),
         ("BootloaderBugfix", c_uint16),
         ("FirmwareMajor", c_uint8),
         ("FirmwareMinor", c_uint8),
         ("FirmwareBugfix", c_uint16),
         ("SerialNumber", c_uint32),
         ("reserved", c_uint8 * 8),
    ]

class get_analog_data_t(Structure):
    _fields_ = [
         ("OutputCurrents_ADC", c_uint16 * 4),
         ("OutputCurrents", c_int32 * 4),
         ("SupplyVoltage_ADC", c_uint16),
         ("SupplyVoltage", c_int16),
         ("Temp_ADC", c_uint16),
         ("reserved", c_uint8 * 18),
    ]

class debug_read_t(Structure):
    _fields_ = [
         ("DebugData", c_uint8 * 128),
         ("reserved", c_uint8 * 8),
    ]

class debug_write_t(Structure):
    _fields_ = [
         ("DebugData", c_uint8 * 128),
         ("reserved", c_uint8 * 8),
    ]

class set_output_enable_t(Structure):
    _fields_ = [
         ("EnableFlags", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class set_output_disable_t(Structure):
    _fields_ = [
         ("DisableFlags", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class get_output_state_t(Structure):
    _fields_ = [
         ("OutputFlags", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class secure_settings_t(Structure):
    _fields_ = [
         ("CriticalT", c_uint16),
         ("MaxOutputCurrent", c_uint32 * 4),
         ("MinOutputCurrent", c_uint32 * 4),
         ("MaxPower", c_uint32),
         ("MinPower", c_uint32),
         ("Flags", c_uint32),
         ("reserved", c_uint8 * 6),
    ]

class calibration_settings_t(Structure):
    _fields_ = [
         ("Out_A", c_uint16 * 4),
         ("Out_B", c_int16 * 4),
         ("Temp_A", c_uint16),
         ("Temp_B", c_int16),
         ("Volt_A", c_uint16),
         ("Volt_B", c_int16),
         ("reserved", c_uint8 * 24),
    ]


# -------------------------
# END OF GENERATED code
# -------------------------