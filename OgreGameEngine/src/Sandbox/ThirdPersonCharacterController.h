#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "OgreSceneManager.h"
#include "OgreAnimationState.h"
#include "Core/InputSystem/InputListener.h"
#include "GraphicsEngine/Scene/Camera.h"
#include "GraphicsEngine/Scene/Model.h"
#include "GraphicsEngine/Scene/Trail.h"


class ThirdPersonCharacterController : public InputListener
{
private:

    enum AnimationID
    {
        ANIM_IDLE_BASE,
        ANIM_IDLE_TOP,
        ANIM_RUN_BASE,
        ANIM_RUN_TOP,
        ANIM_HANDS_CLOSED,
        ANIM_HANDS_RELAXED,
        ANIM_DRAW_SWORDS,
        ANIM_SLICE_VERTICAL,
        ANIM_SLICE_HORIZONTAL,
        ANIM_DANCE,
        ANIM_JUMP_START,
        ANIM_JUMP_LOOP,
        ANIM_JUMP_END,
        NUM_ANIMS,
        ANIM_NONE = NUM_ANIMS
    };

    const int CHAR_HEIGHT = 5;            // height of character's center of mass above ground
    const int CAM_HEIGHT = 2;             // height of camera above character's center of mass
    const int RUN_SPEED = 17;             // character running speed in units per second
    const float TURN_SPEED = 500.0f;      // character turning in degrees per second
    const float ANIM_FADE_SPEED = 7.5f;   // animation crossfade speed in % of full weight per second
    const float JUMP_ACCEL = 30.0f;       // character jump acceleration in upward units per squared second
    const float GRAVITY = 90.0f;          // gravity in downward units per squared second

    // Render
    Model* body_;
    Model* leftSword_;
    Model* rightSword_;
    Trail* swordTrail_;
    Camera* camera_;
    MovableObject* cameraPivot_;
    MovableObject* cameraGoal_;
    float pivotPitch_;

    // Animations
    Ogre::AnimationState* animations_[NUM_ANIMS];    // master animation list
    AnimationID currentBaseAnimation_;               // current base (full- or lower-body) animation
    AnimationID currentTopAniamtion_;                // current top (upper-body) animation
    bool fadingInAnimations_[NUM_ANIMS];             // which animations are fading in
    bool fadingOutAnimations_[NUM_ANIMS];            // which animations are fading out
    float timer_;                                    // general timer to see how long animations have been playing
    bool swordsDrawn_;

    // Input
    Ogre::Vector3 keyDirection_;   // player's local intended direction based on WASD keys
    Ogre::Vector3 goalDirection_;  // actual intended direction in world-space
    float jumpSpeed_;              // for jumping

public:
	ThirdPersonCharacterController(Camera* cam);

    void update(float deltaTime);

    bool keyPressed(const KeyboardEvent& evt) override;
    bool keyReleased(const KeyboardEvent& evt) override;
    bool mouseMoved(const MouseMotionEvent& evt) override;
    bool mouseWheelRolled(const MouseWheelEvent& evt) override;
    bool mousePressed(const MouseButtonEvent& evt) override;

private:
    void setupBody();
    void setupCamera();
    void setupAnimations();

    void updateBody(float deltaTime);
    void updateCamera(float deltaTime);
    void updateAnimations(float deltaTime);
    void fadeAnimations(float deltaTime);

    void updateCameraGoal(float deltaYaw, float deltaPitch, float deltaZoom);

    void setBaseAnimation(AnimationID id, bool reset = false);
    void setTopAnimation(AnimationID id, bool reset = false);
};

#endif // !__CHARACTER_H__
