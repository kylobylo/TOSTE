#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#pragma once



class tileRenderer : public sf::Drawable{
    protected:

        //These should be self explanatory
        sf::VertexArray foreGround;
        sf::VertexArray middleGround;
        sf::VertexArray backGround;
        sf::Texture tileTex;
        static const int mapHeight = 2000;
        static const int mapWidth = 2000;
        static const short height = 18;
        static const short width = 32;

    public:

        //Only displays what can be seen on screen
        unsigned short level[18][32][3];

        //Required for heap allocation of 3D array
        typedef unsigned short dimensions[tileRenderer::mapWidth][3];

        //Loads the entiry map into memory
        dimensions* tileMap = new dimensions[tileRenderer::mapHeight];

        ~tileRenderer();
        tileRenderer();



        //Transition tile IDs from map to level
        bool windowPos(sf::Vector2i cameraPos, sf::Vector2i tileSize);

        /*Creates a tile map with a foreground, middle ground, and background*/
        bool renderTile(std::string fileName, sf::Vector2i tileSize, sf::Vector2i cameraPos); 

        /*loads the tilesmaps stored in binary and runs renderTile*/
        bool loadTile(std::string tilemapFile);

        /*Saves the tilemap being worked on to specified file*/
        bool saveTile(std::string tilemapFile);

        //Creates a new array of all ones
        bool newMap();

    private:

        //Used to call window.draw(object) like an SFML entity
        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;

};

class tileSelector : public sf::Drawable{

    protected:

        short height;
        short width;

        sf::VertexArray tilesOfFile;
        sf::VertexArray tileBoxTop;
        sf::VertexArray tileBoxLeft;
        sf::VertexArray tileBoxRight;
        sf::VertexArray tileBoxBottom;
        sf::Texture tileTex;
        tileRenderer rend;

    public:

        //Render the tile Selector
        bool tileSelect(std::string fileName, sf::Vector2i tileSize, short scrollPos, sf::Vector2i windowStart, int tileNumber);

        int selectTile(int tileNumber, sf::Vector2i tileSize, short scrollPos, sf::Vector2i windowStart);

    private:

        //Used to call window.draw(object) like an SFML entity
        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;
};