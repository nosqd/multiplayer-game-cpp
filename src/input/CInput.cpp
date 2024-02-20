#include "CInput.hpp"

Game::CInput::CInput()
{
    Game::CInput::instance = this;
}
Game::CInput *Game::CInput::instance = nullptr;
Game::CInput *Game::CInput::get()
{
    if (Game::CInput::instance == nullptr)
    {
        Game::CInput::instance = new Game::CInput();
    }
    return Game::CInput::instance;
}
void Game::CInput::HandleKeyEvent(sf::Event event)
{
    assert(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased);
    this->keys[event.key.code] = event.type == sf::Event::KeyPressed;
}
bool Game::CInput::IsKeyPressed(sf::Keyboard::Key key)
{
    return this->keys[key];
}
Game::PlayerCmd Game::CInput::GetLocalCmd() {
    Game::PlayerCmd cmd = (Game::PlayerCmd){
        .keys = 0
    };
    if (Game::CInput::get()->IsKeyPressed(sf::Keyboard::Key::W)) {
        cmd.keys |= PlayerKeys::UP;
    }
    if (Game::CInput::get()->IsKeyPressed(sf::Keyboard::Key::S)) {
        cmd.keys |= PlayerKeys::DOWN;
    }
    return cmd;
}
