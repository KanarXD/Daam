#include "pch.h"
#include "MapLibrary.h"
#include "Renderer/Library/ShadersLibrary.h"
#include "Renderer/Library/TextureLibrary.h"
#include "Game/GameObjectManager.h"
#include "Game/World/Enemies/Spawner.h"

std::shared_ptr<MapLibrary> MapLibrary::GetInstance()
{
    static std::shared_ptr<MapLibrary> mapLibraryInstance(new MapLibrary());
    return mapLibraryInstance;
}

std::optional<const Map*> MapLibrary::Load(const std::string& mapPath)
{
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> params;
    if (!ReadFile(mapPath, params))
    {
        LOGERROR("failed to load map", mapPath);
        return {};
    }

    float width = std::stof(params["surface:"]["width:"]);
    float height = std::stof(params["surface:"]["height:"]);
    float boxSize = std::stof(params["box:"]["size:"]);
    std::string skyBoxDirectory = params["skyBox:"]["directory:"];
    
    auto skyBoxShader = ShadersLibrary::GetInstance()->Get(params["skyBox:"]["shaderName:"]);
    if (!skyBoxShader.has_value())
    {
        LOGERROR("skybox shader", mapPath);
        return {};
    }

    auto mapSurfaceShader = ShadersLibrary::GetInstance()->Get(params["surface:"]["shaderName:"]);
    if (!mapSurfaceShader.has_value())
    {
        LOGERROR("surface shader", mapPath);
        return {};
    }

    auto boxShader = ShadersLibrary::GetInstance()->Get(params["box:"]["shaderName:"]);
    if (!boxShader.has_value())
    {
        LOGERROR("box shader", mapPath);
        return {};
    }

    auto surfaceTexture = TextureLibrary::GetInstance()->Load(params["surface:"]["texturePath:"], true);
    if (!surfaceTexture.has_value())
    {
        LOGERROR("surfaceTexture", mapPath);
        return {};
    }

    auto boxTexture = TextureLibrary::GetInstance()->Load(params["box:"]["texturePath:"], false);
    if (!surfaceTexture.has_value())
    {
        LOGERROR("surfaceTexture", mapPath);
        return {};
    }

    std::vector<std::string> skyBoxSidesTextureNamesVector;
    std::string_view texturePaths = params["skyBox:"]["sides:"];
    size_t start = 0, end = 0;
    while (end = texturePaths.find('|') < texturePaths.size())
    {
        texturePaths = texturePaths.substr(start);
        end = texturePaths.find('|');
        skyBoxSidesTextureNamesVector.push_back(std::string(texturePaths.substr(0, end)));
        start = end + 1;
    }

    std::vector<Map::Box> boxVector;
    std::string key = "0:";
    int i = 0, j;
    auto gameObjectManager = GameObjectManager::GetInstance();
    while (params["boxMap:"].find(key) != params["boxMap:"].end())
    {
        j = 0;
        for (char& x : params["boxMap:"][key])
        {
            switch (x)
            {
                // obstacles
            case 'O': boxVector.push_back({ float(i), float(j) }); break;
                // healthkit
            case 'H': GameObjectManager::GetInstance()->Add<Healthkit>(Transform(glm::vec3(i * boxSize, 2, j * boxSize))); break;
                // enemy
            case 'S': Spawner::GetInstance()->AddSpawnLocation(glm::vec2(i * boxSize, j * boxSize)); break;
            }

            j++;
        }
        key = std::to_string(++i) + ":";
    }

    Mesh surfaceMesh(Map::GetPlaneVertexes(width, height, boxSize), Map::GetPlaneIndices());
    surfaceMesh.AddTexture(surfaceTexture.value());
    surfaceMesh.SetUseTextures(true);

    Mesh boxMesh(Map::GetCubeVertexes(boxSize), Map::GetCubeIndices());
    boxMesh.AddTexture(boxTexture.value());
    boxMesh.SetUseTextures(true);

    Map::Params mapParams = {
        { width, height, std::move(surfaceMesh) , mapSurfaceShader.value() },
        { boxSize, std::move(boxMesh), boxShader.value(), std::move(boxVector) },
        { skyBoxDirectory, skyBoxSidesTextureNamesVector, skyBoxShader.value() }
    };

    return InsertData(mapPath, mapParams);
}

bool MapLibrary::ReadFile(const std::string& mapPath, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& params)
{
    std::ifstream file(mapPath);

    if (file.is_open())
    {
        std::stringstream buffor;
        buffor << file.rdbuf();
        std::string input;
        std::string entity;
        std::string key;
        while (buffor >> input)
        {
            if (input.front() == '!') continue;
            switch (input.back())
            {
            case ':':
                if (entity == "")
                {
                    entity = input;
                }
                else if (key == "") {
                    key = input;
                }
                else {
                    LOGWARNING("key after key", mapPath);
                    return false;
                }
                break;
            case '{':
                if (entity == "") {
                    LOGWARNING("no entity before { in", mapPath);
                    return false;
                }
                break;
            case '}':
                entity = "";
                key = "";
                break;
            default:
                if (entity != "" && key != "")
                {
                    params[entity][key] = input;
                    key = "";
                }
                else {
                    LOGWARNING("key or entity missiong", mapPath);
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
