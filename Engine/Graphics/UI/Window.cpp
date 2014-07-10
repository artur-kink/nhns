#include "Window.hpp"

Window::Window():InterfaceElement(0, 0, 100, 100){
	isMoving = false;

    //Setup window background.
	background.color = Color::Red;
	background.setSize(100, 100);
	background.setPosition(0, 0);
	
    //Setup window layouts
    contentPanel.setPosition(0, 20);
    contentPanel.setSize(100, 80);
    
	title.setString(12, Color::White, "Title");
	title.setPosition(2, 0);
	topBar.setSize(100, 20);
	topBar.add(&title);
    
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
		moveOffsetX = x - this->x;
		moveOffsetY = y - this->y;
	}
    
    //We don't check for this until now to make sure the window can be repositioned if necessary above.
    if(!InterfaceElement::collisionCheck(x, y))
        return 0;
    
    //Check for top bar collision.
    InterfaceElement * element = topBar.collisionCheck(x - this->x, y - this->y);
    if(element)
        return element;
    
    //Check for window content collision.
    element = contentPanel.collisionCheck(x - this->y, y - this->x);
    if(element)
        return element;
    
    return this;
}

/**
 * Set size of window.
 */
void Window::setSize(int width, int height){
    InterfaceElement::setSize(width, height);
    background.setSize(width, height);
	topBar.setSize(width, 20);

    contentPanel.setSize(width, height - 20);
    contentPanel.onResize(width, height - 20);
}

/** 
* Set window title.
*/
void Window::setTitle(std::string t){
	title.setString(t.c_str());
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

void Window::draw(RenderTarget* target, RenderObject obj) const{
    MatrixTransformation::translate(obj, x, y);
    background.draw(target, obj);
    topBar.draw(target, obj);
    contentPanel.draw(target, obj);
}

Window::~Window(){
    contentPanel.clear();
}