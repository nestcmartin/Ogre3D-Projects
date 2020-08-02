#include "FirstPersonCharacterController.h"
#include "Core/InputSystem/InputManager.h"
#include "GraphicsEngine/Scene/SceneManager.h"

FirstPersonCharacterController::FirstPersonCharacterController(Camera* cam) :
    camera_(cam)
{
    body_ = new MovableObject(Ogre::Vector3::UNIT_Y * CHAR_HEIGHT, Ogre::Quaternion::IDENTITY);
    cameraPivot_ = new MovableObject(Ogre::Vector3(0, 0, 0), Ogre::Quaternion::IDENTITY);
    cameraGoal_ = new MovableObject(cameraPivot_, Ogre::Vector3(0, 0, 5), Ogre::Quaternion::IDENTITY);

    camera_->setPosition(cameraPivot_->getPosition() + cameraGoal_->getPosition());
    camera_->setNearClipDistance(0.1);
    camera_->setFarClipDistance(100);

    cameraPivot_->setFixedYawAxis(true);
    cameraGoal_->setFixedYawAxis(true);
    camera_->setFixedYawAxis(true);

    weapon_ = new Model("RightSword", "Sword.mesh", camera_, Ogre::Vector3(2, -2, -5));
    weapon_->yaw(180);
    weapon_->pitch(-40);

    keyDirection_ = Ogre::Vector3::ZERO;
    jumpSpeed_ = 0;
    pivotPitch_ = 0;
    jumping_ = false;

    InputManager::Instance()->addInputListener(this);
}

void FirstPersonCharacterController::update(float deltaTime)
{
    goalDirection_ = Ogre::Vector3::ZERO;

    if (keyDirection_ != Ogre::Vector3::ZERO)
    {
        goalDirection_ += keyDirection_.z * camera_->getRotation().zAxis();
        goalDirection_ += keyDirection_.x * camera_->getRotation().xAxis();
        goalDirection_.y = 0;

        Ogre::Quaternion toGoal = body_->getRotation().zAxis().getRotationTo(goalDirection_.normalisedCopy());
        float yawToGoal = toGoal.getYaw().valueDegrees();
        body_->yaw(yawToGoal);

        body_->translate(Ogre::Vector3(0, 0, deltaTime * WALK_SPEED), TransformSpace::LOCAL);
    }

    if (jumping_)
    {
        body_->translate(0, jumpSpeed_ * deltaTime, 0, TransformSpace::LOCAL);
        jumpSpeed_ -= GRAVITY * deltaTime;

        Ogre::Vector3 pos = body_->getPosition();
        if (pos.y <= CHAR_HEIGHT)
        {
            pos.y = CHAR_HEIGHT;
            body_->setPosition(pos);
            jumping_ = false;
        }
    }

    cameraPivot_->setPosition(body_->getPosition() + Ogre::Vector3::UNIT_Y * CAM_HEIGHT);
    Ogre::Vector3 goalOffset = cameraGoal_->getDerivedPosition() - camera_->getPosition();
    camera_->translate(goalOffset * deltaTime * 9.0f);
    camera_->lookAt(cameraPivot_->getDerivedPosition(), TransformSpace::PARENT);
}

bool FirstPersonCharacterController::keyPressed(const KeyboardEvent& evt)
{
    Keycode key = evt.keysym.sym;

    // Move
    if (key == 'w') keyDirection_.z = -1;
    else if (key == 'a') keyDirection_.x = -1;
    else if (key == 's') keyDirection_.z = 1;
    else if (key == 'd') keyDirection_.x = 1;

    // Jump
    else if (key == InputKey::SPACE && !jumping_)
    {
        jumping_ = true;
        jumpSpeed_ = JUMP_ACCEL;
    }

    return true;
}

bool FirstPersonCharacterController::keyReleased(const KeyboardEvent& evt)
{
    Keycode key = evt.keysym.sym;

    if (key == 'w' && keyDirection_.z == -1) keyDirection_.z = 0;
    else if (key == 'a' && keyDirection_.x == -1) keyDirection_.x = 0;
    else if (key == 's' && keyDirection_.z == 1) keyDirection_.z = 0;
    else if (key == 'd' && keyDirection_.x == 1) keyDirection_.x = 0;

    return true;
}

bool FirstPersonCharacterController::mouseMoved(const MouseMotionEvent& evt)
{
    updateCameraGoal(-0.5f * evt.xrel, -0.5f * evt.yrel, 0);
    return true;
}

bool FirstPersonCharacterController::mouseWheelRolled(const MouseWheelEvent& evt)
{
    updateCameraGoal(0, 0, -0.05f * evt.y);
    return true;
}

void FirstPersonCharacterController::updateCameraGoal(float deltaYaw, float deltaPitch, float deltaZoom)
{
    cameraPivot_->yaw(deltaYaw, TransformSpace::PARENT);

    if (!(pivotPitch_ + deltaPitch > 25 && deltaPitch > 0) &&
        !(pivotPitch_ + deltaPitch < -60 && deltaPitch < 0))
    {
        cameraPivot_->pitch(deltaPitch, TransformSpace::LOCAL);
        pivotPitch_ += deltaPitch;
    }

    float dist = cameraGoal_->distance(cameraPivot_);
    float distChange = deltaZoom * dist;

    if (!(dist + distChange < 8 && distChange < 0) &&
        !(dist + distChange > 25 && distChange > 0))
    {
        cameraGoal_->translate(0, 0, distChange, TransformSpace::LOCAL);
    }
}