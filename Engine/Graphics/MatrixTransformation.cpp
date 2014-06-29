#include "MatrixTransformation.hpp"
#include "StaticSprite.hpp"

/**
 * Create identity matrix.
 */
MatrixTransformation::MatrixTransformation(){
    type = BaseTransformation::tt_Matrix;
    index = 0;

    transformFlags = 0;
    tX = tY = rAngle = rX = rY = 0;
    sY = sX = 0.0;
}

/**
 * Create Identity matrix with initial index of i.
 */
MatrixTransformation::MatrixTransformation(unsigned short i){
    type = BaseTransformation::tt_Matrix;
    index = i;

    transformFlags = 0;
    tX = tY = rAngle = rX = rY = 0;
    sY = sX = 0.0;
}

/**
 * Apply matrix operations in this transformation to the render state.
 * Order of operations performed as follows: Rotate, Translate, Scale.
 */

void MatrixTransformation::apply(RenderObject& obj){
#ifdef _PC_
    if(transformFlags & MatrixTransformation::to_Rotate)
        obj.state.transform.rotate(rAngle, rX, rY);

    if(transformFlags & MatrixTransformation::to_Translate)
        obj.state.transform.translate(tX, tY);

    if(transformFlags & MatrixTransformation::to_Scale)
        obj.state.transform.scale(sX, sY);
    
    if(transformFlags & MatrixTransformation::to_FlipX){
        obj.state.transform.translate(obj.sourceWidth, 0);
        obj.state.transform.scale(-1, 1);
    }
    
    if(transformFlags & MatrixTransformation::to_FlipY){
        obj.state.transform.translate(0, obj.sourceHeight);
        obj.state.transform.scale(1, -1);
    }
#endif
}

void MatrixTransformation::clear(RenderObject& obj){
#ifdef _PC_
    obj.state.transform = sf::Transform::Identity;
#endif
}

/** 
 * Scale image by floating point multiplier.
 * @param x X scale amount.
 * @param y Y scale amount. 
 */
void MatrixTransformation::scale(float x, float y){
    transformFlags = transformFlags | MatrixTransformation::to_Scale;
    sX = x;
    sY = y;
}

/** 
 * Scale image by floating point multiplier on given RenderObject.
 * @param obj RenderObject to scale.
 * @param x X scale amount.
 * @param y Y scale amount. 
 */
void MatrixTransformation::scale(RenderObject& obj, float x, float y){
    MatrixTransformation transform;
    transform.scale(x, y);
    transform.apply(obj);
}

/**
 * Flip image horizontally.
 */
void MatrixTransformation::flipHorizontally(){
    transformFlags = transformFlags | MatrixTransformation::to_FlipX;
}

/**
 * Flip image horizontally on given RenderObject.
 * @param obj RenderObject to flip.
 */
void MatrixTransformation::flipHorizontally(RenderObject& obj){
    MatrixTransformation transform;
    transform.flipHorizontally();
    transform.apply(obj);
}

/**
 * Flip image vertically.
 */
void MatrixTransformation::flipVertically(){
    transformFlags = transformFlags | MatrixTransformation::to_FlipY;
}

/**
 * Rotate image around center of rotation.
 * @param degrees Angle in degrees.
 * @param x Center of rotation x value.
 * @param y Center of rotation y value.
 */
void MatrixTransformation::rotate(float degrees, int x, int y){
    transformFlags = transformFlags | MatrixTransformation::to_Rotate;
    rAngle = degrees;
    rX = x;
    rY = y;
}

/**
 * Translate image position.
 * @param x X amount to translate by.
 * @param y Y amount to translate by.
 */
void MatrixTransformation::translate(int x, int y){
    transformFlags = transformFlags | MatrixTransformation::to_Translate;
    tX += x;
    tY += y;
}

/**
 * Translate image position on given RenderObject.
 * @param obj RenderObject to translate.
 * @param x X amount to translate by.
 * @param y Y amount to translate by.
 */
void MatrixTransformation::translate(RenderObject& obj, int x, int y){
    MatrixTransformation transform;
    transform.translate(x, y);
    transform.apply(obj);
}