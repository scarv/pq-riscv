
SRC = $(SCHEME_SRC)/additive_fft.c \
      $(SCHEME_SRC)/berlekamp_massey.c \
      $(SCHEME_SRC)/ff.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/m4r.c \
      $(SCHEME_SRC)/matrix_ff2.c \
      $(SCHEME_SRC)/nts_kem.c \
      $(SCHEME_SRC)/polynomial.c \
      $(SCHEME_SRC)/random.c \
      $(SCHEME_SRC)/stack.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SRC)/keccakf1600.c

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
