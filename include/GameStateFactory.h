#ifndef GAMESTATEFACTORY
#define GAMESTATEFACTORY

#include "GameState.h"

class GameStateFactory final {
public:
    GameStateFactory();

    GameState* createState(States state); // returns a data handle, does not manage
private:
    GameState* createTitleScreenState();
};

#endif