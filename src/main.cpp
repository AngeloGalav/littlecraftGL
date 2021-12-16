#include <iostream>

#include "include/ShaderMaker.h"
#include "include/Lib.h"
#include "include/geometria.h"
#include "include/GestioneTesto.h"
#include <ft2build.h>
#include FT_FREETYPE_H

int width = 1024;
int height = 800;
int width_i = 400;
int height_i = 400;

int w_up = width;
int h_up = height;
mat4 Projection_text;
string stringa_asse;
string Operazione;
int idfg, idfi;

static unsigned int programId, programId_text, MatrixProj, MatrixProj_txt, MatModel, MatView;
unsigned int VAO_Text, VBO_Text;
vec3 asse = vec3(0.0, 1.0, 0.0);
static float quan= 0;
int selected_obj = -1;
Mesh Cubo, Piano, Piramide, Centri, Sfera;
const float sphere_radius = 3.0f;


bool firstMouse = true;
float lastX = (float)width / 2;
float lastY = (float)height / 2;
float yaw_ = -90.0f;	
float pitch_ = 0.0f;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
float cameraSpeed=0.05;
mat4 Projection, Model, View;
enum {
	NAVIGATION,
	CAMERA_MOVING,
	TRASLATING,
	ROTATING,
	SCALING
} OperationMode;
enum {
	X,
	Y,
	Z
} WorkingAxis;


float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
void update(int a)
{
	 
	glutTimerFunc(10, update, 0);
	glutPostRedisplay();
}

void INIT_SHADER(void)

{
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"shaders/vertexShader_C.glsl";
	char* fragmentShader = (char*)"shaders/fragmentShader_C.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);

	//Generazione del program shader per la gestione del testo
	vertexShader = (char*)"shaders/VertexShader_Text.glsl";
	fragmentShader = (char*)"shaders/FragmentShader_Text.glsl";

	programId_text = ShaderMaker::createProgram(vertexShader, fragmentShader);

}



void crea_VAO_Vector(Mesh* mesh)
{
	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);
	//Genero , rendo attivo, riempio il VBO della geometria dei vertici
	glGenBuffers(1, &mesh->VBO_G);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_G);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertici.size() * sizeof(vec3), mesh->vertici.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//Genero , rendo attivo, riempio il VBO dei colori
	glGenBuffers(1, &mesh->VBO_C);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO_C);
	glBufferData(GL_ARRAY_BUFFER, mesh->colori.size() * sizeof(vec4), mesh->colori.data(), GL_STATIC_DRAW);
	//Adesso carico il VBO dei colori nel layer 2
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	//EBO di tipo indici
	glGenBuffers(1, &mesh->EBO_indici);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO_indici);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indici.size() * sizeof(GLuint), mesh->indici.data(), GL_STATIC_DRAW);
}


void INIT_VAO(void)
{

	crea_cubo(&Cubo);
	crea_VAO_Vector(&Cubo);
	Cubo.nome = "Cubo";
	Cubo.Model = mat4(1.0);
	Cubo.Model = translate(Cubo.Model, vec3(4.5, 0.5, 2.5));
	//CENTRO CUBO
	centri.push_back(vec3(4.5, 0.5, 3.5));
	Cubo.Model = scale(Cubo.Model, vec3(2.0f, 2.0f, 2.0f));
	raggi.push_back(1.5);
	Cubo.Model = translate(Cubo.Model, vec3(-0.5, 0.0, -0.5));
	Scena.push_back(Cubo);
	crea_piano_suddiviso(&Piano);
	crea_VAO_Vector(&Piano);
	
	Piano.nome = "Piano";
	Piano.Model = mat4(1.0);
//	Piano.Model = translate(Piano.Model, vec3(0.5, -1, 0.5));

	//CENTRO PIANO
	centri.push_back(vec3(0.0, 0.0, 0.0));
	Piano.Model = scale(Piano.Model, vec3(100.0f, 1.0f, 100.0f));
	raggi.push_back(1.5);
	Scena.push_back(Piano);
	crea_piramide(&Piramide);
	crea_VAO_Vector(&Piramide);
	Piramide.nome = "Piramide";
	Piramide.Model = mat4(1.0);
	Piramide.Model = translate(Piramide.Model, vec3(-1.5, 0.0, 0.5));
	
	//CENTRO PIRAMIDE
	centri.push_back(vec3(-1.5, 1.0, 0.5));
	
	Piramide.Model = scale(Piramide.Model, vec3(2.0f, 2.0f, 2.0f));
	raggi.push_back(1.5);
	Piramide.Model = translate(Piramide.Model, vec3(-0.5, 0.0, -0.5));
	Scena.push_back(Piramide);
}
void INIT_VAO_Text(void)
{

	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &VAO_Text);
	glGenBuffers(1, &VBO_Text);
	glBindVertexArray(VAO_Text);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Text);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
 
void moveCameraLeft()
{

	glm::vec3 direzione_scorrimento = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));   //direzione perpendicolare al piano individuato da direction e upvector
	ViewSetup.position -= glm::vec4(direzione_scorrimento, .0) * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction * cameraSpeed;;

}

void moveCameraRight()
{
	glm::vec3 direzione_scorrimento = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));
	ViewSetup.position += glm::vec4(direzione_scorrimento, .0) * cameraSpeed;
	ViewSetup.target = ViewSetup.position +ViewSetup.direction;
}

void moveCameraForward() {
	
	ViewSetup.position += ViewSetup.direction * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void moveCameraBack() {
	ViewSetup.position -= ViewSetup.direction * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void modifyModelMatrix(glm::vec3 translation_vector, glm::vec3 rotation_vector, GLfloat angle, GLfloat scale_factor)
{
	//ricordare che mat4(1) costruisce una matrice identit� di ordine 4
	mat4 traslation = glm::translate(glm::mat4(1), translation_vector);
	mat4 scale = glm::scale(glm::mat4(1), glm::vec3(scale_factor, scale_factor, scale_factor));
	mat4 rotation = glm::rotate(glm::mat4(1), angle, rotation_vector);

	//Modifica la matrice di Modellazione dell'oggetto della scena selezionato postmolitplicando per le matrici scale*rotation*traslation

	if (selected_obj > -1)
	{
		Scena[selected_obj].Model = Scena[selected_obj].Model * scale * rotation * traslation;
		centri[selected_obj] = centri[selected_obj] + translation_vector;
		raggi[selected_obj] = raggi[selected_obj] * scale_factor;
	}

}
void keyboardPressedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		moveCameraLeft();
		break;
	case 'd':
		moveCameraRight();
		break;

	case 'w':
		moveCameraForward();
		break;

	case 's':
		moveCameraBack();
		break;

	case 'g':  //Si entra in modalit� di operazione traslazione
				OperationMode = TRASLATING;
				Operazione = "TRASLAZIONE";
				break;
	case 'r': //Si entra in modalit� di operazione rotazione
				OperationMode = ROTATING;
				Operazione = "ROTAZIONE";
				break;
	case 'S':
				OperationMode = SCALING; //Si entra in modalit� di operazione scalatura
				Operazione = "SCALATURA";
				break;
	case 27:
				glutLeaveMainLoop();
				break;
				// Selezione dell'asse
			case 'x':
				WorkingAxis = X;  //Seleziona l'asse X come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
				stringa_asse = " Asse X";
				break;
			case 'y':
				WorkingAxis = Y;  //Seleziona l'asse X come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
				stringa_asse = " Asse Y";
				break;
			case 'z':
				WorkingAxis = Z;
				stringa_asse = " Asse Z";  //Seleziona l'asse X come asse lungo cui effettuare l'operazione selezionata (tra traslazione, rotazione, scalatura)
				break;

			default:
				break;
	}

			// Selezione dell'asse per le trasformazioni
	switch (WorkingAxis) {
			case X:	asse = glm::vec3(1.0, 0.0, 0.0);

				break;
			case Y: asse = glm::vec3(0.0, 1.0, 0.0);

				break;
			case Z: asse = glm::vec3(0.0, 0.0, 1.0);

				break;
			default:
				break;
			}

			glutSetWindow(idfi);
			glutPostRedisplay();

			// I tasti + e -  aggiornano lo spostamento a destra o a sinistra, la rotazione in segno antiorario o in senso orario, la scalatura come amplificazione o diminuizione delle dimensioni

			float amount = .01;
			if (key == '+')
				amount *= 1;

			if (key == '-')
				amount *= -1;


			switch (OperationMode) {

				//la funzione modifyModelMatrix(glm::vec3 translation_vector, glm::vec3 rotation_vector, GLfloat angle, GLfloat scale_factor) 
				// definisce la matrice di modellazione che si vuole postmoltiplicare alla matrice di modellazione dell'oggetto selezionato, per poterlo traslare, ruotare scalare.

			case TRASLATING:
				// si passa angle 0 e scale factor =1, 
				modifyModelMatrix(asse * amount, asse, 0.0f, 1.0f);
				break;
			case ROTATING:
				// SI mette a zero il vettore di traslazione (vec3(0) e ad 1 il fattore di scale
				modifyModelMatrix(glm::vec3(0), asse, amount * 2.0f, 1.0f);
				break;
			case SCALING:
				// SI mette a zero il vettore di traslazione (vec3(0), angolo di rotazione a 0 e ad 1 il fattore di scala 1+amount.
				modifyModelMatrix(glm::vec3(0), asse, 0.0f, 1.0f + amount);
				break;
			}

	glutSetWindow(idfi);
	glutPostRedisplay();

	glutSetWindow(idfg);
	glutPostRedisplay();
}

	
void INIT_CAMERA_PROJECTION(void)
{
	//Imposto la telecamera
	ViewSetup = {};
	ViewSetup.position = glm::vec4(0.0, 0.5, 25.0, 0.0);
	ViewSetup.target = glm::vec4(0.0, 0.0, 0.0, 0.0);
	ViewSetup.direction = ViewSetup.target - ViewSetup.position;
	ViewSetup.upVector = glm::vec4(0.0, 1.0, 0.0, 0.0);


	//Imposto la proiezione prospettica
	PerspectiveSetup = {};
	PerspectiveSetup.aspect = (GLfloat)width / (GLfloat)height;
	PerspectiveSetup.fovY = 45.0f;
	PerspectiveSetup.far_plane = 2000.0f;
	PerspectiveSetup.near_plane = 0.1f;
}


vec3 get_ray_from_mouse(float mouse_x, float mouse_y) {

	
	// mappiamo le coordinate di viewport del mouse [0,width], [height,0] in coordinate normalizzate [-1,1]  
	float x = (2.0f * mouse_x) / width - 1.0;
	float y = 1.0f - (2.0f * mouse_y) / height;
	float z = 1.0f;
	vec3  ray_nds = vec3(x, y, z);
	// clip space
	vec4 ray_clip = vec4(x, y, -1.0, 1.0);

	// eye space
	
	vec4 ray_eye = inverse(Projection) * ray_clip;


	ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

	// world space
	vec3 ray_wor = vec3(inverse(View) * ray_eye);

	ray_wor = normalize(ray_wor);

	return ray_wor;
}

/*controlla se un raggio interseca una sfera. In caso negativo, restituisce false. Rigetta
le intersezioni dietro l'origine del raggio, e pone  intersection_distance all'intersezione p i� vicina.
*/

bool ray_sphere(vec3 ray_origin_wor, vec3 ray_direction_wor, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {
	 
	//Calcoliamo O-C
	vec3 dist_sfera = ray_origin_wor - sphere_centre_wor;
	float b = dot(dist_sfera, ray_direction_wor);
	float f = dot(dist_sfera, dist_sfera) - sphere_radius * sphere_radius;

	float delta = b * b - f;

	if (delta < 0)
		return false;

	if (delta > 0.0f) {
		//calcola le due intersezioni
		float t_a = -b + sqrt(delta);
		float t_b = -b - sqrt(delta);
		*intersection_distance = t_b;

		if (t_a <0.0) {
			if (t_b < 0)
				return false;
		}

		return true;
	}

	if (delta==0) {
		float t = -b + sqrt(delta);
		if (t < 0)
			return false;
		*intersection_distance = t;
		return true;
	}

	return false;
}

void mouse(int button, int state, int x, int y)
{
	float xmouse = x;
	float ymouse = y;
	vec3 ray_wor = get_ray_from_mouse(xmouse,ymouse);

	selected_obj = -1;
	float closest_intersection = 0.0f;
	for (int i=0; i<Scena.size();i++)
	{
		float t_dist = 0.0f;

		if(ray_sphere(ViewSetup.position,ray_wor,centri[i],raggi[i],&t_dist))
		{
			if(selected_obj==-1 || t_dist < closest_intersection )
			{
				selected_obj = i;
				closest_intersection = t_dist;
			}
		}
	}

	printf("Oggetto selezionato %d \n", selected_obj);

	glutSetWindow(idfi);
	glutPostRedisplay();

	glutSetWindow(idfg);
	glutPostRedisplay();

}
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	PerspectiveSetup.aspect = (GLfloat)w / (GLfloat)h;
	Projection = perspective(radians(PerspectiveSetup.fovY), PerspectiveSetup.aspect, PerspectiveSetup.near_plane, PerspectiveSetup.far_plane);
	w_up = w;
	h_up = h;
}

void resize1(int w, int h)
{
	glViewport(0, 0, w, h);
	Projection_text = ortho(0.0f, (float)w, 0.0f, (float)h);

	w_up = w;
	h_up = h;
}

void drawScene(void)
{
	/*
	float timeValue = glutGet(GLUT_ELAPSED_TIME) * 0.001;
	ViewSetup.position.x = sin(timeValue) * 10.0;
	ViewSetup.position.z = cos(timeValue) * 10.0;
	*/
	
	//Passo al Vertex Shader il puntatore alla matrice Projection, che sar� associata alla variabile Uniform mat4 Projection
	//all'interno del Vertex shader. Uso l'identificatio MatrixProj

	glUseProgram(programId);

	Projection = perspective(radians(PerspectiveSetup.fovY), PerspectiveSetup.aspect, PerspectiveSetup.near_plane, PerspectiveSetup.far_plane);

	glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(Projection));


	glClearColor(0.0, 0.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Costruisco la matrice di Vista che applicata ai vertici in coordinate del mondo li trasforma nel sistema di riferimento della camera.
	View = lookAt(vec3(ViewSetup.position), vec3(ViewSetup.target), vec3(ViewSetup.upVector));

	   
	//Passo al Vertex Shader il puntatore alla matrice View, che sar� associata alla variabile Uniform mat4 Projection
   //all'interno del Vertex shader. Uso l'identificatio MatView

	glPointSize(20.0);
	glUniformMatrix4fv(MatView, 1, GL_FALSE, value_ptr(View));
	for (int k =0; k <Scena.size(); k++)
	{
		glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Scena[k].Model));
		glBindVertexArray(Scena[k].VAO);
		  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		 glDrawElements(GL_TRIANGLES, (Scena[k].indici.size()-1)*sizeof(GLuint), GL_UNSIGNED_INT, 0);
 		int ind = Scena[k].indici.size() - 1;
		glDrawElements(GL_POINTS, 1, GL_UNSIGNED_INT, BUFFER_OFFSET(ind * sizeof(GLuint)));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, (Scena[k].indici.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);
 		 
		//Disegno il centro della mesh: un punto in quella posizione
	    glDrawElements(GL_POINTS, 1,GL_UNSIGNED_INT, BUFFER_OFFSET(ind*sizeof(GLuint)));

		glBindVertexArray(0);

	}





	glutSwapBuffers();

}

void drawScene1(void)
{

	glClearColor(0.0, 1.0, 0.0, 0.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Projection_text = ortho(0.0f, (float)w_up, 0.0f, (float)h_up);


	RenderText(programId_text, Projection_text, Operazione, VAO_Text, VBO_Text, 10.0f, 100.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));

	RenderText(programId_text, Projection_text, stringa_asse, VAO_Text, VBO_Text, 10.0f, 70.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));


	RenderText(programId_text, Projection_text, "Oggetto selezionato", VAO_Text, VBO_Text, 10.0f, 50.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));
	if(selected_obj>-1)
	RenderText(programId_text, Projection_text, Scena[selected_obj].nome.c_str(), VAO_Text, VBO_Text, 10.0f, 10.0f, 0.5f, glm::vec3(1.0, 0.0f, 0.2f));

	glutSwapBuffers();

}

void my_passive_mouse(int xpos, int ypos)
{


	float alfa = 0.05; //serve ridimensionare l'offset tra due posizioni successive del mosue
	ypos = height - ypos;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	xoffset *= alfa;
	yoffset *= alfa;
	yaw_ += xoffset;  //aggiorno l'angolo yaw
	pitch_ += yoffset;  // aggiorno l'angolo Pitch

	// Facciamo si' che l'angolo di Picht vari tra -90 e 90.
	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	ViewSetup.direction = vec4(normalize(front), 0.0);
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
	glutSetWindow(idfg);
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	//Inizializzo finestra per il rendering della scena 3d con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	idfg = glutCreateWindow("mimeCraft");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(my_passive_mouse);

	glutKeyboardFunc(keyboardPressedEvent);
	glutTimerFunc(10, update, 0);
	
	glewExperimental = GL_TRUE;
	glewInit();
	INIT_SHADER();
	INIT_VAO();
	INIT_CAMERA_PROJECTION();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Inizializzo finestra per il rendering delle informazioni con tutti i suoi eventi le sue inizializzazioni e le sue impostazioni

	glutInitWindowSize(width_i, height_i);
	glutInitWindowPosition(500, 350);
	idfi = glutCreateWindow("Informazioni");
	glutDisplayFunc(drawScene1);
	glutReshapeFunc(resize1);


	INIT_SHADER();
	INIT_VAO_Text();
	Init_Freetype();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	//QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sar� poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 View (in vertex shader)
	//QUesto identificativo sar� poi utilizzato per il trasferimento della matrice View al Vertex Shader
	MatView = glGetUniformLocation(programId, "View");

	glutMainLoop();
}

