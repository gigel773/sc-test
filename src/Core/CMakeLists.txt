set(SOURCES
        Engine.cpp
        Map.cpp
        ResourceRegistry.cpp
        ResourceAccessor.cpp
        Decorators/ActionLogger.cpp
        Decorators/ActionLogger.hpp
        ObjectRegistry.cpp
        ObjectRegistry.hpp
        Decorators/ObjectRegistryLogger.cpp
        Decorators/ObjectRegistryLogger.hpp
        Decorators/MapLogger.cpp
        Decorators/MapLogger.hpp
        OrderRegistry.cpp
        OrderRegistry.hpp
        Decorators/ObjectController.cpp
        Decorators/ObjectController.hpp
)

add_library(core OBJECT ${SOURCES})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
