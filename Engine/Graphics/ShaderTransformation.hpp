#ifndef _SHADERTRANSFORMATION_
#define _SHADERTRANSFORMATION_

#include "BaseTransformation.hpp"
#include "Utilities/Serializable.hpp"

#ifdef _PC_
#include "SFML/Graphics/Shader.hpp"
#endif

/**
 * Shader transformation.
 * Contains shader information and is used to apply shaders.
 */
class ShaderTransformation:public BaseTransformation, Serializable{
private:
#ifdef _PC_
    /** SFML implementation of shader. */
    sf::Shader shader;
#endif
public:

    /** Shader type enum. */
    enum ShaderType{
        /** Pixel shader. */
        st_Pixel = 0,
        /** Vertex shader. */
        st_Vertex = 1,
        /** Both Pixel and Vertex shader. */
        st_Both = 2
    };

    /** The type of this shader. */
    ShaderType shaderType;

    /** Index of this shader inside the ShaderManager. */
    unsigned short index;
    
    /** 
     * Name of shader.
     * The memory for this string is allocated inside the ShaderManager.
     * This memory should not be freed.
     */
    char* name;

    /** Name of file containing shader. */
    char* fileName;

    ShaderTransformation();
    void loadShader(const char* file);
    
    virtual void apply(RenderObject& obj);
    static void clear(RenderObject& obj);

    void setParameter(const char* name, float v1); 
    void setParameter(const char* name, float v1, float v2); 
    void setParameter(const char* name, float v1, float v2, float v3); 
    void setParameter(const char* name, float v1, float v2, float v3, float v4); 

#ifdef _PC_
    virtual void serialize(std::ofstream& destination);
#endif
    virtual void deserialize(MemoryPool* source);
};

#endif