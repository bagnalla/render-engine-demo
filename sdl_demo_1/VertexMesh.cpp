#include "VertexMesh.h"
#include "DrawableObject.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderGraph.h"
#include "Game.h"
#include "Shadow.h"
#include <iostream>

namespace Bagnall
{
	// PUBLIC

	VertexMesh::VertexMesh()
	{
		init();
	}

	VertexMesh::VertexMesh(DrawableObject *o, const Material& mat, int iOffset, int iCount, bool tStrip)
	{
		init();

		owner = o;
		material = mat;
		indexOffset = iOffset;
		indexCount = iCount;
		triangleStrip = tStrip;
		texture = 0;
	}

	VertexMesh::~VertexMesh()
	{
		if (renderNode != NULL)
			renderNode->meshes.erase(std::find(renderNode->meshes.begin(), renderNode->meshes.end(), this));
	}

	void VertexMesh::AddVertexMeshPrototype(const char *name, const Material& mat, int vOffset, int vCount, bool tStrip)
	{
		auto it = vertexMeshPrototypeMap.find(name);
		if (it == vertexMeshPrototypeMap.end())
			vertexMeshPrototypeMap.emplace(name, VertexMesh(NULL, mat, vOffset, vCount, tStrip));
		else
			std::cerr << "vertex mesh already exists with name: " << name << std::endl;
	}

	VertexMesh VertexMesh::GetVertexMeshPrototypeByName(const char *name)
	{
		auto it = vertexMeshPrototypeMap.find(name);
		if (it != vertexMeshPrototypeMap.end())
			return vertexMeshPrototypeMap[name];
		else
		{
			std::cerr << "vertex mesh doesn't exist with name: " << name << std::endl;
			return VertexMesh(NULL, Material::None(), 0, 0, 0);
		}
	}

	void VertexMesh::Draw() const
	{
		owner->SendTransformToGPU();

		if (cubeMap != 0)
			Shader::SetReflectiveCubeMap(reflectiveCubeMap);

		// hacky way of doing triangle strip instead of triangles when the bool is set
		// because GL_TRIANGLES is 4 and GL_TRIANGLE_STRIP is 5
		//glDrawArrays(GL_TRIANGLES + triangleStrip, globalVertexOffset, vertexCount);
		glDrawElements(GL_TRIANGLES + triangleStrip, indexCount, GL_UNSIGNED_INT, reinterpret_cast<void*>(indexOffset * sizeof(uint)));
	}

	void VertexMesh::UpdateRenderNode()
	{
		if (renderNode != NULL)
			renderNode->meshes.erase(std::find(renderNode->meshes.begin(), renderNode->meshes.end(), this));
		renderNode = Game::MainRenderGraph->AddVertexMesh(this);
		Shadow::AddToDepthRenderList(this);
	}

	void VertexMesh::EnableRender()
	{
		renderEnabled = true;
	}

	void VertexMesh::DisableRender()
	{
		renderEnabled = false;
	}

	void VertexMesh::Cull()
	{
		if (renderNode != NULL)
			renderNode->meshes.erase(std::find(renderNode->meshes.begin(), renderNode->meshes.end(), this));
		renderNode = NULL;

		Shadow::RemoveFromDepthRenderList(this);
	}

	void VertexMesh::UnCull()
	{
		Shadow::AddToDepthRenderList(this);
		UpdateRenderNode();
	}

	DrawableObject* VertexMesh::GetOwner()
	{
		return owner;
	}
	void VertexMesh::SetOwner(DrawableObject *o)
	{
		owner = o;
	}

	Material VertexMesh::GetMaterial()
	{
		return material;
	}
	void VertexMesh::SetMaterial(const Material& mat)
	{
		material = mat;
	}

	GLuint VertexMesh::GetTexture()
	{
		return texture;
	}
	void VertexMesh::SetTexture(GLuint tex)
	{
		texture = tex;
	}

	GLuint VertexMesh::GetCubeMap()
	{
		return cubeMap;
	}
	void VertexMesh::SetCubeMap(GLuint cMap)
	{
		cubeMap = cMap;
	}

	bool VertexMesh::GetReflectiveCubeMap()
	{
		return reflectiveCubeMap;
	}
	void VertexMesh::SetReflectiveCubeMap(bool b)
	{
		reflectiveCubeMap = b;
	}

	bool VertexMesh::GetBumpMapEnabled()
	{
		return bumpMapEnabled;
	}
	void VertexMesh::SetBumpMapEnabled(bool b)
	{
		bumpMapEnabled = b;
	}

	bool VertexMesh::GetEmissive()
	{
		return emissive;
	}
	void VertexMesh::SetEmissive(bool b)
	{
		emissive = b;
	}

	vec4 VertexMesh::GetEmissionColor()
	{
		return emissionColor;
	}
	void VertexMesh::SetEmissionColor(const vec4& eColor)
	{
		emissionColor = eColor;
	}

	bool VertexMesh::GetRenderEnabled()
	{
		return renderEnabled;
	}
	void VertexMesh::SetRenderEnabled(bool b)
	{
		renderEnabled = b;
	}

	// PRIVATE

	std::unordered_map<const char*, VertexMesh> VertexMesh::vertexMeshPrototypeMap;

	void VertexMesh::init()
	{
		owner = NULL;
		material = Material::None();
		texture = 0;
		cubeMap = 0;
		reflectiveCubeMap = false;
		bumpMapEnabled = true;
		emissive = false;
		emissionColor = vec4();
		renderNode = NULL;
		renderEnabled = true;

		indexOffset = 0;
		indexCount = 0;
		triangleStrip = false;
	}
}
