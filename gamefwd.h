#include <SDL.h>

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
    static SDL_Surface* screenSurface;

  protected:
    Game() { }
    Game( const Game& );
    Game& operator = ( Game& );
   ~Game() { }
    friend class GameDestroyer;

  public:
    static void run();
    static Game& getInstance();
};
