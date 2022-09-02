#include <iostream>
#include "include/definitions.h"
#include "include/ShaderMaker.h"
#include "include/Lib.h"
#include "include/Camera.h"
#include "include/Raycaster.h"
#include "include/InputHandler.h"
#include "include/Mesh.h"
#include "include/EventHandler.h"
#include "include/FastNoiseLite.h"
#include "include/Chunk.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

Raycaster raycast;
int main_window_id;

GLuint render_mode = GL_FILL;

static unsigned int programId, MatrixProj, MatModel, MatView;
static unsigned int texture_programId, MatrixProj_texture, MatModel_texture, MatView_texture;

int texture_width, texture_height, nrChannels;

World main_world;
Cube look_cube(LOOKCUBE_COLOR);

Camera mainCamera;

unsigned int texture;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
mat4 Projection, Model, View;

void INIT_SHADER(void)
{
	char *vertexShader = (char *) "shaders/plain.vert.glsl";
	char *fragmentShader = (char *) "shaders/plain.frag.glsl";
	char *fragmentShader_texture = (char *) "shaders/texture.frag.glsl";
	char *vertexShader_texture = (char *) "shaders/texture.vert.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	texture_programId = ShaderMaker::createProgram(vertexShader_texture, fragmentShader_texture);
	glUseProgram(programId);

	MatModel = glGetUniformLocation(programId, "Model");
}

void INIT_VAO(void)
{
	main_world.initWorld();
}

///TODO: Should move this inside a texture class
void INIT_TEXTURES(){
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);  // flippa la texture
	unsigned char *data = stbi_load("res/texture_atlas.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glUniform1i(glGetUniformLocation(texture_programId, "texture_quad"), 0);
}


void drawScene(void)
{
	// crea il cielo azzurro
	glClearColor(52.9/100.0, 80.8/100.0, 92.2/100.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //GL_DEPTH_BUFFER_BIT risolve il bug dello z-indexing su linux
	// Passo al Vertex Shader il puntatore alla matrice Projection, che sar� associata alla variabile Uniform mat4 Projection
	// all'interno del Vertex shader. Uso l'identificatio MatrixProj

	glUseProgram(programId);
	Projection = perspective(radians(mainCamera.PerspectiveSetup.fovY), mainCamera.PerspectiveSetup.aspect, mainCamera.PerspectiveSetup.near_plane, mainCamera.PerspectiveSetup.far_plane);
	
	glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(Projection));

	// Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
	View = lookAt(vec3(mainCamera.ViewSetup.position), vec3(mainCamera.ViewSetup.target), vec3(mainCamera.ViewSetup.upVector));

	// Passo al Vertex Shader il puntatore alla matrice View, che sar� associata alla variabile Uniform mat4 Projection
	// all'interno del Vertex shader. Uso l'identificatio MatView
	glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));	

	main_world.updateGizmos();
	main_world.drawGizmos(MatModel);
	
	// lo stesso che abbiamo fatto prima lo dobbiamo ripetere per il nostro nuovo shader
	glUseProgram(texture_programId);
	glUniformMatrix4fv(MatrixProj_texture, 1, GL_FALSE, value_ptr(Projection));
	glUniformMatrix4fv(MatView_texture, 1, GL_FALSE, value_ptr(View));

	glBindTexture(GL_TEXTURE_2D, texture);

	// renderizza il mondo
	main_world.renderWorld(MatModel_texture);

	glutSwapBuffers();

	main_world.updateWorld();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// Inizializzo finestra per il rendering della scena 3d con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	main_window_id = glutCreateWindow("littleCraft");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(my_passive_mouse);

	glutKeyboardFunc(keyboardPressedEvent);
	glutTimerFunc(10, update, 0);

	// Inizializzo finestra per il rendering delle informazioni con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni
	glewExperimental = GL_TRUE;
	glewInit();
	mainCamera = Camera();
	mainCamera.initCamera();
	INIT_TEXTURES();
	INIT_SHADER();
	INIT_VAO();

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	MatrixProj_texture = glGetUniformLocation(texture_programId, "Projection");

	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");
	MatModel_texture = glGetUniformLocation(texture_programId, "Model");
	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 View (in vertex shader)
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice View al Vertex Shader
	MatView = glGetUniformLocation(programId, "View");
	MatView_texture = glGetUniformLocation(texture_programId, "View");

	glutMainLoop();
}
