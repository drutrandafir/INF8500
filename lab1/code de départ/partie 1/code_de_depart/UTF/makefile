### Variables ###
PROJETINC	=	'/usr/local/systemc/include'
PROJETLIB	=	'/usr/local/systemc/lib-linux64'

AS	    =	as
CC	    =	g++
CXX	    =	g++
LD	    =	g++

CFLAGS	    =	-g -O0 -Wall $(INCDIR)
CXXFLAGS	=	-g -O0 -Wall $(INCDIR) --std=c++17
LDFLAGS	    =	$(LIBDIR) -std=c++17

### Includes ###
INCDIR	=	-I $(PROJETINC) -I .

### Libs ###
LIBDIR	=	-L $(PROJETLIB)
	
### Sources ###
SOURCES = 	main.cpp \
			Reader.cpp \
			Bubble.cpp \
			DataRAM.cpp \
			RAM.cpp 
	
CSOURCES = assert.c

SSOURCES =

### Objects ###
OBJECTSCPP = $(patsubst %.cpp, $(CFG).%.o, $(SOURCES))
OBJECTSC   = $(patsubst %.c, $(CFG).%.o, $(CSOURCES))
OBJECTSS   = $(patsubst %.s, $(CFG).%.o, $(SSOURCES))

### Librairies ###
LIBS	=	-Wl,--start-group \
			-lsystemc \
			-lm\
			-Wl,--end-group

### Target ###
TARGET	= executable

VPATH = './include'

####### Implicit rules
.SUFFIXES: .cpp .c .s

$(CFG).%.o: %.cpp
		@echo ""
		@echo "Compiling ==>" $<
		$(CXX) -c $< -o $@ $(CXXFLAGS)

$(CFG).%.o: %.c
		@echo ""
		@echo "Compiling ==>" $<
		$(CC) -c $< -o $@ $(CFLAGS)

$(CFG).%.o: %.s
		@echo ""
		@echo "Compiling ==>" $<
		$(AS) $< -o $@ $(ASFLAGS)

####### lib rules
all: $(TARGET)

$(TARGET):	$(OBJECTSCPP) $(OBJECTSC) $(OBJECTSS)
		@echo ""
		@echo "-- Linking files and creating binary target --" $(TARGET)
		-rm -f $(TARGET)
		$(LD) $(LDFLAGS)  $(OBJECTSCPP) $(OBJECTSC) $(OBJECTSS) $(LIBDIR) $(LIBS) -o $(TARGET)
		@echo DONE!

clean:
		@echo ""
		@echo "-- Cleaning files --" $(TARGET)
		-rm -f $(OBJECTSCPP) $(OBJECTSC) $(OBJECTSS) $(TARGET)
		-rm -f *~ core
		@echo DONE!

compile_all:	$(OBJECTSCPP) $(OBJECTSC) $(OBJECTSS)
		@echo ""
		@echo DONE!
		
rebuild: clean all

relink:
		@echo ""
		@echo "-- Creating binary target --" $(TARGET)
		-rm -f *~ core
		$(LD) $(LDFLAGS) $(OBJECTSCPP) $(OBJECTSC) $(OBJECTSS) $(LIBDIR) $(LIBS) -o $(TARGET)
		@echo DONE!
		
run:
	LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(PROJETLIB) ./executable

