cmake_minimum_required(VERSION 3.0)
project(PURITY_GEANT4)
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
# ------------------------------------------------------------------------------
include_directories(${PROJECT_SOURCE_DIR}/include)

# file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
add_executable(GEANT4 
    src/DetectorConstruction.cc
    src/PhysicsList.cc
    src/PrimaryGeneratorAction.cc
    src/EventAction.cc
    src/HistoManager.cc
    main.cc
)

# Link against Geant4 libraries
target_link_libraries(GEANT4 ${Geant4_LIBRARIES})

# For out-of-source builds, place executables here:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)