#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include "Button.hpp"
#include "tileRenderer.hpp"
#pragma once


class UI : public sf::Drawable {
    
    protected:

        sf::VertexArray UIBar;
        sf::VertexArray fileSubMenu;
        Button fileButton;
        Button newButton;
        Button saveButton;
        Button loadButton;
        Button editButton;
        Button backgroundButton;
        tileRenderer* pTRender;
        bool wasClicked = false;
        short clickedIterations = 0;
        sf::Vector2i* pMousePos;
        unsigned short fileButtonXCenter;

    public:

        unsigned short height = 12;

        UI(tileRenderer* ptrTileRenderer);
        bool UIPeriodic(sf::Vector2i* inMousePos);

    private:

        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;
};