#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#pragma once

class Button : public sf::Drawable, public sf::Transformable{

    protected:
        int x;
        int y;
        sf::Text contents;
        bool wasClicked = false;
        short clickedIterations = 0;
        std::string fontFile = "Graphics/Ubuntu-L.ttf";
        sf::Font font;
        unsigned short fontSize;  
        sf::VertexArray subMenu; 


    public:

        std::vector<Button> subButtons;

        bool menuOpened = false; 

        unsigned short subMenuWidth = 44;

        unsigned short height = 12;
        sf::FloatRect boundingBox;

        Button(unsigned int inX, unsigned int inY, std::string inContents);
        Button(sf::Vector2i inPos, std::string inContents);
        Button();
        
        void move(int inX, int inY);
        void move(sf::Vector2i inPos);
        void setPosition(int inX, int inY);
        void setPosition(sf::Vector2i inPos);
        void setText(std::string inContents);
        sf::Vector2i getCenter();
        void addButton(Button *ptr);


        bool buttonClicked(sf::Vector2i mousePos);

    private:

        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;

};


