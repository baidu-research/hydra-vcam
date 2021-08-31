ARM_ABI = armv7hf
export ARM_ABI

#include ../Makefile.def

LITE_ROOT=../../../

THIRD_PARTY_DIR=${LITE_ROOT}/third_party

OPENCV_VERSION=opencv4.1.0
OPENCV = `pkg-config opencv --cflags --libs`

LDFLAGS = -latomic -pthread -ldl  -lz -lstdc++ -lm -lPlatform -L./ -L../../../../public

CXX_FLAGS = -mfpu=neon -fexceptions -frtti  -std=c++11 -fopenmp -O3 -DNDEBUG -fPIE $(OPENCV)
CXXFLAGS_LINK = $(CXX_FLAGS) -pie -Wl,--gc-sections -Wl,-z,nocopyreloc $(LDFLAGS)

OPENCV_INCLUDE = 
CXX_INCLUDES = $(INCLUDES) ${OPENCV_INCLUDE} -I$(LITE_ROOT)/cxx/include -Iinclude -I../../../../public/include

CXX_LIBS = -L$(LITE_ROOT)/cxx/lib/ -lpaddle_light_api_shared $(SYSTEM_LIBS)


###############################################################
# How to use one of static libaray:                           #
#  `libpaddle_api_full_bundled.a`                             #
#  `libpaddle_api_light_bundled.a`                            #
###############################################################
# Note: default use lite's shared library.                    #
###############################################################
# 1. Comment above line using `libpaddle_light_api_shared.so`
# 2. Undo comment below line using `libpaddle_api_light_bundled.a`

#CXX_LIBS = $(LITE_ROOT)/cxx/lib/libpaddle_api_light_bundled.a $(SYSTEM_LIBS)

ocr_db_crnn: fetch_opencv ocr_db_crnn.o crnn_process.o db_post_process.o clipper.o cls_process.o
	$(CC) $(SYSROOT_LINK) $(CXXFLAGS_LINK) ocr_db_crnn.o crnn_process.o db_post_process.o clipper.o cls_process.o -o ocr_db_crnn  $(CXX_LIBS) $(LDFLAGS)
	cp $@ debug
	
ocr_db_crnn.o: ocr_db_crnn.cc
	$(CC) $(SYSROOT_COMPLILE) $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o ocr_db_crnn.o -c ocr_db_crnn.cc

crnn_process.o: fetch_opencv crnn_process.cc
	$(CC) $(SYSROOT_COMPLILE) $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o crnn_process.o -c crnn_process.cc

cls_process.o: fetch_opencv cls_process.cc
	$(CC) $(SYSROOT_COMPLILE) $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o cls_process.o -c cls_process.cc

db_post_process.o: fetch_clipper fetch_opencv db_post_process.cc
	$(CC) $(SYSROOT_COMPLILE) $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o db_post_process.o -c db_post_process.cc

clipper.o: fetch_clipper
	$(CC) $(SYSROOT_COMPLILE) $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o clipper.o -c clipper.cpp

fetch_clipper:
	@test -e clipper.hpp || \
        ( echo "Fetch clipper " && \
        wget -c https://paddle-inference-dist.cdn.bcebos.com/PaddleLite/Clipper/clipper.hpp)
	@ test -e clipper.cpp || \
        wget -c https://paddle-inference-dist.cdn.bcebos.com/PaddleLite/Clipper/clipper.cpp

fetch_opencv:
#	@ test -d ${THIRD_PARTY_DIR} ||  mkdir ${THIRD_PARTY_DIR}
#	@ test -e ${THIRD_PARTY_DIR}/${OPENCV_VERSION}.tar.gz || \
#      (echo "fetch opencv libs" && \
#      wget -P ${THIRD_PARTY_DIR} https://paddle-inference-dist.bj.bcebos.com/${OPENCV_VERSION}.tar.gz)
#	@ test -d ${THIRD_PARTY_DIR}/${OPENCV_VERSION} || \
#      tar -zxvf ${THIRD_PARTY_DIR}/${OPENCV_VERSION}.tar.gz -C ${THIRD_PARTY_DIR}


.PHONY: clean
clean:
	rm -f ocr_db_crnn.o clipper.o db_post_process.o crnn_process.o cls_process.o
	rm -f ocr_db_crnn
