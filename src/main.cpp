#include <iostream>
#include "include/definitions.h"
#include "include/ShaderMaker.h"
#include "include/Lib.h"
#include "include/Camera.h"
#include "include/InputHandler.h"
#include "include/Mesh.h"
#include "include/EventHandler.h"
#include "include/FastNoiseLite.h"
#include "include/Chunk.h"
#include "include/Texture.h"

int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

int main_window_id;

GLuint render_mode = GL_FILL;

static unsigned int programId, MatrixProj, MatModel, MatView;
static unsigned int texture_programId, MatrixProj_texture, MatModel_texture, MatView_texture;

World main_world;

Camera mainCamera;
Texture textureMaker;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
mat4 Projection, Model, View;

void init(void){
	mainCamera = Camera();
	mainCamera.initCamera();

	char *vertexShader = (char *) "shaders/plain.vert.glsl";
	char *fragmentShader = (char *) "shaders/plain.frag.glsl";
	char *fragmentShader_texture = (char *) "shaders/texture.frag.glsl";
	char *vertexShader_texture = (char *) "shaders/texture.vert.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	texture_programId = ShaderMaker::createProgram(vertexShader_texture, fragmentShader_texture);
	glUseProgram(programId);

	MatModel = glGetUniformLocation(programId, "Model");

	// inizializza la texture usando il programId dello shader
	textureMaker.initTexture(&texture_programId);

	main_world.initWorld();
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

	textureMaker.useTexture();

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
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
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

	init();

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
