/**	File che crea la geometria degli oggetti nella scena
 * 
 * 
 */

#include "include/Strutture.h"
#include "include/Lib.h"

void crea_cubo(Mesh* mesh)
{

	mesh->vertici.push_back(vec3(-1.0, -1.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, -1.0, 1.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 1.0, 1.0));
	mesh->colori.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0, 1.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 1.0, 0.5));
	// back
	mesh->vertici.push_back(vec3(-1.0, -1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, -1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0, 1.0, -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 0.5));

	
	
	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));


	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(2); mesh->indici.push_back(3); mesh->indici.push_back(0);
	mesh->indici.push_back(1); mesh->indici.push_back(5); mesh->indici.push_back(6);
	mesh->indici.push_back(6); mesh->indici.push_back(2); mesh->indici.push_back(1);
	mesh->indici.push_back(7); mesh->indici.push_back(6); mesh->indici.push_back(5);
	mesh->indici.push_back(5); mesh->indici.push_back(4); mesh->indici.push_back(7);
	mesh->indici.push_back(4); mesh->indici.push_back(0); mesh->indici.push_back(3);
	mesh->indici.push_back(3); mesh->indici.push_back(7); mesh->indici.push_back(4);
	mesh->indici.push_back(4); mesh->indici.push_back(5); mesh->indici.push_back(1);
	mesh->indici.push_back(1); mesh->indici.push_back(0); mesh->indici.push_back(4);
	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(6);
	mesh->indici.push_back(6); mesh->indici.push_back(7); mesh->indici.push_back(3);
	int nv = mesh->vertici.size();
 
	mesh->indici.push_back(nv-1);


}
void crea_piramide(Mesh* mesh)
{
	mesh->vertici.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 0.0,  1.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 0.5));
	mesh->vertici.push_back(vec3(1.0, 0.0, -1.0));
	mesh->colori.push_back(vec4(0.0, 0.0, 1.0, 0.5));
	mesh->vertici.push_back(vec3(-1.0,  0.0,  -1.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 0.0, 0.5));
	// Apice piramide
	mesh->vertici.push_back(vec3(0.0,1.0,0.0));
	mesh->colori.push_back(vec4(1.0, 1.0, 1.0, 1.0));


	

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(0); mesh->indici.push_back(2); mesh->indici.push_back(3);

	mesh->indici.push_back(0); mesh->indici.push_back(4); mesh->indici.push_back(3);
	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(4);

	mesh->indici.push_back(3); mesh->indici.push_back(2); mesh->indici.push_back(4);
	mesh->indici.push_back(1); mesh->indici.push_back(2); mesh->indici.push_back(4);

	mesh->vertici.push_back(vec3(0.0,0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));

	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);

}
void crea_piano(Mesh* mesh)
{

	mesh->vertici.push_back(vec3(-1.0, 0.0, 1.0));
	mesh->vertici.push_back(vec3(1.0, 0.0, 1.0));
	mesh->vertici.push_back(vec3(1.0, 0.0, -1.0));
	mesh->vertici.push_back(vec3(-1.0, 0.0, -1.0));

	mesh->indici.push_back(0); mesh->indici.push_back(1); mesh->indici.push_back(2);
	mesh->indici.push_back(0); mesh->indici.push_back(2); mesh->indici.push_back(3);

}

void crea_piano_suddiviso(Mesh* mesh)
{

	int N = 128;

	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			mesh->vertici.push_back(vec3(-0.5+(float)i / N, 0.0, -0.5+(float)j / N));
			mesh->colori.push_back(vec4(1.0, 0.0, 0.0, 1.0));
			
		}
	}
	int cont = -1;


	/*
	for (i = 0; i <= pow(N, 2) - (N + 1); i++) {


		j = i % (N);

		if (j != N - 1)
		{
			mesh->indici.push_back(i);
			mesh->indici.push_back(i + 1);
			mesh->indici.push_back(i + N + 1);

			mesh->indici.push_back(i + N + 1);
			mesh->indici.push_back(i);
			mesh->indici.push_back(i + N);

		}
		
	}
	*/

	for (i = 0; i <= pow(N, 2) - (N + 1); i++) {

		j = i % (N);

		if (j != N - 1)
		{
			mesh->indici.push_back(i);
			mesh->indici.push_back(i + 1);
			mesh->indici.push_back(i + N );

			mesh->indici.push_back(i + N + 1);
			mesh->indici.push_back(i+1);
			mesh->indici.push_back(i + N);
		}
		

	}
 

	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv-1);

 

}

void crea_sfera (Mesh* mesh)
{
	vec3 raggio(1.0);
	vec3 centro(0.0);
	int Stacks = 30;  //numero di suddivisioni sull'asse y
	int Slices = 30;  // numero di suddivisioni sull'asse x

	//Calc The Vertices

	//Stacks= suddivisioni lungo l'asse y
	for (int i = 0; i <= Stacks; ++i) {

		float V = i / (float)Stacks;
		float phi = V * pi <float>();

		// Loop Through Slices suddivisioni lungo l'asse x
		for (int j = 0; j <= Slices; ++j) {

			float U = j / (float)Slices;
			float theta = U * (pi <float>() * 2);

			// Calc The Vertex Positions
			float x = centro.x + raggio.x * (cosf(theta) * sinf(phi));
			float y = centro.y + raggio.y * cosf(phi);
			float z = centro.z + raggio.z * sinf(theta) * sinf(phi);

			mesh->vertici.push_back(vec3(x,y,z)),
			mesh->colori.push_back(vec4(0.5,1.0,0.6,0.5));
			
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < Slices * Stacks + Slices; ++i) {

		mesh->indici.push_back(i);
		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i + Slices);


		mesh->indici.push_back(i + Slices + 1);
		mesh->indici.push_back(i);
		mesh->indici.push_back(i + 1);
	}

	mesh->vertici.push_back(vec3(0.0, 0.0, 0.0));
	mesh->colori.push_back(vec4(0.0, 1.0, 0.0, 1.0));
	int nv = mesh->vertici.size();
	mesh->indici.push_back(nv - 1);

 
}
