# Reduced Universal Makefile   Version: 01.05.2015-reduced
#
# Appears to work under Linux, OSX, and Cygwin/Windows.
# Under OSX it should be named "Makefile".
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

# The MIT License (MIT)
#
# Copyright (c) 2014-2015 Klaus-Peter Zauner
# Copyright (c) 2015 Fabrizio Lungo
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#===================================================================
