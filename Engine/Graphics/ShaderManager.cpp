#include "ShaderManager.hpp"

/**
 * Initialize empty shader manager.
 */
ShaderManager::ShaderManager(){
    shaderCount = 0;
    shaderNames = 0;
    shaders = 0;
}

/**
 * Get shader by name.
 * @param name Name of shader to retrieve.
 */
ShaderTransformation* ShaderManager::getShader(const char* name){
    return KeyValuePair<ShaderTransformation>::findValue(shaderNames, shaderCount, name);
}

void ShaderManager::load(const char* path){
    Log << LC_G << LL_D <<"Loading shader definition file: " << path;
    //Open file
    FileHandler fileHandler;
    MemoryPool* file = fileHandler.readFile(path);

    //If file reading succeeded.
    if(file->getBuffer()){

        //Load audio definitions
        file->read((char*) &shaderCount, sizeof(shaderCount));
        shaders = new ShaderTransformation*[shaderCount];

        Log << "Shaders Found: " << shaderCount;
        for(unsigned short i = 0; i < shaderCount; i++){
            shaders[i] = new ShaderTransformation();
            shaders[i]->index = i;
            shaders[i]->deserialize(file);
            shaders[i]->loadShader(shaders[i]->fileName);
        }

        //Load ordered sprite name index
        shaderNames = new KeyValuePair<ShaderTransformation>[shaderCount];
        for(unsigned int i = 0; i < shaderCount; i++){
            unsigned short index = 0;

            file->read((char*) &index, sizeof(index));
            shaderNames[i].value = shaders[index];
            byte nameLen = 0;
            file->read((char*) &nameLen, sizeof(nameLen));
            shaderNames[i].key = new char[nameLen + 1];
            file->readString(shaderNames[i].key, nameLen);
            shaderNames[i].key[nameLen] = '\0';
            shaders[index]->name = shaderNames[i].key;
            Log << "Shader: " << shaders[index]->name 
                << "Shader Type: " << shaders[index]->shaderType 
                << ", File: " << shaders[index]->fileName;
        }

        Log << "Shaders loaded.";

        delete file;
    }
}

#ifdef _PC_
void ShaderManager::loadRaw(const char* file){
    //Open xml document.
    pugi::xml_document doc;
    pugi::xml_parse_result loadResult = doc.load_file(file);

    Log << LC_F << LL_D << "Load Result: " << loadResult.description();

    //Parse audio objects
    std::vector<ShaderTransformation*> shaderList;
    std::vector<char*> namesList;

    Log << LC_F << LL_D << "Shaders: ";
    for(pugi::xml_node node = doc.first_child().first_child(); node; node = node.next_sibling()){
        if(strcmp(node.name(), "shader") == 0){

            ShaderTransformation* shader = new ShaderTransformation();
            char* name = new char[strlen(node.attribute("name").value()) + 1];
            strcpy(name, node.attribute("name").value());
            name[strlen(node.attribute("name").value())] = '\0';

            shader->name = name;

            shader->fileName = new char[strlen(node.attribute("file").value()) + 1];
            strcpy(shader->fileName, node.attribute("file").value());
            shader->fileName[strlen(node.attribute("file").value())] = '\0';

            byte type;
            if(strcmp(node.attribute("type").value(), "pixel") == 0){
                type = ShaderTransformation::st_Pixel;
            }else if(strcmp(node.attribute("type").value(), "vertex") == 0){
                type = ShaderTransformation::st_Vertex;
            }else{
                type = ShaderTransformation::st_Both;
            }
            shader->shaderType = (ShaderTransformation::ShaderType)type;
            Log << "Name: " << name << ", Shader Type: " << (int)type << ", File: " << shader->fileName;

            shaderList.push_back(shader);
            namesList.push_back(name);
        }
    }

    //Copy sprites into sprite array
    shaderCount = shaderList.size();
    shaders = new ShaderTransformation*[shaderCount];
    for(unsigned short i = 0; i < shaderCount; i++){
        shaders[i] = shaderList.at(i);
        shaders[i]->index = i;
    }

    //Copy sprite names into sprite names array while sorting them by name
    shaderNames = new KeyValuePair<ShaderTransformation>[shaderCount];
    for(unsigned short i = 0; i < namesList.size(); i++){
        shaders[i]->name = namesList.at(i);
        KeyValuePair<ShaderTransformation>::insertSort(shaders[i], shaders[i]->name, shaderNames, shaderCount);
    }

	shaderList.clear();

    Log << LC_F << LL_D << "Loaded raw shader file.";
}

void ShaderManager::save(const char* file){
    //Open destination file.
    Log << LC_F << LL_D << "Saving shaders.";
    std::ofstream fileWriter;
    fileWriter.open(file, std::ios::binary | std::ios::out);
    if(fileWriter.fail()){
        Log << LC_F << LL_C << "Open file failed.";
        return;
    }

    //Write audio objects.
    fileWriter.write((char*) &shaderCount, sizeof(shaderCount));
    for(unsigned short i = 0; i < shaderCount; i++){
        shaders[i]->serialize(fileWriter);
    }

    Log << LC_F << LL_D << "Saving name index.";
    //Write audio object name index.
    for(int i = 0; i < shaderCount; i++){
        fileWriter.write((char*)&shaderNames[i].value->index, sizeof(shaderNames[i].value->index));
        byte nameLen = strlen(shaderNames[i].key);
        fileWriter.write((char*)&nameLen, sizeof(nameLen));
        fileWriter.write(shaderNames[i].key, nameLen);
    }

    fileWriter.close();
    Log << LC_F << LL_D << "Saved shaders.";
}
#endif