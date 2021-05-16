#pragma once

#include "Renderer/Library/Library.h"
#include "Map.h"

class MapLibrary : public Library<Map>
{
public:
	static std::shared_ptr<MapLibrary> GetInstance();

	std::optional<const Map*> Load(const std::string& mapPath);

private:
	static bool ReadFile(const std::string& mapPath, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& params);
private:
	MapLibrary() = default;
	MapLibrary(MapLibrary const&) = delete;
	void operator=(MapLibrary const&) = delete;
};

