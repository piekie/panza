#include <SDL.h>
#include <SDL_thread.h>

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

    static int renderFunction(void* data);
    static int inputFunction(void* data);

    static bool quit;

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

