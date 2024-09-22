# Compiler and Linker settings
CXX = g++
CXXFLAGS = -std=c++20 -O3 -DMAKELINUX -fPIC -Wno-deprecated-enum-enum-conversion
# CXXFLAGS += -Wall -Wextra
LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_photo -lopencv_reg -lopencv_ximgproc -lopencv_xobjdetect -lopencv_shape -lopencv_img_hash -lopencv_highgui -lopencv_features2d -lopencv_face -lopencv_objdetect -lopencv_videoio

# Include directories
INCLUDES = -I/usr/include/opencv4

# Source files
SRCS = \
	BitExactImgFinder.cpp \
	FaceDetection/FaceDetector.cpp \
	FaceDetection/FacesCropped.cpp \
	Parser.cpp \
	_Main.cpp \
	ImgFileScanner.cpp \
	ImgMatchFinderBase.cpp \
	ImgSearch.cpp \
	OrbMatcher.cpp \
	SimilarImgFinder.cpp \
	SurfMatcher.cpp

# Object files (in the build folder)
BUILD_DIR = build
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Target executable
TARGET = $(BUILD_DIR)/ImgOrganizer

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files in the build directory
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

