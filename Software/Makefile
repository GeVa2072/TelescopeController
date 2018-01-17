ARDUINO_DIR=${HOME}/ardusim

AR=ar
ARFLAGS=rcs
CXX=g++
CXXFLAGS= -g 
CXXFLAGS+= -DF_CPU=8000000L -DARDUSIM -D__AVR_ATmega168P__
CXXFLAGS+= -x c++
INCLUDEDIRS= arduino/cores arduino/variants/standard include
INCLUDES= $(patsubst %,-I$(ARDUINO_DIR)/%,$(INCLUDEDIRS))
OBJS= $(ARDUINO_DIR)/*.o
LDFLAGS=-lardusim -larduinounit
# -lardusim

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
endif

all: setup fetch check

setup:
	mkdir -p $(ARDUINO_DIR)/ArduinoUnit/

fetch: setup fetch-ardusim fetch-arduinounit

fetch-arduinounit:
	@wget https://github.com/mmurdoch/arduinounit/archive/v2.2.0.tar.gz
	@tar xf v2.2.0.tar.gz
	@cp -r arduinounit-2.2.0/src/* $(ARDUINO_DIR)/ArduinoUnit/
	
fetch-ardusim:
	@wget https://github.com/GeVa2072/ArduSim/archive/master.zip
	@unzip master.zip
	@cp -r ArduSim-master/* $(ARDUINO_DIR)

check: ardusim arduinounit MAIN

ardusim:
	@$(MAKE) -C $(ARDUINO_DIR)
	ls -al $(ARDUINO_DIR)
	cp $(ARDUINO_DIR)/ardusim.a $(ARDUINO_DIR)/libardusim.a
	objdump -D  $(ARDUINO_DIR)/libardusim.a

arduinounit:
	@cd $(ARDUINO_DIR)/ArduinoUnit/ && \
	$(CXX) -c $(CXXFLAGS) -fpermissive $(LDFLAGS) $(INCLUDES) -I$(ARDUINO_DIR)/ArduinoUnit/ ArduinoUnitUtility/*.cpp
	@$(AR) $(ARFLAGS) arduinounit.a $(ARDUINO_DIR)/ArduinoUnit/*.o
	ls -al $(ARDUINO_DIR)/ArduinoUnit/
	cp arduinounit.a libarduinounit.a
	objdump -D  libarduinounit.a

MAIN: MAIN.o
	$(CXX) -o main -L $(ARDUINO_DIR)/libardusim.a -L libarduinounit.a *.o
	
MAIN.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -I. -I$(ARDUINO_DIR)/ArduinoUnit/ TelescopeController.ino 
	objdump -D  TelescopeController.o

