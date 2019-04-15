
SRC = $(SCHEME_SRC)/library/H_Q_matrices_generation.c \
      $(SCHEME_SRC)/library/aes256.c \
      $(SCHEME_SRC)/library/bf_decoding.c \
      $(SCHEME_SRC)/library/gf2x_arith.c \
      $(SCHEME_SRC)/library/gf2x_arith_mod_xPplusOne.c \
      $(SCHEME_SRC)/library/kem.c \
      $(SCHEME_SRC)/library/niederreiter_decrypt.c \
      $(SCHEME_SRC)/library/niederreiter_encrypt.c \
      $(SCHEME_SRC)/library/niederreiter_keygen.c \
      $(SCHEME_SRC)/rng.c \
      $(COMMON_SRC)/aes.c

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

LEDACRYPT_SL ?= 5
LEDACRYPT_N0 ?= 2

CFLAGS += -I$(SCHEME_SRC)/include \
           -DCATEGORY=$(LEDACRYPT_SL) -DN0=$(LEDACRYPT_N0) \
           -DCPU_WORD_BITS=$(ISA_XLEN)

$(BUILD)/%.o : $(SCHEME_SRC)/library/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
