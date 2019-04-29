/*
 * Parent class to manage states of game
 * We will have following states in our game:
 *  1. Splash state -   Where we display logo
 *  2. Menu state   -   Game menu
 *  3. Game state   -   State in which we play our game
 *  4. Pause state  -   When we pause game in between
 *  5. Game Over state  -   When game is over
 *  6. Settings state   - When we go to settings (either from menu or from pause screen)
 */

#ifndef STATE_H
#define STATE_H

namespace SSEngine
{
class State
{
public:
    /*
        * Initialize the game state
        */
    virtual void Init() = 0;

    /*
        * Handle input in current state
        */
    virtual void HandleInput( float dt ) = 0;

    /*
        * Update frames / game in current state
        */
    virtual void Update( float dt ) = 0;

    /*
        * Draw frame in current state
        */
    virtual void Draw() = 0;

    /*
        * Pause game
        */
    virtual void Pause() {};

    /*
        * Resume game
        */
    virtual void Resume() {};
};
}

#endif // STATE_H