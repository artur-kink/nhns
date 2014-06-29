#ifndef _SHADERMANAGER_
#define	_SHADERMANAGER_

#include "Utilities/ResourceManager.hpp"
#include "Utilities/KeyValuePair.hpp"
#include "Graphics/ShaderTransformation.hpp"

/**
 * Class used to manage shaders.
 */
class ShaderManager:public ResourceManager{
public:
    /** Number of shaders. */
    unsigned short shaderCount;
    /** Shader array. */
    ShaderTransformation** shaders;
    /** Shader Names. */
    KeyValuePair<ShaderTransformation>* shaderNames;

    ShaderManager();

    ShaderTransformation* getShader(const char* name);

    virtual void load(const char* path);
#ifdef _PC_
    virtual void loadRaw(const char* file);
    virtual void save(const char* file);
#endif

};

#endif

