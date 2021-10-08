#include "Sprite.h"

namespace Engine
{
	Sprite::Sprite() :position({ 0.0f, 0.0f }), rotZ(0.0f), center({ 0.0f, 0.0f}), enable(true), size({1.0f,1.0f})
	{
		columns = 1;
		rows = 1;
		frame_width = 0;
		frame_height = 0;
		animation_speed = 0.03;
		animation_interval = 0.0;
		enable_animation = true;
		frame_total = 1;
		frame_count = 0;
		frame_block = { 0, 0, 0, 0 };
		contact_x = contact_top = contact_bot = false;
		color = D3DCOLOR_XRGB(255, 255, 255);
		arcade_movement = true;
		collision_flag = false;
		collision_type = CCIRCULAR;
		last_animation_time = 0;
		total_time = 0.0f;
		tag = "NULL";
		name = "NULL";
		gp_Engine->SetCollision(this);
		
	}

	Sprite::~Sprite()
	{
		
		fputs("\n Sprite Released", gp_Engine->GetDestFile());

		gp_Engine->RemoveCollision(this);
	}

	void Sprite::Load(char* filename)
	{
		name = filename;
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(filename, &info);
		//Creating Texture with non-power of 2
		D3DXCreateTextureFromFileEx(gp_Engine->getDevice(), filename, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
									1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
									0, &info, NULL, &texture);
	

		texture_height = (int)info.Height;
		texture_width = (int)info.Width;
		this->FindFrameDimension();

		this->Transform();										//Newly Added
		//center = Vector2(148 / 2, 180 / 2);
		
	}

	void Sprite::FindFrameDimension()
	{
		frame_width = (texture_width / columns);
		frame_height = (texture_height / rows);
	}

	void Sprite::Transform()
	{

		
		//Set Up Collision Points
	
		CollisionPoints cp[8] = { { position.x + frame_width*(1.0f / 4.0f) , position.y },								//Top From Left Offset
								  { position.x + frame_width*(3.0f / 4.0f), position.y },								//Top From Right Offset
								  { position.x + frame_width*(1.0f / 4.0f), (position.y - frame_height) },	//Bottom From Left Offset
								  { position.x + frame_width*(3.0f / 4.0f), (position.y - frame_height) },	//Bottom From Right Offset
								  { position.x, position.y - frame_height*(1.0f / 4.0f)},								//Left Arm Offset
								  { position.x, position.y - frame_height*(3.0f / 4.0f) },								//Left Arm Offset
								  { (position.x + frame_width), position.y - frame_height*(1.0f / 4.0f) },	//Right Arm Offset
								  { (position.x + frame_width), position.y - frame_height*(3.0f / 4.0f) },	//Right Arm Offset						  
								};
		//Copy the CollisionPoints to Sprite
		for (int i = 0; i < 8; i++)
		{
			
			CP[i] = cp[i];
		
		}

		center = Vector2((frame_width / 2)*size.x, (frame_height / 2)*size.y);
		//center = D3DXVECTOR2(center.x, center.y);
		D3DXMATRIX mat_world;
		//D3DXMatrixRotationZ(&mat_rot, rotZ);
		//D3DXMatrixScaling(&mat_scale, size.x, size.y, 1.0f);
		//D3DXMatrixTranslation(&mat_translate,position.x,position.y,0.0f);

		D3DXMatrixTransformation2D(&mat_world, NULL, 0, &D3DXVECTOR2(size.x, size.y), &D3DXVECTOR2(center.x, center.y), rotZ, &D3DXVECTOR2(position.x, position.y));

		//gp_Engine->GetInterfaceSprite()->SetTransform(&(mat_scale*mat_rot*mat_translate));
		gp_Engine->GetInterfaceSprite()->SetTransform(&mat_world);
		
	}

	void Sprite::Draw()
	{
		if (enable)
		{
			this->Transform();
			this->Animation();
			gp_Engine->GetInterfaceSprite()->Draw(texture,&frame_block, NULL, NULL, color);
			//gp_Engine->GetInterfaceSprite()->Flush();
			//gp_Engine->GetInterfaceSprite()->End();
		}

	}

	void Sprite::Animation()
	{
		float dt = gp_Engine->GetDeltaTime();
		total_time += dt;
		if (total_time >= animation_speed && gp_Engine->GetTimer()->totalTime() >= last_animation_time + animation_interval)
		{
			int c = (frame_count % columns )*frame_width;
			int r = (0 / rows)*frame_height;
			frame_block = { c,r, (c + frame_width), (r + frame_height) };
			total_time = 0.0f;
			frame_count++;
			if (frame_count >= frame_total)
			{
				frame_count = 0;
				last_animation_time = gp_Engine->GetTimer()->totalTime();
			}
		}
	}
	
	void Sprite::Translate(const Vector2& value)
	{
		
		Vector2 dir(sinf(rotZ), -cosf(rotZ));
			//Calculate Sprite Direction depending on its Rotation
			if (!arcade_movement)
			{
				velocity = {value.x*dir.x, value.y*dir.y };
				if (!this->isCollided())
				{
					position.x += velocity.x;
					position.y += velocity.y;
				}
			}
			else
			{
				velocity = value;
				if (!this->isCollided())
				{
					position.x += velocity.x;
					position.y += velocity.y;
				}
			}
		}

	Vector2 Sprite::CollisionEscape()
	{
		Vector2 pos_escape;

		if (!arcade_movement)
		{
			pos_escape.x += velocity.x;
			pos_escape.y += velocity.y;
		}
		else if (arcade_movement)
		{
			pos_escape.x += velocity.x;
			pos_escape.y += velocity.y;
		}

		return pos_escape;
	}

	void Sprite::Rotate(const float& Angle)
	{
		//Convert Angle to Radians
		rotZ +=(D3DX_PI/180.0f)*Angle;
	}
};