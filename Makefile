
PQRV      = $(PWD)

ISA_XLEN  = 64
ISA_BASE  = rv$(ISA_XLEN)i
ISA_EXT   = mafd
ISA_STR   = $(ISA_BASE)$(ISA_EXT)

CC        = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-gcc
CXX       = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-g++
AS        = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-as 
LD        = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-ld 
AR        = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-ar 
OBJDUMP   = $(RISCV)/bin/riscv$(ISA_XLEN)-unknown-elf-objdump

CFLAGS    = -O3 -march=$(ISA_STR) -I$(PQRV)/common
CXXFLAGS  = -O3 -march=$(ISA_STR) -I$(PQRV)/common

SCHEME   ?= kem_bike
VARIANT  ?= ref

BUILD     = $(PQRV)/build/$(SCHEME)/$(VARIANT)
SCHEME_SRC= $(PQRV)/candidates/$(SCHEME)/$(VARIANT)

include $(PQRV)/candidates/$(SCHEME)/$(VARIANT)/Makefile

lib: $(BUILD)/lib$(SCHEME).a 

clean:
	rm -rf $(BUILD)/*

