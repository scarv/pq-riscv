
SRC = $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/melas_fec.c \
      $(SCHEME_SRC)/ring.c \
      $(SCHEME_SRC)/shake.c \
      $(SCHEME_SRC)/threebears.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
