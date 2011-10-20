proj = main
CXX = g++

CCFLAGS = -Wall `pkg-config --cflags opencv` `pkg-config --libs opencv`

all: ${proj} 

${proj}: ${proj}.o color/ColorMatch.o color/ColorHistogram.o feature/DescriptorMatch.o feature/Keypoints.o feature/Descriptors.o training/BagOfWords.o
 
	${CXX} ${CCFLAGS} -o ${proj}  ${proj}.o color/ColorMatch.o color/ColorHistogram.o feature/DescriptorMatch.o feature/Keypoints.o feature/Descriptors.o training/BagOfWords.o

${proj}.o: ${proj}.cpp 
	${CXX} ${CCFLAGS} -c ${proj}.cpp

$ColorMatch.o: color/ColorMatch.cpp
	${CXX} ${CCFLAGS} -c color/ColorMatch.cpp

$ColorHistogram.o: color/ColorHistogram.cpp
	${CXX} ${CCFLAGS} -c color/ColorHistogram.cpp

$DescriptorMatch.o: feature/DescriptorMatch.cpp
	${CXX} ${CCFLAGS} -c feature/DescriptorMatch.cpp

$Keypoints.o: feature/Keypoints.cpp
	${CXX} ${CCFLAGS} -c feature/Keypoints.cpp

$Descriptors.o: feature/Descriptors.cpp
	${CXX} ${CCFLAGS} -c feature/Descriptors.cpp

$BagOfWords.o: training/BagOfWords.cpp
	${CXX} ${CCFLAGS} -c training/BagOfWOrds.cpp

clean:
	-rm *.o color/*.o feature/*.o ${proj} 
