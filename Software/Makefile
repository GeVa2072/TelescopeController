ARDUINO_DIR=${HOME}/ardusim

CXX=g++
CXXFLAGS= -g 
CXXFLAGS+= -DF_CPU=8000000L -DARDUSIM -D__AVR_ATmega168P__
CXXFLAGS+= -x c++
INCLUDEDIRS= arduino/cores arduino/variants/standard include
INCLUDES= $(patsubst %,-I$(ARDUINO_DIR)/%,$(INCLUDEDIRS))
OBJS= $(ARDUINO_DIR)/*.o
LDFLAGS=-L /home/travis/ardusim/main.o 
# -lardusim

ifeq ($(OS),Windows_NT)
    CCFLAGS += -D WIN32
endif

all: setup fetch check

setup:
	mkdir -p $(ARDUINO_DIR)/ArduinoUnit/

fetch: setup fetch-ardusim fetch-arduinounit

fetch-arduinounit:
	cd /tmp/
	 wget https://github.com/mmurdoch/arduinounit/archive/v2.2.0.tar.gz
	 tar xf v2.2.0.tar.gz
	 cp -r arduinounit-2.2.0/src/* $(ARDUINO_DIR)/ArduinoUnit/
	 ls -al $(ARDUINO_DIR)/ArduinoUnit/

fetch-ardusim:
	cd /tmp/
	wget https://github.com/GeVa2072/ArduSim/archive/master.zip
	unzip master.zip
	cp -r ArduSim-master/* $(ARDUINO_DIR)
	

check: ardusim arduinounit MAIN

ardusim:
	$(MAKE) -C $(ARDUINO_DIR)

arduinounit:
	cd $(ARDUINO_DIR)/ArduinoUnit/ && \
	@$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) ArduinoUnitUtility/*.cpp -o ArduinoUnit.o

MAIN: MAIN.o
	echo @$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino
	@$(CXX) -o main /home/travis/ardusim/*.o *.o
	
MAIN.o:
	echo @$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. TelescopeController.ino
	@$(CXX) -c $(CXXFLAGS) $(LDFLAGS) $(INCLUDES) -I. -I$HOME/arduino_ide/libraries/ArduinoUnit/ TelescopeController.ino 

