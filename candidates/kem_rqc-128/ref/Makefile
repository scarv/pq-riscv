
SRC = $(SCHEME_SRC)/gabidulin.cpp \
      $(SCHEME_SRC)/kem.cpp \
      $(SCHEME_SRC)/parsing.cpp \
      $(SCHEME_SRC)/q_polynomial.cpp \
      $(SCHEME_SRC)/rqc.cpp \
      $(SCHEME_SRC)/ffi/ffi_elt.cpp \
      $(SCHEME_SRC)/ffi/ffi_field.cpp \
      $(SCHEME_SRC)/ffi/ffi_vec.cpp \
      $(COMMON_SRC)/rng.c \
      $(COMMON_SRC)/aes.c 

OBJ = $(addprefix $(BUILD)/,$(addsuffix .o,$(notdir $(basename $(SRC)))))

CXXFLAGS += -I$(SCHEME_SRC)/ffi

$(BUILD)/%.o : $(SCHEME_SRC)/ffi/%.cpp
	mkdir -p $(BUILD)/ffi
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/%.o : $(SCHEME_SRC)/%.cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(info $(BUILD))

$(LIBNAME) : $(OBJ)
	$(AR) rcs $@ $^
