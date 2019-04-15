
# BIKE reference and optimized implementations assume that OpenSSL and NTL libraries are available in the platform.

# To compile this code for NIST KAT routine use: make bike-nist-kat
# To compile this code for demo tests use: make bike-demo-test

# TO EDIT PARAMETERS AND SELECT THE BIKE VARIANT: please edit defs.h file in the indicated sections.

# The file measurements.h controls how the cycles are counted. Note that #define REPEAT is initially set to 100, 
# which means that every keygen, encaps and decaps is repeated 100 times and the number of cycles is averaged.

# Verbose levels: 0, 1, 2 or 3

SRC = $(SCHEME_SRC)/conversions.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/parallel_hash.c \
      $(SCHEME_SRC)/ring_buffer.c \
      $(SCHEME_SRC)/sampling.c \
      $(SCHEME_SRC)/threshold.c \
      $(SCHEME_SRC)/aes_ctr_prf.c \
      $(SCHEME_SRC)/decode.c \
      $(SCHEME_SRC)/utilities.c \
      $(SCHEME_SRC)/ntl.c \
      $(COMMON_SRC)/aes.c \
      $(COMMON_SRC)/sha2.c \
      $(COMMON_SRC)/rng.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
