set(SOURCES
        Units/Swordsman.cpp
        Units/Ranger.cpp
        Actions/Move.cpp
        Actions/Attack.cpp
        Resources/Integer.cpp
        Orders/March.cpp
        Orders/March.hpp
)

add_library(features OBJECT ${SOURCES})
target_link_libraries(features PUBLIC core)
target_include_directories(features PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
