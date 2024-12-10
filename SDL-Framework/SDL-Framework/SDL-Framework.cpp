#include "GameManager.h"

using SDLFramework::GameManager;


int main(int argc, char* args[])
{   
    GameManager* Game = GameManager::Instance();

    Game->Run();
    
    GameManager::Release();
    Game = nullptr;
       
    return 0;
}
