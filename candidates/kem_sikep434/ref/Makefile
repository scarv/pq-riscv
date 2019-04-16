
SRC = $(SCHEME_SRC)/SIKEp434/api.c \
      $(SCHEME_SRC)/src/api_generic.c \
      $(SCHEME_SRC)/src/encoding.c \
      $(SCHEME_SRC)/src/fp.c \
      $(SCHEME_SRC)/src/fp2.c \
      $(SCHEME_SRC)/src/isogeny.c \
      $(SCHEME_SRC)/src/montgomery.c \
      $(SCHEME_SRC)/src/sidh.c \
      $(SCHEME_SRC)/src/sike.c \
      $(SCHEME_SRC)/src/sike_params.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_SRC)/aes.c \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SRC)/keccakf1600.c

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

CFLAGS += -I$(SCHEME_SRC)/include

$(BUILD)/%.o : $(SCHEME_SRC)/SIKEp434/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.o : $(SCHEME_SRC)/src/%.c
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
