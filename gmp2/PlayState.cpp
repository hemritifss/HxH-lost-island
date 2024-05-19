#include <sstream>
#include "PlayState.hpp"
#include "CONSTS.hpp"
#include "EndGameState.hpp"
#include <iostream>

namespace HxH {

    // Constructor to initialize the PlayState with engine data
    PlayState::PlayState(EngineDataRef data) : _refData(data) {}

    // Initialize the play state: load resources and set up initial game objects
    void PlayState::Init() {
		
        if (!_collisionSoundBuffer.loadFromFile(COLLISION_SOUND_PATH)) {
            std::cerr << "Error loading Collision Sound Effect" << std::endl;
        }
        if (!_flapSoundBuffer.loadFromFile(FLAP_SOUND_PATH)) {
            std::cerr << "Error loading Flap Sound Effect" << std::endl;
        }
        if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_PATH)) {
            std::cerr << "Error loading Point Sound Effect" << std::endl;
        }
		
        _collisionSound.setBuffer(_collisionSoundBuffer);
        _flapSound.setBuffer(_flapSoundBuffer);
        _pointSound.setBuffer(_pointSoundBuffer);

        _refData->resManager.LoadTexture("Game Background", GAME_BG_PATH);
        _refData->resManager.LoadTexture("Obstacle Up", OBSTACLE_UP_PATH);
        _refData->resManager.LoadTexture("Obstacle Down", OBSTACLE_DOWN_PATH);
        _refData->resManager.LoadTexture("Scoring Obstacle", SCORING_OBSTACLE_PATH);
        _refData->resManager.LoadTexture("Ground", GROUND_PATH);
        _refData->resManager.LoadTexture("Enemy", ENEMY_PATH);
        _refData->resManager.LoadTexture("Bullet", ENEMY_BULLET_PATH);
        _refData->resManager.LoadTexture("Player Frame 1", PLAYER_FRAME_1_PATH);
        _refData->resManager.LoadTexture("Player Frame 2", PLAYER_FRAME_2_PATH);
        _refData->resManager.LoadTexture("Player Frame 3", PLAYER_FRAME_3_PATH);
        _refData->resManager.LoadTexture("Player Frame 4", PLAYER_FRAME_4_PATH);
        _refData->resManager.LoadFont("Flappy Font", FLAPPY_FONT_PATH);

        obstacles = std::make_unique<Obstacles>(_refData);
        ground = std::make_unique<Ground>(_refData);
        player = std::make_unique<Player>(_refData);
        blink = std::make_unique<Blink>(_refData);
        scoreDisplay = std::make_unique<ScoreDisplay>(_refData);
        enemy = std::make_unique<Enemy>(_refData);

        _bgSprite.setTexture(_refData->resManager.GetTexture("Game Background"));

        _score = 0;
        scoreDisplay->UpdateScore(_score);

        _currentState = GameStates::eReady;
    }

    // Handle user input: close window or start the game
    void PlayState::ProcessInput() {
        sf::Event event;

        while (_refData->wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _refData->wnd.close();
            }

            if (_refData->evtManager.IsSpriteClicked(_bgSprite, sf::Mouse::Left, _refData->wnd) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (_currentState != GameStates::eGameOver) {
                    _currentState = GameStates::ePlaying;
                    player->Jump();
                    _flapSound.play();
                }
            }
        }
    }

    // Update the game state: animate player, move ground, obstacles, and enemies
    void PlayState::Update(float dt) {
        if (_currentState != GameStates::eGameOver) {
            player->Animate(dt);
            ground->MoveGround(dt);
        }

        if (_currentState == GameStates::ePlaying) {
            obstacles->MoveObstacles(dt);
            enemy->MoveEnemy(dt);
            enemy->Shoot();
            enemy->UpdateBullets(dt);
			if (clock.getElapsedTime().asSeconds()>ENEMY_SPAWN_FREQUENCY)
				enemy->SpawnEnemy();
            if (clock.getElapsedTime().asSeconds() > OBSTACLE_SPAWN_FREQUENCY) {
                obstacles->RandomizeObstacleOffset();
                obstacles->SpawnInvisibleObstacle();
                obstacles->SpawnBottomObstacle();
                obstacles->SpawnTopObstacle();
                obstacles->SpawnScoringObstacle();
                clock.restart();
            }

            player->Update(dt);

            // Check collisions with ground
            for (const auto& sprite : ground->GetSprites()) {
                if (collider.CheckSpriteCollision(player->GetSprite(), 0.7f, sprite, 1.0f)) {
                    _currentState = GameStates::eGameOver;
                    clock.restart();
                    _collisionSound.play();
                }
            }

            // Check collisions with obstacles
            for (const auto& sprite : obstacles->GetSprites()) {
                if (collider.CheckSpriteCollision(player->GetSprite(), 0.625f, sprite, 1.0f)) {
                    _currentState = GameStates::eGameOver;
                    clock.restart();
                    _collisionSound.play();
                }
            }

            // Check collisions with enemy bullets
            for (const auto& bullet : enemy->GetBullets()) {
                if (collider.CheckSpriteCollision(player->GetSprite(), 0.625f, bullet, 1.0f)) {
                    _currentState = GameStates::eGameOver;
                    clock.restart();
                    _collisionSound.play();
                }
            }

            // Scoring logic
            if (_currentState == GameStates::ePlaying) {
                // Check if player passes scoring obstacles
                auto& scoringSprites = obstacles->GetScoringSprites();
                for (auto it = scoringSprites.begin(); it != scoringSprites.end();) {
                    if (collider.CheckSpriteCollision(player->GetSprite(), 0.625f, *it, 1.0f)) {
                        _score++;
                        scoreDisplay->UpdateScore(_score);
                        _pointSound.play();
                        it = scoringSprites.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                // Check if player jumps over bullets
                for (const auto& bullet : enemy->GetBullets()) {
                    if (player->isJumping() && player->GetSprite().getGlobalBounds().intersects(bullet.getGlobalBounds()) &&
                        player->GetSprite().getPosition().y < bullet.getPosition().y) {
                        _score += 2;  // Award 2 points for jumping over a bullet
                        scoreDisplay->UpdateScore(_score);
                    }
                }

                // Check if enemies reach the left side
                auto& enemySprites = enemy->GetSprites();
                for (auto it = enemySprites.begin(); it != enemySprites.end();) {
                    if (it->getPosition().x < 0) {
                        _score += 1;  // Award 1 point for bypassing enemies
                        scoreDisplay->UpdateScore(_score);
                        it = enemySprites.erase(it);
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        if (_currentState == GameStates::eGameOver) {
            blink->Toggle(dt);

            if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
                _refData->stateCtrl.AddState(StageRef(new EndGameState(_refData, _score)), true);
            }
        }
    }

    // Render the game elements
    void PlayState::Render(float dt) {
        _refData->wnd.clear();
        _refData->wnd.draw(_bgSprite);
        obstacles->RenderObstacles();
        ground->RenderGround();
        player->Render();
        enemy->RenderEnemy();
        enemy->RenderBullets();
        blink->Render();
        scoreDisplay->Render();
        _refData->wnd.display();
    }
}
