#include "include/InputHandler.h"
#include "include/Raycaster.h"
#include "include/Strutture.h"
#include "include/Mesh.h"

extern Camera mainCamera;
extern Raycaster raycast;
extern int selected_obj;
extern vector<Mesh> Scena;
extern vector<vec3> centri;
extern vector<float> raggi;

bool firstMouse = true;
float lastX = (float)width / 2;
float lastY = (float)height / 2;
float yaw_ = -90.0f;
float pitch_ = 0.0f;


void keyboardPressedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		mainCamera.moveCameraLeft();
		break;
	case 'd':
		mainCamera.moveCameraRight();
		break;

	case 'w':
		mainCamera.moveCameraForward();
		break;

	case 's':
		mainCamera.moveCameraBack();
		break;
	// case 'j':
	// 	mainCamera.forceRotation(-1);
	// 	break;
	// case 'k':
	// 	mainCamera.forceRotation(1);
	// 	break;


	default:
		break;
	}
}


void mouse(int button, int state, int x, int y)
{
	float xmouse = x;
	float ymouse = y;
	vec3 ray_wor = raycast.get_ray_from_mouse(xmouse, ymouse);

	//selected_obj = -1;
	float closest_intersection = 0.0f;
    selected_obj = -1;
	// for (int i = 0; i < Scena.size(); i++)
	// {
	// 	float t_dist = 0.0f;

	// 	if (raycast.ray_sphere(mainCamera.ViewSetup.position, ray_wor, centri[i], raggi[i], &t_dist))
	// 	{
	// 		if (selected_obj == -1 || t_dist < closest_intersection)
	// 		{
	// 			selected_obj = i;
	// 			closest_intersection = t_dist;
	// 		}
	// 	}
	// }

	// stato per controllare che il bottone destro del mouse sia stato effettivamente cliccato
	if (button == GLUT_RIGHT_BUTTON)
    {
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    }

	rotateCamera(x, y);

	// printf("Oggetto selezionato %d \n", selected_obj);
}


/**
 * @brief Cambia la visuale in base alla posizione del mouse, senza che si faccia click. 
 * TODO: (da modificare con un algoritmo migliore)
 * 
 */
void my_passive_mouse(int xpos, int ypos) // camera rotation function
{

	rotateCamera(xpos, ypos);
	
	// glutSetCursor(GLUT_CURSOR_INHERIT);
	// float alfa = 0.05; // serve ridimensionare l'offset tra due posizioni successive del mosue
	// ypos = height - ypos;
	// if (firstMouse)
	// {
	// 	lastX = xpos;
	// 	lastY = ypos;
	// 	firstMouse = false;
	// }

	// // inserire codice per lo scan della velocità del mouse qui

	// float xoffset = xpos - lastX;
	// float yoffset = ypos - lastY;
	// lastX = xpos;
	// lastY = ypos;

	// xoffset *= alfa;
	// yoffset *= alfa;
	// yaw_ += xoffset;   // aggiorno l'angolo yaw
	// pitch_ += yoffset; // aggiorno l'angolo Pitch

	// // Facciamo si' che l'angolo di Picht vari tra -90 e 90.
	// if (pitch_ > 89.0f)
	// 	pitch_ = 89.0f;
	// if (pitch_ < -89.0f)
	// 	pitch_ = -89.0f;

	// glm::vec3 front;
	// front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	// front.y = sin(glm::radians(pitch_));
	// front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	// mainCamera.ViewSetup.direction = vec4(normalize(front), 0.0);
	// mainCamera.ViewSetup.target = mainCamera.ViewSetup.position + mainCamera.ViewSetup.direction;

}

// funzione che ruota la telecamera durante il gioco
void rotateCamera(int xpos, int ypos) {
	float alfa = 0.05; // serve ridimensionare l'offset tra due posizioni successive del mosue
	ypos = height - ypos;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	// inserire codice per lo scan della velocità del mouse qui

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	xoffset *= alfa;
	yoffset *= alfa;
	yaw_ += xoffset;   // aggiorno l'angolo yaw
	pitch_ += yoffset; // aggiorno l'angolo Pitch

	// Facciamo si' che l'angolo di Picht vari tra -90 e 90.
	if (pitch_ > 89.0f)
		pitch_ = 89.0f;
	if (pitch_ < -89.0f)
		pitch_ = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	mainCamera.ViewSetup.direction = vec4(normalize(front), 0.0);
	mainCamera.ViewSetup.target = mainCamera.ViewSetup.position + mainCamera.ViewSetup.direction;
}

void onMouseEvent(int button, int state, int x, int y)
{
//    if(state == GLUT_DOWN){
//       if(button == GLUT_RIGHT_BUTTON)
//          glutMotionFunc(onRightMouseEvent);
//       else if(button == GLUT_LEFT_BUTTON)
//          glutMotionFunc(onLeftMouseEvent);
//    }
}

// void onLeftMouseEvent(int x, int y){
// 	rotateCamera(x, y);
// }

void onRightMouseEvent(int x , int y){
	// evento per selezionare un cubo(?)
	// evento action?
}