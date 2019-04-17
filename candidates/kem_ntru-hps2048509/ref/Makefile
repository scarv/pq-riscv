
SRC = $(SCHEME_SRC)/crypto_sort.c \
      $(SCHEME_SRC)/fips202.c \
      $(SCHEME_SRC)/kem.c \
      $(SCHEME_SRC)/owcpa.c \
      $(SCHEME_SRC)/pack3.c \
      $(SCHEME_SRC)/packq.c \
      $(SCHEME_SRC)/poly.c \
      $(SCHEME_SRC)/sample.c \
      $(SCHEME_SRC)/verify.c \
      $(COMMON_SRC)/rng.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/keccakf1600.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

