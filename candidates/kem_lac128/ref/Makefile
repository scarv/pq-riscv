
SRC = $(SCHEME_SRC)/ake.c \
      $(SCHEME_SRC)/bch.c \
      $(SCHEME_SRC)/bin-lwe.c \
      $(SCHEME_SRC)/ecc.c \
      $(SCHEME_SRC)/encrypt.c \
      $(SCHEME_SRC)/ke.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/rand.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_SRC)/aes.c \
      $(COMMON_SRC)/sha2.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
