#include "tileRenderer.hpp"
#include <math.h>
using namespace sf;

bool tileRenderer::renderTile(std::string fileName, sf::Vector2i tileSize, sf::Vector2i cameraPos) {
    
    //Calls cameraPos so we grab the correct section of tileMap as it helps performance considering tileMap is 12 million tiles in capacity
    this->windowPos(cameraPos, tileSize);

    
    tileRenderer::foreGround.setPrimitiveType(Quads);
    tileRenderer::middleGround.setPrimitiveType(Quads);
    tileRenderer::backGround.setPrimitiveType(Quads);
    tileRenderer::foreGround.resize(width * height * 4);
    tileRenderer::middleGround.resize(width * height * 4);
    tileRenderer::backGround.resize(width * height * 4);


    //Sets the texture to a file which contains all of the tile textures
    if (!tileTex.loadFromFile(fileName)) {
        #ifdef DEBUGRENDERING

            std::cout << "ERROR LOADING FILE" << std::endl;
        #endif
        return false;
    }
    

    //Render first layer
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {

            //Multiply height iterations by width so that it represents what elements to access ccorrectly.
            sf::Vertex* foreArray = &foreGround[(w+h * width) * 4];



            if (level[h][w][0] != 0) {

                //Used to transotopm from row to row on texture file
                unsigned short roundRow = std::floor(((level[h][w][0] - 1) / 40));

                //Assign vectors to draw lines between
                foreArray[0].position = Vector2f(tileSize.x * w, tileSize.y * h);
                foreArray[1].position = Vector2f(tileSize.x * (w + 1), tileSize.y * h);
                foreArray[2].position = Vector2f(tileSize.x * (w + 1), tileSize.y * (h + 1));
                foreArray[3].position = Vector2f(tileSize.x * w, tileSize.y * (h + 1));


                //Assign corners of textures to corners of tiles
                foreArray[0].texCoords = Vector2f(((level[h][w][0] - 1) % 40) * tileSize.x, 0.f + (tileSize.y * roundRow));
                foreArray[1].texCoords = Vector2f((((level[h][w][0] - 1) % 40) * tileSize.x) + tileSize.x, 0.f + (tileSize.y * roundRow));
                foreArray[2].texCoords = Vector2f((((level[h][w][0] - 1) % 40) * tileSize.x) + tileSize.x, tileSize.y + (tileSize.y * roundRow));
                foreArray[3].texCoords = Vector2f(((level[h][w][0] - 1) % 40) * tileSize.x, tileSize.y + (tileSize.y * roundRow));

            }
        }
    }
    
    //Render second layer
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {

            //This is litterally the same as the first one except for replacing a few array values and vertex arrays

            sf::Vertex* midArray = &middleGround[(w+h * width) * 4];

            #ifdef DEBUGRENDERING
                std::cout << "Rendering Second Width: " << w << " Rendering Second Height: " << h << " Second Level Number " << level[h][w][1] << std::endl;
            #endif
            if (level[h][w][1] != 0) {

                unsigned short roundRow = std::floor(((level[h][w][1] - 1) / 40));


                midArray[0].position = Vector2f(tileSize.x * w, tileSize.y * h);
                midArray[1].position = Vector2f(tileSize.x * (w + 1), tileSize.y * h);
                midArray[2].position = Vector2f(tileSize.x * (w + 1), tileSize.y * (h + 1));
                midArray[3].position = Vector2f(tileSize.x * w, tileSize.y * (h + 1));



                midArray[0].texCoords = Vector2f(((level[h][w][1] - 1) % 40) * tileSize.x, 0.f + (tileSize.y * roundRow));
                midArray[1].texCoords = Vector2f((((level[h][w][1] - 1) % 40) * tileSize.x) + tileSize.x, 0.f + (tileSize.y * roundRow));
                midArray[2].texCoords = Vector2f((((level[h][w][1] - 1) % 40) * tileSize.x) + tileSize.x, tileSize.y + (tileSize.y * roundRow));
                midArray[3].texCoords = Vector2f(((level[h][w][1] - 1) % 40) * tileSize.x, tileSize.y + (tileSize.y * roundRow));
            }
        }
    }

    //Render third layer
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {

            //This is litterally the same as the first one except for replacing a few array values and vertex arrays

            sf::Vertex* backArray = &backGround[(w+h * width) * 4];

            #ifdef DEBUGRENDERING
                std::cout << "Rendering Third Width: " << w << " Rendering Third Height: " << h << " Third Level Number " << level[h][w][2] << std::endl;
            #endif
            if (level[h][w][2] != 0) {

                unsigned short roundRow = std::floor(((level[h][w][2] - 1) / 40));


                backArray[0].position = Vector2f(tileSize.x * w, tileSize.y * h);
                backArray[1].position = Vector2f(tileSize.x * (w + 1), tileSize.y * h);
                backArray[2].position = Vector2f(tileSize.x * (w + 1), tileSize.y * (h + 1));
                backArray[3].position = Vector2f(tileSize.x * w, tileSize.y * (h + 1));



                backArray[0].texCoords = Vector2f(((level[h][w][2] - 1) % 40) * tileSize.x, 0.f + (tileSize.y * roundRow));
                backArray[1].texCoords = Vector2f((((level[h][w][2] - 1) % 40) * tileSize.x) + tileSize.x, 0.f + (tileSize.y * roundRow));
                backArray[2].texCoords = Vector2f((((level[h][w][2] - 1) % 40) * tileSize.x) + tileSize.x, tileSize.y + (tileSize.y * roundRow));
                backArray[3].texCoords = Vector2f(((level[h][w][2] - 1) % 40) * tileSize.x, tileSize.y + (tileSize.y * roundRow));
            }
        }
    }
    

    return true;
};



void tileRenderer::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const  {

    //Draws each layer in order so the last layer to be drawn is on top

    states.texture = &tileTex;
    rtarget.draw(backGround, states);
    rtarget.draw(middleGround, states);
    rtarget.draw(foreGround, states);  
};

bool tileRenderer::loadTile(std::string tilemapFile) {

    

    std::fstream fs;

    //Open an input filestream
    fs.open(tilemapFile, std::ios::in | std::ios::binary);

    //Checks for file errors
    if(fs.is_open()) {

        //Due to custom Dimension class used to store a 3D array in the Heap, height must be iterated as it only reads one height at a time.
        for(int h = 0; h < mapHeight; h++) {
            fs.read((char*)(*tileMap[h]), sizeof(*tileMap));
        }
        fs.close();
        return true;
    } else {
        #ifdef DEBUG
            std::cout << "ERROR OPENING TILEMAP FILE.  DOES IT EXIST?\n";
        #endif
        return false;
    }


};



bool tileRenderer::saveTile(std::string tilemapFile) {

    std::fstream fs;

    fs.open(tilemapFile, std::ios::out | std::ios::binary);
    
    //Check for file errors
    if(fs.is_open()) {

        //Iterates through height due to Dimension class
        for(int h = 0; h < mapHeight; h++) {
            fs.write((char*)(tileMap[h]), sizeof(*tileMap));
        }
        fs.close();
        return true;
    } else {
        #ifdef DEBUG
            std::cout << "ERROR OPENING TILEMAP FILE.  DOES THE PROGRAM HAVE PERMISSION?\n";
        #endif
        return false;
    }
};


bool tileRenderer::newMap() {

    //Iterates to set all array elements to 1 which appears as a blank(the first 16x16 texture is blank in the tileMap file)
    for(int h = 0; h < mapHeight; h++) {
        for(int w = 0; w < mapWidth; w++) {
            for(int t = 0; t < 3; t++) {
                tileMap[h][w][t] = 1;
            }
        }
    }
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            for(int t = 0; t < 3; t++) {
                level[h][w][t] = 1;
            }
        }
    }

    return true;
};

tileRenderer::~tileRenderer() {
    delete[] tileMap;
};

tileRenderer::tileRenderer() {
    newMap();
};

bool tileRenderer::windowPos(sf::Vector2i cameraPos, sf::Vector2i tileSize) {

    int y = (std::floor(cameraPos.y / tileSize.y)); 
    int x = (std::floor(cameraPos.x / tileSize.x));

    for(int h = y, l = 0; h < y + height; h++, l++) {
        for(int w = x, r = 0; w < x + width; w++, r++) {
            for(int t = 0; t < 3; t++) {
                level[l][r][t] = tileMap[h][w][t];
            }
        }
    }
    return true;
};

bool tileSelector::tileSelect(std::string fileName, sf::Vector2i tileSize, short scrollPos, Vector2i windowStart, int tileNumber) {
    tilesOfFile.setPrimitiveType(Quads);
    tilesOfFile.resize(17 * 6 * 4);
    height = 17;
    width = 6;

    this->selectTile(tileNumber, tileSize, scrollPos, windowStart);

    if(!tileTex.loadFromFile(fileName)) {
        std::cout << "ERROR FAILED TO READ TILE FILE\n";
        return false;
    }

    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++){

            sf::Vertex* tileArray = &tilesOfFile[(w + h * width) * 4];

            short textureRow = std::floor((((h + scrollPos) * width) + w) / 40);

            short textureColumn = (((h + scrollPos) * width) + w) % 40;

            #ifdef SELECTORDEBUG
                std::cout <<"H = " << h << ", W = "  << w << ", TextureRow = " << textureRow << ", Texture Column = " << textureColumn << std::endl;
            #endif


            tileArray[0].position = Vector2f(w * tileSize.x + windowStart.x, h * tileSize.y + windowStart.y);
            tileArray[1].position = Vector2f(w * tileSize.x + windowStart.x, h * tileSize.y + tileSize.y + windowStart.y);
            tileArray[2].position = Vector2f(w * tileSize.x + tileSize.x + windowStart.x, h * tileSize.y + tileSize.y + windowStart.y);
            tileArray[3].position = Vector2f(w * tileSize.x + tileSize.x + windowStart.x, h * tileSize.y + windowStart.y);

            tileArray[0].texCoords = Vector2f(textureColumn * tileSize.x, textureRow * tileSize.y);
            tileArray[1].texCoords = Vector2f(textureColumn * tileSize.x, textureRow * tileSize.y + tileSize.y);
            tileArray[2].texCoords = Vector2f(textureColumn * tileSize.x + tileSize.x, textureRow * tileSize.y + tileSize.y);
            tileArray[3].texCoords = Vector2f(textureColumn * tileSize.x + tileSize.x, textureRow * tileSize.y);
        }

    }

    return true;

};


int tileSelector::selectTile(int tileNumber, Vector2i tileSize, short scrollPos, sf::Vector2i windowStart) {

    #ifdef SELECTORDEBUG
        std::cout << "In selectTile functions" << std::endl;
    #endif

    tileNumber--;



    //I know there is a lineStrip primitive but it was being annoying so I forwent it.
    tileBoxBottom.resize(2);
    tileBoxTop.resize(2);
    tileBoxLeft.resize(2);
    tileBoxRight.resize(2);
    #ifdef SELECTORDEBUG
        std::cout << "Highlight Array Resized" << std::endl;
    #endif
    tileBoxBottom.setPrimitiveType(Lines);
    tileBoxTop.setPrimitiveType(Lines);
    tileBoxLeft.setPrimitiveType(Lines);
    tileBoxRight.setPrimitiveType(Lines);
    #ifdef SELECTORDEBUG
        std::cout << "Highlight Array set to Lines" << std::endl;
    #endif

    unsigned short h = std::floor(tileNumber / width) - scrollPos;

    tileBoxTop[0].position = Vector2f((tileNumber % width) * tileSize.x + windowStart.x , h * tileSize.y + windowStart.y);
    tileBoxLeft[0].position = Vector2f((tileNumber % width) * tileSize.x + windowStart.x , h * tileSize.y + windowStart.y);
    
    #ifdef SELECTORDEBUG
        std::cout << "One highlight point allocated" << std::endl;
    #endif
    tileBoxLeft[1].position = Vector2f((tileNumber % width) * tileSize.x + windowStart.x, (h * tileSize.y) + tileSize.y + windowStart.y);
    tileBoxBottom[0].position = Vector2f((tileNumber % width) * tileSize.x + windowStart.x, (h * tileSize.y) + tileSize.y + windowStart.y);
    #ifdef SELECTORDEBUG
        std::cout << "Two highlight points allocated" << std::endl;
    #endif
    tileBoxBottom[1].position = Vector2f(((tileNumber % width) * tileSize.x) +  tileSize.x + windowStart.x, (h * tileSize.y) + tileSize.y + windowStart.y);
    tileBoxRight[1].position = Vector2f(((tileNumber % width) * tileSize.x) + tileSize.x + windowStart.x, (h * tileSize.y) + tileSize.y + windowStart.y);
    #ifdef SELECTORDEBUG
        std::cout << "Three highlight points allocated" << std::endl;
    #endif
    tileBoxTop[1].position = Vector2f(((tileNumber % width) * tileSize.x) +  tileSize.x + windowStart.x, h * tileSize.y + windowStart.y);
    tileBoxRight[0].position = Vector2f(((tileNumber % width) * tileSize.x) + tileSize.x + windowStart.x, h * tileSize.y + windowStart.y);


    #ifdef SELECTORDEBUG
        std::cout << "All highlight points allocated" << std::endl;
    #endif





    return(tileNumber);


};






void tileSelector::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const {

    states.texture = &tileTex;

    rtarget.draw(tilesOfFile, states);
    rtarget.draw(tileBoxTop);
    rtarget.draw(tileBoxLeft);
    rtarget.draw(tileBoxRight);
    rtarget.draw(tileBoxBottom);

};





background::background(std::string filename, Vector2i window) {
    if(!backgroundTex.loadFromFile(filename)) {
        std::cout << "ERROR FAILED TO LOAD FROM FILE FOR BACKGROUND!\n";
    }

    windowSize = window;
}

bool background::set(sf::Vector2i cameraPos) {
    actualBackground.setPrimitiveType(Quads);
    actualBackground.resize(4);

    actualBackground[0].position = Vector2f(0, 12);
    actualBackground[1].position = Vector2f(0, windowSize.y);
    actualBackground[2].position = Vector2f(windowSize.x * 0.836601307, windowSize.y);
    actualBackground[3].position = Vector2f(windowSize.x * 0.836601307, 12);

    actualBackground[0].texCoords = Vector2f(0, 0);
    actualBackground[1].texCoords = Vector2f(0, backgroundTextureSize.y);
    actualBackground[2].texCoords = Vector2f(backgroundTextureSize.x, backgroundTextureSize.y);
    actualBackground[3].texCoords = Vector2f(backgroundTextureSize.x, 0);

    return true;
};


void background::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const {

    states.texture = &backgroundTex;
    rtarget.draw(actualBackground, states);
}
