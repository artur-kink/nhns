#include "ScrollPanel.hpp"

/** 
* Create a scroll bar with temporary parameters.
*/
ScrollPanel::ScrollBar::ScrollBar():InterfaceElement(0, 0, 0, 0){
    sf::Color bgColor = sf::Color(60,60,60,55);
    background.setFillColor(bgColor);
    setBarDown(false);
}

/** 
* Set the bar to be pressed up/down. Changes bar color.
*/
void ScrollPanel::ScrollBar::setBarDown(bool value){
    if(value){
        sf::Color barColor = sf::Color(100, 100, 100, 200);
        scrollBar.setFillColor(barColor);
    }else{
        sf::Color barColor = sf::Color(150, 150, 150, 200);
        scrollBar.setFillColor(barColor);
    }
}

void ScrollPanel::ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= sf::Transform().translate((float)rect.left, (float)rect.top);
    target.draw(background, states);
    target.draw(scrollBar, states);
}

/** 
* Set size of scroll bar area and scroll bar.
*/
void ScrollPanel::ScrollBar::setSize(int width, int height, int scrollerHeight){
    rect.width = width;
    rect.height = height;
    scrollBar.setSize(sf::Vector2f(width, scrollerHeight));
    background.setSize(sf::Vector2f(width, height));
}

/** 
* Set y position of bar.
*/
void ScrollPanel::ScrollBar::setBarPosition(int y){
    scrollBar.setPosition(0, y);
    if(scrollBar.getPosition().y < 0)
        scrollBar.setPosition(0,0);
    else if(scrollBar.getPosition().y + scrollBar.getSize().y > rect.height )
        scrollBar.setPosition(0, rect.height - scrollBar.getSize().y - rect.top);
}

/** 
* Create new scroll panel.
*/
ScrollPanel::ScrollPanel(int x, int y, int width, int height, int type):Panel(x, y, width, height, type) {
    scrollBar.setSize(10, rect.height, 0);
    scrollBar.rect.left = rect.width - 10;
    scrollBar.parent = this;
    scrollBar.visible = false;
    yScroll = 0;
    scrollArea.x = rect.width;
    scrollArea.y = 0;
    scrollTexture = 0;
    isScrolling = false;
    
    trap(InterfaceEvent::LeftPressed |
            InterfaceEvent::LeftReleased |
            InterfaceEvent::MouseWheelMoved);
}

ScrollPanel::ScrollPanel():Panel(){
	scrollBar.setSize(10, rect.height, 0);
	scrollBar.rect.left = rect.width - 10;
    scrollBar.parent = this;
    scrollBar.visible = false;
	yScroll = 0;
    scrollArea.x = rect.width;
    scrollArea.y = 0;
    scrollTexture = 0;
    isScrolling = false;
    formatType = Panel::Static;
    
    trap(InterfaceEvent::LeftPressed |
            InterfaceEvent::LeftReleased |
            InterfaceEvent::MouseWheelMoved);
}

/** 
* Redraw scroll image.
*/
void ScrollPanel::updateScrollView(){
    //If a rendered scroll area texture exists, delete it.
    if(scrollTexture != 0){
        delete scrollTexture;
    }
    
    //Calculate the y rectangle of scroll area to draw.
    int maxY = 0;
    for(unsigned int i = 0; i < interfaceElements.size(); i++){
        if(interfaceElements.at(i)->visible){
            if(interfaceElements.at(i)->rect.top + interfaceElements.at(i)->rect.height > maxY)
                maxY = interfaceElements.at(i)->rect.top + interfaceElements.at(i)->rect.height;
        }
    }
    scrollArea.y = maxY + rect.top + 3;
    
    //Setup scroll bar.
    scrollBar.visible = scrollArea.y > rect.height;
    if(!scrollBar.visible){
        yScroll = 0;
        scrollArea.x = rect.width;
    }else{
        scrollArea.x = rect.width - scrollBar.rect.width + 1;
        scrollBar.setSize(10, rect.height, ((float)rect.height / (float)scrollArea.y)*rect.height);
        scrollBar.setBarPosition(((float)(yScroll)/((float)scrollArea.y))*((float)rect.height));
    }

    scrollChanged();
    
    //Create and render scroll area image.
    scrollTexture = new sf::RenderTexture();
    scrollTexture->create(scrollArea.x, scrollArea.y, true);
    scrollTexture->clear(sf::Color::Transparent);

    Panel::draw(*scrollTexture, sf::RenderStates::Default);

    scrollTexture->display();

    scrollSprite.setTexture(scrollTexture->getTexture(), true);
    scrollSprite.setPosition(0, 0);
    scrollSprite.setTextureRect(sf::IntRect(0, yScroll, rect.width, rect.height));
}

/** 
* Get the current vertical scroll position.
* @return y value of current scroll position.
*/
int ScrollPanel::getScroll(){
    return yScroll;
}

/** 
* Set the scroll panel to show bottom of scroll area.
*/
void ScrollPanel::setScrollBottom(){
    yScroll = scrollArea.y - rect.height + rect.top;
    scrollBar.setBarPosition(((float)(yScroll)/((float)scrollArea.y - rect.height))*((float)rect.height));
    scrollSprite.setTextureRect(sf::IntRect(0, yScroll, rect.width, rect.height));
}

InterfaceElement* ScrollPanel::collisionCheck(int x, int y){
    if(!InterfaceElement::collisionCheck(x, y))
        return 0;
    
    //Update scroll position if necessary.
    if(isScrolling){
        yScroll = ((float)(y-rect.top-scrollBar.scrollBar.getSize().y/2)/((float)rect.height))*(float)scrollArea.y;
        scrollChanged();
    }
    
    if(scrollBar.collisionCheck(x, y)){
        return &scrollBar;
    }
    
    //Check if collision occurs with any panel elements.
    InterfaceElement* scrollViewCollision = Panel::collisionCheck(x, y + yScroll - rect.top);
    if(scrollViewCollision)
        return scrollViewCollision;
    
    return this;
}

/** 
* Called when the scroll position has been changed. Changes draw view rect.
*/
void ScrollPanel::scrollChanged(){

    if(yScroll > scrollArea.y - rect.height + rect.top){
        yScroll = scrollArea.y - rect.height + rect.top;
    }else if(yScroll < 0){
        yScroll = 0;
        scrollBar.setBarPosition(0);
    }
    
    scrollBar.setBarPosition(((float)(yScroll)/((float)scrollArea.y))*((float)rect.height));
    scrollSprite.setTextureRect(sf::IntRect(0, yScroll, rect.width, rect.height));
}

bool ScrollPanel::trapped(InterfaceEvent* event){
    if(event->source == &scrollBar && scrollBar.visible){
        //Handle scroll bar events
        if(event->type == InterfaceEvent::LeftPressed){
            isScrolling = true;
            scrollBar.setBarDown(isScrolling);
        }else if(event->type == InterfaceEvent::LeftReleased){
            isScrolling = false;
            scrollBar.setBarDown(isScrolling);
        }else if(event->type == InterfaceEvent::MouseWheelMoved){
            if(scrollBar.visible){
                yScroll -= (scrollArea.y / 20)*(*(int*)event->args);
                scrollChanged();
            }
        }
        return true;
    }else if(event->type == InterfaceEvent::MouseWheelMoved && scrollBar.visible){
        //If mouse wheel is scrolled anywhere in this panel apply scroll.
        yScroll -= (scrollArea.y / 20)*(*(int*)event->args);
        scrollChanged();
        return true;
    }
    return false;
}

void ScrollPanel::add(InterfaceElement* element){
    Panel::add(element);
}

void ScrollPanel::onResize(int width, int height){
    Panel::onResize(width, height);
    
    scrollBar.setSize(10, rect.height, 0);
	scrollBar.rect.left = rect.width - 10;
    scrollBar.parent = this;
    scrollBar.visible = false;
	yScroll = 0;
    scrollArea.x = rect.width;
    scrollArea.y = 0;
    updateScrollView();
}

void ScrollPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= sf::Transform().translate((float)rect.left, (float)rect.top);
    target.draw(scrollSprite, states);
    if(scrollBar.visible) target.draw(scrollBar, states);
}


ScrollPanel::~ScrollPanel(){
    delete scrollTexture;
    scrollTexture = 0;
}