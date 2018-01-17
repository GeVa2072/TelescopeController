ARDUINO_DIR=${HOME}/ardusim

AR=ar
ARFLAGS=rcs
CXX=g++
CXXFLAGS= -g 
CXXFLAGS+= -DF_CPU=8000000L -DARDUSIM -D__AVR_ATmega168P__
CXXFLAGS+= -x c++
INCLUDEDIRS= arduino/cores arduino/variants/standard include ArduinoUnit/
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
	@wget https://github.com/GeVa2072/arduinounit/archive/master.zip
	@unzip master.zip
	@cp -r arduinounit-master/src/* $(ARDUINO_DIR)/ArduinoUnit/
	@rm master.zip
	@rm -rf arduinounit-master
	
fetch-ardusim:
	@wget https://github.com/GeVa2072/ArduSim/archive/master.zip
	@unzip master.zip
	@cp -r ArduSim-master/* $(ARDUINO_DIR)
	@rm master.zip
	@rm -rf ArduSim-master

check: ardusim arduinounit MAIN

ardusim:
	@$(MAKE) -C $(ARDUINO_DIR)
	ls -al $(ARDUINO_DIR)
	cp $(ARDUINO_DIR)/ardusim.a $(ARDUINO_DIR)/libardusim.a
	nm -g -C $(ARDUINO_DIR)/libardusim.a

arduinounit:
	@cd $(ARDUINO_DIR)/ArduinoUnit/ && \
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -fpermissive ArduinoUnitUtility/*.cpp
	@$(AR) $(ARFLAGS) arduinounit.a $(ARDUINO_DIR)/ArduinoUnit/*.o
	ls -al $(ARDUINO_DIR)/ArduinoUnit/
	cp arduinounit.a libarduinounit.a
	nm -g -C libarduinounit.a

MAIN: MAIN.o
	$(CXX) -o main $(ARDUINO_DIR)/*.o $(ARDUINO_DIR)/ArduinoUnit/*.o *.o
	
MAIN.o:
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) -I. TelescopeController.ino 
	nm -g -C TelescopeController.o

