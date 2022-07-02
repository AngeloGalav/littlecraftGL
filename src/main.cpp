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

vector<Mesh*> Scena;
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
Quad greenQuad(vec4(0.0, 1.0f, 0.0, 1.0f));
Quad redQuad(vec4(1.0f, 0.0f, 0.0, 1.0f));
Quad blueQuad(vec4(0.0f, 0.0f, 1.0f, 1.0f));
Quad cyanQuad(vec4(0.0, 1.0f, 1.0f, 1.0f));
Quad yellowQuad(vec4(1.0f, 1.0f, 0.0, 1.0f));
Quad purpleQuad(vec4(1.0f, 0.0f, 1.0f, 1.0f));


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
	greenQuad.crea_VAO_Vector();
	greenQuad.Model = mat4(1.0);
	greenQuad.Model = scale(greenQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	Scena.push_back((Mesh*) &greenQuad);

	redQuad.crea_VAO_Vector();
	redQuad.Model = mat4(1.0);
	redQuad.Model = scale(redQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	redQuad.Model = translate(redQuad.Model, vec3(0.0, 0.0, -2.0f));
	Scena.push_back((Mesh*) &redQuad);

	cyanQuad.crea_VAO_Vector();
	cyanQuad.Model = mat4(1.0);
	cyanQuad.Model = scale(cyanQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	cyanQuad.Model = translate(cyanQuad.Model, vec3(1.0f, 0.0, -1.0f));
	cyanQuad.Model = rotate(cyanQuad.Model, radians(-90.0f), vec3(0, 1, 0));
	Scena.push_back((Mesh*) &cyanQuad);


	blueQuad.crea_VAO_Vector();
	blueQuad.Model = mat4(1.0);
	blueQuad.Model = scale(blueQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	blueQuad.Model = translate(blueQuad.Model, vec3(-1.0f, 0.0, -1.0f));
	blueQuad.Model = rotate(blueQuad.Model, radians(90.0f), vec3(0, 1, 0));
	Scena.push_back((Mesh*) &blueQuad);

	yellowQuad.crea_VAO_Vector();
	yellowQuad.Model = mat4(1.0);
	yellowQuad.Model = scale(yellowQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	yellowQuad.Model = translate(yellowQuad.Model, vec3(0, 1.0f, -1.0f));
	yellowQuad.Model = rotate(yellowQuad.Model, radians(90.0f), vec3(1, 0, 0));
	Scena.push_back((Mesh*) &yellowQuad);

	purpleQuad.crea_VAO_Vector();
	purpleQuad.Model = mat4(1.0);
	purpleQuad.Model = scale(purpleQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	purpleQuad.Model = translate(purpleQuad.Model, vec3(0.0, -1.0f, -1.0f));
	purpleQuad.Model = rotate(purpleQuad.Model, radians(-90.0f), vec3(1, 0, 0));
	Scena.push_back((Mesh*) &purpleQuad);
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

	// glPointSize(20.0);
	glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));
	
	
	// Draw scene elements
	for (int k = 0; k < Scena.size(); k++){
		Scena[k]->drawMesh(MatModel);
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
