ARDUINO_DIR=${HOME}/ardusim

CXX=g++
CXXFLAGS= -g 
CXXFLAGS+= -DF_CPU=8000000L -DARDUSIM -D__AVR_ATmega168P__
CXXFLAGS+= -x c++
INCLUDEDIRS= arduino/cores arduino/variants/standard include
INCLUDES= $(patsubst %,-I$(ARDUINO_DIR)/%,$(INCLUDEDIRS))
LDFLAGS= $(ARDUINO_DIR)/*.o
# -lardusim

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
endif


MAIN:
	echo @$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino -lardusim
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino -lardusim
