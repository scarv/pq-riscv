
PQRV      = $(PWD)

ISA_XLEN  = 32
ISA_BASE  = rv$(ISA_XLEN)i
ISA_EXT   = mc
ISA_STR   = $(ISA_BASE)$(ISA_EXT)

GNU_STRING= riscv$(ISA_XLEN)-unknown-elf

CC        = $(RISCV)/bin/$(GNU_STRING)-gcc
CXX       = $(RISCV)/bin/$(GNU_STRING)-g++
AS        = $(RISCV)/bin/$(GNU_STRING)-as 
LD        = $(RISCV)/bin/$(GNU_STRING)-ld 
AR        = $(RISCV)/bin/$(GNU_STRING)-ar 
OBJDUMP   = $(RISCV)/bin/$(GNU_STRING)-objdump

CFLAGS    = -O2 -march=$(ISA_STR) -I$(PQRV) -g -DRV_ISA=$(ISA_STR)
CXXFLAGS  = -O2 -march=$(ISA_STR) -I$(PQRV) -g -DRV_ISA=$(ISA_STR)

SCHEME   ?= kem_saber_1
VARIANT  ?= ref

BUILD     = $(PQRV)/build/$(SCHEME)/$(VARIANT)
SCHEME_SRC= $(PQRV)/candidates/$(SCHEME)/$(VARIANT)
COMMON_SRC= $(PQRV)/common

LIBNAME   = $(BUILD)/lib$(SCHEME).a
EXENAME   = $(BUILD)/$(SCHEME).exe
HARNESS   = $(PQRV)/harness/main.c

include $(PQRV)/candidates/$(SCHEME)/$(VARIANT)/Makefile

exe: $(EXENAME)
lib: $(LIBNAME)

$(BUILD)/%.o : $(COMMON_SRC)/%.c
	mkdir -p $(dir $(BUILD))
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXENAME) : $(HARNESS) $(LIBNAME)
	$(CC) $(CFLAGS) -I$(SCHEME_SRC) -o $@ $< $(LIBNAME) -lm
	$(OBJDUMP) -D $@ > $@.dis

run: $(EXENAME)
	$(RISCV)/bin/spike \
        $(RISCV)/$(GNU_STRING)/bin/pk $(EXENAME)

clean:
	rm -rf $(BUILD)/*

