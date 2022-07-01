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

vector<Mesh> Scena;
vector<vec3> centri;
vector<float> raggi;

int width = SCREEN_WIDTH;
int height = SCREEN_HEIGHT;

int w_up = width;
int h_up = height;

Camera mainCamera;
Raycaster raycast;

int main_window_id;

static unsigned int programId, MatrixProj, MatModel, MatView;
int selected_obj = -1;
Quad testQuad(vec4(0.0, 1.0f, 0.0, 1.0f));
Quad testQuad_2(vec4(1.0f, 0.0f, 0.0, 1.0f));
Quad testQuad_3(vec4(0.0f, 0.0f, 1.0f, 1.0f));
Quad testQuad_4(vec4(0.0, 1.0f, 1.0f, 1.0f));
Quad testQuad_5(vec4(1.0f, 1.0f, 0.0, 1.0f));
Quad testQuad_6(vec4(1.0f, 0.0f, 1.0f, 1.0f));


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
	testQuad.crea_VAO_Vector();
	testQuad.Model = mat4(1.0);
	testQuad.Model = scale(testQuad.Model, vec3(2.0f, 2.0f, 2.0f));
	testQuad.Model = translate(testQuad.Model, vec3(0.0, 0.0, 0.0));
	Scena.push_back((Mesh) testQuad);

	testQuad_2.crea_VAO_Vector();
	testQuad_2.Model = mat4(1.0);
	testQuad_2.Model = scale(testQuad_2.Model, vec3(2.0f, 2.0f, 2.0f));
	testQuad_2.Model = translate(testQuad_2.Model, vec3(0.0, 0.0, 2.0));
	Scena.push_back((Mesh) testQuad_2);

	testQuad_3.crea_VAO_Vector();
	testQuad_3.Model = mat4(1.0);
	testQuad_3.Model = scale(testQuad_3.Model, vec3(2.0f, 2.0f, 2.0f));
	testQuad_3.Model = translate(testQuad_3.Model, vec3(0.0, 0.0, 0.0));
	testQuad_3.Model = rotate(testQuad_3.Model, radians(90.0f), vec3(0, 1, 0));
	Scena.push_back((Mesh) testQuad_3);

	testQuad_4.crea_VAO_Vector();
	testQuad_4.Model = mat4(1.0);
	testQuad_4.Model = scale(testQuad_4.Model, vec3(2.0f, 2.0f, 2.0f));
	testQuad_4.Model = rotate(testQuad_4.Model, radians(-90.0f), vec3(0, 1, 0));
	testQuad_4.Model = translate(testQuad_4.Model, vec3(1.0, 0.0, 0.0));
	Scena.push_back((Mesh) testQuad_4);

	// testQuad_5.crea_VAO_Vector();
	// testQuad_5.Model = mat4(1.0);
	// testQuad_5.Model = scale(testQuad_5.Model, vec3(2.0f, 2.0f, 2.0f));
	// testQuad_5.Model = translate(testQuad_5.Model, vec3(0, 1.5, 0.0));
	// testQuad_5.Model = rotate(testQuad_5.Model, radians(90.0f), vec3(1, 0, 0));
	// Scena.push_back((Mesh) testQuad_5);

	// testQuad_6.crea_VAO_Vector();
	// testQuad_6.Model = mat4(1.0);
	// testQuad_6.Model = translate(testQuad_6.Model, vec3(0.0, 0.0, 0.0));
	// testQuad_6.Model = rotate(testQuad_6.Model, radians(-90.0f), vec3(1, 0, 0));
	// testQuad_6.Model = scale(testQuad_6.Model, vec3(2.0f, 2.0f, 2.0f));
	// Scena.push_back((Mesh) testQuad_6);
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
	for (int k = 0; k < Scena.size(); k++)
	{
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[k].Model));
		glBindVertexArray(Scena[k].VAO);
		glDrawElements(GL_TRIANGLES, (Scena[k].indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(0);
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
