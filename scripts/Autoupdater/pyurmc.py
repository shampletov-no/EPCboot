

from ctypes import *
import os
import platform

# Load library

# use cdecl on unix and stdcall on windows
def project_shared_lib():
    if platform.system() == "Windows":
        return CDLL("urmc.dll")
    else:
        return CDLL("liburmc.so")

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

SETPOS_IGNORE_POSITION  =  0x1
SETPOS_IGNORE_ENCODER  =  0x2
MOVE_STATE_MOVING  =  0x1
MOVE_STATE_TARGET_SPEED  =  0x2
MOVE_STATE_ANTIPLAY  =  0x4
MVCMD_NAME_BITS  =  0x3f
MVCMD_UKNWN  =  0x0
MVCMD_MOVE  =  0x1
MVCMD_MOVR  =  0x2
MVCMD_LEFT  =  0x3
MVCMD_RIGHT  =  0x4
MVCMD_STOP  =  0x5
MVCMD_HOME  =  0x6
MVCMD_LOFT  =  0x7
MVCMD_SSTP  =  0x8
MVCMD_ERROR  =  0x40
MVCMD_RUNNING  =  0x80
PWR_STATE_UNKNOWN  =  0x0
PWR_STATE_OFF  =  0x1
PWR_STATE_NORM  =  0x3
PWR_STATE_REDUCT  =  0x4
PWR_STATE_MAX  =  0x5
ENC_STATE_ABSENT  =  0x0
ENC_STATE_UNKNOWN  =  0x1
ENC_STATE_MALFUNC  =  0x2
ENC_STATE_REVERS  =  0x3
ENC_STATE_OK  =  0x4
STATE_CONTR  =  0x3f
STATE_EEPROM_CONNECTED  =  0x10
STATE_IS_HOMED  =  0x20
STATE_SECUR  =  0x3ffc0
STATE_ALARM  =  0x40
STATE_CTP_ERROR  =  0x80
STATE_POWER_OVERHEAT  =  0x100
STATE_CONTROLLER_OVERHEAT  =  0x200
STATE_OVERLOAD_POWER_VOLTAGE  =  0x400
STATE_OVERLOAD_POWER_CURRENT  =  0x800
STATE_OVERLOAD_USB_VOLTAGE  =  0x1000
STATE_LOW_USB_VOLTAGE  =  0x2000
STATE_OVERLOAD_USB_CURRENT  =  0x4000
STATE_BORDERS_SWAP_MISSET  =  0x8000
STATE_LOW_POWER_VOLTAGE  =  0x10000
STATE_H_BRIDGE_FAULT  =  0x20000
STATE_CURRENT_MOTOR_BITS  =  0xc0000
STATE_CURRENT_MOTOR0  =  0x0
STATE_CURRENT_MOTOR1  =  0x40000
STATE_CURRENT_MOTOR2  =  0x80000
STATE_CURRENT_MOTOR3  =  0xc0000
STATE_DIG_SIGNAL  =  0xffff
STATE_RIGHT_EDGE  =  0x1
STATE_LEFT_EDGE  =  0x2
STATE_BUTTON_RIGHT  =  0x4
STATE_BUTTON_LEFT  =  0x8
STATE_GPIO_PINOUT  =  0x10
STATE_GPIO_LEVEL  =  0x20
STATE_HALL_A  =  0x40
STATE_HALL_B  =  0x80
STATE_HALL_C  =  0x100
STATE_BRAKE  =  0x200
STATE_REV_SENSOR  =  0x400
STATE_SYNC_INPUT  =  0x800
STATE_SYNC_OUTPUT  =  0x1000
STATE_ENC_A  =  0x2000
STATE_ENC_B  =  0x4000
FEEDBACK_ENCODER  =  0x1
FEEDBACK_ENCODERHALL  =  0x3
FEEDBACK_EMF  =  0x4
FEEDBACK_NONE  =  0x5
FEEDBACK_ENC_REVERSE  =  0x1
FEEDBACK_HALL_REVERSE  =  0x2
FEEDBACK_ENC_TYPE_BITS  =  0xc0
FEEDBACK_ENC_TYPE_AUTO  =  0x0
FEEDBACK_ENC_TYPE_SINGLE_ENDED  =  0x40
FEEDBACK_ENC_TYPE_DIFFERENTIAL  =  0x80
HOME_DIR_FIRST  =  0x1
HOME_DIR_SECOND  =  0x2
HOME_MV_SEC_EN  =  0x4
HOME_HALF_MV  =  0x8
HOME_STOP_FIRST_BITS  =  0x30
HOME_STOP_FIRST_REV  =  0x10
HOME_STOP_FIRST_SYN  =  0x20
HOME_STOP_FIRST_LIM  =  0x30
HOME_STOP_SECOND_BITS  =  0xc0
HOME_STOP_SECOND_REV  =  0x40
HOME_STOP_SECOND_SYN  =  0x80
HOME_STOP_SECOND_LIM  =  0xc0
HOME_USE_FAST  =  0x100
ENGINE_REVERSE  =  0x1
ENGINE_CURRENT_AS_RMS  =  0x2
ENGINE_MAX_SPEED  =  0x4
ENGINE_ANTIPLAY  =  0x8
ENGINE_ACCEL_ON  =  0x10
ENGINE_LIMIT_VOLT  =  0x20
ENGINE_LIMIT_CURR  =  0x40
ENGINE_LIMIT_RPM  =  0x80
MICROSTEP_MODE_FULL  =  0x1
MICROSTEP_MODE_FRAC_2  =  0x2
MICROSTEP_MODE_FRAC_4  =  0x3
MICROSTEP_MODE_FRAC_8  =  0x4
MICROSTEP_MODE_FRAC_16  =  0x5
MICROSTEP_MODE_FRAC_32  =  0x6
MICROSTEP_MODE_FRAC_64  =  0x7
MICROSTEP_MODE_FRAC_128  =  0x8
MICROSTEP_MODE_FRAC_256  =  0x9
ENGINE_TYPE_NONE  =  0x0
ENGINE_TYPE_DC  =  0x1
ENGINE_TYPE_2DC  =  0x2
ENGINE_TYPE_STEP  =  0x3
ENGINE_TYPE_TEST  =  0x4
ENGINE_TYPE_BRUSHLESS  =  0x5
POWER_REDUCT_ENABLED  =  0x1
POWER_OFF_ENABLED  =  0x2
POWER_SMOOTH_CURRENT  =  0x4
ALARM_ON_DRIVER_OVERHEATING  =  0x1
LOW_UPWR_PROTECTION  =  0x2
H_BRIDGE_ALERT  =  0x4
ALARM_ON_BORDERS_SWAP_MISSET  =  0x8
ALARM_FLAGS_STICKING  =  0x10
USB_BREAK_RECONNECT  =  0x20
BORDER_IS_ENCODER  =  0x1
BORDER_STOP_LEFT  =  0x2
BORDER_STOP_RIGHT  =  0x4
BORDERS_SWAP_MISSET_DETECTION  =  0x8
ENDER_SWAP  =  0x1
ENDER_SW1_ACTIVE_LOW  =  0x2
ENDER_SW2_ACTIVE_LOW  =  0x4
CTP_ENABLED  =  0x1
CTP_BASE  =  0x2
CTP_ALARM_ON_ERROR  =  0x4
REV_SENS_INV  =  0x8
CTP_ERROR_CORRECTION  =  0x10
EEPROM_PRECEDENCE  =  0x1
MOTOR_TYPE_UNKNOWN  =  0x0
MOTOR_TYPE_STEP  =  0x1
MOTOR_TYPE_DC  =  0x2
MOTOR_TYPE_BLDC  =  0x3
ENCSET_DIFFERENTIAL_OUTPUT  =  0x1
ENCSET_PUSHPULL_OUTPUT  =  0x4
ENCSET_INDEXCHANNEL_PRESENT  =  0x10
ENCSET_REVOLUTIONSENSOR_PRESENT  =  0x40
ENCSET_REVOLUTIONSENSOR_ACTIVE_HIGH  =  0x100
MB_AVAILABLE  =  0x1
MB_POWERED_HOLD  =  0x2
TS_TYPE_BITS  =  0x7
TS_TYPE_UNKNOWN  =  0x0
TS_TYPE_THERMOCOUPLE  =  0x1
TS_TYPE_SEMICONDUCTOR  =  0x2
TS_AVAILABLE  =  0x8
LS_ON_SW1_AVAILABLE  =  0x1
LS_ON_SW2_AVAILABLE  =  0x2
LS_SW1_ACTIVE_LOW  =  0x4
LS_SW2_ACTIVE_LOW  =  0x8
LS_SHORTED  =  0x10



class command_add_sync_in_action_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 16),
    ]

class command_move_t(Structure):
    _fields_ = [
         ("Position", c_int32),
         ("uPosition", c_int16),
         ("reserved", c_uint8 * 6),
    ]

class command_movr_t(Structure):
    _fields_ = [
         ("DeltaPosition", c_int32),
         ("uDeltaPosition", c_int16),
         ("reserved", c_uint8 * 6),
    ]

class get_position_t(Structure):
    _fields_ = [
         ("Position", c_int32),
         ("uPosition", c_int16),
         ("EncPosition", c_int64),
         ("reserved", c_uint8 * 6),
    ]

class set_position_t(Structure):
    _fields_ = [
         ("Position", c_int32),
         ("uPosition", c_int16),
         ("EncPosition", c_int64),
         ("PosFlags", c_uint8),
         ("reserved", c_uint8 * 5),
    ]

class status_impl_t(Structure):
    _fields_ = [
         ("MoveSts", c_uint8),
         ("MvCmdSts", c_uint8),
         ("PWRSts", c_uint8),
         ("EncSts", c_uint8),
         ("WindSts", c_uint8),
         ("CurPosition", c_int32),
         ("uCurPosition", c_int16),
         ("EncPosition", c_int64),
         ("CurSpeed", c_int32),
         ("uCurSpeed", c_int16),
         ("Ipwr", c_int16),
         ("Upwr", c_int16),
         ("Iusb", c_int16),
         ("Uusb", c_int16),
         ("CurT", c_int16),
         ("Flags", c_uint32),
         ("GPIOFlags", c_uint32),
         ("reserved", c_uint8 * 5),
    ]

class chart_data_t(Structure):
    _fields_ = [
         ("WindingVoltageA", c_int16),
         ("WindingVoltageB", c_int16),
         ("WindingVoltageC", c_int16),
         ("WindingCurrentA", c_int16),
         ("WindingCurrentB", c_int16),
         ("WindingCurrentC", c_int16),
         ("Pot", c_uint16),
         ("Joy", c_uint16),
         ("DutyCycle", c_int16),
         ("reserved", c_uint8 * 14),
    ]

class device_information_impl_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 4),
         ("ManufacturerId", c_int8 * 2),
         ("ProductDescription", c_int8 * 8),
         ("Major", c_uint8),
         ("Minor", c_uint8),
         ("Release", c_uint16),
         ("reserved", c_uint8 * 12),
    ]

class get_serial_number_t(Structure):
    _fields_ = [
         ("SerialNumber", c_uint32),
    ]

class firmware_version_t(Structure):
    _fields_ = [
         ("Major", c_uint8),
         ("Minor", c_uint8),
         ("Release", c_uint16),
    ]

class set_serial_number_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 44),
    ]

class analog_data_t(Structure):
    _fields_ = [
         ("A1Voltage_ADC", c_uint16),
         ("A2Voltage_ADC", c_uint16),
         ("B1Voltage_ADC", c_uint16),
         ("B2Voltage_ADC", c_uint16),
         ("SupVoltage_ADC", c_uint16),
         ("ACurrent_ADC", c_uint16),
         ("BCurrent_ADC", c_uint16),
         ("FullCurrent_ADC", c_uint16),
         ("Temp_ADC", c_uint16),
         ("Joy_ADC", c_uint16),
         ("Pot_ADC", c_uint16),
         ("L5_ADC", c_uint16),
         ("H5_ADC", c_uint16),
         ("A1Voltage", c_int16),
         ("A2Voltage", c_int16),
         ("B1Voltage", c_int16),
         ("B2Voltage", c_int16),
         ("SupVoltage", c_int16),
         ("ACurrent", c_int16),
         ("BCurrent", c_int16),
         ("FullCurrent", c_int16),
         ("Temp", c_int16),
         ("Joy", c_int16),
         ("Pot", c_int16),
         ("L5", c_int16),
         ("H5", c_int16),
         ("deprecated", c_uint16),
         ("R", c_int32),
         ("L", c_int32),
         ("reserved", c_uint8 * 8),
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

class bootloader_version_t(Structure):
    _fields_ = [
         ("Major", c_uint8),
         ("Minor", c_uint8),
         ("Release", c_uint16),
    ]

class service_command_goto_firmware_impl_t(Structure):
    _fields_ = [
         ("sresult", c_uint8),
         ("reserved", c_uint8 * 8),
    ]

class change_motor_t(Structure):
    _fields_ = [
         ("Motor", c_uint8),
         ("reserved", c_uint8 * 15),
    ]

class feedback_settings_t(Structure):
    _fields_ = [
         ("IPS", c_uint16),
         ("FeedbackType", c_uint8),
         ("FeedbackFlags", c_uint8),
         ("HallSPR", c_uint16),
         ("HallShift", c_int8),
         ("reserved", c_uint8 * 5),
    ]

class home_settings_t(Structure):
    _fields_ = [
         ("FastHome", c_uint32),
         ("uFastHome", c_uint8),
         ("SlowHome", c_uint32),
         ("uSlowHome", c_uint8),
         ("HomeDelta", c_int32),
         ("uHomeDelta", c_int16),
         ("HomeFlags", c_uint16),
         ("reserved", c_uint8 * 9),
    ]

class move_settings_t(Structure):
    _fields_ = [
         ("Speed", c_uint32),
         ("uSpeed", c_uint8),
         ("Accel", c_uint16),
         ("Decel", c_uint16),
         ("AntiplaySpeed", c_uint32),
         ("uAntiplaySpeed", c_uint8),
         ("reserved", c_uint8 * 10),
    ]

class engine_settings_t(Structure):
    _fields_ = [
         ("NomVoltage", c_uint16),
         ("NomCurrent", c_uint16),
         ("NomSpeed", c_uint32),
         ("uNomSpeed", c_uint8),
         ("EngineFlags", c_uint16),
         ("Antiplay", c_int16),
         ("MicrostepMode", c_uint8),
         ("StepsPerRev", c_uint16),
         ("reserved", c_uint8 * 12),
    ]

class entype_settings_t(Structure):
    _fields_ = [
         ("EngineType", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class power_settings_t(Structure):
    _fields_ = [
         ("HoldCurrent", c_uint8),
         ("CurrReductDelay", c_uint16),
         ("PowerOffDelay", c_uint16),
         ("CurrentSetTime", c_uint16),
         ("PowerFlags", c_uint8),
         ("reserved", c_uint8 * 6),
    ]

class secure_settings_t(Structure):
    _fields_ = [
         ("LowUpwrOff", c_uint16),
         ("CriticalIpwr", c_uint16),
         ("CriticalUpwr", c_uint16),
         ("CriticalT", c_uint16),
         ("CriticalIusb", c_uint16),
         ("CriticalUusb", c_uint16),
         ("MinimumUusb", c_uint16),
         ("Flags", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class edges_settings_t(Structure):
    _fields_ = [
         ("BorderFlags", c_uint8),
         ("EnderFlags", c_uint8),
         ("LeftBorder", c_int32),
         ("uLeftBorder", c_int16),
         ("RightBorder", c_int32),
         ("uRightBorder", c_int16),
         ("reserved", c_uint8 * 6),
    ]

class pid_settings_t(Structure):
    _fields_ = [
         ("KpU", c_uint16),
         ("KiU", c_uint16),
         ("KdU", c_uint16),
         ("reserved", c_uint8 * 36),
    ]

class sync_in_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 22),
    ]

class sync_out_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 10),
    ]

class extio_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 12),
    ]

class brake_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 19),
    ]

class control_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 87),
    ]

class joystick_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 16),
    ]

class ctp_settings_t(Structure):
    _fields_ = [
         ("CTPMinError", c_uint8),
         ("CTPFlags", c_uint8),
         ("reserved", c_uint8 * 10),
    ]

class uart_settings_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 10),
    ]

class controller_name_t(Structure):
    _fields_ = [
         ("ControllerName", c_int8 * 16),
         ("CtrlFlags", c_uint8),
         ("reserved", c_uint8 * 7),
    ]

class nonvolatile_memory_t(Structure):
    _fields_ = [
         ("reserved", c_uint8 * 30),
    ]

class stage_name_t(Structure):
    _fields_ = [
         ("PositionerName", c_int8 * 16),
         ("reserved", c_uint8 * 8),
    ]

class stage_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 16),
         ("PartNumber", c_int8 * 24),
         ("reserved", c_uint8 * 24),
    ]

class stage_settings_t(Structure):
    _fields_ = [
         ("LeadScrewPitch", c_float),
         ("Units", c_int8 * 8),
         ("MaxSpeed", c_float),
         ("TravelRange", c_float),
         ("SupplyVoltageMin", c_float),
         ("SupplyVoltageMax", c_float),
         ("MaxCurrentConsumption", c_float),
         ("HorizontalLoadCapacity", c_float),
         ("VerticalLoadCapacity", c_float),
         ("reserved", c_uint8 * 24),
    ]

class motor_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 16),
         ("PartNumber", c_int8 * 24),
         ("reserved", c_uint8 * 24),
    ]

class motor_settings_t(Structure):
    _fields_ = [
         ("MotorType", c_uint8),
         ("ReservedField", c_uint8),
         ("Poles", c_uint16),
         ("Phases", c_uint16),
         ("NominalVoltage", c_float),
         ("NominalCurrent", c_float),
         ("NominalSpeed", c_float),
         ("NominalTorque", c_float),
         ("NominalPower", c_float),
         ("WindingResistance", c_float),
         ("WindingInductance", c_float),
         ("RotorInertia", c_float),
         ("StallTorque", c_float),
         ("DetentTorque", c_float),
         ("TorqueConstant", c_float),
         ("SpeedConstant", c_float),
         ("SpeedTorqueGradient", c_float),
         ("MechanicalTimeConstant", c_float),
         ("MaxSpeed", c_float),
         ("MaxCurrent", c_float),
         ("MaxCurrentTime", c_float),
         ("NoLoadCurrent", c_float),
         ("NoLoadSpeed", c_float),
         ("reserved", c_uint8 * 24),
    ]

class encoder_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 16),
         ("PartNumber", c_int8 * 24),
         ("reserved", c_uint8 * 24),
    ]

class encoder_settings_t(Structure):
    _fields_ = [
         ("MaxOperatingFrequency", c_float),
         ("SupplyVoltageMin", c_float),
         ("SupplyVoltageMax", c_float),
         ("MaxCurrentConsumption", c_float),
         ("PPR", c_uint32),
         ("EncoderSettings", c_uint32),
         ("reserved", c_uint8 * 24),
    ]

class hallsensor_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 16),
         ("PartNumber", c_int8 * 24),
         ("reserved", c_uint8 * 24),
    ]

class hallsensor_settings_t(Structure):
    _fields_ = [
         ("MaxOperatingFrequency", c_float),
         ("SupplyVoltageMin", c_float),
         ("SupplyVoltageMax", c_float),
         ("MaxCurrentConsumption", c_float),
         ("PPR", c_uint32),
         ("reserved", c_uint8 * 24),
    ]

class gear_information_t(Structure):
    _fields_ = [
         ("Manufacturer", c_int8 * 16),
         ("PartNumber", c_int8 * 24),
         ("reserved", c_uint8 * 24),
    ]

class gear_settings_t(Structure):
    _fields_ = [
         ("ReductionIn", c_float),
         ("ReductionOut", c_float),
         ("RatedInputTorque", c_float),
         ("RatedInputSpeed", c_float),
         ("MaxOutputBacklash", c_float),
         ("InputInertia", c_float),
         ("Efficiency", c_float),
         ("reserved", c_uint8 * 24),
    ]

class accessories_settings_t(Structure):
    _fields_ = [
         ("MagneticBrakeInfo", c_int8 * 24),
         ("MBRatedVoltage", c_float),
         ("MBRatedCurrent", c_float),
         ("MBTorque", c_float),
         ("MBSettings", c_uint32),
         ("TemperatureSensorInfo", c_int8 * 24),
         ("TSMin", c_float),
         ("TSMax", c_float),
         ("TSGrad", c_float),
         ("TSSettings", c_uint32),
         ("LimitSwitchesSettings", c_uint32),
         ("reserved", c_uint8 * 24),
    ]


# -------------------------
# END OF GENERATED code
# -------------------------