cmake_minimum_required(VERSION 3.1)
project(MyQtApp)

# Find the necessary Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)

if(Qt6_FOUND)
    message(STATUS "Found Qt6: ${Qt6_VERSION}")
else()
    message(FATAL_ERROR "Qt6 not found")
endif()

# Add your executable
add_executable(MyApp main.cpp)

# Use the appropriate modules from Qt
target_link_libraries(MyApp PRIVATE Qt6::Widgets Qt6::Widgets)
