#ifndef _BASETRANSFORMATION_
#define _BASETRANSFORMATION_

#include "Types.hpp"
#include "BaseRenderTarget.hpp"
#ifdef _PC_
#include "SFML/Graphics/RenderStates.hpp"
#endif

/**
 * Base class for Sprite transformations.
 * @see BaseSprite
 */
class BaseTransformation{
public:
    
    /** 
    * Transformation index in the transformation list.
    */
    unsigned short index;

    /** Type code for transformation type. */
    enum TransformationType{
        /** Matrix transformation. */
        tt_Matrix = 1,
        tt_Shader = 2
    };
    
    /** The Transformation type. */
    TransformationType type;

    /**
     * Perform transformation on a RenderState.
     */
    virtual void apply(RenderObject& obj) = 0;
};

#endif