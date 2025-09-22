#include "include/Camera.h"

// constructor with vectors
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      MovementSpeed(SPEED),
      MouseSensitivity(SENSITIVITY),
      Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix() {
    // std::cout << "cout position" << Position.x <<", " << Position.y << ","
    // <<Position.z << std::endl;
    return glm::lookAt(Position, Position + Front, Up);
}

// processes input received from any keyboard-like input system. Accepts input
// parameter in the form of camera defined ENUM (to abstract it from windowing
// systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == CAM_FORWARD) Position += Front * velocity;
    if (direction == CAM_BACKWARD) Position -= Front * velocity;
    if (direction == CAM_LEFT) Position -= Right * velocity;
    if (direction == CAM_RIGHT) Position += Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value
// in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset,
                                  GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input
// on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 60.0f) Zoom = 60.0f;
}

void Camera::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(
        Front, WorldUp));  // normalize the vectors, because their length gets
                           // closer to 0 the more you look up or down which
                           // results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::updateCameraMatrices(){
    ProjectionMatrix = glm::perspective(glm::radians(Zoom),
                                  (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
                                  0.1f, 100.0f);
    ViewMatrix = glm::lookAt(Position, Position + Front, Up);
}

// bool Camera::raycastToBlock(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, 
//                    glm::vec3& outBlockPos) {
//     // Simple implementation - step along the ray and check for blocks
//     float step = 0.1f; // Step size
    
//     for (float dist = 0; dist < raycastDistance; dist += step) {
//         glm::vec3 checkPos = rayOrigin + rayDirection * dist;
        
//         // Convert world position to chunk/block coordinates
//         int blockX = floor(checkPos.x / UNIT_SIZE);
//         int blockY = floor(checkPos.y / UNIT_SIZE);
//         int blockZ = floor(checkPos.z / UNIT_SIZE);
        
//         // Calculate which chunk this belongs to
//         int chunkX = floor(blockX / CHUNK_SIZE);
//         int chunkY = floor(blockY / CHUNK_SIZE);
//         int chunkZ = floor(blockZ / CHUNK_SIZE);
        
//         // Get local coordinates within chunk
//         int localX = blockX - chunkX * CHUNK_SIZE;
//         int localY = blockY - chunkY * CHUNK_SIZE;
//         int localZ = blockZ - chunkZ * CHUNK_SIZE;
        
//         // Find the chunk and check if there's a block at these coordinates
//         // (You'll need to adapt this to your chunk storage system)
//         NewChunk* chunk = getChunkAt(chunkX, chunkY, chunkZ);
//         if (chunk && chunk->chunk_map[localX][localY][localZ]) {
//             outBlockPos = glm::vec3(blockX, blockY, blockZ) * (float)UNIT_SIZE;
//             return true;
//         }
//     }
    
//     return false;
// }

// void Camera::updateSelection() {
//     glm::vec3 selectedBlockPos;
//     bool blockHit = raycastToBlock(Position, Front, selectedBlockPos);
    
//     // Clear previous selection
//     for (auto& chunk : chunks) {
//         chunk->resetHighlight();
//     }
    
//     if (blockHit) {
//         // Find which chunk this block belongs to
//         int chunkX = floor(selectedBlockPos.x / UNIT_SIZE / CHUNK_SIZE);
//         int chunkY = floor(selectedBlockPos.y / UNIT_SIZE / CHUNK_SIZE);
//         int chunkZ = floor(selectedBlockPos.z / UNIT_SIZE / CHUNK_SIZE);
        
//         NewChunk* chunk = getChunkAt(chunkX, chunkY, chunkZ);
//         if (chunk) {
//             // Option 1: Highlight the block by changing its color
//             chunk->highlightCube(selectedBlockPos);

//             // Store selected block for later use (removing it)
//             currentlySelectedBlock = selectedBlockPos;
//         }
//     } else {
//         currentlySelectedBlock = glm::vec3(-1); // Invalid position to indicate no selection
//     }
// }