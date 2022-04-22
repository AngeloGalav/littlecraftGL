#include "include/Camera.h"

Camera::Camera(){
    cameraSpeed = 0.5;
    INIT_CAMERA_PROJECTION();
}

void Camera::moveCameraLeft()
{

	glm::vec3 direzione_scorrimento = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));   //direzione perpendicolare al piano individuato da direction e upvector
	ViewSetup.position -= glm::vec4(direzione_scorrimento, .0) * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction * cameraSpeed;;

}

void Camera::moveCameraRight()
{
	glm::vec3 direzione_scorrimento = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));
	ViewSetup.position += glm::vec4(direzione_scorrimento, .0) * cameraSpeed;
	ViewSetup.target = ViewSetup.position +ViewSetup.direction;
}

void Camera::moveCameraForward() {
	
	ViewSetup.position += ViewSetup.direction * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void Camera::moveCameraBack() {
	ViewSetup.position -= ViewSetup.direction * cameraSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void Camera::INIT_CAMERA_PROJECTION(void)
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