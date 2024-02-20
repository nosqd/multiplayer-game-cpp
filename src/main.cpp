#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui-SFML.h>
#include "game/CGame.hpp"

int main(int argc, char *argv[])
{
    Game::CGame* game = new Game::CGame();
    game->Start();
    return 0;
}