.SUFFIXES : .o .exe
# These are the folders where #include <header> will look for the header files
INCLUDES = -I"C:\Program Files\opencv\build\include" -I"c:\Program Files\opencv\build\include\opencv" -I"c:\Program Files\opencv\build\include\opencv2"

# The include folders have to added when compiling the C++ source codes,
 # thus the flag "$(INCLUDES)"
CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 $(INCLUDES)

# Link all OpenCV libraries during compilation
LIBS = -lopencv_core310.dll -lopencv_imgproc310.dll -lopencv_highgui310.dll \
-lopencv_ml310.dll -lopencv_video310.dll -lopencv_videoio310.dll -lopencv_features2d310.dll \
-lopencv_calib3d310.dll -lopencv_objdetect310.dll -lopencv_flann310.dll \
-lopencv_imgcodecs310.dll

LIBPATH =  -L"c:\Program Files\opencv\build\x64\mingw_1\lib"

# TARGET = object_demo1.exe
# TARGET = key_demo1.exe
TARGET = graph_demo1.exe
.o.exe:
	$(CXX) -o $@ $< $(LIBPATH) $(LIBS)

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)
