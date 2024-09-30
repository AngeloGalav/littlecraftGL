#include "include/Chunk2.h"
// TODO: ADD REFERENCE TO CHUNK POSITION, AND TRANSFORM THE CHUNK ACCORDINGLY!

// TODO: REMOVE CHUNK NOISE WHEN DONE WITH DEBUGGING

NewChunk::NewChunk() {}

NewChunk::NewChunk(glm::vec3 position){}

void NewChunk::setup() {

    Model = glm::mat4(1.0);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
                 indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, tex_coord));
    glEnableVertexAttribArray(2);
}

// DEBUG noise function
void NewChunk::quickNoisedChunk(){

    // change to diffnoise (layered?)
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1);

    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int x = 0; x <  CHUNK_SIZE; x++)
        {
            noiseData[x][y] = (int)CHUNK_SIZE * noise.GetNoise((float)x, (float)y) + 10;
        }
    }

    std::cout << "\n [DEBUG] Loaded CHUNK noise" << std::endl;

}

void NewChunk::build(bool debug) {
    // TODO: remove after generating the World class
    quickNoisedChunk();
    
    // Chunk generation placeholder
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (debug) {
                    if ((z <= CHUNK_SIZE/2 - x + 20 && z <= x - CHUNK_SIZE/2 + 20) &&
                        (z <= CHUNK_SIZE/2 - y + 20 && z <= y - CHUNK_SIZE/2 + 20))
                        chunk_map[x][y][z] = 1;
                    else
                        chunk_map[x][y][z] = 0;
                }
                // non-debug (noised chunk) 
                else 
                {
                    if (noiseData[x][y] <= z)
                        chunk_map[x][y][z] = 1;
                    else
                        chunk_map[x][y][z] = 0;
                    
                    if (x==0 || y == 0 || z == 0) chunk_map[x][y][z] = 1;
                }

            }
        }
    }

    chunk_map[CHUNK_SIZE/2 + 10][CHUNK_SIZE/2 + 10][CHUNK_SIZE/2 + 10] = 1;


    // Chunk generation placeholder
    // todo: find another way to guard arrays
    for (int x = 1; x < CHUNK_SIZE-1; x++) {
        for (int y = 1; y < CHUNK_SIZE-1; y++) {
            for (int z = 1; z < CHUNK_SIZE-1; z++) {
                if (chunk_map[x][y][z]) {
                    if (!chunk_map[x+1][y][z]) addFace(glm::vec3(y,z,x), glm::ivec3(1,0,0));
                    if (!chunk_map[x-1][y][z]) addFace(glm::vec3(y,z,x), glm::ivec3(-1,0,0));
                    if (!chunk_map[x][y+1][z]) addFace(glm::vec3(y,z,x), glm::ivec3(0,1,0));
                    if (!chunk_map[x][y-1][z]) addFace(glm::vec3(y,z,x), glm::ivec3(0,-1,0));
                    if (!chunk_map[x][y][z+1]) addFace(glm::vec3(y,z,x), glm::ivec3(0,0,1));
                    if (!chunk_map[x][y][z-1]) addFace(glm::vec3(y,z,x), glm::ivec3(0,0,-1));
                    
                    // out of bounds face check (will be replaced by btwn chunks check in the future)
                    // todo: change
                    // if (z-1 < 1)          addFace(glm::vec3(y,-1,x), glm::ivec3(0,0,-1));
                    // if (z+1 > CHUNK_SIZE-1) addFace(glm::vec3(y, 1,x), glm::ivec3(0,0, 1));
                    // if (x-1 < 1)          addFace(glm::vec3(y,z,-1), glm::ivec3(-1,0,0));
                    // if (x+1 > CHUNK_SIZE-1) addFace(glm::vec3(y,z, 1), glm::ivec3( 1,0,0));
                    // if (z-1 < 1)          addFace(glm::vec3(-1,z,x), glm::ivec3(0,-1,0));
                    // if (z+1 > CHUNK_SIZE-1) addFace(glm::vec3(-1,z,x), glm::ivec3(0, 1,0));
                }
            }
        }
    }

    std::cout << "Finished building" << std::endl;
    std::cout << "indices size is " << indices.size() << std::endl;
    std::cout << "vertex size is " << vertices.size() << std::endl;
}

void NewChunk::addCube(glm::vec3 position) {
    NewCube cube(position);
    cube.init();
    unsigned int indexOffset = (int) vertices.size();
    std::vector<Vertex>& cube_vertices = cube.getVertexData(); // addFace here
    vertices.insert(vertices.end(), cube_vertices.begin(), cube_vertices.end());

    //local indices
    std::vector<GLuint>& cube_indices = cube.getIndices();

    // modify indices of chunk
    indices.resize(indices.size() + 36);
    std::transform(std::begin(cube_indices), std::end(cube_indices),
                   indices.end() - 36,
                   [indexOffset](unsigned int i) { return i + indexOffset; });
}

void NewChunk::addFace(glm::vec3 position, glm::ivec3 direction) {
    NewCube cube(position);
    cube.init();
    unsigned int indexOffset = (int) vertices.size();
    std::vector<Vertex>& cube_vertices = cube.getVertexData(); // addFace here

    // insert face in mesh based on direction
    auto [faceStart, faceEnd] = cube.getFaceVertexRange(direction);
    vertices.insert(vertices.end(),
                    cube_vertices.begin() + faceStart,
                    cube_vertices.begin() + faceEnd);

    // f_dir
    int f_dir = (direction.x < 0.0f || direction.y < 0.0f || direction.z < 0.0f);

    /* HANDLING INDICES */
    //local indices
    std::vector<GLuint>& cube_indices = cube.getIndices();

    // modify indices of chunk
    // Add indices for the two triangles that form the face
    indices.push_back(indexOffset);     // Triangle 1: Vertex 0
    indices.push_back(indexOffset + 1 + f_dir*2); // Triangle 1: Vertex 1
    indices.push_back(indexOffset + 2); // Triangle 1: Vertex 2

    indices.push_back(indexOffset);     // Triangle 2: Vertex 0
    indices.push_back(indexOffset + 2); // Triangle 2: Vertex 2
    indices.push_back(indexOffset + 3 - f_dir*2); // Triangle 2: Vertex 3

}

void NewChunk::draw(int ModelUniform) {
    glBindVertexArray(VAO);
    glUniformMatrix4fv(ModelUniform, 1, GL_FALSE, value_ptr(Model));
    glDrawElements(GL_TRIANGLES, (indices.size() - 1) * sizeof(GLuint),
                   GL_UNSIGNED_INT, 0);
    // keep it glfront for debug
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glPolygonMode(GL_FRONT, GL_FILL);

    glBindVertexArray(0);
}

void NewChunk::translate(glm::vec3 translate_vector) {
    Model =
        glm::translate(Model, ((float)UNIT_SIZE) * glm::vec3(translate_vector));
}

void NewChunk::moveTo(glm::vec3 position) {
    translate(position - this->position);
    this->position = position;
}