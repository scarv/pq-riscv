
SRC = $(SCHEME_SRC)/benes.c \
      $(SCHEME_SRC)/bm.c \
      $(SCHEME_SRC)/controlbits.c \
      $(SCHEME_SRC)/decrypt.c \
      $(SCHEME_SRC)/encrypt.c \
      $(SCHEME_SRC)/gf.c \
      $(SCHEME_SRC)/operations.c \
      $(SCHEME_SRC)/pk_gen.c \
      $(SCHEME_SRC)/root.c \
      $(SCHEME_SRC)/sk_gen.c \
      $(SCHEME_SRC)/synd.c \
      $(SCHEME_SRC)/transpose.c \
      $(SCHEME_SRC)/util.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SHA3_SRC) \
      $(COMMON_AES_SRC)

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

