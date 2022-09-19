#include "tileRenderer.hpp"
#include <math.h>
using namespace sf;

bool tileRenderer::renderTile(std::string fileName, sf::Vector2i cameraPos) {
    
    //Calls cameraPos so we grab the correct section of tileMap as it helps performance considering tileMap is 12 million tiles in capacity
    this->windowPos(cameraPos);

    this->showCollidables();
    
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

                //Used to transfer from row to row on texture file
                unsigned short roundRow = std::floor(((level[h][w][0] - 1) / 40));

                //Assign vectors to draw lines between
                foreArray[0].position = Vector2f(tileSize * w, tileSize * h);
                foreArray[1].position = Vector2f(tileSize * (w + 1), tileSize * h);
                foreArray[2].position = Vector2f(tileSize * (w + 1), tileSize * (h + 1));
                foreArray[3].position = Vector2f(tileSize * w, tileSize * (h + 1));


                //Assign corners of textures to corners of tiles
                foreArray[0].texCoords = Vector2f(((level[h][w][0] - 1) % 40) * tileSize, 0.f + (tileSize * roundRow));
                foreArray[1].texCoords = Vector2f((((level[h][w][0] - 1) % 40) * tileSize) + tileSize, 0.f + (tileSize * roundRow));
                foreArray[2].texCoords = Vector2f((((level[h][w][0] - 1) % 40) * tileSize) + tileSize, tileSize + (tileSize * roundRow));
                foreArray[3].texCoords = Vector2f(((level[h][w][0] - 1) % 40) * tileSize, tileSize + (tileSize * roundRow));

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


                midArray[0].position = Vector2f(tileSize * w, tileSize * h);
                midArray[1].position = Vector2f(tileSize * (w + 1), tileSize * h);
                midArray[2].position = Vector2f(tileSize * (w + 1), tileSize * (h + 1));
                midArray[3].position = Vector2f(tileSize * w, tileSize * (h + 1));


                midArray[0].texCoords = Vector2f(((level[h][w][1] - 1) % 40) * tileSize, 0.f + (tileSize * roundRow));
                midArray[1].texCoords = Vector2f((((level[h][w][1] - 1) % 40) * tileSize) + tileSize, 0.f + (tileSize * roundRow));
                midArray[2].texCoords = Vector2f((((level[h][w][1] - 1) % 40) * tileSize) + tileSize, tileSize + (tileSize * roundRow));
                midArray[3].texCoords = Vector2f(((level[h][w][1] - 1) % 40) * tileSize, tileSize + (tileSize * roundRow));

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


                backArray[0].position = Vector2f(tileSize * w, tileSize * h);
                backArray[1].position = Vector2f(tileSize * (w + 1), tileSize * h);
                backArray[2].position = Vector2f(tileSize * (w + 1), tileSize * (h + 1));
                backArray[3].position = Vector2f(tileSize * w, tileSize * (h + 1));



                backArray[0].texCoords = Vector2f(((level[h][w][2] - 1) % 40) * tileSize, 0.f + (tileSize * roundRow));
                backArray[1].texCoords = Vector2f((((level[h][w][2] - 1) % 40) * tileSize) + tileSize, 0.f + (tileSize * roundRow));
                backArray[2].texCoords = Vector2f((((level[h][w][2] - 1) % 40) * tileSize) + tileSize, tileSize + (tileSize * roundRow));
                backArray[3].texCoords = Vector2f(((level[h][w][2] - 1) % 40) * tileSize, tileSize + (tileSize * roundRow));
            }
        }
    }
    

    return true;
};

void tileRenderer::showCollidables() {
    tops.setPrimitiveType(Lines);
    tops.resize(2 * height * width);
    rights.setPrimitiveType(Lines);
    rights.resize(2 * height * width);
    bottoms.setPrimitiveType(Lines);
    bottoms.resize(2 * height * width);
    lefts.setPrimitiveType(Lines);
    lefts.resize(2 * height * width);

    for(short h = 0; h < height; h++) {
        for(short w = 0; w < width; w++) {

            Vertex* renTops = &tops[(w + h * width) * 2];
            Vertex* renRights = &rights[(w + h * width) * 2];
            Vertex* renBottoms = &bottoms[(w + h * width) * 2];
            Vertex* renLefts = &lefts[(w + h * width) * 2];

            renTops[0].position = Vector2f(w * tileSize, h * tileSize);
            renTops[1].position = Vector2f(w * tileSize + tileSize, h * tileSize);

            renRights[0].position = Vector2f(w * tileSize + tileSize, h * tileSize);
            renRights[1].position = Vector2f(w * tileSize + tileSize, h * tileSize + tileSize);

            renBottoms[0].position = Vector2f(w * tileSize + tileSize, h * tileSize + tileSize);
            renBottoms[1].position = Vector2f(w * tileSize, h * tileSize + tileSize);

            renLefts[0].position = Vector2f(w * tileSize, h * tileSize + tileSize);
            renLefts[1].position = Vector2f(w * tileSize, h * tileSize);
                
            if(collidableLevel[h][w] == true) {

                renTops[0].color = Color::Blue;
                renTops[1].color = Color::Blue;

                renRights[0].color = Color::Blue;
                renRights[1].color = Color::Blue;

                renBottoms[0].color = Color::Blue;
                renBottoms[1].color = Color::Blue;

                renLefts[0].color = Color::Blue;
                renLefts[1].color = Color::Blue;


            } else {
                renTops[0].color = Color::Transparent;
                renTops[1].color = Color::Transparent;

                renRights[0].color = Color::Transparent;
                renRights[1].color = Color::Transparent;

                renBottoms[0].color = Color::Transparent;
                renBottoms[1].color = Color::Transparent;

                renLefts[0].color = Color::Transparent;
                renLefts[1].color = Color::Transparent;
            }
        }
    }

}



void tileRenderer::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const  {

    //Draws each layer in order so the last layer to be drawn is on top

    states.texture = &tileTex;
    rtarget.draw(backGround, states);
    rtarget.draw(middleGround, states);
    rtarget.draw(foreGround, states); 
    if (showColides == true) { 
        rtarget.draw(tops);
        rtarget.draw(lefts);
        rtarget.draw(rights);
        rtarget.draw(bottoms);
    }

};

bool tileRenderer::saveToPNG() {
    RenderTexture rtarget;
    if(!rtarget.create(mapHeight, mapWidth)){
        std::cout << "ERROR FAILED TO CREATE TEXTURE\n";
        return false;
    }

    
    rtarget.draw(*this);
    rtarget.display();
    rtarget.getTexture().copyToImage().saveToFile(pngSavePath);

    return true;
}

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
        for(int h = 0; h < mapHeight; h++) {
            fs.read((char*)(collidableMap[h]), sizeof(*collidableMap));
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


void tileRenderer::convertToColide() {

    for(int h = 0; h < mapHeight; h++) {
        for(int w = 0; w < mapWidth; w++) {
            if(tileMap[h][w][1] == 1) {
                collidableMap[h][w] = false;
            } else {
                collidableMap[h][w] = true;
                #ifdef DEBUG
                std::cout << collidableMap[h][w];
                #endif
            }


        }
    }



}


bool tileRenderer::saveTile(std::string tilemapFile) {

    std::fstream fs;

    fs.open(tilemapFile, std::ios::out | std::ios::binary);
    
    //Check for file errors
    if(fs.is_open()) {

        //Iterates through height due to Dimension class
        for(int h = 0; h < mapHeight; h++) {
            fs.write((char*)(tileMap[h]), sizeof(*tileMap));
        }
        for(int h = 0; h < mapHeight; h++) {
             fs.write((char*)(collidableMap[h]), sizeof(*collidableMap));
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
                collidableMap[h][w] = false;
            }
        }
    }
    for(int h = 0; h < height; h++) {
        for(int w = 0; w < width; w++) {
            for(int t = 0; t < 3; t++) {
                level[h][w][t] = 1;
                collidableLevel[h][w] =false;
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

bool tileRenderer::windowPos(sf::Vector2i cameraPos) {

    int y = (std::floor(cameraPos.y / tileSize)); 
    int x = (std::floor(cameraPos.x / tileSize));

    for(int h = y, l = 0; h < y + height; h++, l++) {
        for(int w = x, r = 0; w < x + width; w++, r++) {
            for(int t = 0; t < 3; t++) {
                level[l][r][t] = tileMap[h][w][t];
                collidableLevel[l][r] = collidableMap[h][w];
            }
        }
    }
    return true;
};

bool tileSelector::tileSelect(std::string fileName, short scrollPos, Vector2i windowStart, int tileNumber) {
    tilesOfFile.setPrimitiveType(Quads);
    tilesOfFile.resize(17 * 6 * 4);
    height = 17;
    width = 6;

    this->selectTile(tileNumber, scrollPos, windowStart);

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


            tileArray[0].position = Vector2f(w * tileSize + windowStart.x, h * tileSize + windowStart.y);
            tileArray[1].position = Vector2f(w * tileSize + windowStart.x, h * tileSize + tileSize + windowStart.y);
            tileArray[2].position = Vector2f(w * tileSize + tileSize + windowStart.x, h * tileSize + tileSize + windowStart.y);
            tileArray[3].position = Vector2f(w * tileSize + tileSize + windowStart.x, h * tileSize + windowStart.y);

            tileArray[0].texCoords = Vector2f(textureColumn * tileSize, textureRow * tileSize);
            tileArray[1].texCoords = Vector2f(textureColumn * tileSize, textureRow * tileSize + tileSize);
            tileArray[2].texCoords = Vector2f(textureColumn * tileSize + tileSize, textureRow * tileSize + tileSize);
            tileArray[3].texCoords = Vector2f(textureColumn * tileSize + tileSize, textureRow * tileSize);
        }

    }

    return true;

};


int tileSelector::selectTile(int tileNumber, short scrollPos, sf::Vector2i windowStart) {

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

    tileBoxTop[0].position = Vector2f((tileNumber % width) * tileSize + windowStart.x , h * tileSize + windowStart.y);
    tileBoxLeft[0].position = Vector2f((tileNumber % width) * tileSize + windowStart.x , h * tileSize + windowStart.y);
    
    #ifdef SELECTORDEBUG
        std::cout << "One highlight point allocated" << std::endl;
    #endif
    tileBoxLeft[1].position = Vector2f((tileNumber % width) * tileSize + windowStart.x, (h * tileSize) + tileSize + windowStart.y);
    tileBoxBottom[0].position = Vector2f((tileNumber % width) * tileSize + windowStart.x, (h * tileSize) + tileSize + windowStart.y);
    #ifdef SELECTORDEBUG
        std::cout << "Two highlight points allocated" << std::endl;
    #endif
    tileBoxBottom[1].position = Vector2f(((tileNumber % width) * tileSize) +  tileSize + windowStart.x, (h * tileSize) + tileSize + windowStart.y);
    tileBoxRight[1].position = Vector2f(((tileNumber % width) * tileSize) + tileSize + windowStart.x, (h * tileSize) + tileSize + windowStart.y);
    #ifdef SELECTORDEBUG
        std::cout << "Three highlight points allocated" << std::endl;
    #endif
    tileBoxTop[1].position = Vector2f(((tileNumber % width) * tileSize) +  tileSize + windowStart.x, h * tileSize + windowStart.y);
    tileBoxRight[0].position = Vector2f(((tileNumber % width) * tileSize) + tileSize + windowStart.x, h * tileSize + windowStart.y);


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
