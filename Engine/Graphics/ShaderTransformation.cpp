#include "ShaderTransformation.hpp"

ShaderTransformation::ShaderTransformation(){
    type = BaseTransformation::tt_Shader;
    name = 0;
    fileName = 0;
}

/**
 * Apply this shader to the given RenderObject.
 */
void ShaderTransformation::apply(RenderObject& obj){
#ifdef _PC_
    obj.state.shader = &shader;
#endif
}

/**
 * Clear any shader that is applied to given RenderObject.
 * @param obj RenderObject to remove shader from.
 */
void ShaderTransformation::clear(RenderObject& obj){
#ifdef _PC_
    obj.state.shader = 0;
#endif
}

/**
 * Load shader from file.
 */
void ShaderTransformation::loadShader(const char* file){
#ifdef _PC_
    if(shaderType == ShaderTransformation::st_Pixel)
        shader.loadFromFile(file, sf::Shader::Fragment);
    else if(shaderType == ShaderTransformation::st_Vertex)
        shader.loadFromFile(file, sf::Shader::Vertex);
    else{
        FileHandler handler;
        MemoryPool* fileData = handler.readFile(file);
        const char* vertexShader = (const char*)fileData->getBuffer();
        int i;
        while(vertexShader[i] != 0)
            i++;
        const char* pixelShader = vertexShader + i + 1;

        shader.loadFromMemory(vertexShader, pixelShader);
        delete fileData;
    }
#endif
}

/**
 * Set Vec1 parameter.
 */
void ShaderTransformation::setParameter(const char* name, float v1){
#ifdef _PC_
    shader.setParameter(name, v1);
#endif
}

/**
 * Set Vec2 parameter.
 */
void ShaderTransformation::setParameter(const char* name, float v1, float v2){
#ifdef _PC_
    shader.setParameter(name, v1, v2);
#endif
}

/**
 * Set Vec3 parameter.
 */
void ShaderTransformation::setParameter(const char* name, float v1, float v2, float v3){
#ifdef _PC_
    shader.setParameter(name, v1, v2, v3);
#endif
}

/**
 * Set Vec4 parameter.
 */
void ShaderTransformation::setParameter(const char* name, float v1, float v2, float v3, float v4){
#ifdef _PC_
    shader.setParameter(name, v1, v2, v3, v4);
#endif
}

#ifdef _PC_
void ShaderTransformation::serialize(std::ofstream& destination){
    //Write type
    byte t = shaderType;
    destination.write((char*)&t, sizeof(t));
    //Write filename.
    byte fileLen = strlen(fileName);
    destination.write((char*)&fileLen, sizeof(fileLen));
    destination.write(fileName, fileLen);
}
#endif

void ShaderTransformation::deserialize(MemoryPool* source){
    //Load type
    byte t = 0;
    source->read((char*) &t, sizeof(t));
    shaderType = (ShaderType)t;
    //Load file name
    byte fileNameLen = 0;
    source->read((char*) &fileNameLen, sizeof(fileNameLen));
    fileName = new char[fileNameLen + 1];
    source->readString(fileName, fileNameLen);
    fileName[fileNameLen] = '\0';
}