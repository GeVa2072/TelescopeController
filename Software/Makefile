ARDUINO_DIR=${HOME}/ardusim

CXX=g++
CXXFLAGS= -g 
CXXFLAGS+= -DF_CPU=8000000L -DARDUSIM -D__AVR_ATmega168P__
CXXFLAGS+= -x c++
INCLUDEDIRS= arduino/cores arduino/variants/standard include
INCLUDES= $(patsubst %,-I$(ARDUINO_DIR)/%,$(INCLUDEDIRS))
LD_LIBRARY_PATH="$LD_LIBRARY_PATH":${ARDUINO_DIR}
LDFLAGS=-lardusim
# -lardusim

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
endif


MAIN:
	echo @$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino
