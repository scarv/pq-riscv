
SRC = $(SCHEME_SRC)/ffi_elt.c \
      $(SCHEME_SRC)/ffi_field.c \
      $(SCHEME_SRC)/ffi_vec.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/main_kat.c \
      $(SCHEME_SRC)/parsing.c \
      $(SCHEME_SRC)/rsr_algorithm.c \
      $(COMMON_SRC)/rng.c  \
      $(COMMON_AES_SRC)   

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
