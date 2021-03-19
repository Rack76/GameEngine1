#include "MeshLoader.h"
#include <iostream>

void MeshLoader::loadOBJFile(std::string filepath)
{
    OBJFile.open(filepath);

    verticeArray.erase(verticeArray.begin(), verticeArray.end());
    textureArray.erase(textureArray.begin(), textureArray.end());
    verticeIndices.erase(verticeIndices.begin(), verticeIndices.end());
    textureIndices.erase(textureIndices.begin(), textureIndices.end());
    verticeTextureArray.erase(verticeTextureArray.begin(), verticeTextureArray.end());
    normalIndices.erase(normalIndices.begin(), normalIndices.end());

    while(getline(OBJFile, line))
    {
        if(line.substr(0, 2) == "v ")
        {
            std::stringstream ss;
            ss << line.substr(2);
            float number;

            for(int i = 0; i < 3; i++)
            {
            ss >> number;
            verticeArray.push_back(number);
            }
        }
        if(line.substr(0, 2) == "vt")
        {
            std::stringstream ss;
            ss << line.substr(2);
            float number;

            for(int i = 0; i < 2; i++)
            {
            ss >> number;
            textureArray.push_back(number);
            }
        }
        if(line.substr(0, 2) == "f ")
        {
            std::replace(line.begin(), line.end(), '/', ' ');
            std::stringstream ss;

            ss << line.substr(2);
            float x, y, z;

            for(int i = 0; i < 3; i++)
            {
                ss >> x;
                --x;
                verticeIndices.push_back(x);
                ss >> y;
                --y;
                textureIndices.push_back(y);
                ss >> z;
                --z;
                normalIndices.push_back(z);
            }
        }
    }

    orderArray(verticeArray, verticeIndices, &verticeArray, 3);
    orderArray(textureArray, textureIndices, &textureArray, 2);
    combineVerticeAndTextureArray();
}

void MeshLoader::orderArray(std::vector<float> unorderedArray, std::vector<unsigned int> indices, std::vector<float>* orderedArray, int numbersPerLine)
{
    std::vector<float> tempArray;
    for(int i = 0; i < indices.size(); i++)
    {
    tempArray.push_back(unorderedArray[indices[i] * numbersPerLine]);
    tempArray.push_back(unorderedArray[indices[i] * numbersPerLine + 1]);
    if(numbersPerLine == 3)
    {
        tempArray.push_back(unorderedArray[indices[i] * numbersPerLine + 2]);
    }
    }

    *orderedArray = tempArray;
}

void MeshLoader::combineVerticeAndTextureArray()
{
    int verticeSize = 3;
    int textureSize = 2;
    for(int i = 0; i < verticeIndices.size(); i++)
    {
        verticeTextureArray.push_back(verticeArray[i * verticeSize]);
        verticeTextureArray.push_back(verticeArray[(i * verticeSize) + 1]);
        verticeTextureArray.push_back(verticeArray[(i * verticeSize) + 2]);
        verticeTextureArray.push_back(textureArray[(i * textureSize)]);
        verticeTextureArray.push_back(textureArray[(i * textureSize) + 1]);
    }
}


