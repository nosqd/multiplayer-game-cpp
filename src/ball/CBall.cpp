#include "CBall.hpp"
#include "../game/CGame.hpp"

Game::CBall::CBall()
{
    this->ResetPosition();
}
void Game::CBall::Draw(sf::RenderTarget *target)
{
    sf::CircleShape shape;
    shape.setRadius(20.f);
    shape.setPosition(this->GetPosition());
    target->draw(shape);

}
void Game::CBall::Update(float dt)
{
    this->position += this->velocity * dt;
    sf::Rect<int> shapeRect(this->position.x - (20.f / 2.f), this->position.y - (20.f / 2.f), 20.f, 20.f);
    sf::Rect<int> leftPaddle(0, (int)Game::CGame::get()->left->GetPosition(), 10, 50);
    sf::Rect<int> rightPaddle(1280 - 10, (int)Game::CGame::get()->right->GetPosition(), 10, 50);
    if (this->position.x < 0)
    {
        CGame::get()->right->AddScore(1);
        CGame::get()->ResetPositions();
        this->velocity.x *= -1.f;
    }
    else if (this->position.x > 1280.f - 20.f)
    {
        CGame::get()->left->AddScore(1);
        CGame::get()->ResetPositions();
        this->velocity.x *= -1.f;
    }
    if (this->position.y < 0 || this->position.y > 720.f - 20.f)
    {
        this->velocity.y *= -1.f;
    }
    if (shapeRect.intersects(leftPaddle) || shapeRect.intersects(rightPaddle))
    {
        this->velocity *= -1.f;
    }
}
sf::Vector2f Game::CBall::GetPosition()
{
    return this->position;
}
sf::Vector2f Game::CBall::GetVelocity()
{
    return this->velocity;
}
void Game::CBall::ResetPosition()
{
    this->position = sf::Vector2f(1280.f / 2.f - 20.f / 2.f, 720.f / 2.f - 20.f / 2.f);
    this->velocity = sf::Vector2f(((((float)rand() / (float)RAND_MAX)) / 2.f + 0.5f) * BALL_ACCELL, ((((float)rand() / (float)RAND_MAX)) / 2.f + 0.5f) * BALL_ACCELL);
}