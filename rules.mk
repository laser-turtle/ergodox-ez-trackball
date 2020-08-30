# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
LINK_TIME_OPTIMIZATION_ENABLE = yes
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
ORYX_ENABLE = yes
SRC = matrix.c
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = yes
POINTING_DEVICE_ENABLE = yes

OPT_DEFS += -DPIMORONI_TRACKBALL_ENABLE
SRC += pimoroni_trackball.c
QUANTUM_LIB_SRC += i2c_master.c

CONSOLE_ENABLE = yes
