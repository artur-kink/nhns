#include "Window.hpp"

Window::Window():InterfaceElement(0, 0, 100, 100){
	isMoving = false;

    //Setup window background.
	background.setFillColor(sf::Color::Black);
	background.setSize(sf::Vector2f(100, 100));
	background.setPosition(0, 0);
	
    //Setup window layouts
    contentPanel.setPosition(0, 20);
    contentPanel.setSize(100, 80);
    
	title.setString(12, sf::Color::White, sf::Text::Bold, "Title");
	title.setPosition(2, 0);
	topBar.setSize(100, 20);
	topBar.add(&title);

	closeButton.setSize(16, 16);
	topBar.add(&closeButton);
    
    topBar.parent = this;
    contentPanel.parent = this;
    
    //Trap mouse clicks to capture window movement.
	trap(InterfaceEvent::LeftPressed | InterfaceEvent::LeftReleased);
}

bool Window::trapped(InterfaceEvent* event){
	if(event->source == &topBar || event->source == &title){
		if(event->type == InterfaceEvent::LeftPressed){
			isMoving = true;
		}else if(event->type == InterfaceEvent::LeftReleased){
			isMoving = false;
		}
		return true;
	}
	return false;
}

InterfaceElement* Window::collisionCheck(int x, int y){

    //Update window position if its being moved,
    //otherwise store as last mouse position.
	if(isMoving){
		setPosition(x - moveOffsetX, y - moveOffsetY);
	}else{
		moveOffsetX = x - rect.left;
		moveOffsetY = y - rect.top;
	}
    
    //We don't check for this until now to make sure the window can be repositioned if necessary above.
    if(!InterfaceElement::collisionCheck(x, y))
        return 0;
    
    //Check for top bar collision.
    InterfaceElement * element = topBar.collisionCheck(x - rect.left, y - rect.top);
    if(element)
        return element;
    
    //Check for window content collision.
    element = contentPanel.collisionCheck(x - rect.left, y - rect.top);
    if(element)
        return element;
    
    return this;
}

/**
 * Set size of window.
 */
void Window::setSize(int width, int height){
    InterfaceElement::setSize(width, height);
    background.setSize(sf::Vector2f(width, height));
	topBar.setSize(width, 20);
    closeButton.setPosition(width - 16, 0);
    contentPanel.setSize(width, height - 20);
    contentPanel.onResize(width, height - 20);
}

/** 
* Set window title.
*/
void Window::setTitle(std::string t){
	title.setString(t);
}

/** 
* Add elements to the window content panel.
*/
void Window::add(InterfaceElement* element){
    contentPanel.add(element);
}

void Window::update(unsigned int time){
    contentPanel.update(time);
}

void Window::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	states.transform *= sf::Transform().translate((float)rect.left, (float)rect.top);
    target.draw(background, states);
	target.draw(topBar, states);
	target.draw(contentPanel, states);
}

Window::~Window(){
    contentPanel.elements.clear();
}