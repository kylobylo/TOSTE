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
        sf::RenderWindow* tileWindow;
        Button fileButton;
        Button newButton;
        Button saveButton;
        Button loadButton;
        Button editButton;
        Button backgroundButton;
        short debouncer = 0;
        tileRenderer* pTRender;
        bool wasClicked = false;
        short clickedIterations = 0;
        sf::Vector2i* pMousePos;

    public:

        sf::Vector2i mousePos;

        unsigned short height = 12;

        UI(tileRenderer* ptrTileRenderer, sf::RenderWindow *window);

        //We need to update the UI in case the buttons are clicked and we have to make sure that left-clicks
        //Only go through the UI handler so we don't accide3ntally draw when we want to use the UI.
        //Periodic returns true if no UI button that goes over the map is pressed.
        bool UIPeriodic();

    private:

        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;
};
