CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = ./Aux
CommonTools = ./CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore -L$(INC)/include -lCustomPdfs

CPPFLAGS += -g -std=c++17

#TARGET = MakeFit
#TARGET1 = MakeFitRun2
TARGET2 = ./bin/PlotAllBiasTest
TARGET4 = ./bin/CreateDataCardCommands
TARGET5 = ./bin/testCustomPdf
TARGET6 = ./bin/MakeFitRun3

#SRC = app/testapp.cc src/makeInvertedANFit_v2.cc $(Aux)/src/CommandLineInput.cc
   #SRC = app/testapp.cc $(Aux)/src/CommandLineInput.cc
#SRC1 = app/MakeFitRun2.cc src/RunTwoFitMgg.cc src/DefinePdfs.cc src/PrintAIC.cc $(Aux)/src/CommandLineInput.cc
SRC2 = app/PlotAllBiasTest.cc src/PlotBias.cc $(Aux)/src/CommandLineInput.cc $(CommonTools)/src/HggAux.cc
SRC4 = app/CreateDataCardCommands.cc $(Aux)/src/CommandLineInput.cc
SRC5 = app/testCustomPdf.cc
SRC6 = app/MakeFitRun3.cc src/RunTwoFitMgg.cc src/DefinePdfs.cc src/PrintAIC.cc src/makeInvertedANFit_v2.cc $(Aux)/src/CommandLineInput.cc

#OBJ = $(SRC:.cc=.o)
#OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ4 = $(SRC4:.cc=.o)
OBJ5 = $(SRC5:.cc=.o)
OBJ6 = $(SRC6:.cc=.o)

all : $(TARGET2) $(TARGET4) $(TARGET5) $(TARGET6)
#all : $(TARGET1) $(TARGET2) $(TARGET4) $(TARGET5)

#$(TARGET) : $(OBJ)
#	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
#	@echo $@
#	@echo $<
#	@echo $^


#$(TARGET1) : $(OBJ1)
#	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)
#	@echo $@
#	@echo $<
#	@echo $^

$(TARGET2) : $(OBJ2)
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^


$(TARGET4) : $(OBJ4)
	$(LD) $(CPPFLAGS) -o $(TARGET4) $(OBJ4) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET5) : $(OBJ5)
	$(LD) $(CPPFLAGS) -o $(TARGET5) $(OBJ5) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET6) : $(OBJ6)
	$(LD) $(CPPFLAGS) -o $(TARGET6) $(OBJ6) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<


clean :
	rm -f *.o app/*.o src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET2) $(TARGET4) $(TARGET5) $(TARGET6) *~
