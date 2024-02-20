#ifndef CPLAYER_HPP
#define CPLAYER_HPP
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../config.hpp"
#include "../input/CInput.hpp"
#include "../utils/Utils.hpp"

#define PLAYER_ACCEL 400

namespace Game {
    enum EPlayerSide {
        LEFT,
        RIGHT
    };

    std::string PlayerSideToString(EPlayerSide side);

    class CPlayer {
    private:
        bool local;
        float position;
        Game::EPlayerSide side;
        uint16_t score;

    public:
        CPlayer() = delete;
        CPlayer(Game::EPlayerSide side, bool isLocal);

        void Draw(sf::RenderTarget* target);
        void Update(float dt);
        void ResetPosition();

        EPlayerSide GetSide();
        float GetPosition();
        Game::PlayerCmd UserCmd();
        void AddScore(uint16_t ds);
        uint16_t GetScore();
    };
};

#endif
