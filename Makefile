
KEMS = $(subst /,,$(subst ./candidates/,,$(wildcard ./candidates/*/)))

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
