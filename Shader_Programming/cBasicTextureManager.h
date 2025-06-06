#ifndef _cBasicTextureManager_HG_
#define _cBasicTextureManager_HG_

#include <string>
#include <map>
//#include "CTextureFromBMP.h"
#include "Texture.h"
// LoadPNG

class cBasicTextureManager
{
public:
	~cBasicTextureManager();
	Texture* Create2DTextureFromBMPFile( std::string textureFileName, bool bGenerateMIPMap);

	// Picks a random texture from the textures loaded
	std::string PickRandomTexture(void);

	bool CreateCubeTextureFromBMPFiles( std::string cubeMapName, 
		                                std::string posX_fileName, std::string negX_fileName, 
		                                std::string posY_fileName, std::string negY_fileName, 
										std::string posZ_fileName, std::string negZ_fileName, 
										bool bIsSeamless, std::string &errorString );


	// returns 0 on error
	GLuint getTextureIDFromName( std::string textureFileName );

	void SetBasePath(std::string basepath);
	std::map< std::string, Texture* > textureMap;

private:
	std::string m_basePath;
	std::string m_lastError;
	void m_appendErrorString( std::string nextErrorText );
	void m_appendErrorStringLine( std::string nextErrorTextLine );

	//std::map< std::string, CTextureFromBMP* > m_map_TexNameToTexture;


};

#endif
