
# BIKE reference and optimized implementations assume that OpenSSL and NTL libraries are available in the platform.

# To compile this code for NIST KAT routine use: make bike-nist-kat
# To compile this code for demo tests use: make bike-demo-test

# TO EDIT PARAMETERS AND SELECT THE BIKE VARIANT: please edit defs.h file in the indicated sections.

# The file measurements.h controls how the cycles are counted. Note that #define REPEAT is initially set to 100, 
# which means that every keygen, encaps and decaps is repeated 100 times and the number of cycles is averaged.

# Verbose levels: 0, 1, 2 or 3
VERBOSE=0

SRC:=*.c ntl.cpp FromNIST/rng.c
OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename SRC)))

INCLUDE:=-I. -I$(OpenSSL)/include -L$(OpenSSL)/lib -lcrypto -lssl -lm -ldl -lpthread -lntl -lgmp

all: bike-nist-kat

bike-demo-test: $(SRC) *.h tests/test.c
	$(CC) $(CFLAGS) tests/test.c $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

bike-nist-kat: $(SRC) *.h FromNIST/*.h FromNIST/PQCgenKAT_kem.c
	$(CC) $(CFLAGS) FromNIST/PQCgenKAT_kem.c $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

lib:
	$(CC) $(CFLAGS) $(SRC) -c -o $(BUILD)/bike.o

clean:
	rm -f PQCkemKAT_*
	rm -f bike*

