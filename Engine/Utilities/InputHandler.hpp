#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#ifdef _PC_
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Joystick.hpp"
#endif

#include "Types.hpp"

class InputHandler{
    friend class EngineCore;
public:

    /** Number of input devices. */
    byte numInputs;
    byte* inputs;
    byte* numButtons;

    enum Inputs{
        i_Keyboard = 0,
        i_Mouse = 1,
        i_Controller = 2,
        i_Other = 3
    };

    /** Button definitions. */
    enum InputButtons{
#ifdef _PC_
        ib_Left = 0,
        ib_Middle = 1,
        ib_Right = 2
#endif
    };

    /** Pointer definitions. */
    enum InputPointer{
#ifdef _PC_
        ip_Mouse,
#endif
        ip_Last
    };
private:

#ifdef _PC_
    sf::Window* window;
#endif

    /** Last time of update. */
    unsigned int lastUpdateTime;

    /** Singleton instance. */
    static InputHandler* instance;

    /** Last time button was pressed. */
    unsigned int** pressedTime;

    /** Has the button been pressed this frame. */
    bool** pressedState;

    /** Is the button being pressed this frame. */
    bool** downState;

    /** Has the button been released this frame. */
    bool** releasedState;

    /** Has there been any button pressed this frame. */
    bool* anyButtonPressed;

    byte* numPointers;
    /** Pointers. */
    float** pointer;

    void updateButtonState(byte input, byte button, bool down);

public:

    InputHandler();
    
    static InputHandler* I();
    
    void update(unsigned int time);

    bool isButtonDown(byte input, byte button);
    bool isButtonPressed(byte input, byte button);
    bool isButtonReleased(byte input, byte button);
    bool isAnyButtonPressed(byte input);

    float getPointer(byte input, byte axis);

    ~InputHandler();
};

#endif
