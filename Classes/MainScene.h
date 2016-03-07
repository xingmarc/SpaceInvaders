#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void update(float dt) override;
    
    
    void handleMissilesBehavior(float dt);
    void checkMissileInvaderCollision();
    void checkMissileShieldCollision();
    void calculateScore();
    void checkWinOrLose();
    
    void didAccelerate(cocos2d::Acceleration* acc, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    
    void setupTouchHandling();
    void setupAcceleration();
    
    void setupAll();
    void setupScoreLabels();
    void setupSpaceShip();
    void setupShields();
    void setupInvaders();
    void setupInvadersRow(const std::string& filename, const int quantity, const int rowNum);
    
    void changeInvadersGroupPosition();
    void changeInvadersPositionAccordingly();
    void changeInvadersTexture();
    void invadersShoot();
    
    void removeAll();
    void resetScore();
    

    void titleAnimation();
    
    void setSpaceShipPosition(cocos2d::Point newPosition){
        spaceShipPosition = newPosition;
    }
    cocos2d::Point getSpaceShipPosition(){
        return spaceShipPosition;
    }
    
    void setInvadersGroupPosition(cocos2d::Point newPosition){
        invadersGroupPosition = newPosition;
    }
    cocos2d:: Point getInvadersGroupPosition(){
        return invadersGroupPosition;
    }

private:
    
    // there may be multiple missiles in the scene.
    std::vector<cocos2d:: Sprite*> playerMissileVector;
    std::vector<cocos2d:: Sprite*> enemyMissileOrRayVector;
    
    // invader's 2d array
    std::vector<std::vector<cocos2d:: Sprite*>> invadersVector;
    
    std::vector<cocos2d:: Sprite*> shieldsVector;
    
    cocos2d::Point spaceShipPosition;
    
    cocos2d::Point invadersGroupPosition;
    bool invadersGroupMovingRight;
    
    cocos2d::Node* scorePanel;
    cocos2d::ui::Text* scoreLabel;
    cocos2d::ui::Text* gameStateLabel;
    cocos2d::ui::Text* titleLabel;
    
    bool gameStop = true;
    
    float time = 0.0;
};

#endif // __MainScene_SCENE_H__
