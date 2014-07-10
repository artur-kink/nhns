#ifndef _TEXTBOX_
#define _TEXTBOX_

#include "InterfaceElement.hpp"
#include "KeyboardElement.hpp"
#include "Label.hpp"
#include "Utilities/TandemTimer.hpp"

/**
 * A textbox is an input field that binds the keyboard.
 */
class TextBox:public Label, public KeyboardElement{
protected:

    /** Is the cursor location | being shown. */
    bool hasCursor;

    /** Index of the cursor in the string. */
    byte cursorIndex;

    /**
    * Time since last cursor switch.
    */
    unsigned int cursorTimer;

    /**
    * Time since last special key input. (Arrow keys)
    */
    TandemTimer keyboardTimer;

public:

    /** Max input length for this textbox. */
    byte maxLength;

    /** Text in textbox. */
    std::string text;

    /** Time of last input. */
    unsigned int lastInput;

    TextBox();
    TextBox(int x, int y, int width, int height, int maxLen, int fontSize, Color color);
    
    virtual void setString(const char* value);
    virtual void setString(int fontSize, Color fontColor, const char* text);

    void clear();

    virtual void keyEvent(sf::Uint32 key);
    virtual bool hasKeyboard();
    virtual void giveKeyboard();
    virtual void takeKeyboard();
    virtual void releaseKeyboard();

    virtual void update(unsigned int time);
    
    virtual ~TextBox();
};

#endif