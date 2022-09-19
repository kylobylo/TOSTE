#include "Button.hpp"
using namespace sf;

Button::Button(unsigned int inX, unsigned int inY, std::string inContents) {
    
    fontSize = height - std::floor(height/6);
    boundingBox = contents.getGlobalBounds();


    #ifdef UIDEBUG
        std::cout << "Bounding box of Button is at: " << boundingBox.left << ", " << boundingBox.top << std::endl;
    #endif
    
    this->setPosition(x,y);
    contents.setString(inContents);
    if(!font.loadFromFile(fontFile)) {
        std::cout << "ERROR: Failed To Load File From Font!\n";
    }

    contents.setFont(font);
    contents.setCharacterSize(fontSize);
    contents.setFillColor(Color::Black);

    subMenu.setPrimitiveType(Quads);
    subMenu.resize(4);


};

Button::Button(sf::Vector2i inPos, std::string inContents) {

    fontSize = height - std::floor(height/6);
    boundingBox = contents.getGlobalBounds();
    
    this->setPosition(inPos);
    contents.setString(inContents);
    if(!font.loadFromFile(fontFile)) {
        std::cout << "ERROR: Failed To Load File From Font!\n";
    }

    contents.setFont(font);
    contents.setCharacterSize(fontSize);
    contents.setFillColor(Color::Black);

    subMenu.setPrimitiveType(Quads);
    subMenu.resize(4);

};

void Button::addButton(Button *ptr) {

    boundingBox = contents.getGlobalBounds();



    #ifdef UIDEBUG
        std::cout << "Button added to submenu\n";
    #endif
    

    #ifdef UIDEBUG
        std::cout << "subButtons size: " << subButtons.size() << std::endl;
    #endif
    

    ptr->setPosition(boundingBox.left, (height - std::floor(height / 6)) * (subButtons.size() + 1));

    short widthFit = 0;

    subButtons.push_back(*ptr);

    if(subMenuWidth < ptr->boundingBox.width) {
        subMenuWidth += ptr->boundingBox.width - subMenuWidth + 5/*I'll put this here for some space on the end*/;
    }

    subMenu[0].position = Vector2f(boundingBox.left - 1, height);
    #ifdef UIDEBUG
        std::cout << "bounding box width: " << ptr->boundingBox.width << std::endl;
        std::cout << "subMenu[0] position: " << subMenu[0].position.x << ", " << subMenu[0].position.y << std::endl;
    #endif
    subMenu[1].position = Vector2f(boundingBox.left - 1, (subButtons.size() * this->boundingBox.height) + height + (subButtons.size() *std::ceil(height / 6)));
    #ifdef UIDEBUG
        std::cout << "subMenu[1] position: " << subMenu[1].position.x << ", " << subMenu[1].position.y << std::endl;
    #endif
    subMenu[2].position = Vector2f(subMenuWidth + (boundingBox.left - 1) + widthFit, (subButtons.size() * this->boundingBox.height) + height + (subButtons.size() * std::ceil(height / 6)));
    #ifdef UIDEBUG
        std::cout << "subMenu[2] position: " << subMenu[2].position.x << ", " << subMenu[2].position.y << std::endl;
    #endif
    subMenu[3].position = Vector2f(subMenuWidth + (boundingBox.left - 1) + widthFit, height);
    #ifdef UIDEBUG
        std::cout << "subMenu[3] position: " << subMenu[3].position.x << ", " << subMenu[3].position.y << std::endl;
    #endif

    subMenu[0].color = Color::White;
    subMenu[1].color = Color::White;
    subMenu[2].color = Color::White;
    subMenu[3].color = Color::White;

};



void Button::move(int inX, int inY) {

    x = x + inX;
    y = y + inY;
    contents.setPosition(x, y);

    boundingBox = contents.getGlobalBounds();
};



void Button::move(Vector2i inPos) {

    x = x + inPos.x;
    y = y + inPos.y;
    contents.setPosition(x, y);

    boundingBox = contents.getGlobalBounds();
};



void Button::setText(std::string inContents) {

    contents.setString(inContents);

};

void Button::setPosition(int inX, int inY) {



    #ifdef UIDEBUG
        std::cout << "Bounding box width: " << boundingBox.width << ", Bounding box height: " << boundingBox.height << std::endl;
    #endif

    x = inX;
    y = inY;
    contents.setPosition(x, y);
    boundingBox = contents.getGlobalBounds();
};

void Button::setPosition(Vector2i inPos) {

    x = inPos.x;
    y = inPos.y;
    contents.setPosition(x, y);
        boundingBox = contents.getGlobalBounds();
};

Button::Button() {
    fontSize = height - std::floor(height/6);
    if(!font.loadFromFile(fontFile)) {
        std::cout << "ERROR: Failed To Load File From Font!\n";
    }

    contents.setFont(font);
    contents.setCharacterSize(fontSize);
    contents.setFillColor(Color::Black);

    subMenu.setPrimitiveType(Quads);
    subMenu.resize(4);
};

void Button::draw(sf::RenderTarget& rtarget, sf::RenderStates states) const {

    states.texture = &font.getTexture(fontSize);

    VertexArray *ptr;

    if(menuOpened) {

        rtarget.draw(subMenu, states);

        for(auto it = subButtons.begin(); it != subButtons.end(); ++it) {

            rtarget.draw(*it);
        }

    }
    

    rtarget.draw(contents, states);


};

bool Button::buttonClicked(Vector2i mousePos) {
    if(boundingBox.contains(mousePos.x, mousePos.y) && Mouse::isButtonPressed(Mouse::Left) && !wasClicked) {
        #ifdef UIDEBUG
            std::cout << "Button pressed\n";
        #endif
            menuOpened = !menuOpened;
            wasClicked = true;
            clickedIterations = 0;
        
        return true;
    } else if(clickedIterations > 8) {

        wasClicked = false;
        clickedIterations = 0;

        return false;

    }else {
        clickedIterations++;

        return false;
    }

};

Vector2i Button::getCenter() {
    boundingBox = contents.getGlobalBounds();
    Vector2i fileButtonCenter;
    #ifdef UIDEBUG
        std::cout << "Bounding box left: " << boundingBox.left << ", Bounding Box top: " << boundingBox.top <<std::endl;
    #endif
    fileButtonCenter.x = boundingBox.left + std::floor(boundingBox.width / 2);
    fileButtonCenter.y = boundingBox.top + std::floor(boundingBox.height / 2);
    #ifdef UIDEBUG
        std::cout << "fileButtonCenter: " << fileButtonCenter.x << ", " << fileButtonCenter.y << std::endl;
    #endif
    return fileButtonCenter;
};

