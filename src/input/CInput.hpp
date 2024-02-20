#ifndef CINPUT_H
#define CINPUT_H
#include <map>
#include <SFML/Window/Event.hpp>
#include <assert.h>
#include "../utils/Utils.hpp"
#include <iostream>

namespace Game
{
    // https://stackoverflow.com/a/4922366
    enum PlayerKeys {
        UP = BITMASK(1),
        DOWN = BITMASK(2)
    };

    typedef struct {
        uint16_t keys;
    } PlayerCmd;

    class CInput
    {
    private:
        CInput();
        static CInput *instance;

        std::map<int, bool> keys;

    public:
        static CInput *get();

        void HandleKeyEvent(sf::Event event);
        bool IsKeyPressed(sf::Keyboard::Key key);
        PlayerCmd GetLocalCmd();
    };
};
#endif