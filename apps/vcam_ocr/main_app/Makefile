#CROSS_COMPILE =aarch64-linux-gnu-
#CROSS_COMPILE =arm-hisiv500-linux-
#CROSS_COMPILE = mipsel-openwrt-linux-
CC = $(CROSS_COMPILE)gcc 
CPP = $(CROSS_COMPILE)g++ -std=c++11
CXX = $(CROSS_COMPILE)g++ -std=c++11
AR = $(CROSS_COMPILE)ar 
LINK=$(CROSS_COMPILE)g++

OPENCV = `pkg-config opencv --cflags --libs`
PUBLIC_LIB=../public/libPlatform.a
LIB_NCC=./libvcam.a

INCS =  -I../public/include/  -I./ncc_inc

COMMFLAG= $(OPENCV) -Wall -O2 -g

LDFLAGS =  -lrt -ldl  -lusb-1.0  -lpthread 
#-lwiringPi

# -lzlib
CFLAGS = -D_GNU_SOURCE 

PWD=$(shell pwd)
TARGET =  $(notdir $(PWD))

# change to you project file dir

# the obj dir
OBJDIR = obj
BINDIR = bin
###########################################################################

TEST_SOURCES = $(wildcard *.cpp)
TEST_OBIS = $(TEST_SOURCES:%.cpp=%.o)

# head files

CFLAGS += $(INCS) $(COMMFLAG)
CXXFLAGS += $(INCS) $(COMMFLAG)

all: $(TARGET)
test:$(TARGET)

$(TARGET): $(TEST_OBIS)  
	@echo "TEST_SOURCES: $(TEST_SOURCES)"
	@test -d $(BINDIR) | mkdir -p $(BINDIR)
	$(CXX) -o $@ $^ $(PUBLIC_LIB)  $(LIB_NCC) $(CXXFLAGS) $(LDFLAGS) 
	mv $@ $(BINDIR)/
	
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
	
clean:
	rm -rf $(OBJDIR) *.o
	rm -f  $(BINDIR)/$(TARGET)
 
	
