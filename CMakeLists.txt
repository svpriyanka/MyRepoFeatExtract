cmake_minimum_required(VERSION 2.8)
project( featureExtractor )

#The version number
set (featureExtractor_version_MAJOR 1)
set (featureExtractor_version_MINOR 0)


find_package( OpenCV REQUIRED )



include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")
#add lib


set(CMAKE_CXX_FLAGS "-std=c++0x")

set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
#set (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/)



set (PROJECT_LIB ${PROJECT_SOURCE_DIR}/lib)#lib

set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/MainScript.cpp
${PROJECT_SOURCE_DIR}/GaborFilter.cpp
${PROJECT_SOURCE_DIR}/FeatureExtractor.cpp
${PROJECT_SOURCE_DIR}/SQI.cpp
${PROJECT_SOURCE_DIR}/GaborPhasePatterns.cpp
${PROJECT_SOURCE_DIR}/HGPP.cpp
)

#add_library(MyLibFeatExtractor ${PROJECT_SRC}/FeatureExtractor.cpp ${PROJECT_LIB}/headers.h ${PROJECT_LIB}/FeatureExtractor.h ${PROJECT_SRC}/HGPP.cpp ${PROJECT_SRC}/GaborPhasePatterns.cpp  ${PROJECT_LIB}/GaborPhasePatterns.h)

#add_library(MyLibSQI ${PROJECT_SRC}/SQI.cpp ${PROJECT_LIB}/headers.h ${PROJECT_LIB}/SQI.h)

#add_library(MyLibGPP ${PROJECT_SRC}/GaborPhasePatterns.cpp ${PROJECT_SRC}/HGPP.cpp ${PROJECT_LIB}/headers.h ${PROJECT_LIB}/GaborPhasePatterns.h)

#add_library(MyLibGaborFilter ${PROJECT_SRC}/GaborFilter.cpp ${PROJECT_LIB}/headers.h ${PROJECT_LIB}/GaborFilter.h)


#Add executable
#add_executable( HGPP MainScript.cpp )
#target_link_libraries( HGPP ${OpenCV_LIBS} MyLibFeatExtractor MyLibSQI MyLibGPP MyLibGaborFilter)

add_executable(featureExtractor ${SRC})
target_link_libraries(featureExtractor ${OpenCV_LIBS})
