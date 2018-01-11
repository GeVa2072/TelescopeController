ARDUINO_DIR=${HOME}/ardusim
ARDUINO_IDE=${HOME}/arduino-ide

# Project name
EXEC=TelescopeControllerTest.exe

# Compiler
IDIR=$(ARDUINO_DIR)/include  $(ARDUINO_DIR)/arduino/cores $(ARDUINO_DIR)/arduino/variants/standard $(ARDUINO_IDE)/libraries/ArduinoUnit
IDIRFLAG=$(foreach idir, $(IDIR), -I$(idir))
CXXFLAGS=-DARDUSIM -DENABLE_API_NAME -D__AVR_ATmega328P__ -D_UINTPTR_T_DEFINED -D_INTPTR_T_DEFINED
CXXFLAGS+= -DF_CPU=16000000L 
CXXFLAGS+= -DARDUINO=101 -fno-exceptions -ffunction-sections
CXXFLAGS+= -fdata-sections -x c++ -Wl,--gc-sections $(IDIRFLAG)
CXXFLAGS+= -DUSE_EEPROM=0 -DUSE_ETHERNET=0 -DUSE_FIRMATA=0 -DUSE_LCD=0 -DUSE_LCD4884=0 -DUSE_OBD=0 -DUSE_SD=0
CXXFLAGS+= -DUSE_SERVO=0 -DUSE_SOFTSERIAL=0 -DUSE_SPI=0 -DUSE_STEPPER=0 -DUSE_TINYGPS=0 -DUSE_WIRE=0

#-std=c++0x -std=c++11 $(IDIRFLAG)
# Linker
LFLAGS=$(IDIRFLAG)
LIBS=
# Directories
SRCDIR=. $(ARDUINO_DIR)/arduino/cores $(ARDUINO_DIR)/arduino/variants/standard $(ARDUINO_DIR)/include
#INCDIR=include
OBJDIR=obj
BINDIR=bin
RELEASEDIR=Release
DEBUGDIR=Debug

# Files
SOURCES=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp))
OBJECTS=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SOURCES)))

# For rm
SOURCESTILDE=$(foreach sdir, $(SRCDIR), $(wildcard $(sdir)/*.cpp~))
INCLUDESTILDE=$(foreach idir, $(IDIR), $(wildcard $(idir)/*.hpp~))

vpath %.cpp $(SRCDIR)

# Reminder, 'cause it is easy to forget makefile's fucked-up syntax...
# $@ is what triggered the rule, ie the target before :
# $^ is the whole dependencies list, ie everything after :
# $< is the first item in the dependencies list

# Rules
gcc: clean
gcc: CXX=g++
gcc: LINKER=g++ -o
gcc: CXXFLAGS += -DNDEBUG
gcc: $(EXEC)

$(EXEC): $(OBJECTS)
	echo $(OBJECTS)
	@$(CXX) $(CXXFLAGS) TelescopeController.ino -o $(EXEC)

$(OBJDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: gcc gcc-debug clang clang-debug clean

clean:
	rm -fr core *~ $(OBJECTS) $(EXEC) $(SOURCESTILDE) $(INCLUDESTILDE)