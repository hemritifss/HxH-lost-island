#pragma once

// Window dimensions
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 1024

// Timing
#define INTRO_STATE_SHOW_TIME 3.0

// Paths to resources
#define ENEMY_PATH "resources/res/enemy.png"
#define ENEMY_BULLET_PATH "resources/res/bullet.png"
#define INTRO_SCENE_BG_PATH "resources/res/Splash-Background.png"
#define MAIN_MENU_BG_PATH "resources/res/sky.png"
#define GAME_BG_PATH "resources/res/sky.png"
#define GAME_OVER_BG_PATH "resources/res/sky.png"
#define GAME_TITLE_PATH "resources/res/title.png"
#define START_BTN_PATH "resources/res/PlayButton.png"
#define OBSTACLE_UP_PATH "resources/res/PipeUp.png"
#define OBSTACLE_DOWN_PATH "resources/res/PipeDown.png"
#define SCORING_OBSTACLE_PATH "resources/res/InvisibleScoringPipe.png"
#define GROUND_PATH "resources/res/land.png"
#define PLAYER_FRAME_1_PATH "resources/res/player-01.png"
#define PLAYER_FRAME_2_PATH "resources/res/player-02.png"
#define PLAYER_FRAME_3_PATH "resources/res/player-03.png"
#define PLAYER_FRAME_4_PATH "resources/res/player-04.png"
#define FLAPPY_FONT_PATH "resources/fonts/FlappyFont.ttf"
#define GAME_OVER_TITLE_PATH "resources/res/Game-Over-Title.png"
#define GAME_OVER_BODY_PATH "resources/res/Game-Over-Body.png"
#define BRONZE_MEDAL_PATH "resources/res/Bronze-Medal.png"
#define SILVER_MEDAL_PATH "resources/res/Silver-Medal.png"
#define GOLD_MEDAL_PATH "resources/res/Gold-Medal.png"
#define PLATINUM_MEDAL_PATH "resources/res/Platinum-Medal.png"
#define STARTING_SOUND_PATH "resources/audio/HxH.wav"
#define COLLISION_SOUND_PATH "resources/audio/Hit.wav"
#define POINT_SOUND_PATH "resources/audio/Point.wav"
#define FLAP_SOUND_PATH "resources/audio/Wing.wav"

// Gameplay constants
#define ENEMY_SPAWN_FREQUENCY 4.0f
#define BULLET_SPEED 300.0f
#define SHOOT_INTERVAL 2.0f
#define OBSTACLE_SPEED 200.0f
#define OBSTACLE_SPAWN_FREQUENCY 3.0f
#define PLAYER_ANIMATION_DURATION 0.4f

// Player states
#define PLAYER_STATE_STILL 1
#define PLAYER_STATE_FALLING 2
#define PLAYER_STATE_FLYING 3

// Physics
#define GRAVITY 350.0f
#define FLYING_SPEED 350.0f
#define FLYING_DURATION 0.25f
#define ROTATION_SPEED 100.0f

// Game states
enum GameStates {
    eReady,
    ePlaying,
    eGameOver
};

// Blink effect
#define BLINK_SPEED 1500.0f
#define TIME_BEFORE_GAME_OVER_APPEARS 1.5f

// Medals
#define BRONZE_MEDAL_SCORE 0
#define SILVER_MEDAL_SCORE 5
#define GOLD_MEDAL_SCORE 25
#define PLATINUM_MEDAL_SCORE 100
