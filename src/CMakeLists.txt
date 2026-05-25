set(SOURCES main.cpp)

add_subdirectory(Core)
add_subdirectory(Features)
add_subdirectory(IO)

add_executable(sw_battle_test ${SOURCES})
target_link_libraries(sw_battle_test io core features)
