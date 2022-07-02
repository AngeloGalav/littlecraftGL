#include <iostream>
#include "include/definitions.h"
#include "include/ShaderMaker.h"
#include "include/Lib.h"
#include "include/Camera.h"
#include "include/Raycaster.h"
#include "include/InputHandler.h"
#include "include/GestioneTesto.h"
#include "include/Mesh.h"
#include "include/EventHandler.h"
#include "include/Quad.h"
#include "include/Cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

vector<Cube*> Scena;
vector<Mesh*> Scena_Extras;

vector<vec3> centri;
vector<float> raggi;

int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

int w_up = width;
int h_up = height;

Camera mainCamera;
Raycaster raycast;

int main_window_id;

// debug time
int t = -180;

static unsigned int programId, MatrixProj, MatModel, MatView;
int selected_obj = -1;
Quad purpleQuad(vec4(1.0f, 0.0f, 1.0f, 1.0f));

int texture_width, texture_height, nrChannels;
unsigned char *data = stbi_load("res/texture_atlas.png", &texture_width, &texture_height, &nrChannels, 0);

Cube cubo;


#define BUFFER_OFFSET(i) ((char *)NULL + (i))
mat4 Projection, Model, View;

void INIT_SHADER(void)
{
	GLenum ErrorCheckValue = glGetError();

	char *vertexShader = (char *)"shaders/vertexShader_C.glsl";
	char *fragmentShader = (char *)"shaders/fragmentShader_C.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);
}

void INIT_VAO(void)
{
	purpleQuad.crea_VAO_Vector();
	purpleQuad.Model = mat4(1.0);
	purpleQuad.Model = scale(purpleQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	purpleQuad.Model = translate(purpleQuad.Model, vec3(-5.0f, 0.0, 1.0f));
	Scena_Extras.push_back((Mesh*) &purpleQuad);

	cubo.initCube();
	Scena.push_back(&cubo);
}

void INIT_TEXTURES(){
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("res/texture_atlas.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}


void drawScene(void)
{
	// crea il cielo azzurro
	glClearColor(52.9/100.0, 80.8/100.0, 92.2/100.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	
	// Draw scene elements
	for (int k = 0; k < Scena.size(); k++){
		Scena[k]->drawMesh(MatModel);
	}

	// Draw scene elements
	for (int k = 0; k < Scena_Extras.size(); k++){
		Scena_Extras[k]->drawMesh(MatModel);
	}

	glutSwapBuffers();

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
	INIT_TEXTURES();
	INIT_SHADER();
	INIT_VAO();

	mainCamera = Camera();
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");
	// Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 View (in vertex shader)
	// QUesto identificativo sar� poi utilizzato per il trasferimento della matrice View al Vertex Shader
	MatView = glGetUniformLocation(programId, "View");

	glutMainLoop();
}
