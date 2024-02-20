#ifndef CBALL_HPP
#define CBALL_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include "../config.hpp"

#define BALL_ACCELL 400

namespace Game {
    class CBall {
    private:
        sf::Vector2f position;
        sf::Vector2f velocity;

    public:
        CBall();

        void Draw(sf::RenderTarget* target);
        void Update(float dt);
        void ResetPosition();

        sf::Vector2f GetPosition();
        sf::Vector2f GetVelocity();
    };
};

#endif
