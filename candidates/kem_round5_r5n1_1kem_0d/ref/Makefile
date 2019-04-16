
SRC = $(SCHEME_SRC)/a_fixed.c \
      $(SCHEME_SRC)/a_random.c \
      $(SCHEME_SRC)/cca_encrypt.c \
      $(SCHEME_SRC)/cpa_kem.c \
      $(SCHEME_SRC)/drbg.c \
      $(SCHEME_SRC)/little_endian.c \
      $(SCHEME_SRC)/misc.c \
      $(SCHEME_SRC)/pack.c \
      $(SCHEME_SRC)/parameters.c \
      $(SCHEME_SRC)/r5_cca_kem.c \
      $(SCHEME_SRC)/r5_cca_pke.c \
      $(SCHEME_SRC)/r5_core.c \
      $(SCHEME_SRC)/r5_cpa_kem.c \
      $(SCHEME_SRC)/r5_cpa_pke.c \
      $(SCHEME_SRC)/r5_dem.c \
      $(SCHEME_SRC)/r5_hash.c \
      $(SCHEME_SRC)/r5_memory.c \
      $(SCHEME_SRC)/r5_parameter_sets.c \
      $(SCHEME_SRC)/xef_ref.c \
      $(COMMON_SRC)/aes.c \
      $(COMMON_SRC)/rng.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
