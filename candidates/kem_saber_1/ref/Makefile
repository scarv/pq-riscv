
SRC = $(SCHEME_SRC)/SABER_indcpa.c \
      $(SCHEME_SRC)/cbd.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/pack_unpack.c \
      $(SCHEME_SRC)/poly.c \
      $(SCHEME_SRC)/poly_mul.c \
      $(SCHEME_SRC)/verify.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SHA3_SRC)

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

