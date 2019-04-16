
SRC = $(SCHEME_SRC)/Decode.c \
      $(SCHEME_SRC)/Encode.c \
      $(SCHEME_SRC)/int32.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/uint32.c \
      $(SCHEME_SRC)/uint32_sort.c \
      $(COMMON_SRC)/sha2.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)  

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
