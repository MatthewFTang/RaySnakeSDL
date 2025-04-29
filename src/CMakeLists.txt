
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    Core/Application.h
    Core/Application.cpp
    Core/Game.h
    Core/Game.cpp
    Core/LoaderParams.h
    Core/Vector2.cpp
    Core/Vector2.h
    Core/Level.cpp
    Menu/Menu.h
    Menu/MainMenu.cpp
    Menu/DifficultlyMenu.cpp
    Menu/AboutMenu.cpp
    Objects/Food.cpp
    Objects/Player.cpp
    Objects/GameObject.cpp
    Managers/FontManger.cpp
    Managers/SoundManger.cpp
    Managers/TextureManger.cpp
    Managers/InputManager.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})




