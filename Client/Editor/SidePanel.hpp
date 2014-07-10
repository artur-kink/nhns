#ifndef _SIDEPANEL_
#define	_SIDEPANEL_

#include "Graphics/UI/UI.hpp"

class SidePanel:public Panel{
public:
    Rectangle bg;
    Label headerLabel;
    TextBox mapName;

    SidePanel();
    virtual void onResize(int w, int h);
};

#endif

