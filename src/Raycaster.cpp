/** Creates a ray from the player's camera to the plane
 * 
 */

#include "include/Raycaster.h"

extern int width;
extern int height;
extern mat4 Projection, Model, View;

vec3 Raycaster::get_ray_from_mouse(float mouse_x, float mouse_y) {
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

/** Ritorna la direzione della camera praticamente. 
 * 
 */
vec3 Raycaster::get_ray_from_camera(Camera camera){
	return vec3(camera.ViewSetup.direction.x, camera.ViewSetup.direction.y, camera.ViewSetup.direction.z);
}

/*controlla se un raggio interseca una sfera. In caso negativo, restituisce false. Rigetta
le intersezioni dietro l'origine del raggio, e pone  intersection_distance all'intersezione p i� vicina.
*/

bool Raycaster::ray_sphere(vec3 ray_origin_wor, vec3 ray_direction_wor, vec3 sphere_centre_wor, float sphere_radius, float* intersection_distance) {
	 
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