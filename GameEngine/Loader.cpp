#include "Loader.h"
#include<SOIL.h>



RawModel Loader::loadToVAO(ARRAY<glm::vec3> positions, ARRAY<glm::vec2> uv, ARRAY<glm::vec3> Normal, ARRAY<unsigned short> index)
{
	GLuint vaoId =createVAO();
	storeDataInAttributeList<glm::vec3>(0, 3, positions);
	storeDataInAttributeList<glm::vec2>(1, 2, uv);
	storeDataInAttributeList<glm::vec3>(2, 3, Normal);
	LoadIndexBuffer(index);
	glBindVertexArray(0);
	return RawModel(vaoId, index.numberOfElements);

}

RawModel Loader::loadToVAO(ARRAY<glm::vec2> positions)
{
	GLuint vaoId = createVAO();
	storeDataInAttributeList<glm::vec2>(0, 2, positions);
	glBindVertexArray(0);
	return RawModel(vaoId, positions.numberOfElements);
}

RawModel Loader::loadToVAO(ARRAY<glm::vec3> positions)
{
	GLuint vaoId = createVAO();
	storeDataInAttributeList<glm::vec3>(0, 3, positions);
	glBindVertexArray(0);
	return RawModel(vaoId, positions.numberOfElements);
}

GLuint Loader::createVAO()
{
	
	numberofvao++;
	glGenVertexArrays(1, &VaoIDes[numberofvao]);
	glBindVertexArray(VaoIDes[numberofvao]);
	return VaoIDes[numberofvao];

}

GLuint Loader::createVBO()
{
	
	numberofvbo++;
	glGenBuffers(1, &VboIDes[numberofvbo]);
	return VboIDes[numberofvbo];
}

GLuint Loader::LoadIndexBuffer(ARRAY<unsigned short> index){

	numberofindexBuffer++;
	glGenBuffers(1, &VIboIDes[numberofindexBuffer]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VIboIDes[numberofindexBuffer]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size, index.arrayPointer, GL_STATIC_DRAW);
	return VIboIDes[numberofindexBuffer];

}

GLuint Loader::loadTexture(char * filepath)
{

	numberofTexture++;
	int width, height;
	textures[numberofTexture]= SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);
	if (!textures[numberofTexture])
	{
		std::cout << "failed to laod image" << std::endl;
	}
	glGenTextures(1, &GLTextureIDes[numberofTexture]);
	glBindTexture(GL_TEXTURE_2D, GLTextureIDes[numberofTexture]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[numberofTexture]);
	SOIL_free_image_data(textures[numberofTexture]);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	
	return GLTextureIDes[numberofTexture];

}

GLuint Loader::loadCubeMap(std::string filepath)
{
	int width, height;
	unsigned char* qubeTexArray[6];

	std::string tempString = "./res/" + filepath + "right.png";
	char* path = const_cast<char *>(tempString.c_str());
	qubeTexArray[0] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	tempString = "./res/" + filepath + "left.png";
	path = const_cast<char *>(tempString.c_str());
	qubeTexArray[1] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	tempString = "./res/" + filepath + "top.png";
	path = const_cast<char *>(tempString.c_str());
	qubeTexArray[2] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	tempString = "./res/" + filepath + "bottom.png";
	path = const_cast<char *>(tempString.c_str());
	qubeTexArray[3] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	tempString = "./res/" + filepath + "front.png";
	path = const_cast<char *>(tempString.c_str());
	qubeTexArray[4] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	tempString = "./res/" + filepath + "back.png";
	path = const_cast<char *>(tempString.c_str());
	qubeTexArray[5] = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);

	for (int i = 0; i < 6; i++)
	{
		if (!qubeTexArray[i])
		{
			std::cout << "couldent load " << i << "picture form" << filepath.c_str()<< "box" << std::endl;
		}
		
	}

	numberofTexture++;
	glGenTextures(1, &GLTextureIDes[numberofTexture]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, GLTextureIDes[numberofTexture]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[0]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[1]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[2]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[3]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[5]);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, qubeTexArray[4]);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return GLTextureIDes[numberofTexture];
}

template<class T>
void Loader::storeDataInAttributeList(int attributeNumber, int Coordinatesize, ARRAY<T> data)
{
	GLuint vboID = createVBO();
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size, data.arrayPointer, GL_STATIC_DRAW);
	glEnableVertexAttribArray(attributeNumber);
	glVertexAttribPointer(attributeNumber, Coordinatesize,GL_FLOAT, false, 0, 0);

}

Loader::Loader()
{
}


Loader::~Loader()
{
	for (int i = 0; i <= numberofvao; i++)
	{
		glDeleteVertexArrays(1, &VaoIDes[i]);
	}
	for (int i = 0; i <= numberofvbo; i++)
	{
		glDeleteBuffers(1, &VboIDes[i]);
	}
	for (int i = 0; i <= numberofindexBuffer; i++)
	{
		glDeleteBuffers(1, &VIboIDes[i]);
	}
	for (int i = 0; i < numberofTexture; i++)
	{
		glDeleteTextures(1, &GLTextureIDes[i]);
	}
}


