#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#pragma once

inline unsigned short tileSize = 16;

class tileRenderer : public sf::Drawable{
    protected:

        //These should be self explanatory
        sf::VertexArray foreGround;
        sf::VertexArray middleGround;
        sf::VertexArray backGround;




        //used for drawing collidable boxes
        sf::VertexArray tops;
        sf::VertexArray rights;
        sf::VertexArray bottoms;
        sf::VertexArray lefts;

        sf::Texture tileTex;

        sf::Vector2i windowSize;
        static const int mapHeight = 2000;
        static const int mapWidth = 2000;
        static const short height = 18;
        static const short width = 32;

    public:

        bool showColides = false;


        //Only displays what can be seen on screen
        unsigned short level[height][width][3];

        typedef bool boolRay[mapWidth];

        boolRay* collidableMap = new boolRay[mapHeight];

        bool collidableLevel[height][width];

        //Required for heap allocation of 3D array
        typedef unsigned short dimensions[tileRenderer::mapWidth][3];

        //Loads the entiry map into memory
        dimensions* tileMap = new dimensions[tileRenderer::mapHeight];

        ~tileRenderer();
        tileRenderer();



        //Transition tile IDs from map to level
        bool windowPos(sf::Vector2i cameraPos);

        /*Creates a tile map with a foreground, middle ground, and background*/
        bool renderTile(std::string fileName, sf::Vector2i cameraPos); 

        /*loads the tilesmaps stored in binary and runs renderTile*/
        bool loadTile(std::string tilemapFile);

        /*Saves the tilemap being worked on to specified file*/
        bool saveTile(std::string tilemapFile);

        //Creates a new array of all ones
        bool newMap();

        //Called for development to move all second layer tiles into a boolean array
        void convertToColide();

        //Outlines all collidable tiles and is toggleable
        void showCollidables();

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
        bool tileSelect(std::string fileName, short scrollPos, sf::Vector2i windowStart, int tileNumber);

        int selectTile(int tileNumber, short scrollPos, sf::Vector2i windowStart);

    private:

        //Used to call window.draw(object) like an SFML entity
        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;
};



class background : public sf::Drawable {
    protected:
        sf::Vector2i windowSize;
        sf::Texture backgroundTex;
        sf::VertexArray actualBackground;
        sf::Vector2i backgroundTextureSize = sf::Vector2i(512, 288);
    public:
        //Renders the background if called
        background(std::string filename, sf::Vector2i window);


        bool set(sf::Vector2i cameraPos);

    private:
        //Used to call window.draw(object) like an SFML entity
        void draw(sf::RenderTarget& rtarget, sf::RenderStates states) const;
};

