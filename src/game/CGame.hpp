#ifndef CGAME_HPP
#define CGAME_HPP
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include "../utils/Utils.hpp"
#include "../input/CInput.hpp"
#include "../ball/CBall.hpp"
#include "../player/CPlayer.hpp"

namespace Game {
    class CGame {
    private:
        static CGame* instance;
        sf::RenderWindow* window;
        sf::Clock* deltaClock;
        sf::Time lastDt;
        sf::Font* font;
        bool running;
        
        void Loop();
        void Draw();    
        void Update(float dt);
        void DrawDebugInfo();
    public:
        Game::CPlayer* left;
        Game::CPlayer* right;
        Game::CBall* ball;
        
        static CGame* get();
        CGame();
        void Start();
        void ResetPositions();
    };
};
#endif