#ifndef _cShaderManager_HG_
#define _cShaderManager_HG_

#include "GraphicsCommon.h"
#include <string>
#include <vector>
#include <map>
#include "cBasicTextureManager.h"
#include <glm/gtc/type_ptr.hpp>	// For glm::value_ptr
#include <glm/glm.hpp>		// For the vec3
#include <unordered_map>
//#include "../PandaEngine/GraphicsCommon.h"	// For all the OpenGL calls, etc.

struct Material
{
	std::string name;
	GLint shaderID;
	Texture* texture;

	std::unordered_map<std::string, GLuint> textureBindings;

	void SetAttribute(GLuint layoutLocation, int size, int sizeOfStruct,int offset)
	{
		glEnableVertexAttribArray(layoutLocation);
		glVertexAttribPointer(layoutLocation, size, GL_FLOAT, GL_FALSE, sizeOfStruct, (void*)offset);
	}

	void SetUniform1f(std::string name, float value)
	{
		glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
	}

	void SetUniform3f(std::string name, glm::vec3 value)
	{
		glUniform3f(glGetUniformLocation(shaderID, name.c_str()), value.x, value.y, value.z);
	}

	void SetMat4(std::string name, glm::mat4 value)
	{
		glGetError();
		GLuint location = glGetUniformLocation(shaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));

		CHECK_GL_ERROR();
	}

	void SetTexture(std::string textureNameInShader, Texture* texture)
	{
	//	GLuint location = glGetUniformLocation(shaderID, textureNameInShader.c_str());
		textureBindings[textureNameInShader] = texture->getTextureNumber();

	//	glUseProgram(shaderID);
	//	glUniform1i(glGetUniformLocation(shaderID, textureNameInShader.c_str()), textureUnit);

	//	glActiveTexture(GL_TEXTURE0 + textureUnit);
	//	glBindTexture(GL_TEXTURE_2D, texture->getTextureNumber());
	}
};

class cShaderManager
{
public:
	class cShader  {
	public:
		cShader();
		~cShader();
		enum eShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			UNKNOWN
		};
		eShaderType shaderType;
		std::string getShaderTypeString(void);

		unsigned int ID;	// or "name" from OpenGL
		std::vector<std::string> vecSource;
		bool bSourceIsMultiLine;
		std::string fileName;
			
	};

	class cShaderProgram {
	public:
		cShaderProgram() : ID(0) {};
		~cShaderProgram() {};
		unsigned int ID;	// ID from OpenGL (calls it a "name")
		std::string friendlyName;	// We give it this name

		// TODO: For the students to do, because it's FUN, FUN, FUN
		std::map< std::string /*name of uniform variable*/,
		          int /* uniform location ID */ > 
								mapUniformName_to_UniformLocation;
		// Returns -1 (just like OpenGL) if NOT found
		int getUniformID_From_Name(std::string name);
		// Look up the uniform location and save it.
		bool LoadUniformLocation(std::string variableName);

	};

	cShaderManager();
	~cShaderManager();

	bool useShaderProgram( unsigned int ID );
	bool useShaderProgram( std::string friendlyName );
	bool createProgramFromFile( std::string friendlyName, 
		                        cShader &vertexShad, 
					            cShader &fragShader, cShader& tessControl, cShader& tessEval, Material &material);
	void setBasePath( std::string basepath );
	unsigned int getIDFromFriendlyName( std::string friendlyName );

	// Used to load the uniforms. Returns NULL if not found.
	cShaderProgram* pGetShaderProgramFromFriendlyName( std::string friendlyName );


	// Clears last error
	std::string getLastError(void);

	static cShaderManager* getInstance(void);
private:
	// Returns an empty string if it didn't work
	bool m_loadSourceFromFile( cShader &shader );
	std::string m_basepath;

	bool m_compileShaderFromSource( cShader &shader, std::string &error );
	// returns false if no error
	bool m_wasThereACompileError( unsigned int shaderID, std::string &errorText );
	bool m_wasThereALinkError( unsigned int progID, std::string &errorText );

	std::string m_lastError;

	std::map< unsigned int /*ID*/, cShaderProgram > m_ID_to_Shader;
	std::map< std::string /*name*/, unsigned int /*ID*/ > m_name_to_ID;
};

#endif