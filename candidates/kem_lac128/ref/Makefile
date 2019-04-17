
SRC = $(SCHEME_SRC)/ake.c \
      $(SCHEME_SRC)/bch.c \
      $(SCHEME_SRC)/bin-lwe.c \
      $(SCHEME_SRC)/ecc.c \
      $(SCHEME_SRC)/encrypt.c \
      $(SCHEME_SRC)/ke.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/rand.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SHA_256_SRC)

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

