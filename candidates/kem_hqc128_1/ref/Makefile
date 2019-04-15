
SRC = $(SCHEME_SRC)/bch.c \
      $(SCHEME_SRC)/gf2x.c \
      $(SCHEME_SRC)/hqc.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/parsing.c \
      $(SCHEME_SRC)/repetition.c \
      $(SCHEME_SRC)/tensor.c \
      $(SCHEME_SRC)/vector.c \
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
