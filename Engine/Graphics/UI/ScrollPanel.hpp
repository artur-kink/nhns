#ifndef _SCROLLPANEL_
#define _SCROLLPANEL_

#include "Panel.hpp"

/** 
* A scrollable container for elements.
*/
class ScrollPanel: public Panel{
private:
    
    /** 
    * Scroll bar in a scroll panel.
    */
    class ScrollBar: public InterfaceElement{
    public:
        
        /** 
        * Scroll bar rectangle.
        */
        sf::RectangleShape scrollBar;
        
        /** 
        * Scroll bar area.
        */
        sf::RectangleShape background;
        
        ScrollBar();
        void setSize(int width, int height, int scrollerHeight);
        void setBarPosition(int y);
        void setBarDown(bool value);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
     };

protected:

    /** 
    * Size of the entire scrollable area.
    */
    sf::Vector2i scrollArea;
    
    /** 
    * Current y scroll offset.
    */
    int yScroll;

    /**
    * A render of the scroll area.
    */
    sf::RenderTexture* scrollTexture;
    
    /**
    * Sprite view of the current scroll view.
    */
    sf::Sprite scrollSprite;

	/** 
	* The scroll panel's scroll bar.
	*/
	ScrollBar scrollBar;

	/** 
	* Is the mouse currently inside scroll bar.
	*/
	bool inScroll;
	
	/** 
	* Is the panel currently being scrolled.
	*/
	bool isScrolling;
public:
	ScrollPanel();
    ScrollPanel(int x, int y, int width, int height, int type);

    void scrollChanged();
    void updateScrollView();
    int getScroll();
    void setScrollBottom();

    virtual bool trapped(InterfaceEvent* event);
    
    virtual void add(InterfaceElement* element);
    virtual InterfaceElement* collisionCheck(int x, int y);
    virtual void onResize(int width, int height);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual ~ScrollPanel();
};

#endif