#pragma once
#include<glm\gtc\matrix_transform.hpp>
#include<map>
#include<list>
#include"StaticShader.h"
#include"Rendrer.h"
#include"textureModel.h"
#include"entity.h"
#include"Camera.h"
#include"Light.h"
#include"terrain.h"
#include"TerrainShader.h"
#include"TerrainRenderer.h"
#include"SkyboxRenderer.h"
class RenderMaster
{
private:
	StaticShader Staticshader;
	Rendrer rendrer;
	SkyboxRenderer skyRenderer;

	const float SkyRed = 0.4f;
	const float SkyGreen = 0.4f;
	const float SkyBlue = 0.5f;
	glm::vec3 SkyColor = glm::vec3(SkyRed, SkyGreen, SkyBlue);

	std::map<textureModel, std::list<entity>> entities;
	TerrainShader terrainShader;
	TerrainRenderer terrainRenderer;
	std::list<terrain> terrains;
	void prepare();

public:
	static const glm::mat4 proj;

	RenderMaster::RenderMaster(Loader& loader);
	void Render(std::vector<Light> & lights, Camera & camera, Player&player, float deltaTime,float TimeOfDay,glm::fvec4 & Culling_plane);
	void ProcessEntity(entity& Entity);
	void ProcessTerrain(terrain & terrain);
	void processWorld(std::list<terrain>&terriansList, std::list<entity>&entitiesList);
	void CleanWorld();
	void CleanUp() ;
	static void EnableBackFaceCulling();
	static void DisableBackFaceCulling();

};

