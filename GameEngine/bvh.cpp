#include "bvh.h"

vec4 dummy(0, 0, 0, 1);
vector<vec4> world_coordinates;

/** \brief Calculates Difference

\param x a float
\param y a float
*/
float bvh::difference(float x, float y)
{
	if (y < 0)
	{
		return (x + (abs(y)));
	}
	else
	{
		return (x - y);
	}
}

/** \brief Generates a bvh node

\param x maximum x
\param y maximum y
\param z maximum z
\param nx minimum x
\param ny minimum y
\param nz minimum z
\param obj a vector of renderers
\param l left child node
\param r right child node
*/
 bvh::bvh_nope* bvh::generate_bvh_nope(int x, int y, int z, int nx, int ny, int nz, vector<shared_ptr<Renderer>> obj, bvh_nope *l, bvh_nope *r)
{
	bvh_nope *nope = new bvh_nope;
	nope->max_x = x;
	nope->max_y = y;
	nope->max_z = z;
	nope->min_x = nx;
	nope->min_y = ny;
	nope->min_z = nz;
	nope->left = l;
	nope->right = r;
	nope->objects = obj;
	return nope;
}

/** \brief Initialize bvh

\param the_scene a scene to apply bvh to
*/
 bvh::bvh_nope* bvh::initialise_bvh(Scene the_scene)
 {
	 vector<shared_ptr<Renderer>> all_objects = the_scene.Renderers;
	 return generate_bvh_tree(all_objects);
 }

/** \brief Generates bvh tree

\param objects a vector of renderers
*/
 bvh::bvh_nope* bvh::generate_bvh_tree(vector<shared_ptr<Renderer>> objects)
 {
	 // std::cout << objects.size() <<"  Objects in the layer. \n";
	 if (objects.size() <= 1)
	 {
		 return bvh::generate_bvh_nope(objects[0]->transform.Position.x,
									   objects[0]->transform.Position.y, 
									   objects[0]->transform.Position.z, 
									   objects[0]->transform.Position.x,
									   objects[0]->transform.Position.y,
									   objects[0]->transform.Position.z, objects, NULL, NULL);
	 }
	 float max_x = -INFINITY;
	 float max_y = -INFINITY;
	 float max_z = -INFINITY;
	 float min_x = INFINITY;
	 float min_y = INFINITY;
	 float min_z = INFINITY;
	 for (int i = 0; i < objects.size(); i++)
	 {
		 if (objects[i]->transform.Position.x > max_x)
		 {
			 max_x = objects[i]->transform.Position.x;
		 }
		 if (objects[i]->transform.Position.y > max_y)
		 {
			 max_y = objects[i]->transform.Position.y;
		 }
		 if (objects[i]->transform.Position.z > max_z)
		 {
			 max_z = objects[i]->transform.Position.z;
		 }
		 if (objects[i]->transform.Position.x < min_x)
		 {
			 min_x = objects[i]->transform.Position.x;
		 }
		 if (objects[i]->transform.Position.y < min_y)
		 {
			 min_y = objects[i]->transform.Position.y;
		 }
		 if (objects[i]->transform.Position.z < min_z)
		 {
			 min_z = objects[i]->transform.Position.z;
		 }

	 }
	 float x_diff = abs(bvh::difference(max_x, min_x));
	 float y_diff = abs(bvh::difference(max_y, min_y));
	 float z_diff = abs(bvh::difference(max_z, min_z));
	 float mid_x = ((max_x + min_x) / 2);
	 float mid_y = ((max_y + min_y) / 2);
	 float mid_z = ((max_z + min_z) / 2);
	 /* std::cout << min_x << " min_x coordinate - " << max_x << "max_x coordinate - " << x_diff << " x_diff " << mid_x << " mid_x \n" 
		 << min_y << " min_y coordinate - " << max_y << "max_y coordinate - " << y_diff << " y_diff " << mid_y << " mid_y \n"
		 << min_z << " min_z coordinate - " << max_z << " max_z coordinate - " << z_diff << " z_diff " << mid_z << " mid_z \n \n";
	*/
	 vector<shared_ptr<Renderer>> left;
	 vector<shared_ptr<Renderer>> right;
	 if ((x_diff >= y_diff) && (x_diff >= z_diff))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 if ((objects[i]->transform.Position.x) <= mid_x)
			 {
				 left.push_back(objects[i]);
			 }
			 else
			 {
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 if ((y_diff > x_diff) && (y_diff >= z_diff))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 if ((objects[i]->transform.Position.y) <= mid_y)
			 {
				 left.push_back(objects[i]);
			 }
			 else
			 {
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 if ((z_diff > y_diff) && (z_diff > x_diff))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 if ((objects[i]->transform.Position.z) < mid_z)
			 {
				 left.push_back(objects[i]);
			 }
			 else
			 {
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 return bvh::generate_bvh_nope(max_x, max_y, max_z, min_x, min_y, min_z, objects, generate_bvh_tree(left), generate_bvh_tree(right));
 }
