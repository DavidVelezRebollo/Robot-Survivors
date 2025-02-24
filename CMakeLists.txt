cmake_minimum_required(VERSION 3.23)
project(VampireSurvivors LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

# Download and add SFML as a dependency
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Download and add tmxlite (tiled editor loader) as a dependency
FetchContent_Declare(
    TMXLITE
    GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    GIT_TAG v1.4.4
    SOURCE_SUBDIR tmxlite)
FetchContent_MakeAvailable(TMXLITE)


set(PROJECT_HEADERS 
    include/Utils/Constants.h

    include/Core/AssetManager.h
    include/Core/Game.h
    include/Core/World.h
    include/Core/BulletPool.h
    include/Core/EnemyPool.h
    include/Core/WeaponManager.h
	include/Core/SpawnManager.h
	include/Core/CollisionManager.h
	include/Core/GameManager.h
	include/Core/SoundManager.h

    include/Gameplay/Enemy.h
    include/Gameplay/GameObject.h
    include/Gameplay/Runner.h
	include/Gameplay/Shooter.h
    include/Gameplay/Player.h
    include/Gameplay/Projectile.h
	include/Gameplay/Weapon.h
	include/Gameplay/Pistol.h
	include/Gameplay/Raygun.h
	include/Gameplay/Shotgun.h
	include/Gameplay/Spawner.h
	include/Gameplay/Tank.h

	include/Render/ObjectLayer.h
	include/Render/MapLayer.h

    include/UI/UIScreenMainMenu.h
	include/UI/UIManager.h
	include/UI/HUD.h
	include/UI/WeaponCard.h
	include/UI/ExperienceBar.h
	include/UI/LoseScreen.h
	include/UI/HpBar.h
)

set(PROJECT_SOURCES 

    src/Core/AssetManager.cpp
    src/Core/Game.cpp
    src/Core/World.cpp
    src/Core/BulletPool.cpp
    src/Core/EnemyPool.cpp
    src/Core/WeaponManager.cpp
	src/Core/SpawnManager.cpp
	src/Core/CollisionManager.cpp
	src/Core/GameManager.cpp
	src/Core/SoundManager.cpp

    src/Gameplay/Enemy.cpp
	src/Gameplay/Runner.cpp
	src/Gameplay/Shooter.cpp
    src/Gameplay/Player.cpp
    src/Gameplay/Projectile.cpp
    src/Gameplay/Weapon.cpp
    src/Gameplay/Pistol.cpp
    src/Gameplay/Shotgun.cpp
    src/Gameplay/Raygun.cpp
	src/Gameplay/Spawner.cpp
	src/Gameplay/Tank.cpp
	
	src/Render/MapLayer.cpp
	src/Render/ObjectLayer.cpp
	
	src/UI/UIManager.cpp
	src/UI/UIScreenMainMenu.cpp
	src/UI/HUD.cpp
	src/UI/WeaponCard.cpp
	src/UI/ExperienceBar.cpp
	src/UI/LoseScreen.cpp
	src/UI/HpBar.cpp

    src/main.cpp
)

set(PROJECT_FILES 
  ${PROJECT_HEADERS} 
  ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} PRIVATE ${tmxlite_INCLUDE_DIR} include)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics tmxlite sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG_MODE=0)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()
