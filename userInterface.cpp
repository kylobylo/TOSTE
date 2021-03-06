#include "userInterface.hpp"
using namespace sf;

UI::UI(tileRenderer* ptrTileRenderer, RenderWindow *window) {

    tileWindow = window;

    fileButton.setPosition(0, 0);
    fileButton.setText("File");

    editButton.setPosition(25, 0);
    editButton.setText("Edit");

    backgroundButton.setText("Background");

    newButton.setText("New");
    
    saveButton.setText("Save");


    loadButton.setText("Load");

    pTRender = ptrTileRenderer;

    fileButton.addButton(&saveButton);
    fileButton.addButton(&loadButton);
    fileButton.addButton(&newButton);
    editButton.addButton(&backgroundButton);



    UIBar.setPrimitiveType(Quads);
    UIBar.resize(4);

    UIBar[0].position = Vector2f(0.f, 0.f);
    UIBar[1].position = Vector2f(612.f, 0.f);
    UIBar[2].position = Vector2f(612.f, height);
    UIBar[3].position = Vector2f(0.f, height);

    UIBar[0].color = Color::White;
    UIBar[1].color = Color::White;
    UIBar[2].color = Color::White;
    UIBar[3].color = Color::White; 



};

bool UI::UIPeriodic(){

    mousePos.x = Mouse::getPosition(*tileWindow).x;
    mousePos.y = Mouse::getPosition(*tileWindow).y;

    pMousePos = &mousePos;

    //Buttons automatically open menus of UI items assigned to them.
    fileButton.buttonClicked(*pMousePos);
    editButton.buttonClicked(*pMousePos);
    if (loadButton.buttonClicked(*pMousePos) && fileButton.menuOpened) {
        pTRender->loadTile("level.dat");
        debouncer = 0;
        return false;
    } else if(saveButton.buttonClicked(*pMousePos) && fileButton.menuOpened) {
        pTRender->saveTile("level.dat");
        debouncer = 0;
        return false;
    } else if(newButton.buttonClicked(*pMousePos) && fileButton.menuOpened) {
        pTRender->newMap();
        debouncer = 0;
        return false;
    } else if(Mouse::isButtonPressed(Mouse::Left) && debouncer > 10) {
        return true;
    }

    debouncer++;

    return false;

}

void UI::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const {



    rtarget.draw(UIBar, states);
    rtarget.draw(fileButton);
    rtarget.draw(editButton);
};

