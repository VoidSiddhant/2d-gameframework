#include"Mesh.h"

namespace Engine
{
	Mesh::Mesh()
	{
		materials = 0;
		mesh = 0;
		materialCount = 0;
		textures = 0;
		d3dx_buffer = 0;
		d3dx_material = 0;
		pos = Vector3(0.0f, 0.0f, 0.0f);
		rot = Vector3(0.0f, 0.0f, 0.0f);
		scale = Vector3(1.0f, 1.0f, 1.0f);
	}

	Mesh::~Mesh()
	{
		fopen("Exit.txt", "a");
		fputs( "\n Materials Released \n Textures Relaeased",gp_Engine->GetDestFile());
		fclose(gp_Engine->GetDestFile());
		if (materials != NULL)
			delete[] materials;
		if (textures != NULL)
		{
			for (DWORD i = 0; i < materialCount; i++)
			{
				if (textures[i] != NULL)
					textures[i]->Release();
			}
		}
		delete[] textures;
	}

	bool Mesh::Load(char* filename)
	{
		HRESULT hr;
		hr = D3DXLoadMeshFromX(filename,D3DXMESH_SYSTEMMEM,gp_Engine->getDevice(),NULL,&d3dx_buffer,NULL,&materialCount,&mesh);

		if (hr != D3D_OK)
		{
			return false;
		}

		//Extract Material Properties and Texture names from material buffer
		d3dx_material = (LPD3DXMATERIAL)d3dx_buffer->GetBufferPointer();
		materials = new D3DMATERIAL9[materialCount];
		textures = new LPDIRECT3DTEXTURE9[materialCount];

		//Create the material and texture
		for (DWORD i = 0; i < materialCount; i++)
		{
			//Grab the Material from the Buffer
			materials[i] = d3dx_material[i].MatD3D;
			materials[i].Ambient = materials[i].Diffuse;
			//materials[i].Emissive = materials[i].Diffuse;
			materials[i].Power = 0.5f;
			//materials[i].Specular = materials[i].Diffuse;

			textures[i] = NULL;
			if (d3dx_material[i].pTextureFilename != NULL && lstrlen(d3dx_material[i].pTextureFilename) > 0)
			{
				//Load Texture File in .x File
				hr = D3DXCreateTextureFromFile(gp_Engine->getDevice(), d3dx_material[i].pTextureFilename, &textures[i]);
				if (hr != D3D_OK)
					return false;
			}
		}
		d3dx_buffer->Release();
		return true;
	}

	void Mesh::CreateSphere(float radius,float height,float depth)
	{
		D3DXCreateSphere(gp_Engine->getDevice(), radius, height, depth, &mesh,NULL);
	}

	void Mesh::CreateCube(float width,float height,float depth)
	{
		D3DXCreateBox(gp_Engine->getDevice(), width, height, depth, &mesh, NULL);
	}

	void Mesh::Draw()
	{
		if (materialCount == 0)
		{
			mesh->DrawSubset(0);
		}
		else
		{
			//Draw Each Mesh Subset
			for (DWORD i = 0; i < materialCount; i++)
			{
				gp_Engine->getDevice()->SetMaterial(&materials[i]);

				if (textures[i])
				{
					if (textures[i]->GetType() == D3DRTYPE_TEXTURE)
					{
						D3DSURFACE_DESC desc;
						textures[i]->GetLevelDesc(0, &desc);
						if (desc.Width > 0)
						{
							gp_Engine->getDevice()->SetTexture(0, textures[i]);
						}
					}
				}
				mesh->DrawSubset(i);
			}
		}
	}

	void Mesh::Transform()
	{
		D3DXMATRIX mat_world,mat_rot,mat_scale,mat_pos;
		D3DXMatrixIdentity(&mat_world);
		D3DXMatrixRotationYawPitchRoll(&mat_rot, rot.y,rot.x,rot.z);
		D3DXMatrixScaling(&mat_scale, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&mat_pos, pos.x, pos.y, pos.z);
		mat_world = mat_scale*mat_rot*mat_pos;
			gp_Engine->getDevice()->SetTransform(D3DTS_WORLD, &mat_world);
	}

	void Mesh::Rotate(Vector3 rotation)
	{
		rot.x += rotation.x;
		rot.y += rotation.y;
		rot.z += rotation.z;
	}

	void Mesh::Translate(Vector3 translate)
	{
		pos.x += translate.x;
		pos.y += translate.y;
		pos.z += translate.z;
	}

}