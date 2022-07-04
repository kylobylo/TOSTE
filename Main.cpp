#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "tileRenderer.hpp"
#include "userInterface.hpp"
using namespace sf;

int main() {

    bool load = true;
    bool focus = false;
    bool cursorGrabbed = false;
    unsigned short UIHeight = 12;
    short scrollPos = 0;
    short layer = 2;
    unsigned short addedTile = 2;
    sf::Clock clock;
    Vector2i tileFileResolution(640, 640);
    Vector2i tileSelectorWindowStart(514, 2);

    //Various click iterations which keep make the buttons work all the time.
    short focusIterations;
    bool wasFocused = false;
    short grabIterations;
    bool wasGrabbed = false;

    RenderWindow tileWindow(VideoMode(612, 300), "Tilemap editor");
    tileWindow.setFramerateLimit(60);
    View tileView(Vector2f(306, 144), Vector2f(612, 288));
    View userInterfaceView(Vector2f(306, 150), Vector2f(612, 300));


    Sprite cursor;

    Sprite selectCursor;

    tileView.setViewport(sf::FloatRect(0.f, 0.04f, 1.f, 1.f));


    Texture cursorTexture;

    Vector2i cameraPos(0, 0);

    Vector2i tileSize(16, 16);

    Vector2i mousePos(256, 156);

    tileRenderer map;

    tileSelector ts;

    UI userInterface(&map);




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
                if(Keyboard::isKeyPressed(Keyboard::Down) && cameraPos.y < 1985 * tileSize.y || Keyboard::isKeyPressed(Keyboard::S) && cameraPos.y < 1985 * tileSize.y) {
                    cameraPos.y = cameraPos.y + 16;
                }
                if(Keyboard::isKeyPressed(Keyboard::Left) && cameraPos.x > 15 || Keyboard::isKeyPressed(Keyboard::A) && cameraPos.x > 15) {
                    cameraPos.x = cameraPos.x - 16;
                }
                if(Keyboard::isKeyPressed(Keyboard::Right) && cameraPos.x < 1985 * tileSize.x || Keyboard::isKeyPressed(Keyboard::D) && cameraPos.x < 1985 * tileSize.x) {
                    cameraPos.x = cameraPos.x + 16;

                }



                //Close window if required
                if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                    tileWindow.close();
                }



                //Quick Save tileMap
                if(Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S)) {
                    if(!map.saveTile("level.dat")) {
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

                mousePos.x = Mouse::getPosition(tileWindow).x;
                mousePos.y = Mouse::getPosition(tileWindow).y;

                cursor.setPosition(mousePos.x, mousePos.y);


                #ifdef MOUSEDEBUG
                    std::cout << "Current Mouse Pos: " << Mouse::getPosition().x << ", " << Mouse::getPosition().y << std::endl;
                #endif

                //Checks what tile the mouse is on
                if (Mouse::isButtonPressed(Mouse::Left) && mousePos.y > UIHeight && mousePos.x < tileSelectorWindowStart.x) {
                    #ifdef MOUSEDEBUG
                        std::cout << "Mouse position = " << mousePos.x << " " << mousePos.y << std::endl;
                    #endif
                    short height = (std::floor((mousePos.y  + cameraPos.y - UIHeight)/ tileSize.y)); 
                    short width = (std::floor((mousePos.x + cameraPos.x)/ tileSize.x));
                    #ifdef MOUSEDEBUG
                        std::cout << "Width = " << width << " Height = " << height << std::endl;
                    #endif
                    map.tileMap[height][width][layer] = addedTile;
                }
            }

        userInterface.UIPeriodic(&mousePos);



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

        if(mousePos.x > tileSelectorWindowStart.x && mousePos.y > UIHeight && Mouse::isButtonPressed(Mouse::Left)) {
            short tileHeight = std::floor((mousePos.y - tileSelectorWindowStart.y - UIHeight) / tileSize.y) ; 
            short tileWidth = std::floor((mousePos.x - tileSelectorWindowStart.x) / tileSize.x);
            #ifdef MOUSEDEBUG
                std::cout << "Mouse tilePosition: " << tileHeight << ", " << tileWidth << std::endl;
            #endif
            addedTile = (tileHeight * 6) + tileWidth + 1;
        }




        ts.tileSelect("Graphics/fakeTilePallet.png", tileSize, scrollPos, tileSelectorWindowStart, addedTile);

        //Loads the tileMap into the heap
        if (load) {
            if (!map.loadTile("level.dat")) {
                #ifdef DEBUG
                    std::cout << "ERROR FAILED TO LOAD MAP\n";
                #endif
                return 0;
            } else {
                std::cout << "Loaded from level.dat\n";
            }
            load = false;
        }

        if (!map.renderTile("Graphics/fakeTilePallet.png", tileSize, cameraPos)) {

                std::cout << "ERROR FAILED TO RENDER TILEMAP\n";

            return 0;
        }



        tileWindow.clear();


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