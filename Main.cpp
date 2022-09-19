#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "tileRenderer.hpp"
#include "userInterface.hpp"
using namespace sf;

int main() {

    bool load = false;
    bool focus = false;
    bool cursorGrabbed = false;
    unsigned short UIHeight = 12;
    short scrollPos = 0;
    short layer = 2;
    short mouseHeight = 8;
    unsigned short addedTile = 2;
    //Required to differentiate UI drawing.  See userInterface.hpp for more details
    bool leftClicked;

    Vector2i tileFileResolution(640, 640);
    Vector2i tileSelectorWindowStart(514, 2);
    const Vector2i windowSize(612, 300);

    //Various click iterations which keep make the buttons work all the time.
    short focusIterations = 0;
    bool wasFocused = false;
    short grabIterations = 0;
    bool wasGrabbed = false;

    RenderWindow tileWindow(VideoMode(windowSize.x, windowSize.y), "TOSTE");
    tileWindow.setFramerateLimit(60);
    View tileView(Vector2f(306, 144), Vector2f(612, 288));
    View backgroundView(Vector2f(306, 150), Vector2f(612, 300));
    View userInterfaceView(Vector2f(306, 150), Vector2f(612, 300));


    Sprite cursor;

    std::string backgroundFileName;

    Sprite selectCursor;

    tileView.setViewport(sf::FloatRect(0.f, 0.04f, 1.f, 1.f));


    Texture cursorTexture;

    Vector2i cameraPos(0, 0);

    Vector2i mousePos(256, 156);

    tileRenderer map;

    tileSelector ts;

    UI userInterface(&map, &tileWindow);


    
    background deBackground(backgroundFileName, windowSize);

    if(backgroundFileName == std::string()) {
        #ifdef DEBUG
         std::cout << "NO BACKGROUND FILE PROVIDED\n";
        #endif
    }
    



    if(!cursorTexture.loadFromFile("Graphics/Cursor.png")) {
        std::cout << "ERROR FAILED TO LOAD CURSOR IMAGE FROM FILE\n";
        return 0;
    }

    cursor.setTexture(cursorTexture);

    Mouse::setPosition(mousePos);

    while (tileWindow.isOpen()) {



            if(tileWindow.hasFocus()) {

                //toggles trapping the mouse
                if (Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::G) && !wasGrabbed) {
                    cursorGrabbed = !cursorGrabbed;
                    wasGrabbed = true;
                    grabIterations = 0;
                } else if(grabIterations > 8) {
                    wasGrabbed = false;
                    grabIterations = 0;
                }else if(grabIterations < 9) {
                    grabIterations++;
                }
                

                tileWindow.setMouseCursorGrabbed(cursorGrabbed);



                //Toggles whether mouse is visible or custom cursor is visible
                if(Keyboard::isKeyPressed(Keyboard::Tab) && !wasFocused){
                    focus = !focus;
                    wasFocused = true;
                    focusIterations = 0;
                } else if(focusIterations > 8) {
                    wasFocused = false;
                    focusIterations = 0;
                } else if(focusIterations < 9){
                    focusIterations++;
                }

                tileWindow.setMouseCursorVisible(focus);

                leftClicked = userInterface.UIPeriodic();


                //Switch between layers
                if(Keyboard::isKeyPressed(Keyboard::Num1)) {
                    layer = 0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Num2)) {
                    layer = 1;
                }
                if(Keyboard::isKeyPressed(Keyboard::Num3)) {
                    layer = 2;
                }


                //Move view with arrow keys
                if(Keyboard::isKeyPressed(Keyboard::Up) && cameraPos.y > 15 || Keyboard::isKeyPressed(Keyboard::W) && cameraPos.y > 15) {
                    cameraPos.y = cameraPos.y - 16;
                }
                if(Keyboard::isKeyPressed(Keyboard::Down) && cameraPos.y < 1985 * tileSize || Keyboard::isKeyPressed(Keyboard::S) && cameraPos.y < 1985 * tileSize) {
                    cameraPos.y = cameraPos.y + 16;
                }
                if(Keyboard::isKeyPressed(Keyboard::Left) && cameraPos.x > 15 || Keyboard::isKeyPressed(Keyboard::A) && cameraPos.x > 15) {
                    cameraPos.x = cameraPos.x - 16;
                }
                if(Keyboard::isKeyPressed(Keyboard::Right) && cameraPos.x < 1985 * tileSize || Keyboard::isKeyPressed(Keyboard::D) && cameraPos.x < 1985 * tileSize) {
                    cameraPos.x = cameraPos.x + 16;

                }
                if(Keyboard::isKeyPressed(Keyboard::R)) {
                    map.convertToColide();
                }



                //Close window if required
                if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                    tileWindow.close();
                }



                //Quick Save tileMap
                if(Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S)) {
                    if(!map.saveTile(binarySavePath)) {
                        std::cout << "ERROR SAVING FILE, PLEASE TRY AGAIN AND MAKE SURE PROGRAM HAS PERMISSIONS\n";
                    }else {
                        std::cout << "FILE SAVED\n";
                    }
                }


                //Triggers a load event
                if(Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::L)) {
                    load = true;
                }


                //Creates a new map but does not save it.
                if(Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::N)) {
                    map.newMap();
                }

                if(Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::C)) {
                    map.showColides = !map.showColides;
                }


                mousePos = userInterface.mousePos;

                cursor.setPosition(mousePos.x, mousePos.y);


                #ifdef MOUSEDEBUG
                    std::cout << "Current Mouse Pos: " << Mouse::getPosition() << ", " << Mouse::getPosition() << std::endl;
                #endif

                //Checks what tile the mouse is on for the drawer
                if (leftClicked && mousePos.y > UIHeight && mousePos.x < tileSelectorWindowStart.x) {
                    #ifdef MOUSEDEBUG
                        std::cout << "Mouse position = " << mousePos.x << " " << mousePos.y << std::endl;
                    #endif
                    short height = (std::floor((mousePos.y  + cameraPos.y - UIHeight - mouseHeight)/ tileSize)); 
                    short width = (std::floor((mousePos.x + cameraPos.x)/ tileSize));
                    #ifdef MOUSEDEBUG
                        std::cout << "Width = " << width << " Height = " << height << std::endl;
                    #endif
                    map.tileMap[height][width][layer] = addedTile;
                    if (layer == 1 && addedTile != 1) {
                        map.collidableMap[height][width] = true;
                    } else if(layer == 1 && addedTile == 1) {
                        map.collidableMap[height][width] = false;
                    }
                }
            }

        Event event;
        while (tileWindow.pollEvent(event)) {
            if(event.type == Event::Closed) {
                tileWindow.close();
            }
            if(event.type == Event::MouseWheelScrolled){
                #ifdef MOUSEDEBUG
                    std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                #endif
                if(mousePos.x > tileSelectorWindowStart.x && event.mouseWheelScroll.delta < 0 || scrollPos > 0 && event.mouseWheelScroll.delta != 0) {
                    scrollPos = scrollPos - event.mouseWheelScroll.delta;
                    addedTile = addedTile - event.mouseWheelScroll.delta * 6;
                }
                if(addedTile > 1 && event.mouseWheelScroll.delta < 0 && mousePos.x < tileSelectorWindowStart.x ||  addedTile < 1600 && event.mouseWheelScroll.delta > 0 && mousePos.x < tileSelectorWindowStart.x) {
                    addedTile = addedTile + event.mouseWheelScroll.delta;
                }

            }
        }


        //Detects what tile is being selected in the selector
        if(mousePos.x > tileSelectorWindowStart.x && mousePos.y > UIHeight && leftClicked) {
            short tileHeight = std::floor((mousePos.y - tileSelectorWindowStart.y - UIHeight) / tileSize) ; 
            short tileWidth = std::floor((mousePos.x - tileSelectorWindowStart.x) / tileSize);
            #ifdef MOUSEDEBUG
                std::cout << "Mouse tilePosition: " << tileHeight << ", " << tileWidth << std::endl;
            #endif
            addedTile = (tileHeight * 6) + tileWidth + 1;
        }

        if(backgroundFileName != std::string()) {
            deBackground.set(cameraPos);
        }


        ts.tileSelect("Graphics/TilePallet.png", scrollPos, tileSelectorWindowStart, addedTile);

        //Loads the tileMap into the heap
        if (load) {
            if (!map.loadTile(binarySavePath)) {
                #ifdef DEBUG
                    std::cout << "ERROR FAILED TO LOAD MAP\n";
                #endif
            } else {
                std::cout << "Loaded from level.dat\n";
            }
            load = false;
        }

        if (!map.renderTile("Graphics/TilePallet.png", cameraPos)) {

                std::cout << "ERROR FAILED TO RENDER TILEMAP\n";

            return 0;
        }



        tileWindow.clear();


        tileWindow.setView(backgroundView);

        tileWindow.draw(deBackground);

        //Must come before userInterfaceView
        tileWindow.setView(tileView);

        tileWindow.draw(map);

        tileWindow.draw(ts);

        tileWindow.setView(userInterfaceView);

        tileWindow.draw(userInterface);

        if(!focus) {
            tileWindow.draw(cursor);
        }



        tileWindow.display();


    }
    return 0;
}
