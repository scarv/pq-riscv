
SRC = $(SCHEME_SRC)/cpapke.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/ntt.c \
      $(SCHEME_SRC)/poly.c \
      $(SCHEME_SRC)/precomp.c \
      $(SCHEME_SRC)/reduce.c \
      $(SCHEME_SRC)/verify.c \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/keccakf1600.c \
      $(COMMON_SRC)/rng.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

