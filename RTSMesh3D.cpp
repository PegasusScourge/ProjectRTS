/**

RTSMesh3D.cpp: ProjectRTS

All Mesh related information for a MeshObject3D

See RTSMesh3D.h for more

*/

// Include our header
#include "RTSMesh3D.h"

using namespace std;
using namespace RTSEngine;

// -------------------------------------------------------------------------------------------------- MeshObject3D
MeshObject3D::MeshObject3D() {
	//Constructor - TODO

	// Init a null array for the verticies
	verticies = new glm::vec3[1];
	nVertices = 1;

	normals = new glm::vec3[1];
	uvCoords = new glm::vec3[1];
	vertTangents = new glm::vec3[1];
	vertBitangents = new glm::vec3[1];
}

glm::vec3 MeshObject3D::getPosition() {
	return meshPosition;
}

glm::vec3 MeshObject3D::getRotation() {
	return meshRotation;
}

std::string MeshObject3D::getName() {
	return name;
}

bool MeshObject3D::getReady() {
	return isReady;
}

bool MeshObject3D::HasVertBitangents() {
	return hasVertBitangents;
}

bool MeshObject3D::HasVertTangents() {
	return hasVertTrangents;
}

void MeshObject3D::setPosition(glm::vec3 nPos) {
	meshPosition = nPos;
}

void MeshObject3D::setRotation(glm::vec3 nRot) {
	meshRotation = nRot;
}

void MeshObject3D::setName(std::string nName) {
	name = nName;
}

int MeshObject3D::loadModelWithAssimp(std::string path) {

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	
	// Check if the scene was read
	if (scene == NULL) {
		cout << "Model load failure: " << importer.GetErrorString() << endl;
		return EXIT_FAILURE;
	}

	if (RTSGame::globalDebug) {
		// Do a print to the console of the heirarchy
		cout << "Loaded model " << path << " successfully, heirarchy is as follows:" << endl;

		// Do meshes:
		cout << "\tHasMeshes: " << scene->HasMeshes() << endl;
		if (scene->HasMeshes()) {
			aiMesh**const meshes = scene->mMeshes;
			int nMeshes = scene->mNumMeshes;
			for (int i = 0; i < nMeshes; i++) {
				cout << "\t\tMesh: " << meshes[i]->mName.C_Str() << ", V/F/B: " << std::to_string(meshes[i]->mNumVertices)
					<< "/" << std::to_string(meshes[i]->mNumFaces) << "/" << std::to_string(meshes[i]->mNumBones) << endl;
			}
		}

		// Do textures:
		cout << "\tHasTextures: " << scene->HasTextures() << endl;
		if (scene->HasTextures()) {
			aiTexture** texs = scene->mTextures;
			int nTexs = scene->mNumTextures;
			for (int i = 0; i < nTexs; i++) {
				cout << "\t\tTexture: FormatHint: " << texs[i]->achFormatHint << ", W/H: " << std::to_string(texs[i]->mWidth) << "/" << std::to_string(texs[i]->mHeight) << endl;
			}
		}

		// Do nodes:
		cout << "\tNodes:" << endl;
		aiNode* rootNode = scene->mRootNode;
		DEBUG_recursiveNodeDisplay(rootNode, 1);
	}

	// TODO - Transfer relevant information to our own format

	isReady = true;

	// Scene is cleaned automatically
	return EXIT_SUCCESS;
}

void MeshObject3D::DEBUG_recursiveNodeDisplay(aiNode* node, int level) {
	cout << "\t\t";
	for (int i = 0; i < level; i++) {
		cout << "--";
	}
	cout << node->mName.C_Str() << " MD=(" << node->mMetaData << ")";
	if (level == 1) {
		cout << ", ROOT NODE";
	}
	cout << endl;
	if (node->mNumChildren > 0) {
		for (int i = 0; i < node->mNumChildren; i++) {
			DEBUG_recursiveNodeDisplay(node->mChildren[i], level + 1);
		}
	}
}

// -------------------------------------------------------------------------------------------------- MeshFace3D
MeshFace3D::MeshFace3D(int* n1, int n2) {
	vertIndexes = n1;
	nVertIndexes = n2;
}

// -------------------------------------------------------------------------------------------------- MeshBone3D
MeshBone3D::MeshBone3D() {
	// Constructor - TODO
}

std::string MeshBone3D::getName() {
	return name;
}

Bone3DVertexWeight* MeshBone3D::getVertexWeights() {
	return vertWeights;
}

int MeshBone3D::getNumVertWeights() {
	return nVertWeights;
}

void MeshBone3D::setName(std::string nName) {
	name = nName;
}

// -------------------------------------------------------------------------------------------------- Bone3DVertexWeight
Bone3DVertexWeight::Bone3DVertexWeight(int vId, float w) {
	vertexId = vId;
	weight = w;
}