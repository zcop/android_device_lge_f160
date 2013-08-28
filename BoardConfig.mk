#
# Copyright (C) 2012 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# This variable is set first, so it can be overridden
# by BoardConfigVendor.mk

# Include path
TARGET_SPECIFIC_HEADER_PATH := device/lge/f160/include

include device/lge/qcom-common/BoardCommonConfig.mk
include device/lge/msm8960-common/BoardCommonConfig.mk

LOCAL_PATH := device/lge/f160

TARGET_ARCH := arm

# Bluetooth
TARGET_CUSTOM_BLUEDROID := $(LOCAL_PATH)/bluetooth/bluetooth.c

#Kernel source
TARGET_KERNEL_SOURCE := kernel/lge/d1lsk
TARGET_KERNEL_CONFIG := cyanogenmod_d1lsk_defconfig

# Kernel
BOARD_KERNEL_BASE := 0x80200000
BOARD_KERNEL_PAGE_SIZE := 2048
BOARD_KERNEL_CMDLINE := console=ttyHSL0,115200,n8 androidboot.hardware=d1lsk lpj=676678
BOARD_MKBOOTIMG_ARGS := --ramdisk_offset 0x81500000

# Filesystem
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_BOOTIMAGE_PARTITION_SIZE := 16777216
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 16776704
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1744829440
BOARD_USERDATAIMAGE_PARTITION_SIZE := 2550136320
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_VOLD_MAX_PARTITIONS := 97

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME := F160
