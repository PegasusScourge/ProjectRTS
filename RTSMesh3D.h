#ifndef __INC_RTSMESH3D_H__
#define __INC_RTSMESH3D_H__
#pragma once

/**

RTSMesh3D.h: ProjectRTS

Contains the definitions for the main .cpp file

In namespace RTSEngine, along with the rest of the engine files

*/

// INCLUDE - Dependancies
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "RTSGame.h"

// Include the define constants
#include "RTSDefineConsts.h"

namespace RTSEngine {

	class MeshObject3D;
	class MeshFace3D;
	class MeshBone3D;
	class Bone3DVertexWeight;

	class MeshObject3D {

	public:
		MeshObject3D();

		glm::vec3 getPosition();
		glm::vec3 getRotation();
		std::string getName();
		bool getReady();
		bool HasVertTangents();
		bool HasVertBitangents();

		void setPosition(glm::vec3 nPos);
		void setRotation(glm::vec3 nRot);
		void setName(std::string nName);

		int loadModelWithAssimp(std::string path);

	private:
		void DEBUG_recursiveNodeDisplay(aiNode* node, int level);

		std::string name;

		// Position data
		glm::vec3 meshPosition;
		glm::vec3 meshRotation;

		// Vertex etc data
		glm::vec3 *verticies;
		int nVertices;

		glm::vec3 *normals;
		glm::vec3 *uvCoords;
		glm::vec3 *vertTangents;
		glm::vec3 *vertBitangents;

		// Face data
		MeshFace3D *faces;
		int nFaces;

		// Bone data
		MeshBone3D *bones;
		int nBones;

		bool isReady = false;

		bool hasVertTrangents = false;
		bool hasVertBitangents = false;
	};

	class MeshFace3D {
	public:
		MeshFace3D(int* n1, int n2);

		int* vertIndexes;
		int nVertIndexes;
	};

	class MeshBone3D {
	public:
		MeshBone3D();

		std::string getName();
		Bone3DVertexWeight* getVertexWeights();
		int getNumVertWeights();

		void setName(std::string nName);

	private:
		std::string name;

		Bone3DVertexWeight *vertWeights;
		int nVertWeights;

		glm::mat4x4 offsetMatrix;
	};

	class Bone3DVertexWeight {
	public:
		Bone3DVertexWeight(int vId, float w);

		int vertexId;
		float weight;
	};

}

#endif
