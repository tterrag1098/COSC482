#include "ObjModel.h"

/**
\file ObjModel.cpp
\brief Implementation for graphing Wavefront obj files.

\author    Don Spickler
\version   1.1
\date      Written: 4/10/2016  <BR> Revised: 4/10/2016

*/

/**
\brief Constructor

Default constructor.

*/

ObjModel::ObjModel()
{}

/**
\brief Destructor

Removes the stored data the clears the memory on the graphics card.

*/

ObjModel::~ObjModel()
{
    glBindVertexArray(vboptr);
    glDeleteBuffers(1, &bufptr);

    vertices.clear();
    texcoords.clear();
    normals.clear();
}

/**
\brief Loads the data from the vertex, normal, and texture coordinate
vectors to the graphics card.

*/

void ObjModel::LoadDataToGraphicsCard()
{
    GLint vPosition = 0;
    GLint vNormal = 2;
    GLint vTex = 3;

    glGenVertexArrays(1, &vboptr);
    glGenBuffers(1, &bufptr);

    unsigned int vsize = vertices.size()*sizeof(glm::vec3);
    unsigned int nsize = normals.size()*sizeof(glm::vec3);
    unsigned int tsize = texcoords.size()*sizeof(glm::vec2);

    glBindVertexArray(vboptr);
    glBindBuffer(GL_ARRAY_BUFFER, bufptr);
    glBufferData(GL_ARRAY_BUFFER, vsize + nsize + tsize, NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vsize, &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vsize, nsize, &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vsize+nsize, tsize, &texcoords[0]);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vsize));
    glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vsize+nsize));

    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vNormal);
    glEnableVertexAttribArray(vTex);
}

/**
\brief Loads the data from a Wavefront obj file and stores the data in
the vertex, normal, and texture coordinate vectors.  Finally, the loader
method is called to load the data to the graphics card.

*/

bool ObjModel::Load(std::string filename)
{
    std::vector<unsigned int> vertexIndices, texIndices, normalIndices;
    std::vector<glm::vec3> file_vertices;
    std::vector<glm::vec2> file_texcoords;
    std::vector<glm::vec3> file_normals;

    FILE * file = fopen(filename.c_str(), "r");

    if(file == NULL)
    {
        std::cout << "Cannot open file: " << filename << std::endl;
        return false;
    }

    vertices.clear();
    texcoords.clear();
    normals.clear();

    bool finished = false;
    while(!finished)
    {
        char lineHeader[512];

        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
        {
            finished = true;
        }
        else
        {
            if (strcmp(lineHeader, "v") == 0)
            {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                file_vertices.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vt") == 0)
            {
                glm::vec2 tex;
                fscanf(file, "%f %f\n", &tex.x, &tex.y );
                file_texcoords.push_back(tex);
            }
            else if (strcmp(lineHeader, "vn") == 0)
            {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                file_normals.push_back(normal);
            }
            else if (strcmp( lineHeader, "f" ) == 0)
            {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                if (matches != 9)
                {
                    std::cout << "File read error" << std::endl;
                    return false;
                }

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                texIndices.push_back(uvIndex[0]);
                texIndices.push_back(uvIndex[1]);
                texIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }
    }

    for(unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = file_vertices[vertexIndex - 1];
        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < normalIndices.size(); i++)
    {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = file_normals[normalIndex - 1];
        normals.push_back(normal);
    }

    for(unsigned int i = 0; i < texIndices.size(); i++)
    {
        unsigned int texIndex = texIndices[i];
        glm::vec2 texcoord = file_texcoords[texIndex - 1];
        texcoords.push_back(texcoord);
    }

    LoadDataToGraphicsCard();

    return true;
}

/**
\brief Draws the object.

*/

void ObjModel::draw()
{
    glBindVertexArray(vboptr);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
