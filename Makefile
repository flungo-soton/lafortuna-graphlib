
# Universal Makefile   Version: 31.01.2015
#
# Requires GNU 'make' and 'find'.

# Target Architecture
MCU   := at90usb1286
F_CPU := 8000000UL

# Tool Options
CFLAGS    := -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS    += -Wl,-u,vfprintf -lprintf_flt -lm  # floating point support
#CFLAGS    += -fno-strict-aliasing  # FATfs does not adhere to strict aliasing
CFLAGS    += -Wno-main             # main() will never return
CFLAGS    += -Wall -Wextra -pedantic
CFLAGS    += -Wstrict-overflow=5 -fstrict-overflow -Winline
# CHKFLAGS  := -fsyntax-only
CHKFLAGS  :=
BUILD_DIR := _build

# Ignoring hidden directories; sorting to drop duplicates:
CFILES := $(shell find . ! -path "*/\.*" -type f -name "*.c")
CPATHS := $(sort $(dir $(CFILES)))
vpath %.c $(CPATHS)
HFILES := $(shell find . ! -path "*/\.*" -type f -name "*.h")
HPATHS := $(sort $(dir $(HFILES)))
vpath %.h $(HPATHS)
CFLAGS += $(addprefix -I ,$(HPATHS))
DEPENDENCIES := $(patsubst %.c,$(BUILD_DIR)/%.d,$(notdir $(CFILES)))
OBJFILES     := $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(CFILES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	@avr-gcc $(CFLAGS) -MMD -MP -c $< -o $@

-include $(sort $(DEPENDENCIES))

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

clean:
	@$(RM) -rf $(BUILD_DIR)

all: $(OBJFILES)

# Copyright 2014-2015 Klaus-Peter Zauner
# At your option this work is licensed under a Creative Commons
# Attribution-NonCommercial 3.0 Unported License [1], or under a
# Creative Commons Attribution-ShareAlike 3.0 Unported License [2].
# [1]: See: http://creativecommons.org/licenses/by-nc/3.0/
# [2]: See: http://creativecommons.org/licenses/by-sa/3.0/
#===================================================================
