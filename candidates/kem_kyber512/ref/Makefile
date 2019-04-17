
SRC = $(SCHEME_SRC)/cbd.c \
      $(SCHEME_SRC)/fips202.c \
      $(SCHEME_SRC)/indcpa.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/ntt.c \
      $(SCHEME_SRC)/poly.c \
      $(SCHEME_SRC)/polyvec.c \
      $(SCHEME_SRC)/reduce.c \
      $(SCHEME_SRC)/verify.c \
      $(SCHEME_SRC)/symmetric-fips202.c \
      $(COMMON_SRC)/keccakf1600.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/rng.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

