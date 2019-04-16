
KEMS =  kem_frodo640 \
        kem_kyber512 \
        kem_lac128 \
        kem_ledacrypt \
        kem_mceliece348864 \
        kem_newhope512cca \
        kem_ntru-hps2048509 \
        kem_ntru-prime-ntrulpr653 \
        kem_nts_12_64 \
        kem_saber_1 \
        kem_threebears_babybear 
#        kem_round5_r5n1_1kem_0d # Needs cshake dependency fixing
#        kem_bike \         # Depends on NTL, Bignum
#        kem_hqc128_1 \     # Depends on NTL
#        kem_rollo-i-128 \  # Depends on NTL
#        kem_rqc-128 \      # Depends on NTL, GMP
#        kem_sikep434 \     # Depends on GMP

# Built up by calls to tgt_kem_build
EXES = 

#
# Define a target to build the executable for a given scheme
#
define tgt_kem_build
.PHONY: build_${1}
EXES += build_${1} 
build_${1} :
	$(MAKE) -f Makefile.kem SCHEME=${1} exe
endef


#
# Define a target to run the executable for a given scheme
#
define tgt_kem_run
.PHONY: build_${1}
run_${1} : build_${1}
	$(MAKE) -f Makefile.kem SCHEME=${1} run
endef

$(foreach KEM,$(KEMS),$(eval $(call tgt_kem_build,$(KEM))))
$(foreach KEM,$(KEMS),$(eval $(call tgt_kem_run,$(KEM))))


#
# Run all executables
#
all: $(EXES)

clean-all:
	rm -rf build/*
