cmake_minimum_required(VERSION 3.10)
project(MyOpenCVProject)

# Find OpenCV package
find_package(OpenCV REQUIRED)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your executable
add_executable(MyOpenCVProject wxmain.cpp)

# Link OpenCV libraries
target_link_libraries(MyOpenCVProject ${OpenCV_LIBS})

target_link_libraries(MyOpenCVProject ${wxWidgets_LIBRARIES})