#include <SDL.h>

#ifndef GAME_H
#define GAME_H

class Game;

class GameDestroyer
{
  private:
    Game* instance;
  public:
    ~GameDestroyer();
    void initialize( Game* p );
};

class Game
{
  private:
    static Game* instance;
    static GameDestroyer destroyer;
    static SDL_Window* window;

    static bool init();
    static bool loadMedia();
    static void close();

  protected:
    Game() { }
    Game( const Game& );
    Game& operator = ( Game& );
   ~Game() { }
    friend class GameDestroyer;

  public:
    static SDL_Renderer* renderer;
    static void run();
    static Game& getInstance();
};

#endif // GAME_H

