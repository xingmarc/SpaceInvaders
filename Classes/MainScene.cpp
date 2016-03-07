#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <iostream>

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace std;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    titleLabel = rootNode->getChildByName<cocos2d::ui::Text*>("titleLabel");
    scorePanel = rootNode->getChildByName("ScorePanel");
    scoreLabel = scorePanel->getChildByName<cocos2d::ui::Text*>("ScorePointLabel");
    gameStateLabel = rootNode->getChildByName<cocos2d::ui::Text*>("gameStateLabel");

    addChild(rootNode);

    this->titleAnimation();

    return true;
}

void MainScene:: onEnter(){
    Layer:: onEnter();
    
    this->setupTouchHandling();
    this->setupAcceleration();
}

#pragma mark setup Listeners

void MainScene:: setupAcceleration(){
    
    //Set Accelerometer on:
    Device::setAccelerometerEnabled(true);
    
    //setup the eventListener object
    auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(MainScene::didAccelerate, this));
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(accListener, this);
}

void MainScene:: setupTouchHandling(){
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        if (gameStop) {
            
            this->setupAll();
            return true;
            
        }else{
            Sprite* missile = Sprite::create("assets/Player/player_missle.png");
        
            missile->setPosition(this->getSpaceShipPosition());
            playerMissileVector.push_back(missile);
        
            this->addChild(missile);
        
            return true;
        }
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::didAccelerate(Acceleration* acc, Event* event){
    
    if (gameStop) {
        return;
    }
    
    auto spaceShipSprite = this->getChildByName("spaceShipppp");
    
    auto pos = spaceShipSprite->getPosition();
    
    pos.x += 10 * (acc->x);
    
    if (pos.x < 0){
        pos.x = 0;
    }
    if (pos.x > 960){
        pos.x = 960;
    }
    this->setSpaceShipPosition(pos);
    
    spaceShipSprite->setPosition(pos);
}


#pragma mark update related functions:

void MainScene::update(float dt){
    Layer::update(dt);

    if (gameStop) {
        return;
    }
    this->time += dt;
    
    this->handleMissilesBehavior(dt);
    
    this->changeInvadersGroupPosition();
    this->changeInvadersTexture();
    
    this->invadersShoot();
    
    // a bunch of collision checks:
    this->checkMissileInvaderCollision();
    this->checkMissileShieldCollision();
    
    this->checkWinOrLose();
}

void MainScene:: handleMissilesBehavior(float dt){
    
    // handle player's missile:
    for (int i = 0; i < playerMissileVector.size(); i++) {
        auto missile = playerMissileVector.at(i);
        auto pos = missile->getPosition();
        
        if (pos.y > 640){
            this->removeChild(missile);
            playerMissileVector.erase(playerMissileVector.begin() + i);
            
            //cout << "remove out of bound missiles successfully!"<< endl;
        }else{
            pos.y += 500 * dt;
            missile->setPosition(pos);
        }
    }
    
    for (int i = 0; i < enemyMissileOrRayVector.size(); i++){
        auto missileOrRay = enemyMissileOrRayVector.at(i);
        auto pos = missileOrRay->getPosition();
        
        if (pos.y < 0){
            this->removeChild(missileOrRay);
            enemyMissileOrRayVector.erase(enemyMissileOrRayVector.begin() + i);
            
        }else{
            pos.y -= 300 * dt;
            missileOrRay->setPosition(pos);
        }
    }
}

void MainScene:: checkMissileInvaderCollision(){
    for (int m = 0; m < playerMissileVector.size(); m++) {
        
        auto missile = playerMissileVector.at(m);
        
        for (int i = 0; i < invadersVector.size(); i++) {
            for (int j = 0; j < invadersVector.at(i).size(); j ++) {
                
                auto invader = invadersVector.at(i).at(j);
                if (invader == nullptr) {
                    continue;
                }
                
                if (invader->boundingBox().intersectsRect(missile->boundingBox())){
                    invadersVector.at(i).at(j) = nullptr;
                    
                    playerMissileVector.erase(playerMissileVector.begin() + m);
                    
                    this->removeChild(invader);
                    this->removeChild(missile);
                    
                    calculateScore();
                    
                    return;
                }
            }
        }
    }
}

void MainScene:: checkMissileShieldCollision(){
    
    for (int m = 0; m < playerMissileVector.size(); m++) {
        
        auto missile = playerMissileVector.at(m);
        
        for (int s = 0; s < shieldsVector.size(); s++){
            auto shield = shieldsVector.at(s);
            if (shield != nullptr) {
                
                if (missile->boundingBox().intersectsRect(shield->boundingBox())){
                    this->removeChild(missile);
                    playerMissileVector.erase(playerMissileVector.begin() + m);
                    return;
                }
            }
        }
    }
    
    for (int m = 0; m < enemyMissileOrRayVector.size(); m++) {
        
        auto enemyMissile = enemyMissileOrRayVector.at(m);
        
        for (int s = 0; s < shieldsVector.size(); s++){
            auto shield = shieldsVector.at(s);
            if (shield != nullptr){
                if (enemyMissile->boundingBox().intersectsRect(shield->boundingBox())){
                    this->removeChild(enemyMissile);
                    enemyMissileOrRayVector.erase(enemyMissileOrRayVector.begin() + m);
                    
                    this->removeChild(shield);
                    shieldsVector.at(s) = nullptr;
                    
                    return;
                }
            }
        }
    }
}

void MainScene:: calculateScore(){
    // make the string to int and int to string;
    int score = atoi(scoreLabel->getString().c_str());
    score += 10;
    char newScore[4];
    int i = 3;
    while (i >= 0) {
        int l = score % 10;
        newScore[i] = l + '0';
        score /= 10;
        i--;
    }
    scoreLabel->setString(newScore);
}

void MainScene:: invadersShoot(){
    // make sure the invader shoot at a very low frequency:
    int diceNumber = arc4random() % 200;
    if (diceNumber > 1) {
        return;
    }
    std:: vector<cocos2d:: Vec2> invaderShootStartingPoint(11);
    
    int row = int(invadersVector.size());
    int col = int(invadersVector.at(0).size());
    for (int j = 0; j < col; j++){
        for (int i = row - 1; i >= 0; i--) {
            auto invader = invadersVector.at(i).at(j);
            if (invader != nullptr){
                
                invaderShootStartingPoint.at(j) = invader->getPosition();
                
                break;
            }
        }
    }
    
    int randForMissileOrRay = arc4random() % 2;
    
    Sprite * missileOrRay;
    if (randForMissileOrRay == 1) {
        missileOrRay = Sprite::create("assets/Enemies/enemy_missle.png");
    }else{
        missileOrRay = Sprite::create("assets/Enemies/enemy_ray.png");
    }
    
    int randIndex = arc4random() % 11;
    missileOrRay->setPosition(invaderShootStartingPoint.at(randIndex));
    
    this->addChild(missileOrRay);
    this->enemyMissileOrRayVector.push_back(missileOrRay);
    
}

void MainScene:: checkWinOrLose(){
    
    //auto sceneSprite = this->getChildByName("Scene");
    auto spaceShipSprite = this->getChildByName("spaceShipppp");
    
    for (int m = 0; m < enemyMissileOrRayVector.size(); m++) {
        auto enemyMissile = enemyMissileOrRayVector.at(m);
        if (spaceShipSprite->boundingBox().intersectsRect(enemyMissile->boundingBox())){
        
            gameStop = true;
            
            gameStateLabel->setString("GAME OVER\nTAP TO RESTART");
            gameStateLabel->setVisible(true);
            scorePanel->setVisible(false);
            
            this->removeAll();
            this->resetScore();
            
            return;
        }
    }
    
    int countEnemyLeft = 0;
    for (int i = 0; i < invadersVector.size(); i++){
        auto invaderRow = invadersVector.at(i);
        for (int j = 0; j < invaderRow.size(); j++){
            auto invader = invaderRow.at(j);
            if (invader != nullptr){
                countEnemyLeft += 1;
            }
        }
    }
    
    if (countEnemyLeft == 0){
        gameStop = true;
        
        string yourScore = scoreLabel->getString();
        gameStateLabel->setString("YOU WIN\nSCORE " + yourScore + "\nTAP TO RESTART");
        gameStateLabel->setVisible(true);
        scorePanel->setVisible(false);
        
        this->removeAll();
        this->resetScore();
        
        return;
    }
    
    return;
}


#pragma mark setups
void MainScene:: setupAll(){

    titleLabel->setVisible(false);
    
    gameStateLabel->setVisible(false);
    scorePanel->setVisible(true);
    
    this->setupScoreLabels();
    
    this->setupSpaceShip();
    this->setupInvaders();
    this->setupShields();
    
    this->scheduleUpdate();
    
    this->gameStop = false;
}

void MainScene:: setupScoreLabels(){
    scorePanel->cocos2d::Node::setVisible(true);
}

void MainScene:: setupSpaceShip(){
    Sprite* spaceShip = Sprite:: create("assets/Player/spaceship.png");
    spaceShip->setPosition(480.0, 40);
    
    this->addChild(spaceShip, 0, "spaceShipppp");
    
}

void MainScene:: setupShields(){
    Vec2 center = Vec2(480.0, 100.0);
    
    for (int i = 0; i < 4; i++) {
        Sprite* shield = Sprite:: create("assets/Player/player_shield.png");
        
        shield->setPosition(center.x + (i - 1.50) * 200, center.y);
        
        this->addChild(shield);
        shieldsVector.push_back(shield);
    }
}

void MainScene:: setupInvadersRow(const std::string& filename,
                                  const int quantity,
                                  const int rowNum)
{
    std::vector<cocos2d::Sprite* > invaderRow;
    for (int i = 0 ; i < quantity; i ++){
        Sprite* invader = Sprite:: create(filename);

        auto pos = getInvadersGroupPosition();
        pos.x += (i - quantity / 2) * 60;
        pos.y -= rowNum * 60;
        
        invader->setPosition(pos);
        invaderRow.push_back(invader);
        
        this->addChild(invader);
    }
    this->invadersVector.push_back(invaderRow);
}

void MainScene:: setupInvaders(){
    
    Point originalInvadersGroupPosition = Vec2(480.0, 550.0);
    this->setInvadersGroupPosition(originalInvadersGroupPosition);
    this->invadersGroupMovingRight = true;
    
    setupInvadersRow("assets/Enemies/invaderCframe1.png", 11, 0);
    setupInvadersRow("assets/Enemies/invaderBframe1.png", 11, 1);
    
    setupInvadersRow("assets/Enemies/invaderAframe1.png", 11, 2);
    setupInvadersRow("assets/Enemies/invaderAframe1.png", 11, 3);
}

void MainScene:: changeInvadersGroupPosition(){
    auto currentPos = getInvadersGroupPosition();
    
    if (currentPos.x > 660) {
        invadersGroupMovingRight = false;
        currentPos.y -= 10;
    }
    else if (currentPos.x < 300){
        invadersGroupMovingRight = true;
        currentPos.y -= 10;
    }
    if (invadersGroupMovingRight) {
        currentPos.x += 1;
    }else{
        currentPos.x -= 1;
    }

    this->setInvadersGroupPosition(currentPos);
    
    this->changeInvadersPositionAccordingly();
}

void MainScene:: changeInvadersPositionAccordingly(){

    auto invadersGroupPos = this->getInvadersGroupPosition();
    
    for (int i = 0; i < invadersVector.size(); i++) {
        for (int j = 0; j < invadersVector.at(i).size(); j ++) {
            if (invadersVector.at(i).at(j) != nullptr){
                auto pos = invadersVector.at(i).at(j)->getPosition();
            
            
                int rowNum = int(invadersVector.at(i).size());
            
            
                pos.x = invadersGroupPos.x + ((j -  rowNum / 2) * 60.0);
            
                pos.y = invadersGroupPos.y - i * 60;
        
                invadersVector.at(i).at(j)->setPosition(pos);
                
            }
        }
    }
}

void MainScene:: changeInvadersTexture(){
    bool frame1 = true;
    if (time > 1) {
        frame1 = false;
    }
    if (time > 2){
        time = 0;
    }
    for (int i = 0; i < invadersVector.size(); i++) {
        for (int j = 0; j < invadersVector.at(0).size(); j++) {
            auto invader = invadersVector.at(i).at(j);
            if (invader != nullptr) {
                
                if (i == 0) {
                    if (frame1)
                        invader->setTexture("assets/Enemies/invaderCframe1.png");
                    else
                        invader->setTexture("assets/Enemies/invaderCframe2.png");
                }
                else if (i == 1) {
                    if (frame1)
                        invader->setTexture("assets/Enemies/invaderBframe1.png");
                    else
                        invader->setTexture("assets/Enemies/invaderBframe2.png");
                }
                else {
                    if (frame1)
                        invader->setTexture("assets/Enemies/invaderAframe1.png");
                    else
                        invader->setTexture("assets/Enemies/invaderAframe2.png");

                }
            }
        }
    }
}

void MainScene:: resetScore(){
    scoreLabel->setString("0000");
}

#pragma mark remove:

void MainScene:: removeAll(){
    
    // remove spaceship
    this->removeChildByName("spaceShipppp");
    
    // remove invaders:
    for (int i = 0; i < invadersVector.size(); i++) {
        for (int j = 0; j < invadersVector.at(i).size(); j ++) {
            
            
            auto invader = invadersVector.at(i).at(j);
            
            this->removeChild(invader);
            
        }
    }
    invadersVector.clear();
    
    // remove shields:
    for (int s = 0; s < shieldsVector.size(); s++) {
        auto shield = shieldsVector.at(s);
        this->removeChild(shield);
    }
    shieldsVector.clear();
    
    // remove player missile:
    for (int i = 0; i < playerMissileVector.size(); i++){
        auto missile = playerMissileVector.at(i);
        this->removeChild(missile);
    }
    playerMissileVector.clear();
    
    // remove invader missile:
    for (int i = 0; i < enemyMissileOrRayVector.size(); i++) {
        auto enemyMissile = enemyMissileOrRayVector.at(i);
        this->removeChild(enemyMissile);
    }
    enemyMissileOrRayVector.clear();
}

#pragma mark animations:
void MainScene:: titleAnimation(){

    cocostudio::timeline::ActionTimeline* titleTimeline = CSLoader::createTimeline("MainScene.csb");
    
    this->stopAllActions();
    this->runAction(titleTimeline);
    
    titleTimeline->play("titleAnimation", false);
}
