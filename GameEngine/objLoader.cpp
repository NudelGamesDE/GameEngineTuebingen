#define _CRT_SECURE_NO_DEPRECATE

#include "objLoader.h"

/*Only works if obj specs are known*/
/*Expects all or no faces to have a material*/
/*loadObj for THIS ENGINE only works for .obj files that contain vertices, uvs and normals*/

/** \brief Load an obj file including mtl files

This function parses obj files and corresponding mtl files into Meshes and Materials.
\param path a path to the obj file
\param meshes vector where parsed meshes can be stored
\param materials vector where parsed materials can be stored
\param mtlPath a path to the mtl file
\return true on successful parsing
*/
bool loadObj(
	const char *path,
	std::vector<shared_ptr<Mesh>> &meshes,
	std::vector<shared_ptr<Material>> &materials,
	const char *mtlPath
) {
	std::printf("Loading object file %s...\n", path);

	std::vector<std::vector<unsigned int>> vertexIndicesVector;
	std::vector<std::vector<unsigned int>> uvIndicesVector;
	std::vector<std::vector<unsigned int>> normalIndicesVector;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVer;
	std::vector<glm::vec2> tempUvs;
	std::vector<glm::vec3> tempNor;

	bool usemtl = false;

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;
	std::vector<int> indexMaterial;


	std::vector<shared_ptr<Material>> tempMat;
	char mtlLibPath[128];
	char mtl[128];
	int currentMaterialIndex = NULL;
	FILE *file = fopen(path, "r");
	if (file == NULL) {
		std::printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);
	
		if (res == EOF) {
			if (!vertexIndicesVector.empty()) {
				vertexIndicesVector.push_back(vertexIndices);
				uvIndicesVector.push_back(vertexIndices);
				normalIndicesVector.push_back(vertexIndices);
			}
			break;
		}

		if (strcmp(firstWord, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
			tempVer.push_back(vertex);
		}
		if (strcmp(firstWord, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f", &uv.x, &uv.y);
			tempUvs.push_back(uv);
		}
		if (strcmp(firstWord, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f", &normal.x, &normal.y, &normal.z);
			tempNor.push_back(normal);
		}
		else if (strcmp(firstWord, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
		
			if (matches != 9) {
				std::printf("file can't be read\n");
				fclose(file);
				return false;
			}
		
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if (strcmp(firstWord, "usemtl") == 0) {
			usemtl = true;
			fscanf(file, "%s", mtl);
			for (int i = 0; i < tempMat.size(); i++) {
				if (strcmp(tempMat[i]->Name, mtl) == 0) {
					currentMaterialIndex = i;
					break;
				}
			}
			indexMaterial.push_back(currentMaterialIndex);

			if (vertexIndices.empty() && uvIndices.empty() && normalIndices.empty()) {
			}
			else {
				vertexIndicesVector.push_back(vertexIndices);
				vertexIndices.clear();

				uvIndicesVector.push_back(uvIndices);
				uvIndices.clear();

				normalIndicesVector.push_back(normalIndices);
				normalIndices.clear();
			}

		}
		else if (strcmp(firstWord, "mtllib") == 0) {
			fscanf(file, "%s", mtlLibPath);
			loadMtl(mtlPath, tempMat);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	
	if (!vertexIndicesVector.empty()) {
		for (int i = 0; i < vertexIndicesVector.size(); i++) {
			for (unsigned int j = 0; j < vertexIndicesVector[i].size(); j++) {

				unsigned int vertexIndex = vertexIndicesVector[i][j];
				unsigned int uvIndex = uvIndicesVector[i][j];
				unsigned int normalIndex = normalIndicesVector[i][j];

				glm::vec3 vertex = tempVer[vertexIndex - 1];
				glm::vec2 uv = tempUvs[uvIndex - 1];
				glm::vec3 normal = tempNor[normalIndex - 1];

				out_vertices.push_back(vertex);
				out_uvs.push_back(uv);
				out_normals.push_back(normal);
			}
			auto mesh = make_shared<Mesh>(out_vertices, out_uvs, out_normals);
			meshes.push_back(mesh);
			out_vertices.clear();
			out_uvs.clear();
			out_normals.clear();
		}
	}
	else {
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {

			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			glm::vec3 vertex = tempVer[vertexIndex - 1];
			glm::vec2 uv = tempUvs[uvIndex - 1];
			glm::vec3 normal = tempNor[normalIndex - 1];

			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}
		auto mesh = make_shared<Mesh>(out_vertices, out_uvs, out_normals);
		meshes.push_back(mesh);
	}

	if (!usemtl) {
		for (int i = 0; i < meshes.size(); i++) {
			materials.push_back(getDefaultMaterial());
		}
	}
	else {
		for (int i = 0; i < indexMaterial.size(); i++) {
			materials.push_back(tempMat[indexMaterial[i]]);
		}
	}

	fclose(file);
	std::printf("Loading .obj complete.\n");
	return true;
}

bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	std::vector<glm::vec3> &out_normals,
	const char *mtlPath
) {
	std::printf("Loading object file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVer;
	std::vector<glm::vec2> tempUvs;
	std::vector<glm::vec3> tempNor;

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		std::printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);

		if (res == EOF) {
			break;
		}

		if (strcmp(firstWord, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVer.push_back(vertex);
		}
		else if (strcmp(firstWord, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y for use of DDS textures
			tempUvs.push_back(uv);
		}
		else if (strcmp(firstWord, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNor.push_back(normal);
		}
		else if (strcmp(firstWord, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::printf("file can't be read\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if (strcmp(firstWord, "mtllib") == 0) {
			fscanf(file, "%s", mtlPath);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = tempVer[vertexIndex - 1];
		glm::vec2 uv = tempUvs[uvIndex - 1];
		glm::vec3 normal = tempNor[normalIndex - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);
	}

	fclose(file);
	std::printf("Loading complete.\n");
	return true;
}

bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec2> &out_uvs,
	const char *mtlPath
) {
	std::printf("Loading object file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices;
	std::vector<glm::vec3> tempVer;
	std::vector<glm::vec2> tempUvs;

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		std::printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);

		if (res == EOF) {
			break;
		}

		if (strcmp(firstWord, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVer.push_back(vertex);
		}
		else if (strcmp(firstWord, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			//uv.y = -uv.y for use of DDS textures
			tempUvs.push_back(uv);
		}
		else if (strcmp(firstWord, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3];

			int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
			if (matches != 6) {
				std::printf("file can't be read\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
		}
		else if (strcmp(firstWord, "mtllib") == 0) {
			fscanf(file, "%s", mtlPath);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];

		glm::vec3 vertex = tempVer[vertexIndex - 1];
		glm::vec2 uv = tempUvs[uvIndex - 1];

		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
	}

	fclose(file);
	std::printf("Loading complete.\n");
	return true;
}

bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	std::vector<glm::vec3> &out_normals,
	const char *mtlPath
) {
	std::printf("Loading object file %s...\n", path);

	std::vector<unsigned int> vertexIndices, normalIndices;
	std::vector<glm::vec3> tempVer;
	std::vector<glm::vec3> tempNor;

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		std::printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);

		if (res == EOF) {
			break;
		}

		if (strcmp(firstWord, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVer.push_back(vertex);
		}
		else if (strcmp(firstWord, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNor.push_back(normal);
		}
		else if (strcmp(firstWord, "f") == 0) {
			unsigned int vertexIndex[3], normalIndex[3];

			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6) {
				std::printf("file can't be read\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if (strcmp(firstWord, "mtllib") == 0) {
			fscanf(file, "%s", mtlPath);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		unsigned int vertexIndex = vertexIndices[i];
		unsigned int normalIndex = normalIndices[i];

		glm::vec3 vertex = tempVer[vertexIndex - 1];
		glm::vec3 normal = tempNor[normalIndex - 1];

		out_vertices.push_back(vertex);
		out_normals.push_back(normal);
	}

	fclose(file);
	std::printf("Loading complete.\n");
	return true;
}
bool loadObj(
	const char *path,
	std::vector<glm::vec3> &out_vertices,
	const char *mtlPath
) {
	std::printf("Loading object file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<glm::vec3> tempVer;

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		std::printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);

		if (res == EOF) {
			break;
		}

		if (strcmp(firstWord, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVer.push_back(vertex);
		}
		else if (strcmp(firstWord, "f") == 0) {
			unsigned int vertexIndex[3];

			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			if (matches != 6) {
				std::printf("file can't be read\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
		}
		else if (strcmp(firstWord, "mtllib") == 0) {
			fscanf(file, "%s", mtlPath);
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {

		unsigned int vertexIndex = vertexIndices[i];

		glm::vec3 vertex = tempVer[vertexIndex - 1];

		out_vertices.push_back(vertex);
	}

	fclose(file);
	std::printf("Loading complete.\n");
	return true;
}
