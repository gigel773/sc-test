set(SOURCES 
    System/CommandParser.cpp
        System/EventProducer.cpp
        System/EventProducer.hpp)

add_library(io OBJECT ${SOURCES})
target_include_directories(io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(io PUBLIC core)
