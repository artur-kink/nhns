#include "Camera.hpp"

Camera::Camera(){
    setPosition(0, 0);
    //Place holder values.
    zoom = 1.0;
    screenWidth = screenHeight = 100;
}

/**
 * Update camera state.
 */
void Camera::update(unsigned int frameTime){
    //Update zoom animation if any.
    if(zoomTween.active){
        zoomTween.update(frameTime);
        //Update zoom value changed by the tween.
        setZoom(zoom);
    }

    if(panXTween.active){
        panXTween.update(frameTime);
    }
    if(panYTween.active){
        panYTween.update(frameTime);
    }
}

/**
 * Set camera zoom level.
 * This method is equivalent to calling
 * setSize(screenWidth/z, screenHeight/z).
 * @param z Zoom multiplier(1 for no zoom).
 * A zoom value of <= 0 will reset camera to 1.
 */
void Camera::setZoom(float z){
    zoom = z;
    if(zoom <= 0)
        zoom = 1;

    setSize(((float)screenWidth)/zoom, ((float)screenHeight)/zoom);
}

/**
 * Set position of camera.
 */
void Camera::setPosition(int posX, int posY){
    x = posX;
    y = posY;
}

/**
 * Center position of camera at given point.
 * Equivalent to setPosition(posX - width/2, posY - height/2).
 */
void Camera::setCenter(int posX, int posY){
    setPosition(posX - width/2, posY - height/2);
}

/**
 * Set camera view size.
 */
void Camera::setSize(int w, int h){
    width = w;
    height = h;
}

/**
 * Set size of screen.
 */
void Camera::setScreenSize(int w, int h){
    screenWidth = w;
    screenHeight = h;
}

/**
 * Stop a zoom animation if its running.
 */
void Camera::stopZoomAnimation(){
    zoomTween.stop();
}

/**
 * Stop a pan animation if its running.
 */
void Camera::stopPanAnimation(){
    panXTween.stop();
    panYTween.stop();
}

/**
 * Stop all running animations.
 */
void Camera::stopAllAnimations(){
    stopZoomAnimation();
    stopPanAnimation();
}

/**
 * Zoom to given target zoom level over time.
 * @param targetZoom Target zoom amount.
 * @param frameTime Current time.
 * @param length Length of animation in milliseconds.
 */
void Camera::createZoomAnimation(float targetZoom, unsigned int length, unsigned int frameTime){
    zoomTween.start(&zoom, targetZoom, length, frameTime);
}

/**
 * Pan to given position over time.
 * @param tx Target x position.
 * @param ty Target y position.
 * @param length Length of animation in milliseconds.
 * @param frameTime Current time.
 */
void Camera::createPanAnimation(int tx, int ty, unsigned int length, unsigned int frameTime){
    panXTween.start(&x, tx, length, frameTime);
    panYTween.start(&y, ty, length, frameTime);
}

/**
 * Get starting X tile that is in range of camera.
 */
int Camera::getStartTileX(){
    int startX = x/TILESIZE - 1;
    if(startX < 0)
        startX = 0;

    return startX;
}
/**
 * Get last X tile that is in range of camera.
 */
int Camera::getEndTileX(){
    return (x + width)/TILESIZE + 1;
}

/**
 * Get starting Y tile that is in range of camera.
 */
int Camera::getStartTileY(){
    int startY = y/TILESIZE - 1;
    if(startY < 0)
        startY = 0;

    return startY;
}

/**
 * Get last Y tile that is in range of camera.
 */
int Camera::getEndTileY(){
    return (y + height)/TILESIZE + 1;
}