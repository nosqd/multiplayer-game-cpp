#include "CPlayer.hpp"

Game::CPlayer::CPlayer(Game::EPlayerSide side, bool isLocal)
{
    this->side = side;
    this->ResetPosition();
    this->local = isLocal;
    this->score = 0;
}
void Game::CPlayer::Draw(sf::RenderTarget *target)
{
    sf::Vector2f pos(0, 0);
    if (this->side == EPlayerSide::LEFT)
    {
        pos.x = 0;
    }
    else
    {
        pos.x = 1270; // TODO: GET BOARD SIDE AND SUBTRACT
    }
    pos.y = (int)this->position;
    sf::RectangleShape playerShape;
    playerShape.setPosition(pos);
    playerShape.setSize(sf::Vector2f(10, 50));
    target->draw(playerShape);
}
// meant to be run on server and in prediction process
void Game::CPlayer::Update(float dt)
{
    PlayerCmd cmd = this->UserCmd();
    if (IF_BITMASK(cmd.keys, PlayerKeys::UP) && this->position - PLAYER_ACCEL * dt > 0)
    {
        this->position -= PLAYER_ACCEL * dt;
    }
    if (IF_BITMASK(cmd.keys, PlayerKeys::DOWN) && this->position + PLAYER_ACCEL * dt < 720 - 50) // TODO: check window/board size
    {
        this->position += PLAYER_ACCEL * dt;
    }
}
Game::EPlayerSide Game::CPlayer::GetSide() { return this->side; }
float Game::CPlayer::GetPosition() { return this->position; }
Game::PlayerCmd Game::CPlayer::UserCmd()
{
    if (this->local)
    {
        return CInput::get()->GetLocalCmd();
    }
    return (Game::PlayerCmd){
        .keys = 0};
}
void Game::CPlayer::AddScore(uint16_t ds)
{
    this->score += ds;
    std::cout << "scored " << Game::PlayerSideToString(this->side) << " ds: "<< ds << " s: " << this->score << "\n";
}
uint16_t Game::CPlayer::GetScore()
{
    return this->score;
}
void Game::CPlayer::ResetPosition() {
    this->position = 0.f;
}
std::string Game::PlayerSideToString(EPlayerSide side)
{
    if (side == LEFT)
        return "LEFT";
    if (side == RIGHT)
        return "RIGHT";
    return "UNKNOWN";
}
