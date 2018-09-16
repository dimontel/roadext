#include "GameBoard.h"

#include "GameEngine\GameEngineMain.h"
#include "GameEngine\EntitySystem\Components\CollidableComponent.h"
#include "GameEngine\EntitySystem\Components\CollidablePhysicsComponent.h"
#include "GameEngine\EntitySystem\Components\SpriteRenderComponent.h"
#include "GameEngine\Util\CameraManager.h"
#include "Game\GameEntities\PlayerEntity.h"
#include "Game\GameEntities\ObstacleEntity.h"
#include <SFML/Window.hpp>

#include <iostream>
#include <SFML/Graphics/Color.hpp> 
#include <time.h> 

using namespace Game;

GameBoard::GameBoard()
	: m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
	, m_player(nullptr)
	, m_backGround(nullptr)
{
	m_player = new PlayerEntity();
	
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(50.f, 50.f));	
	m_player->SetSize(sf::Vector2f(40.f, 40.f));
	
	CreateBackGround();
	//Debug
	for (int a = 0; a < 3; ++a)
	{
		//SpawnNewRandomObstacles();
	}

	srand(time(NULL));
}


GameBoard::~GameBoard()
{

}

int drawNumber = 0;
int obstacleNumber = 0;
void GameBoard::Update()
{
	GameEngine::Entity* smile = new GameEngine::Entity();
	smile->SetPos(sf::Vector2f(1120.f, 440.f));
	smile->SetSize(sf::Vector2f(200.f, 200.0f));
	GameEngine::SpriteRenderComponent* renderSmileComponent = static_cast<GameEngine::SpriteRenderComponent*>(smile->AddComponent<GameEngine::SpriteRenderComponent>());
	renderSmileComponent->SetTexture(GameEngine::eTexture::Smile);
	renderSmileComponent->SetZLevel(1);

	GameEngine::GameEngineMain::GetInstance()->AddEntity(smile);


	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2i positionVector = sf::Mouse::getPosition(  *(GameEngine::GameEngineMain::GetInstance()->m_renderWindow) );
	sf::Vector2f positionVectorFloat = static_cast<sf::Vector2f>(positionVector);
	GameEngine::Entity* ent = new GameEngine::Entity();
	//std::cout << "GameBoard::Update" << std::endl;

	if (pressed && (positionVectorFloat.x >= 1020) && (positionVectorFloat.x <= 1220) && (positionVectorFloat.y >= 330) && (positionVectorFloat.y <= 540)) {
		positionVector = sf::Mouse::getPosition(*(GameEngine::GameEngineMain::GetInstance()->m_renderWindow));
		sf::Vector2f positionVectorFloat = static_cast<sf::Vector2f>(positionVector);
		ent->SetPos(positionVectorFloat);
		ent->SetSize(sf::Vector2f(29.0f, 29.0f));
		//std::cout << "Mouse Down, Position: (" << positionVectorFloat.x << ", " << positionVectorFloat.y << ")" << std::endl;
		GameEngine::SpriteRenderComponent* renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(ent->AddComponent<GameEngine::SpriteRenderComponent>());
		renderComponent->SetTexture(GameEngine::eTexture::Finger);
		renderComponent->SetZLevel(2);

		GameEngine::GameEngineMain::GetInstance()->AddEntity(ent); 
		drawNumber++;
		std::cout << drawNumber;

	}
	

	



	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (obstacleNumber <= 2)
		{
			//SpawnNewRandomObstacles();
	SpawnNewRandomTiledObstacles();
	obstacleNumber++;
		}

		UpdateObstacles(dt);
		UpdateBackGround();
		UpdatePlayerDying();
	}		
}

void disappear() {

}


void GameBoard::UpdateObstacles(float dt)
{
	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2i positionVector = sf::Mouse::getPosition(*(GameEngine::GameEngineMain::GetInstance()->m_renderWindow));
	sf::Vector2f positionVectorFloat = static_cast<sf::Vector2f>(positionVector);

	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
	{
		GameEngine::Entity* obstacle = (*it);
		sf::Vector2f currPos = obstacle->GetPos();

		if (pressed && (positionVectorFloat.x <= (currPos.x + 14)) && (positionVectorFloat.x >= (currPos.x - 14))&& (positionVectorFloat.y <= (currPos.y + 14)) && (positionVectorFloat.y >= (currPos.y - 14))) {
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			//it = m_obstacles.erase(it);
			}
		
		it++;

	}
	
	//static float obstacleSpeed = 100.f;
	//int vibrate = -1;
	//
	//for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
	//{
	//	GameEngine::Entity* obstacle = (*it);
	//	sf::Vector2f currPos = obstacle->GetPos();
	//	
	//		if (vibrate < 100) {
	//			currPos.x -= 1;
	//			currPos.y -= 1;
	//			obstacle->SetPos(currPos);
	//			vibrate++;
	//			std::cout << "in 1";

	//		}
	//		else if (vibrate = 100 ) {
	//			/*currPos.x += 1;
	//			currPos.y += 1;
	//			obstacle->SetPos(currPos);*/
	//			vibrate=200;
	//			std::cout << "in -1";
	//			}
	//		else if (vibrate > 100) {
	//			vi
	//		}
			
		
		//If we are to remove ourselves
		//int x = RandomFloatRange(1.0, 10.0);
		/*if (currPos.x < -50.f)
		{
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			it = m_obstacles.erase(it);
		}
		else
		{*/
		
		
	
}


void GameBoard::UpdatePlayerDying()
{	
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;

	static float xToPlayerDie = 0.f;
	if (m_player->GetPos().x < xToPlayerDie)
	{
		m_isGameOver = true;
	}
}


void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;
	
	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewRandomTiledObstacles()
{
	static int minObstacleCount = 2;
	static int maxObstacleCount = 4;

	static float minNextSpawnTime = 1.f;
	static float maxNextSpawnTime = 1.f;

	static float minObstacleXPos = 1130.f;
	static float maxObstacleXPos = 1200.f;
	static float minObstacleYPos = 100.f;
	static float maxObstacleYPos = 350.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));	
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = 1;//(int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	
		SpawnNewObstacle(pos, size);
		//pos.y += size.y;
	

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}

//void GameBoard::SpawnNewObstacleBlocker(const sf::Vector2f& pos, const sf::Vector2f& size)
//{
//	GameEngine::Entity* obstacleBlocker = new GameEngine::Entity();
//	GameEngine::CollidableComponent* blocker = static_cast<GameEngine::CollidableComponent*>(obstacleBlocker->AddComponent<GameEngine::CollidableComponent>());
//	obstacleBlocker->AddComponent<>
//	obstacleBlocker->SetPos(pos);
//	obstacleBlocker->SetSize(sf::Vector2f(size.x, size.y));
//
//	m_obstacles.push_back(obstacle);
//}

void GameBoard::CreateBackGround()
{
	/*GameEngine::Entity* drawEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* drawRender = static_cast<GameEngine::SpriteRenderComponent*>(drawEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	drawRender->SetTexture(GameEngine::eTexture::Phone);
	drawRender->SetZLevel(0);
	drawEntity->SetPos(sf::Vector2f((625.f), (600.f)));
	drawEntity->SetSize(sf::Vector2f(500.f, 500.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(drawEntity);

	m_backGround = drawEntity;*/


	GameEngine::Entity* phone_long = new GameEngine::Entity();
	phone_long->SetPos(sf::Vector2f(1125.f, 360.f));
	phone_long->SetSize(sf::Vector2f(302.f, 660.f));
	GameEngine::SpriteRenderComponent* renderComponentPhoneLong = static_cast<GameEngine::SpriteRenderComponent*>(phone_long->AddComponent<GameEngine::SpriteRenderComponent>());
	renderComponentPhoneLong->SetTexture(GameEngine::eTexture::PhoneLong);
	renderComponentPhoneLong->SetZLevel(0);

	GameEngine::GameEngineMain::GetInstance()->AddEntity(phone_long);
	m_backGround = phone_long; 
}


void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}