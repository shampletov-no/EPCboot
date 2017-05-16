

from ctypes import *
import os
import platform

# Load library

# use cdecl on unix and stdcall on windows
def project_shared_lib():
    if platform.system() == "Windows":
        return CDLL("urlaser.dll")
    else:
        return CDLL("liburlaser.so")

lib = project_shared_lib()

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
STATE_LASER1_OVERCURRENT  =  0x1
STATE_LASER1_UNDERCURRENT  =  0x2
STATE_PD1_OVERCURRENT  =  0x4
STATE_PD1_UNDERCURRENT  =  0x8
STATE_LASER2_OVERCURRENT  =  0x10
STATE_LASER2_UNDERCURRENT  =  0x20
STATE_PD2_OVERCURRENT  =  0x40
STATE_PD2_UNDERCURRENT  =  0x80
STATE_LASER3_OVERCURRENT  =  0x100
STATE_LASER3_UNDERCURRENT  =  0x200
STATE_PD3_OVERCURRENT  =  0x400
STATE_PD3_UNDERCURRENT  =  0x800
STATE_LASER4_OVERCURRENT  =  0x1000
STATE_LASER4_UNDERCURRENT  =  0x2000
STATE_PD4_OVERCURRENT  =  0x4000
STATE_PD4_UNDERCURRENT  =  0x8000
STATE_LASER5_OVERCURRENT  =  0x10000
STATE_LASER5_UNDERCURRENT  =  0x20000
STATE_PD5_OVERCURRENT  =  0x40000
STATE_PD5_UNDERCURRENT  =  0x80000
STATE_LASER6_OVERCURRENT  =  0x100000
STATE_LASER6_UNDERCURRENT  =  0x200000
STATE_PD6_OVERCURRENT  =  0x400000
STATE_PD6_UNDERCURRENT  =  0x800000
STATE_LASER7_OVERCURRENT  =  0x1000000
STATE_LASER7_UNDERCURRENT  =  0x2000000
STATE_PD7_OVERCURRENT  =  0x4000000
STATE_PD7_UNDERCURRENT  =  0x8000000
STATE_LASER8_OVERCURRENT  =  0x10000000
STATE_LASER8_UNDERCURRENT  =  0x20000000
STATE_PD8_OVERCURRENT  =  0x40000000
STATE_PD8_UNDERCURRENT  =  0x80000000
CHANNEL_1  =  0x1
CHANNEL_2  =  0x2
CHANNEL_3  =  0x4
CHANNEL_4  =  0x8
CHANNEL_5  =  0x10
CHANNEL_6  =  0x20
CHANNEL_7  =  0x40
CHANNEL_8  =  0x80
CHANNELS_BITS  =  0xff
OUTPUT_1  =  0x1
OUTPUT_2  =  0x2
OUTPUT_3  =  0x4
OUTPUT_4  =  0x8
OUTPUT_5  =  0x10
OUTPUT_6  =  0x20
OUTPUT_7  =  0x40
OUTPUT_8  =  0x80
OUTPUTS_BITS  =  0xff
OUTPUT_1  =  0x1
OUTPUT_2  =  0x2
OUTPUT_3  =  0x4
OUTPUT_4  =  0x8
OUTPUT_5  =  0x10
OUTPUT_6  =  0x20
OUTPUT_7  =  0x40
OUTPUT_8  =  0x80
OUTPUTS_BITS  =  0xff
ALARM_OUTPUT_OVERCURRENT  =  0x2
ALARM_OUTPUT_UNDERCURRENT  =  0x4
ALARM_PD_OVERCURRENT  =  0x8
ALARM_PD_UNDERCURRENT  =  0x10
ALARM_CONTROLLER_OVERHEAT  =  0x1



class get_status_t(Structure):
    _fields_ = [
         ("CurT", c_int16),
         ("Flags", c_uint32),
         ("LasersSecurityFlags", c_uint32),
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

class analog_data_t(Structure):
    _fields_ = [
         ("LaserCurrents_ADC", c_uint16 * 8),
         ("PDCurrents_ADC", c_uint16 * 8),
         ("LaserCurrents", c_uint32 * 8),
         ("PDCurrents", c_uint16 * 8),
         ("reserved", c_uint8 * 30),
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

class get_laser_output_state_t(Structure):
    _fields_ = [
         ("OutputState", c_uint16),
         ("reserved", c_uint8 * 6),
    ]

class turn_on_laser_t(Structure):
    _fields_ = [
         ("Outputs", c_uint16),
         ("reserved", c_uint8 * 6),
    ]

class turn_off_laser_t(Structure):
    _fields_ = [
         ("Outputs", c_uint16),
         ("reserved", c_uint8 * 6),
    ]

class secure_settings_t(Structure):
    _fields_ = [
         ("CriticalT", c_uint16),
         ("MaxLaserCurrent", c_uint32 * 8),
         ("MinLaserCurrent", c_uint32 * 8),
         ("MaxPDCurrent", c_uint16 * 8),
         ("MinPDCurrent", c_uint16 * 8),
         ("Flags", c_uint32),
         ("reserved", c_uint8 * 6),
    ]

class current_settings_t(Structure):
    _fields_ = [
         ("Currents", c_uint32 * 8),
         ("reserved", c_uint8 * 32),
    ]

class calibration_settings_t(Structure):
    _fields_ = [
         ("Out_A", c_uint16 * 8),
         ("Out_B", c_int32 * 8),
         ("PD_A", c_uint16 * 8),
         ("PD_B", c_int32 * 8),
         ("PWM_A", c_int32 * 8),
         ("PWM_B", c_int32 * 8),
         ("PWM_C", c_int32 * 8),
         ("PWM_D", c_int32 * 8),
         ("Temp_A", c_int32),
         ("Temp_B", c_int32),
         ("reserved", c_uint8 * 11),
    ]


# -------------------------
# END OF GENERATED code
# -------------------------