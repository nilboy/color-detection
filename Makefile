program_NAME := libcolordetection.so
CC := g++
program_OUT_DIR := .
program_OBJ_DIR := obj
program_SRC_DIR := src
program_NAME := $(program_OUT_DIR)/$(program_NAME)
program_CXX_SRCS := $(wildcard $(program_SRC_DIR)/*.cc)
program_CXX_OBJS := $(addprefix $(program_OBJ_DIR)/,$(notdir $(program_CXX_SRCS:.cc=.o)))
program_OBJS := $(program_CXX_OBJS)
program_INCLUDE_DIRS := ./include
program_LIBRARY_DIRS :=
program_LIBRARYS := opencv_core opencv_imgproc opencv_highgui opencv_ml \
opencv_video opencv_features2d opencv_calib3d opencv_legacy opencv_flann
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
CPPFLAGS += -std=c++11 -fPIC
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARYS),-l$(library))
.PHONY: all clean distclean directories
all: directories $(program_NAME)
directories:
	@-mkdir -p $(program_OUT_DIR)
	@-mkdir -p $(program_OBJ_DIR)
$(program_NAME): $(program_OBJS)
	$(CC) -shared $(program_OBJS) -o $(program_NAME) $(CPPFLAGS) $(LDFLAGS)
$(program_OBJ_DIR)/%.o: $(program_SRC_DIR)/%.cc
	$(CC) -o $@ -c $< $(CPPFLAGS) $(LDFLAGS)
clean:
	@-rm $(program_NAME)
	@-rm $(program_OBJS)
disclean: clean
install:
	@-cp $(program_NAME) python/color_detection
