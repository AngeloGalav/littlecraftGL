#include "NewWorld.h"

// ...

void NewWorld::initNoise() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.1);

    // TODO: make new noise function/implementation
    // for (int y = 0; y < WORLD_SIZE * CHUNK_SIZE; y++)
    //     for (int x = 0; x < WORLD_SIZE * CHUNK_SIZE; x++)
    //         noiseData[x][y] = (int)16 * noise.GetNoise((float)x, (float)y);

    std::cout << "\nLoaded noise" << std::endl;
}