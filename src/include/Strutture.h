#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "Lib.h"
 
#include <string>

typedef struct {
	vector<vec3> vertici;
	vector<vec4> colori;
	vector <GLuint>  indici;
	vector<vec3> normali;
	vector<vec2> texCoords;
	mat4 Model;
	int sceltaVS;
	int sceltaFS;
	GLuint VAO;
	GLuint VBO_G;
	GLuint VBO_C;
	GLuint VBO_normali;
	GLuint EBO_indici;
	GLuint VBO_coord_texture;
	string nome;
} Mesh;
static vector<Mesh> Scena;
static vector<vec3> centri;
static vector<float> raggi;
typedef enum {
	GOURAD_SHADING,
	PHONG_SHADING,
	ONDE_SHADING,
	BANDIERA_SHADING,
} ShaderOption;


struct {
	vec4 position;
	vec4 target;
	vec4 upVector;
	vec4 direction;
} ViewSetup;

struct {
	float fovY, aspect, near_plane, far_plane;
} PerspectiveSetup;

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

#endif