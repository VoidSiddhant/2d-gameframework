#include"Engine.h"

#ifndef MESH_H
#define MESH_H

namespace Engine
{
	class Mesh
	{
	public: 
			 Mesh();
		bool Load(char* filename);
		void Draw();
		void SetPosition(Vector3 position) { pos = position; }
		void Transform();
		void CreateCube(float width, float height, float depth);
		void CreateSphere(float radius, float height, float depth);
		void SetRotation(Vector3 rotation){ rot = rotation; }
		void Rotate(Vector3 rotation);
		void Translate(Vector3 translate);
		void SetScale(Vector3 scaling){ scale = scaling; }
		~Mesh();
	public:
		LPD3DXMESH mesh;
		D3DMATERIAL9* materials;
		LPDIRECT3DTEXTURE9* textures;
		LPD3DXMATERIAL d3dx_material;
		LPD3DXBUFFER d3dx_buffer;
		DWORD materialCount;
		Vector3 pos, rot, scale;
	};
}

#endif