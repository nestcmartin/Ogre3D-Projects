#include "ThirdPersonCharacterController.h"
#include "Core/InputSystem/InputManager.h"
#include "GraphicsEngine/Scene/SceneManager.h"

ThirdPersonCharacterController::ThirdPersonCharacterController(Camera* cam) :
    camera_(cam),
    currentBaseAnimation_(ANIM_NONE),
    currentTopAniamtion_(ANIM_NONE)
{
    setupBody();
    setupCamera();
    setupAnimations();

    InputManager::Instance()->addInputListener(this);
}

void ThirdPersonCharacterController::update(float deltaTime)
{
    updateBody(deltaTime);
    updateCamera(deltaTime);
    updateAnimations(deltaTime);
}

bool ThirdPersonCharacterController::keyPressed(const KeyboardEvent& evt)
{
    Keycode key = evt.keysym.sym;

    // Swords
    if (key == 'q' && (currentTopAniamtion_ == ANIM_IDLE_TOP || currentTopAniamtion_== ANIM_RUN_TOP))
    {
        setTopAnimation(ANIM_DRAW_SWORDS, true);
        timer_ = 0;
    }

    // Dance
    else if (key == 'e' && !swordsDrawn_)
    {
        if (currentTopAniamtion_ == ANIM_IDLE_TOP || currentTopAniamtion_ == ANIM_RUN_TOP)
        {
            setBaseAnimation(ANIM_DANCE, true);
            setTopAnimation(ANIM_NONE);
            
            animations_[ANIM_HANDS_RELAXED]->setEnabled(false);
        }
        else if (currentBaseAnimation_ == ANIM_DANCE)
        {
            setBaseAnimation(ANIM_IDLE_BASE);
            setTopAnimation(ANIM_IDLE_TOP);
         
            animations_[ANIM_HANDS_RELAXED]->setEnabled(true);
        }
    }

    // Move
    else if (key == 'w') keyDirection_.z = -1;
    else if (key == 'a') keyDirection_.x = -1;
    else if (key == 's') keyDirection_.z = 1;
    else if (key == 'd') keyDirection_.x = 1;

    // Jump
    else if (key == InputKey::SPACE && (currentTopAniamtion_ == ANIM_IDLE_TOP || currentTopAniamtion_ == ANIM_RUN_TOP))
    {
        setBaseAnimation(ANIM_JUMP_START, true);
        setTopAnimation(ANIM_NONE);
        timer_ = 0;
    }

    if (!keyDirection_.isZeroLength() && currentBaseAnimation_ == ANIM_IDLE_BASE)
    {
        setBaseAnimation(ANIM_RUN_BASE, true);
        if (currentTopAniamtion_ == ANIM_IDLE_TOP) setTopAnimation(ANIM_RUN_TOP, true);
    }
    
    return true;
}

bool ThirdPersonCharacterController::keyReleased(const KeyboardEvent& evt)
{
    Keycode key = evt.keysym.sym;

    if (key == 'w' && keyDirection_.z == -1) keyDirection_.z = 0;
    else if (key == 'a' && keyDirection_.x == -1) keyDirection_.x = 0;
    else if (key == 's' && keyDirection_.z == 1) keyDirection_.z = 0;
    else if (key == 'd' && keyDirection_.x == 1) keyDirection_.x = 0;

    if (keyDirection_.isZeroLength() && currentBaseAnimation_ == ANIM_RUN_BASE)
    {
        setBaseAnimation(ANIM_IDLE_BASE);
        if (currentTopAniamtion_ == ANIM_RUN_TOP) setTopAnimation(ANIM_IDLE_TOP);
    }

    return true;
}

bool ThirdPersonCharacterController::mouseMoved(const MouseMotionEvent& evt)
{
    updateCameraGoal(-0.5f * evt.xrel, -0.5f * evt.yrel, 0);
    return true;
}

bool ThirdPersonCharacterController::mouseWheelRolled(const MouseWheelEvent& evt)
{
    updateCameraGoal(0, 0, -0.05f * evt.y);
    return true;
}

bool ThirdPersonCharacterController::mousePressed(const MouseButtonEvent& evt)
{
    if (swordsDrawn_ && (currentTopAniamtion_ == ANIM_IDLE_TOP || currentTopAniamtion_ == ANIM_RUN_TOP))
    {
        if (evt.button == BUTTON_LEFT) setTopAnimation(ANIM_SLICE_VERTICAL, true);
        else if (evt.button == BUTTON_RIGHT) setTopAnimation(ANIM_SLICE_HORIZONTAL, true);
        timer_ = 0;
        return true;
    }
    return false;
}

void ThirdPersonCharacterController::setupBody()
{
    body_ = new Model("SinbadBody", "Sinbad.mesh", Ogre::Vector3::UNIT_Y * CHAR_HEIGHT);
    body_->setCastShadows(true);
    leftSword_ = new Model("LeftSword", "Sword.mesh");
    leftSword_->setCastShadows(true);
    rightSword_ = new Model("RightSword", "Sword.mesh");
    rightSword_->setCastShadows(true);

    body_->attachObjectToBone(leftSword_, "Sheath.L");
    body_->attachObjectToBone(rightSword_, "Sheath.R");

    swordTrail_ = new Trail(2, 80, 20);
    swordTrail_->setMaterialName("Examples/LightRibbonTrail");
    swordTrail_->setInitialColour(1, 0.8, 0);
    swordTrail_->setColourChange(0.75, 1.25, 1.25, 1.25);
    swordTrail_->setInitialWidth(0.5);
    swordTrail_->setWidthChange(1);

    keyDirection_ = Ogre::Vector3::ZERO;
    jumpSpeed_ = 0;
}

void ThirdPersonCharacterController::setupCamera()
{
    cameraPivot_ = new MovableObject(Ogre::Vector3(0, 0, 0), Ogre::Quaternion::IDENTITY);
    cameraGoal_ = new MovableObject(cameraPivot_, Ogre::Vector3(0, 0, 15), Ogre::Quaternion::IDENTITY);

    camera_->setPosition(cameraPivot_->getPosition() + cameraGoal_->getPosition());
    camera_->setNearClipDistance(0.1);
    camera_->setFarClipDistance(100);

    cameraPivot_->setFixedYawAxis(true);
    cameraGoal_->setFixedYawAxis(true);
    camera_->setFixedYawAxis(true);

    pivotPitch_ = 0;
}

void ThirdPersonCharacterController::setupAnimations()
{
    body_->setAnimationBlendMode(AnimationBlendMode::CUMULATIVE);

    const char* animNames[NUM_ANIMS] =
    { "IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
    "SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd" };

    for (int i = 0; i < NUM_ANIMS; i++)
    {
        animations_[i] = body_->getAnimationState(animNames[i]);
        animations_[i]->setLoop(true);
        fadingInAnimations_[i] = false;
        fadingOutAnimations_[i] = false;
    }

    setBaseAnimation(ANIM_IDLE_BASE);
    setTopAnimation(ANIM_IDLE_TOP);

    animations_[ANIM_HANDS_RELAXED]->setEnabled(true);
    swordsDrawn_ = false;
}

void ThirdPersonCharacterController::updateBody(float deltaTime)
{
    goalDirection_ = Ogre::Vector3::ZERO;

    if (keyDirection_ != Ogre::Vector3::ZERO && currentBaseAnimation_ != ANIM_DANCE)
    {
        goalDirection_ += keyDirection_.z * camera_->getRotation().zAxis();
        goalDirection_ += keyDirection_.x * camera_->getRotation().xAxis();
        goalDirection_.y = 0;
        goalDirection_.normalise();

        Ogre::Quaternion toGoal = body_->getRotation().zAxis().getRotationTo(goalDirection_);
        float yawToGoal = toGoal.getYaw().valueDegrees();
        float yawAtSpeed = yawToGoal / Ogre::Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
        if (currentBaseAnimation_ == ANIM_JUMP_LOOP) yawAtSpeed *= 0.2f;
        if (yawToGoal < 0) yawToGoal = std::min<float>(0, std::max<float>(yawToGoal, yawAtSpeed));
        else if (yawToGoal > 0) yawToGoal = std::max<float>(0, std::min<float>(yawToGoal, yawAtSpeed));

        body_->yaw(yawToGoal);
        body_->translate(Ogre::Vector3(0, 0, deltaTime * RUN_SPEED * animations_[currentBaseAnimation_]->getWeight()), TransformSpace::LOCAL);
    }

    if (currentBaseAnimation_ == ANIM_JUMP_LOOP)
    {
        body_->translate(0, jumpSpeed_ * deltaTime, 0, TransformSpace::LOCAL);
        jumpSpeed_ -= GRAVITY * deltaTime;

        Ogre::Vector3 pos = body_->getPosition();
        if (pos.y <= CHAR_HEIGHT)
        {
            pos.y = CHAR_HEIGHT;
            body_->setPosition(pos);
            setBaseAnimation(ANIM_JUMP_END, true);
            timer_ = 0;
        }
    }
}

void ThirdPersonCharacterController::updateCamera(float deltaTime)
{
    cameraPivot_->setPosition(body_->getPosition() + Ogre::Vector3::UNIT_Y * CAM_HEIGHT);
    Ogre::Vector3 goalOffset = cameraGoal_->getDerivedPosition() - camera_->getPosition();
    camera_->translate(goalOffset * deltaTime * 9.0f);
    camera_->lookAt(cameraPivot_->getDerivedPosition(), TransformSpace::PARENT);
}

void ThirdPersonCharacterController::updateAnimations(float deltaTime)
{
    float baseAnimSpeed = 1;
    float topAnimSpeed = 1;

    timer_ += deltaTime;

    if (currentTopAniamtion_ == ANIM_DRAW_SWORDS)
    {
        topAnimSpeed = swordsDrawn_ ? -1 : 1;

        if (timer_ >= animations_[currentTopAniamtion_]->getLength() / 2 && timer_ - deltaTime < animations_[currentTopAniamtion_]->getLength() / 2)
        {
            body_->detachAllObjectsFromBone();
            body_->attachObjectToBone(leftSword_, swordsDrawn_ ? "Sheath.L" : "Handle.L");
            body_->attachObjectToBone(rightSword_, swordsDrawn_ ? "Sheath.R" : "Handle.R");
            animations_[ANIM_HANDS_CLOSED]->setEnabled(!swordsDrawn_);
            animations_[ANIM_HANDS_RELAXED]->setEnabled(swordsDrawn_);

            if (swordsDrawn_)
            {
                swordTrail_->setVisible(false);
                swordTrail_->untrack(leftSword_);
                swordTrail_->untrack(rightSword_);
            }
            else
            {
                swordTrail_->setVisible(true);
                swordTrail_->track(leftSword_);
                swordTrail_->track(rightSword_);
            }
        }

        if (timer_ >= animations_[currentTopAniamtion_]->getLength())
        {
            if (currentBaseAnimation_ == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
            else
            {
                setTopAnimation(ANIM_RUN_TOP);
                animations_[ANIM_RUN_TOP]->setTimePosition(animations_[ANIM_RUN_BASE]->getTimePosition());
            }
            swordsDrawn_ = !swordsDrawn_;
        }
    }
    else if (currentTopAniamtion_ == ANIM_SLICE_VERTICAL || currentTopAniamtion_ == ANIM_SLICE_HORIZONTAL)
    {
        if (timer_ >= animations_[currentTopAniamtion_]->getLength())
        {
            if (currentBaseAnimation_ == ANIM_IDLE_BASE) setTopAnimation(ANIM_IDLE_TOP);
            else
            {
                setTopAnimation(ANIM_RUN_TOP);
                animations_[ANIM_RUN_TOP]->setTimePosition(animations_[ANIM_RUN_BASE]->getTimePosition());
            }
        }
        if (currentBaseAnimation_ == ANIM_IDLE_BASE) baseAnimSpeed = 0;
    }
    else if (currentBaseAnimation_ == ANIM_JUMP_START)
    {
        if (timer_ >= animations_[currentBaseAnimation_]->getLength())
        {
            setBaseAnimation(ANIM_JUMP_LOOP, true);
            jumpSpeed_ = JUMP_ACCEL;
        }
    }
    else if (currentBaseAnimation_ == ANIM_JUMP_END)
    {
        if (timer_ >= animations_[currentBaseAnimation_]->getLength())
        {
            if (keyDirection_ == Ogre::Vector3::ZERO)
            {
                setBaseAnimation(ANIM_IDLE_BASE);
                setTopAnimation(ANIM_IDLE_TOP);
            }
            else
            {
                setBaseAnimation(ANIM_RUN_BASE, true);
                setTopAnimation(ANIM_RUN_TOP, true);
            }
        }
    }

    if (currentBaseAnimation_ != ANIM_NONE) animations_[currentBaseAnimation_]->addTime(deltaTime * baseAnimSpeed);
    if (currentTopAniamtion_ != ANIM_NONE) animations_[currentTopAniamtion_]->addTime(deltaTime * topAnimSpeed);

    fadeAnimations(deltaTime);
}

void ThirdPersonCharacterController::fadeAnimations(float deltaTime)
{
    for (int i = 0; i < NUM_ANIMS; i++)
    {
        if (fadingInAnimations_[i])
        {
            float newWeight = animations_[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
            animations_[i]->setWeight(Ogre::Math::Clamp<float>(newWeight, 0, 1));
            if (newWeight >= 1) fadingInAnimations_[i] = false;
        }
        else if (fadingOutAnimations_[i])
        {
            float newWeight = animations_[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
            animations_[i]->setWeight(Ogre::Math::Clamp<float>(newWeight, 0, 1));
            if (newWeight <= 0)
            {
                animations_[i]->setEnabled(false);
                fadingInAnimations_[i] = false;
            }
        }
    }
}

void ThirdPersonCharacterController::updateCameraGoal(float deltaYaw, float deltaPitch, float deltaZoom)
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

void ThirdPersonCharacterController::setBaseAnimation(AnimationID id, bool reset)
{
    if (currentBaseAnimation_ != ANIM_NONE)
    {
        fadingInAnimations_[currentBaseAnimation_] = false;
        fadingOutAnimations_[currentBaseAnimation_] = true;
    }

    currentBaseAnimation_ = id;

    if (id != ANIM_NONE)
    {
        animations_[id]->setEnabled(true);
        animations_[id]->setWeight(0);
        fadingOutAnimations_[id] = false;
        fadingInAnimations_[id] = true;
        if (reset) animations_[id]->setTimePosition(0);
    }
}

void ThirdPersonCharacterController::setTopAnimation(AnimationID id, bool reset)
{
    if (currentTopAniamtion_ != ANIM_NONE)
    {
        fadingInAnimations_[currentTopAniamtion_] = false;
        fadingOutAnimations_[currentTopAniamtion_] = true;
    }

    currentTopAniamtion_ = id;

    if (id != ANIM_NONE)
    {
        animations_[id]->setEnabled(true);
        animations_[id]->setWeight(0);
        fadingOutAnimations_[id] = false;
        fadingInAnimations_[id] = true;
        if (reset) animations_[id]->setTimePosition(0);
    }
}