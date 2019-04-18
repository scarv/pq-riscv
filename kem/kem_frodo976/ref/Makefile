
SRC = $(SCHEME_SRC)/frodo976.c \
      $(SCHEME_SRC)/util.c \
      $(COMMON_AES_SRC)   \
      $(COMMON_SRC)/fips202.c \
      $(COMMON_SHA3_SRC) \
      $(COMMON_SRC)/rng.c 
 
OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

CFLAGS += -D_SHAKE128_FOR_A_
CFLAGS += -D_REFERENCE_
