#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifndef DEBUG
#define Debug(x) std::cout << "\033[34m[DEBUG] \033[0m" << x << std::endl;
#else
#define Debug(x)
#endif

#ifndef ERROR
#define Error(err, name) std::cout << "\033[31m[ERROR] \033[0m" << err << " " << name << std::endl;
#else
#define Error(err)
#endif

#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768


#define GAME_BACKGROUND_FILEPATH "../Resources/img/background.png"

#define PLAYER_SHEET_FILEPATH "../Resources/img/player2.png"
#define SCALE_X 2.f
#define SCALE_Y 2.f
#define TILE_WIDTH 50
#define TILE_HEIGHT 40

/* Define box sizes */


#define MARIO_TURN_FILEPATH "../Resources/img/Mario_Turn.png"

// Fonts
#define SCREEN_FONT_FILEPATH "../Resources/font/multivac-interference.ttf"
#define SCREEN_FONT_FILEPATH2 "../Resources/font/multivac-ghost.ttf"
#define BUTTON_FONT_FILEPATH "../Resources/font/Hacked.ttf"
#define LIST_FONT_FILEPATH "../Resources/font/Chapaza.ttf"
#define DEBUG_FONT_FILEPATH "../Resources/font/Alexandria.ttf"

#define TITLE_SIZE 80


enum ButtonState
{
    eBtnIdle = 0,
    eBtnHover,
    eBtnActive
};

// For Buttons
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 70
#define BUTTON_TEXT_SIZE 50

#define TEXT_IDLE_FILL_COLOR 70, 70, 70, 200
#define TEXT_HOVER_FILL_COLOR 250, 250, 250, 250
#define TEXT_ACTIVE_FILL_COLOR 20, 20, 20, 50

#define BUTTON_IDLE_FILL_COLOR 70, 70, 70, 0
#define BUTTON_HOVER_FILL_COLOR 150, 150, 150, 0
#define BUTTON_ACTIVE_FILL_COLOR 20, 20, 20, 0

// For Dropdown list
#define LIST_WIDTH 150
#define LIST_HEIGHT 30
#define LIST_TEXT_SIZE 15

#define LIST_TEXT_IDLE_FILL_COLOR 70, 70, 70, 150
#define LIST_TEXT_HOVER_FILL_COLOR 250, 250, 250, 255
#define LIST_TEXT_ACTIVE_FILL_COLOR 20, 20, 20, 50

#define LIST_IDLE_FILL_COLOR 200, 200, 200, 200
#define LIST_HOVER_FILL_COLOR 150, 150, 150, 150
#define LIST_ACTIVE_FILL_COLOR 20, 20, 20, 150



#define POWER_UP_TILE_FACTOR 2.f

#define GRAVITY 250.0f
#define JUMP_SPEED 250.0f

#define PLAYER_MOVEMENT_SPEED 110.0f
#define RUNNING_FACTOR 2.f

#define JUMP_DURATION 0.4f
#define WALK_ANIMATION_DURATION 12.f
#define SPLASH_STATE_SHOW_TIME 0.5f

// Key binds
#define GENERAL_KEY_BIND_FILEPATH "../Resources/KeyBindings/KeyBinds.ini"
#define GAMESTATE_KEY_BIND_FILEPATH "../Resources/KeyBindings/GameStateKeyBinds.ini"
#define MAIN_MENU_KEY_BIND_FILEPATH "../Resources/KeyBindings/MainMenuKeyBinds.ini"
#define SETTINGS_STATE_KEY_BIND_FILEPATH "../Resources/KeyBindings/SettingsStateKeyBinds.ini"
#define PAUSE_STATE_KEY_BIND_FILEPATH "../Resources/KeyBindings/PauseStateKeyBinds.ini"


enum MovementStates
{
    eIdle = 0,
    eMoving,
    eMovingLeft,
    eMovingRight,
    eMovingUp,
    eMovingDown,
};

enum AttackFace
{
    eNone,
    eAttackFaceLeft,
    eAttackFaceRight
};

enum PlayerStates
{
    eAlive,
    eDead
};

enum PlayerTypes
{
    eNormal,
    eGrownUp,
    ePowered
};

// Tile Map

#define GRID_SIZE 50.f
#define MAP_WIDTH 50
#define MAP_HEIGHT 50
#define LAYERS 1

#endif // DEFINITIONS_H