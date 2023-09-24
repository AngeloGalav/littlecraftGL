#include "include/InputHandler.h"
#include "include/Cube.h"
#include "include/Mesh.h"
#include "include/World.h"

extern Camera mainCamera;
extern World main_world;
extern GLuint render_mode;

bool firstMouse = true;
float lastX = (float)width / 2;
float lastY = (float)height / 2;

// Valori iniziali degli angoli
float yaw_ = -90.0f;
float pitch_ = 0.0f;

float keyboard_rotation_speed = 5.0f;

/** Key callback function.
 *
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// wasd
    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		mainCamera.moveCameraLeft();
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        mainCamera.moveCameraRight();
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		mainCamera.moveCameraForward();
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		mainCamera.moveCameraBack();

	// keyboard camera rotation
	if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT))
        rotateCameraKeyboard(-1, 0);
	if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
        rotateCameraKeyboard(1, 0);
    if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT))
        rotateCameraKeyboard(0, 1);
	if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT))
        rotateCameraKeyboard(0, -1);

	// action buttons
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		main_world.removeBlock();
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		main_world.addBlock();

	if (key == GLFW_KEY_X && action == GLFW_PRESS){
		if (render_mode == GL_LINE) render_mode = GL_FILL;
		else render_mode = GL_LINE;
	}
}

/** Cambia la visuale in base alla posizione del mouse, senza che si faccia click. 
 * 
 */
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	rotateCamera(xpos, ypos);
}

// funzione che ruota la telecamera durante il gioco, usando la tastiera 
void rotateCameraKeyboard(int x, int y) {
	yaw_ += x*keyboard_rotation_speed;   // aggiorno l'angolo yaw
	pitch_ += y*keyboard_rotation_speed; // aggiorno l'angolo Pitch

	// Fissiamo i limiti per routare la visuale verticalmente
	if (pitch_ > 179.0f) pitch_ = 179.0f;
	if (pitch_ < -179.0f) pitch_ = -179.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	mainCamera.ViewSetup.direction = vec4(normalize(front), 0.0);
	mainCamera.ViewSetup.target = mainCamera.ViewSetup.position + mainCamera.ViewSetup.direction;
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
	if (pitch_ > 179.0f)
		pitch_ = 179.0f;
	if (pitch_ < -179.0f)
		pitch_ = -179.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front.y = sin(glm::radians(pitch_));
	front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	mainCamera.ViewSetup.direction = vec4(normalize(front), 0.0);
	mainCamera.ViewSetup.target = mainCamera.ViewSetup.position + mainCamera.ViewSetup.direction;
}