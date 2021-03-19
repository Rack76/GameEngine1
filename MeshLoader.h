#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

class MeshLoader
{
public:
    void loadOBJFile(std::string filepath);
    void orderArray(std::vector<float> unorderedArray, std::vector<unsigned int> indices, std::vector<float>* orderedArray, int numberPerLine);
    void combineVerticeAndTextureArray();
    std::ifstream OBJFile;
    std::string line;
    std::vector<float> verticeArray;
    std::vector<float> textureArray;
    std::vector<unsigned int> verticeIndices;
    std::vector<unsigned int> textureIndices;
    std::vector<unsigned int> normalIndices;
    std::vector<float> verticeTextureArray;
};

#endif // MESHLOADER_H
