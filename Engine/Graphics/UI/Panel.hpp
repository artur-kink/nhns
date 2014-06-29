#ifndef _PANEL_
#define _PANEL_

#include <vector>
#include "InterfaceElement.hpp"

/** 
* A basic container for elements.
*/
class Panel:public InterfaceElement{
public:
    /** How the size and position of the panel acts. */
    enum FormatType{
        /** Size remains whatever it is set. */
        Static = 0,
        /** Panel stretches vertically. */
        VerticalStretch = 1,
        /** Panel stretches horizontally. */
        HorizontalStretch = 2,
        /** Panel keeps its distance from the right constant. */
        BindRight = 4,
        /** Panel keeps its distance from the bottom constant. */
        BindBottom = 8
    };

protected:
    /** Format type of this Panel. */
     int formatType;

public:
    /** List of interface elements within this Panel. */
    std::vector<InterfaceElement*> interfaceElements;

	Panel();
    Panel(int x, int y, int w, int h, int format);

    virtual void onResize(int w, int h);
    virtual void add(InterfaceElement* element);
    virtual void remove(InterfaceElement* element);
    virtual void clear();
    virtual void update(unsigned int time);
    virtual InterfaceElement* collisionCheck(int x, int y);

    virtual void draw(RenderTarget* target, RenderObject obj) const;

    virtual ~Panel();
};

#endif