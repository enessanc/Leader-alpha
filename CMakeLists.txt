cmake_minimum_required(VERSION 3.21)
project(Leader)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("${CMAKE_SOURCE_DIR}/spdlog")
include_directories(${PROJECT_SOURCE_DIR})

add_executable(
        Leader
        main.cpp
        source/campaign/entity/base/Entity.h
        source/campaign/entity/population_identity/PopulationIdentity.cpp
        source/campaign/entity/population_identity/PopulationIdentity.h
        source/campaign/entity/population_identity/PopulationIdentityEnums.h
        source/config/constants.h source/campaign/entity/city/City.cpp
        source/campaign/entity/city/City.h
        source/campaign/entity/ideology/Ideology.cpp
        source/campaign/entity/ideology/Ideology.h
        source/campaign/entity/party/Party.cpp
        source/campaign/entity/party/Party.h
        source/campaign/entity/population_identity/PopulationIdentityTemplate.h
        source/campaign/entity/character/Character.cpp
        source/campaign/entity/character/Character.h
        source/campaign/entity/Country.cpp
        source/campaign/entity/Country.h
        source/campaign/entity/World.cpp
        source/campaign/entity/World.h
        source/tools/Randomizer.cpp
        source/tools/Randomizer.h
        data/json_file/entity/entity_path.h
        source/tools/JsonTools.h
        source/tools/JsonTools.cpp
        source/campaign/entity/population_identity/PopulationIdentityTemplate.cpp
        source/campaign/entity/ideology/IdeologyMathTools.cpp
        source/campaign/entity/ideology/IdeologyMathTools.h source/campaign/entity/ideology/IdeologyCoordinate.cpp source/campaign/entity/ideology/IdeologyCoordinate.h source/campaign/entity/character/CharacterCreator.cpp source/campaign/entity/character/CharacterCreator.h)

target_link_libraries(Leader PRIVATE spdlog::spdlog)


