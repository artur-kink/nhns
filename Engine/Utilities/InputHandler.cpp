#include "InputHandler.hpp"

/** Singleton pointer. */
InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler(){
    lastUpdateTime = 0;

#ifdef _PC_
    numInputs = 1 + sf::Joystick::Count;
#endif

    //Initialize info for inputs.
    inputs = new byte[numInputs];
    numButtons = new byte[numInputs];
    numPointers = new byte[numInputs];
    pointer = new float*[numInputs];
    pressedTime = new unsigned int*[numInputs];
    pressedState = new bool*[numInputs];
    downState = new bool*[numInputs];
    releasedState = new bool*[numInputs];
    anyButtonPressed = new bool[numInputs];
#ifdef _PC_
    //Keyboard
    inputs[0] = InputHandler::i_Keyboard;
    numButtons[0] = sf::Keyboard::KeyCount;
    numPointers[0] = 0;

    //Mouse
    inputs[1] = InputHandler::i_Mouse;
    numButtons[1] = 3;
    numPointers[1] = 2;

    //Joysticks
    for(int i = 0; i < sf::Joystick::Count; i++){
        inputs[2 + i] = i_Controller;
        numButtons[2 + i] = sf::Joystick::getButtonCount(i);
        numPointers[2 + i] = sf::Joystick::AxisCount;
    }
#endif

    //Initialize info for buttons.
    for(int i = 0; i < numInputs; i++){
        pointer[i] = new float[numPointers[i]];
        pressedTime[i] = new unsigned int[numButtons[i]];
        pressedState[i] = new bool[numButtons[i]];
        downState[i] = new bool[numButtons[i]];
        releasedState[i] = new bool[numButtons[i]];
        anyButtonPressed[i] = false;
    }

    instance = this; //Initialize singleton.
}

/**
 * Get InputHandler singleton.
 */
InputHandler* InputHandler::I(){
    return instance;
}

/**
 * Update state of given button.
 * @param button Button to update.
 * @param down Is button pressed.
 */
void InputHandler::updateButtonState(byte input, byte button, bool down){
    if(down){
        if(!downState[input][button]){
            pressedState[input][button] = true;
            anyButtonPressed[input] = true;
            pressedTime[input][button] = lastUpdateTime;
        }else{
            pressedState[input][button] = false;
        }
        downState[input][button] = true;
    }else{
        if(downState[input][button]){
            releasedState[input][button] = true;
        }else{
            releasedState[input][button] = false;
        }
        pressedState[input][button] = false;
        downState[input][button] = false;
    }
}

/**
 * Update input state.
 * @param time Time of update.
 */
void InputHandler::update(unsigned int time){
    lastUpdateTime = time;

#ifdef _PC_

    //Update mouse state
    anyButtonPressed[i_Mouse] = false;
    updateButtonState(i_Mouse, ib_Left, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    updateButtonState(i_Mouse, ib_Middle, sf::Mouse::isButtonPressed(sf::Mouse::Middle));
    updateButtonState(i_Mouse, ib_Right, sf::Mouse::isButtonPressed(sf::Mouse::Right));
    //Update mouse pointer
    pointer[i_Mouse][0] = sf::Mouse::getPosition().x;
    pointer[i_Mouse][1] = sf::Mouse::getPosition().y;

    //Update keyboard state
    anyButtonPressed[0] = false;
    for(byte i = 0; i < sf::Keyboard::KeyCount; i++){
        updateButtonState(0, i, sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i));
    }

    //Update joystick state
    for(int i = 0; i < sf::Joystick::Count; i++){
        if(sf::Joystick::isConnected(i)){
            anyButtonPressed[i+2] = false;
            for(int b = 0; b < sf::Joystick::getButtonCount(i); b++){
                updateButtonState(i+2, b, sf::Joystick::isButtonPressed(i, b));
            }
            //Update axis pointers
            for(int p = 0; p < sf::Joystick::AxisCount; p++){
                pointer[i+2][p] = sf::Joystick::getAxisPosition(i, (sf::Joystick::Axis)p);
            }
        }
    }

    
#endif

}

/**
 * Get pointer's axis position.
 * @param input Input device to check.
 * @param axis Axis to retreive.
 */
float InputHandler::getPointer(byte input, byte axis){
    return pointer[input][axis];
}

/**
 * Is the given button being pressed.
 * @param input Input device to check.
 * @param button Button to check.
 */
bool InputHandler::isButtonDown(byte input, byte button){
    return downState[input][button];
}

/**
 * Has the given button been pressed this frame.
 * @param input Input device to check.
 * @param button Button to check.
 */
bool InputHandler::isButtonPressed(byte input, byte button){
    return pressedState[input][button];
}

/**
 * Has the given button been released this frame.
 * @param input Input device to check.
 * @param button Button to check.
 */
bool InputHandler::isButtonReleased(byte input, byte button){
    return releasedState[input][button];
}

/**
 * Has any key been pressed this frame.
 * @param input Input device to check.
 */
bool InputHandler::isAnyButtonPressed(byte input){
    return anyButtonPressed[input];
}

InputHandler::~InputHandler(){

}