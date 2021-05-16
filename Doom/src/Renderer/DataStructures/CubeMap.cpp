#include "pch.h"
#include "CubeMap.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "Utility/stb_image.h"

static const float CubeMapVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

CubeMap::CubeMap(const std::string& directory, std::vector<std::string> facesNames, const ShaderProgram* shaderProgram)
    : vertexBuffer((void*)CubeMapVertices, sizeof(CubeMapVertices)), shaderProgram(shaderProgram)
{  
    VertexBufferLayout vbl;
    vbl.Push<float>(3);
    vertexArray.AddBuffer(vertexBuffer, vbl);

    if (facesNames.size() == 6)
    {
        glGenTextures(1, &textureCubeMapId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMapId);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        for (uint32_t i = 0; i < 6; i++) {
            int32_t width, height, bpp;
            unsigned char* data = stbi_load((directory + "/" + facesNames[i]).c_str(),
                &width, &height, &bpp, 4);
            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            else {
                LOGERROR("Failed to load texture at", facesNames[i]);
            }

            stbi_image_free(data);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else {
        LOGERROR("Failed to load textures - faceNamesVector size != 6", facesNames.size());
    }
    

}

void CubeMap::Bind() const
{
    vertexArray.Bind();
    shaderProgram->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureCubeMapId);
    glUniform1i(shaderProgram->u("SkyBox"), 0);
}
