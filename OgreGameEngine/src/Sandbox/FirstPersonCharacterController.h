#ifndef __FPS_CHARACTER_H__
#define __FPS_CHARACTER_H__

#include "Core/InputSystem/InputListener.h"
#include "GraphicsEngine/Scene/Camera.h"
#include "GraphicsEngine/Scene/Model.h"

class FirstPersonCharacterController : public InputListener
{
private:
	const int CHAR_HEIGHT = 5;            
	const int CAM_HEIGHT = 2;             
	const int WALK_SPEED = 17;

	const float JUMP_ACCEL = 45.0f;       
	const float GRAVITY = 90.0f;

	Camera* camera_;
	Model* weapon_;
	MovableObject* body_;
	MovableObject* cameraPivot_;
	MovableObject* cameraGoal_;
	float pivotPitch_;

	Ogre::Vector3 keyDirection_;   
	Ogre::Vector3 goalDirection_;  
	float jumpSpeed_;    
	bool jumping_;

public:
	FirstPersonCharacterController(Camera* cam);

	void update(float deltaTime);

	bool keyPressed(const KeyboardEvent& evt) override;
	bool keyReleased(const KeyboardEvent& evt) override;
	bool mouseMoved(const MouseMotionEvent& evt) override;
	bool mouseWheelRolled(const MouseWheelEvent& evt) override;

private:
	void updateCameraGoal(float deltaYaw, float deltaPitch, float deltaZoom);
};

#endif // !__FPS_CHARACTER_H__
