//
// Created by Matt on 3/07/2024.
//

#define ORANGE \
    { 255, 161, 0, 255 }
#include "AboutMenu.h"

#include "Core/Application.h"
#include "Core/Game.h"
#include "MainMenu.h"
#include "Managers/FontManger.h"
#include "Managers/InputManager.h"
#include "Managers/TextureManger.h"

AboutMenu::AboutMenu(Game &game) : game_(game) {
    TextureManger::Instance()->LoadText("src/resources/art/HelpMenu.png", texture_id_);
}
void AboutMenu::Render() {
    int x_center = Application::Instance()->GetScreenWidth() / 2;
    TextureManger::Instance()->DrawImage(texture_id_);

    FontManger::Instance()->RenderText("Help me!", 62, ORANGE, x_center, 50, true);

    FontManger::Instance()->RenderText("Use the arrow keys or WASD to control the direction of the bird",
                                       32, ORANGE, x_center, 250, true);
    FontManger::Instance()->RenderText("Eat the fruit to make the flock grow longer.",
                                       32, ORANGE, x_center, 300, true);
    FontManger::Instance()->RenderText("Avoid hitting the walls or yourself.",
                                       32, ORANGE, x_center, 350, true);
    FontManger::Instance()->RenderText("The difficulty controls the speed of the bird.",
                                       32, ORANGE, x_center, 400, true);
    FontManger::Instance()->RenderText("Sound effects from  Zapsplat.com",
                                       32, ORANGE, x_center, 550, true);
    FontManger::Instance()->RenderText("Sprites from Pixel Adventures 1",
                                       32, ORANGE, x_center, 600, true);
    FontManger::Instance()
            ->RenderText("Press SPACE BAR to return to main menu",
                         32, ORANGE, x_center, Application::Instance()->GetScreenHeight() - 100, true);
}
void AboutMenu::Update() {
    if (InputManager::Instance()->IsKeyPress(SDLK_SPACE)) {
        game_.SetMenu<MainMenu>();
    }
}