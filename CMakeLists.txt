# Makefile generated by CMakefileGenerator.cs (v1.2)
# *DO NOT EDIT*

cmake_minimum_required (VERSION 2.6)
project (Unreal)

# CMake Flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 1 CACHE BOOL "" FORCE)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 1 CACHE BOOL "" FORCE)

# Standard Includes
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-includes.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-definitions.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-headers-ue.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-headers-project.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-sources-engine.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-sources-project.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-csharp-engine.cmake")
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-csharp-project.cmake")

# Optional Shader Include
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-shaders-engine.cmake")
set_source_files_properties(${ENGINE_SHADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-shaders-project.cmake")
set_source_files_properties(${PROJECT_SHADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
source_group("Shader Files" REGULAR_EXPRESSION .*.usf)

# Optional Config Include
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-config-engine.cmake")
set_source_files_properties(${ENGINE_CONFIG_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
include("C:/Users/2001733/UE5/Perception_Exercise/Intermediate/ProjectFiles/cmake-config-project.cmake")
set_source_files_properties(${PROJECT_CONFIG_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
source_group("Config Files" REGULAR_EXPRESSION .*.ini)

add_custom_target(UnrealEditor-Win64-DebugGame call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealEditor-Win64-Shipping call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealEditor call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealEditor Win64 Development  -game -progress -buildscw VERBATIM)

add_custom_target(UnrealGame-Win64-DebugGame call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealGame Win64 DebugGame  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealGame-Win64-Shipping call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealGame Win64 Shipping  -game -progress -buildscw VERBATIM)
add_custom_target(UnrealGame call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" UnrealGame Win64 Development  -game -progress -buildscw VERBATIM)

add_custom_target(Perception-Win64-DebugGame call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" Perception Win64 DebugGame "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(Perception-Win64-Shipping call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" Perception Win64 Shipping "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(Perception call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" Perception Win64 Development "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)

add_custom_target(PerceptionEditor-Win64-DebugGame call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" PerceptionEditor Win64 DebugGame "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(PerceptionEditor-Win64-Shipping call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" PerceptionEditor Win64 Shipping "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)
add_custom_target(PerceptionEditor call "C:/Program Files/Epic Games/UE_5.2/Engine/Build/BatchFiles/Build.bat" PerceptionEditor Win64 Development "-project=C:/Users/2001733/UE5/Perception_Exercise/Perception.uproject" -game -progress -buildscw VERBATIM)

add_executable(FakeTarget ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES} ${ENGINE_CSHARP_FILES} ${ENGINE_SHADER_FILES} ${ENGINE_CONFIG_FILES} ${PROJECT_HEADER_FILES} ${PROJECT_SOURCE_FILES} ${PROJECT_CSHARP_FILES} ${PROJECT_SHADER_FILES} ${PROJECT_CONFIG_FILES})
