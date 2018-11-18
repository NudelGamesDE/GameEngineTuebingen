#define _CRT_SECURE_NO_DEPRECATE

#include "mtlLoader.h"

bool loadMtl(
	const char *path,
	std::vector<shared_ptr<Material>> &materials
) {
	printf("Loading materials from file %s...\n", path);

	FILE *file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open file.\n");
		getchar();
		return false;
	}

	glm::vec3 defaultVector(0.0f, 0.0f, 0.0f);
	float defaultShininess = 0.0f;
	unsigned int defaultIllum = 0;
	float defaultTransparencyD = 1.0f;
	float defaultTransparencyTr = 0.0f;

	std::vector<char*> name;				//newmtl
	std::vector<glm::vec3> ambientColor;	//Ka
	std::vector<glm::vec3> specularColor;	//Ks
	std::vector<glm::vec3> diffuseColor;	//Kd
	std::vector<unsigned short> illum;		//illum
	std::vector<float> shininess;			//Ns
	std::vector<float> transparency;		//Tr or d

	char nameTemp[128];
	glm::vec3 ambientTemp = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 specularTemp = glm::vec3(0.0f, 0.0f, 0.0f);;
	glm::vec3 diffuseTemp = glm::vec3(0.0f, 0.0f, 0.0f);;
	unsigned int illumTemp = 0;
	int shininessTemp = 0;
	float transparencyTemp = 1.0f;

	bool toggle = true;

	while (true) {

		char firstWord[128];

		int res = fscanf(file, "%s", firstWord);

		if (res == EOF) {
			name.push_back(nameTemp);

			if (ambientTemp != defaultVector) {
				ambientColor.push_back(ambientTemp);
				ambientTemp = defaultVector;
			}
			else {
				ambientColor.push_back(ambientTemp);
			}

			if (specularTemp != defaultVector) {
				specularColor.push_back(specularTemp);
				specularTemp = defaultVector;
			}
			else {
				specularColor.push_back(specularTemp);
			}

			if (diffuseTemp != defaultVector) {
				diffuseColor.push_back(diffuseTemp);
				diffuseTemp = defaultVector;
			}
			else {
				diffuseColor.push_back(diffuseTemp);
			}

			if (illumTemp != defaultIllum) {
				illum.push_back(illumTemp);
				illumTemp = defaultIllum;
			}
			else {
				illum.push_back(illumTemp);
			}

			if (shininessTemp != defaultShininess) {
				shininess.push_back(shininessTemp);
				shininessTemp = defaultShininess;
			}
			else {
				shininess.push_back(shininessTemp);
			}

			if (transparencyTemp != defaultTransparencyD) {
				transparency.push_back(transparencyTemp);
				transparencyTemp = defaultTransparencyD;
			}
			else {
				transparency.push_back(transparencyTemp);
			}
			break;
		}

		if (strcmp(firstWord, "newmtl") == 0) {
			if (toggle) {
				fscanf(file, "%s", nameTemp);
				toggle = false;
			}
			else {
				name.push_back(nameTemp);

				if (ambientTemp != defaultVector) {
					ambientColor.push_back(ambientTemp);
					ambientTemp = defaultVector;
				}
				else {
					ambientColor.push_back(ambientTemp);
				}

				if (specularTemp != defaultVector) {
					specularColor.push_back(specularTemp);
					specularTemp = defaultVector;
				}
				else {
					specularColor.push_back(specularTemp);
				}

				if (diffuseTemp != defaultVector) {
					diffuseColor.push_back(diffuseTemp);
					diffuseTemp = defaultVector;
				}
				else {
					diffuseColor.push_back(diffuseTemp);
				}

				if (illumTemp != defaultIllum) {
					illum.push_back(illumTemp);
					illumTemp = defaultIllum;
				}
				else {
					illum.push_back(illumTemp);
				}

				if (shininessTemp != defaultShininess) {
					shininess.push_back(shininessTemp);
					shininessTemp = defaultShininess;
				}
				else {
					shininess.push_back(shininessTemp);
				}

				if (transparencyTemp != defaultTransparencyD) {
					transparency.push_back(transparencyTemp);
					transparencyTemp = defaultTransparencyD;
				}
				else {
					transparency.push_back(transparencyTemp);
				}

				fscanf(file, "%s", nameTemp);
				printf("\n\n%s\n\n\n", nameTemp);
			}
		}
		else if (strcmp(firstWord, "Ka") == 0) {
			fscanf(file, "%f %f %f", &ambientTemp.x, &ambientTemp.y, &ambientTemp.z);
		}
		else if (strcmp(firstWord, "Ks") == 0) {
			fscanf(file, "%f %f %f", &specularTemp.x, &specularTemp.y, &specularTemp.z);
		}
		else if (strcmp(firstWord, "Kd") == 0) {
			fscanf(file, "%f %f %f", &diffuseTemp.x, &diffuseTemp.y, &diffuseTemp.z);
		}
		else if (strcmp(firstWord, "illum") == 0) {
			fscanf(file, "%i", &illumTemp);
		}
		else if (strcmp(firstWord, "Ns") == 0) {
			fscanf(file, "%f", &shininessTemp);
		}
		else if (strcmp(firstWord, "d") == 0) {
			fscanf(file, "%f", &transparencyTemp);
		}
		else if (strcmp(firstWord, "Tr") == 0) {
			fscanf(file, "%f", &transparencyTemp);
			transparencyTemp = 1 - transparencyTemp;
		}
		else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	

	for (int i = 0; i < name.size(); i++) {

		auto mat = make_shared<Material>();
		mat->name = name[i];
		mat->ambientColor = ambientColor[i];
		mat->specularColor = specularColor[i];
		mat->diffuseColor = diffuseColor[i];
		mat->illum = illum[i];
		mat->shininess = shininess[i];
		mat->transparency = transparency[i];

		materials.push_back(mat);
	}

	fclose(file);
	printf("Loading .mtl complete.\n");
	return true;
}

shared_ptr<Material> getDefaultMaterial() {
	glm::vec3 defaultVector(0.0f, 0.0f, 0.0f);
	float defaultShininess = 0.0f;
	unsigned int defaultIllum = 0;
	float defaultTransparencyD = 1.0f;
	float defaultTransparencyTr = 0.0f;

	auto defaultMaterial = make_shared<Material>();
	defaultMaterial->ambientColor = defaultVector;
	defaultMaterial->specularColor = defaultVector;
	defaultMaterial->diffuseColor = defaultVector;
	defaultMaterial->shininess = defaultShininess;
	defaultMaterial->illum = defaultIllum;
	defaultMaterial->transparency = defaultTransparencyD;

	return defaultMaterial;
}