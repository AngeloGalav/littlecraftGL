#include "include/Camera.h"
#include "include/InputHandler.h"
#include <iostream>

Camera::Camera(){
    playerSpeed = 0.5;
    initCamera();
}

void Camera::moveCameraLeft()
{
	// direzione perpendicolare al piano individuato da direction e upvector
	glm::vec3 direction = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));
	ViewSetup.position -= glm::vec4(direction, 0.0) * playerSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void Camera::moveCameraRight()
{
	glm::vec3 direction = glm::cross(vec3(ViewSetup.direction), glm::vec3(ViewSetup.upVector));
	ViewSetup.position += glm::vec4(direction, 0.0) * playerSpeed;
	ViewSetup.target = ViewSetup.position +ViewSetup.direction;
}

void Camera::moveCameraForward() {
	ViewSetup.position += ViewSetup.direction * playerSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void Camera::moveCameraBack() {
	ViewSetup.position -= ViewSetup.direction * playerSpeed;
	ViewSetup.target = ViewSetup.position + ViewSetup.direction;
}

void Camera::initCamera(void)
{
	//Imposto la telecamera
	// ViewSetup = {};
	ViewSetup.position = glm::vec4(20, 0.0, 20, 0.0);
	ViewSetup.target = glm::vec4(0.0, 0.0, 0.0, 0.0);
	ViewSetup.direction = ViewSetup.target - ViewSetup.position;
	ViewSetup.upVector = glm::vec4(0.0, 1.0, 0.0, 0.0);


	//Imposto la proiezione prospettica
	// PerspectiveSetup = {};
	PerspectiveSetup.aspect = (GLfloat)width / (GLfloat)height;
	PerspectiveSetup.fovY = 45.0f;
	PerspectiveSetup.far_plane = 2000.0f;
	PerspectiveSetup.near_plane = 0.1f;

	// workaround per risolvere il bug del comportamento della camera
	// all'avvio dell'app
	rotateCamera(0,0);
}

/** General purpose function/wrapper to easily get the camera direction
 *
 */
vec3 Camera::get_ray_from_camera(){
	return vec3(ViewSetup.direction.x, ViewSetup.direction.y, ViewSetup.direction.z);
}


// void function () {
// 	std::array<glm::vec3, 8> _cameraFrustumCornerVertices{
// 		{
// 			{ -1.0f, -1.0f, 1.0f }, { 1.0f, -1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f },
// 			{ -1.0f, -1.0f, -1.0f }, { 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, -1.0f }, { -1.0f, 1.0f, -1.0f },
// 		}
// 	};

// 	const auto proj = glm::inverse(initialCameraProjection * initialCameraView);

// 	const auto proj = glm::inverse(initialCameraProjection * initialCameraView);
// 	std::array<glm::vec3, 8> _frustumVertices;

// 	std::transform(
// 		_cameraFrustumCornerVertices.begin(),
// 		_cameraFrustumCornerVertices.end(),
// 		_frustumVertices.begin(),
// 		[&](glm::vec3 p) {
// 			auto v = proj * glm::vec4(p, 1.0f);
// 			return glm::vec3(v) / v.w;
// 		}
// 	);
// }