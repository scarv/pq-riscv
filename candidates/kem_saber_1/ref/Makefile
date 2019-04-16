
SRC = $(SCHEME_SRC)/SABER_indcpa.c \
      $(SCHEME_SRC)/cbd.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/pack_unpack.c \
      $(SCHEME_SRC)/poly.c \
      $(SCHEME_SRC)/poly_mul.c \
      $(SCHEME_SRC)/verify.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_SRC)/aes.c \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SRC)/keccakf1600.c

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
