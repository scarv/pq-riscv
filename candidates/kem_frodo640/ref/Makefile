
SRC = $(SCHEME_SRC)/frodo640.c \
      $(SCHEME_SRC)/util.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/sha2.c \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SRC)/keccakf1600.c \
      $(COMMON_SRC)/rng.c 
 
OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

CFLAGS += -D_SHAKE128_FOR_A_
CFLAGS += -D_REFERENCE_

$(BUILD)/%.o : $(SCHEME_SRC)/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
