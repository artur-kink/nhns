#ifndef _CAMERA_
#define _CAMERA_

#include "Utilities/MathHelper.hpp"
#include "Utilities/TimedTween.hpp"
#include "Types.hpp"

/**
 * Game camera.
 * The camera is basically a transformation on a render target.
 * It modifies the drawn world based on its parameters.
 */
class Camera{
private:
    TimedTween<int> panXTween;
    TimedTween<int> panYTween;
    TimedTween<float> zoomTween;

public:
    /** X Position of camera. */
    int x;
    /** Y Position of camera. */
    int y;
    /** Camera width. */
    int width;
    /** Camera height. */
    int height;
    
    /** Height of the screen. */
    int screenWidth;
    /** Width of the screen. */
    int screenHeight;

    /**
     * Camera zoom level.
     * Manually changing width and height of camera
     * will invalidate this value.
     */
    float zoom;

    Camera();

    void update(unsigned int frameTime);

    void setZoom(float z);
    void setPosition(int posX, int posY);
    void setCenter(int posX, int posY);
    void setSize(int w, int h);
    void setScreenSize(int w, int h);

    void createZoomAnimation(float targetZoom, unsigned int length, unsigned int frameTime);
    void stopZoomAnimation();
    void createPanAnimation(int tx, int ty, unsigned int length, unsigned int frameTime);
    void stopPanAnimation();
    void stopAllAnimations();

    int getStartTileX();
    int getEndTileX();
    int getStartTileY();
    int getEndTileY();
};

#endif