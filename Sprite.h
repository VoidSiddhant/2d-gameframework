
#include"Engine.h"
#ifndef SPRITE_H
#define SPRITE_H

namespace Engine
{
	enum COLLISION_TYPE
	{
		CCIRCULAR,
		CBOX,
		CROTATEDBOX
	};

	struct CollisionPoints
	{
		double x; double y;
	};

	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void Load(char* filename);
		void Translate(const Vector2& value);
		void Rotate(const float& Angle);
		void Transform();
		void Draw(void);
		Vector2 CollisionEscape();
		void SetAnimationBlock(RECT* outRect, int frame);
		void Animation(void);

		//Accessor Mutator Methods
		void SetArcadeMovement(const bool& value){ arcade_movement = value; }
		void SetPos(const Vector2& value){ position = value; }
		Vector2& Velocity(){ return velocity ; }
	
		void SetVelocity(const Vector2& value){ velocity = value; }
		void SetRotation(const float& Angle){ rotZ = (D3DX_PI / 180.0f)*Angle; }
		float GetRotation(){ return rotZ; }
		void SetScale(const Vector2& value){ size = value; }
		Vector2 GetScale(){ return size; }
		void Enable(const bool& status) { enable = status; }
		Vector2 GetCenter(){ return center; }
		void EnableCollision(const bool& status){ collision_enable = status; }
		Vector2 GetPos() { return position; }
		float GetDir() { return rotZ; }
		void SetCollision(const bool& value){ collision_flag = value; }
		bool isCollided(){ return collision_flag; }
		void SetCollisionType(const COLLISION_TYPE& value){ collision_type = value; }
		const COLLISION_TYPE& GetCollisionType(){ return collision_type; }
		void SetColor(const D3DCOLOR& value){ color = value; }
		Vector2 GetVelocity(){ return velocity; }
		double GetWidth(){ return texture_width; }
		double GetHeight(){ return texture_height; }
		void SetAnimationState(const bool& status){ enable_animation = status; }
		bool GetAnimationState(){ return enable_animation; }
		void SetAnimationFrames(const int& value){ frame_total = value; }
		//Only Use This Method if Engine is unable to detect frame size upon texture load.
		void SetAnimFrameSize(const int& width, const int& height){ frame_width = width; frame_height = height; }
		void SetAnimationSpeed(const double& speed){ animation_speed = speed; }
		void SetAnimColumnRow(const int& column, const int& row){ columns = column; rows = row; this->FindFrameDimension(); }
		void SetAnimationInterval(const double& pause_time){ animation_interval = pause_time; last_animation_time = -animation_interval; }
		int GetFrameHeight(){ return (int)frame_height; }
		int GetFrameWidth(){ return (int)frame_width; }
		CollisionPoints* GetCollisionPoints(){ return CP; }
		bool& ContactX(){ return contact_x ; }
		bool& ContactTop(){	return contact_top ; }
		bool& ContactBot(){ return contact_bot ; }

	
		std::string& Name(){ return name; }
		std::string& Tag(){ return tag; }

	private:
		void FindFrameDimension(void);
		Vector2 position,center,size,velocity;
		double animation_speed, animation_interval, last_animation_time;
		int frame_count, frame_total, columns, rows,texture_height, texture_width, frame_height, frame_width;
		RECT frame_block;
		COLLISION_TYPE collision_type;
		float rotZ,total_time;
		bool arcade_movement,enable,collision_enable,collision_flag,enable_animation;
		LPDIRECT3DTEXTURE9 texture;
		D3DXMATRIX mat_translate, mat_rot, mat_scale;
		D3DCOLOR color;
		std::string name,tag;
		CollisionPoints CP[8];
		bool contact_x, contact_top, contact_bot,jumping;

	};
};

#endif