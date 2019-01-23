#include "bvh.h"

vec4 dummy(0, 0, 0, 1);
vector<vec4> world_coordinates;

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

 bvh::bvh_nope* bvh::initialise_bvh(Scene the_scene)
 {
	 vector<shared_ptr<Renderer>> all_objects = the_scene.Renderers;
	 return generate_bvh_tree(all_objects);
 }


 bvh::bvh_nope* bvh::generate_bvh_tree(vector<shared_ptr<Renderer>> objects)
 {
	 std::cout << objects.size() <<"  Halt's Maul. \n";
	 if (objects.size() < 1)
	 {
		 std::cout << "Halt den Rand. \n";
		 return bvh::generate_bvh_nope(objects[0]->transform.Position.x,
									   objects[0]->transform.Position.y, 
									   objects[0]->transform.Position.z, 
									   objects[0]->transform.Position.x,
									   objects[0]->transform.Position.y,
									   objects[0]->transform.Position.z, objects, NULL, NULL);
	 }
	 float max_x = -10000;
	 //std::cout << max_x << " Test. TEST! SCHEISSE! \n";
	 float max_y = -INFINITY;
	 float max_z = -INFINITY;
	 float min_x = INFINITY;
	 float min_y = INFINITY;
	 float min_z = INFINITY;
	 for (int i = 0; i < objects.size(); i++)
	 {
		 //std::cout << objects[i]->transform.Position.x << "Fuck that shit. \n";
		//std::cout << objects[i]->transform.Position.z << " \n";
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
	 std::cout << min_x << " - " << max_x << " X \n" << min_y << " - " << max_y << "Y \n" << " - " << min_z << " - " << max_z << " Z \n";
	 //std::cout << x_diff << " - " << y_diff << " - " << z_diff << "\n";
	 vector<shared_ptr<Renderer>> left;
	 vector<shared_ptr<Renderer>> right;
	 if ((max_x >= max_y) && (max_x >= max_z))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 if ((objects[i]->transform.Position.x - min_x) <= x_diff)
			 {
				 std::cout << "Tick. \n";
				 left.push_back(objects[i]);
			 }
			 else
			 {
				 std::cout << "Tock. \n";
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 if ((max_y > max_x) && (max_y >= max_z))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 if ((objects[i]->transform.Position.y - min_y) <= y_diff)
			 {
				 std::cout << "Tack. \n";
				 left.push_back(objects[i]);
			 }
			 else
			 {
				 std::cout << "Tuck. \n";
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 if ((max_z > max_y) && (max_z > max_x))
	 {
		 for (int i = 0; i < objects.size(); i++)
		 {
			 //std::cout << floor(max_z / 2) << "\n";
			 if ((objects[i]->transform.Position.z - min_z) < z_diff)
			 {
				 //std::cout << "Teck. \n";
				 left.push_back(objects[i]);
			 }
			 else
			 {
				// std::cout << "Tyck. \n";
				 right.push_back(objects[i]);
			 }
		 }
	 }
	 return bvh::generate_bvh_nope(max_x, max_y, max_z, min_x, min_y, min_z, objects, generate_bvh_tree(left), generate_bvh_tree(right));
 }