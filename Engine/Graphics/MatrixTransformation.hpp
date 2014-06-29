#ifndef _MATRIXTRANSFORMATION_
#define _MATRIXTRANSFORMATION_

#include "BaseTransformation.hpp"

#ifdef _PC_
#include "SFML/Graphics/Transform.hpp"
#endif

/**
 * A transformation that supports matrix based transformations.
 * Transformations include translation, scaling and rotating.
 */
class MatrixTransformation:public BaseTransformation{
friend class SpriteManager;
protected:
    
public:

    /** Byte flags for transformation operations. */
    enum TransformationOperation{
        /** Translate image. */
        to_Translate = 1,
        /** Rotate image. */
        to_Rotate = 2,
        /** Scale image. */
        to_Scale = 4,
        /** Flip image horizontally. */
        to_FlipX = 8,
        /** Flip image vertically. */
        to_FlipY = 16
    };

    /** Byte flag for operations this transformation performs. */
    byte transformFlags;

    /** Translate x amount. */
    int tX;
    /** Translate y amount. */
    int tY;

    /** Scale y amount. */
    float sY;
    /** Scale x amount. */
    float sX;

    /** Angle of rotation in degrees. */
    int rAngle;
    /** Center of rotation x value. */
    int rX;
    /** Center of rotation y value. */
    int rY;


    MatrixTransformation();
    MatrixTransformation(unsigned short i);

    virtual void apply(RenderObject& obj);
    static void clear(RenderObject& obj);

    static void translate(RenderObject& obj, int x, int y);
    void translate(int x, int y);
    
    static void scale(RenderObject& obj, float x, float y);
    void scale(float x, float y);

    void rotate(float degrees, int x, int y);

    static void flipHorizontally(RenderObject& obj);
    void flipHorizontally();
    void flipVertically();
};

#endif
