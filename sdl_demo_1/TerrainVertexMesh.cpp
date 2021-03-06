#include "TerrainVertexMesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Game.h"
#include "RenderGraph.h"
#include "Shadow.h"

namespace Bagnall
{
	// PUBLIC

	TerrainVertexMesh::TerrainVertexMesh(const Material& mat, int iOffset, int iCount) : VertexMesh(nullptr, mat, iOffset, iCount, true)
	{
	}

	TerrainVertexMesh::~TerrainVertexMesh()
	{
		Game::MainRenderGraph->RemoveTerrainVertexMesh(this);
	}

	void TerrainVertexMesh::DrawWithoutBumpMap() const
	{
		// bind textures
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_2);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_3);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_4);
		glBindTexture(GL_TEXTURE_2D, texture1);

		Shader::SetGroundCoordZ(groundCoordZ);
		Shader::SetTerrainScaleZ(scaleZ);
		Shader::SetTerrainMaxHeight(maxHeight);
		Shader::SetTexHeights(textureHeights);

		VertexMesh::Draw();
	}

	void TerrainVertexMesh::DrawWithBumpMap() const
	{
		// bind textures
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_2);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_3);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_4);
		glBindTexture(GL_TEXTURE_2D, texture4);

		// bind bump maps
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_BUMP_1);
		glBindTexture(GL_TEXTURE_2D, Texture::GetBumpMapByTexture(texture1));
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_BUMP_2);
		glBindTexture(GL_TEXTURE_2D, Texture::GetBumpMapByTexture(texture2));
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_BUMP_3);
		glBindTexture(GL_TEXTURE_2D, Texture::GetBumpMapByTexture(texture3));
		glActiveTexture(GL_TEXTURE0 + TEXTURE_TERRAIN_BUMP_4);
		glBindTexture(GL_TEXTURE_2D, Texture::GetBumpMapByTexture(texture4));

		Shader::SetGroundCoordZ(groundCoordZ);
		Shader::SetTerrainScaleZ(scaleZ);
		Shader::SetTerrainMaxHeight(maxHeight);
		Shader::SetTexHeights(textureHeights);

		VertexMesh::Draw();
	}

	void TerrainVertexMesh::UpdateRenderNode()
	{
		Game::MainRenderGraph->AddTerrainVertexMesh(this);
		Shadow::AddToDepthRenderList(this);
	}

	GLuint TerrainVertexMesh::GetTexture1() const
	{
		return texture1;
	}
	GLuint TerrainVertexMesh::GetTexture2() const
	{
		return texture2;
	}
	GLuint TerrainVertexMesh::GetTexture3() const
	{
		return texture3;
	}
	GLuint TerrainVertexMesh::GetTexture4() const
	{
		return texture4;
	}
	vec4 TerrainVertexMesh::GetTextureHeights() const
	{
		return textureHeights;
	}
	float TerrainVertexMesh::GetGroundCoordZ() const
	{
		return groundCoordZ;
	}
	float TerrainVertexMesh::GetScaleZ() const
	{
		return scaleZ;
	}
	int TerrainVertexMesh::GetMaxHeight() const
	{
		return maxHeight;
	}

	void TerrainVertexMesh::SetTexture1(GLuint tex1)
	{
		texture1 = tex1;
	}
	void TerrainVertexMesh::SetTexture2(GLuint tex2)
	{
		texture2 = tex2;
	}
	void TerrainVertexMesh::SetTexture3(GLuint tex3)
	{
		texture3 = tex3;
	}
	void TerrainVertexMesh::SetTexture4(GLuint tex4)
	{
		texture4 = tex4;
	}
	void TerrainVertexMesh::SetTextureHeights(const vec4& texHeights)
	{
		textureHeights = texHeights;
	}
	void TerrainVertexMesh::SetGroundCoordZ(float z)
	{
		groundCoordZ = z;
	}
	void TerrainVertexMesh::SetScaleZ(float z)
	{
		scaleZ = z;
	}
	void TerrainVertexMesh::SetMaxHeight(int h)
	{
		maxHeight = h;
	}
}
