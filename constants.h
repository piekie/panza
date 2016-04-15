#ifndef CONSTANTS
#define CONSTANTS

#define TOWER_PATH          "textures/tower.bmp"
#define SAND_PATH           "textures/sand.bmp"
#define FONT_MENU_PATH      "fonts/menu.fon"

#define FLAG_LOADING        "loading resources"
#define FLAG_RENDERING      "rendering"
#define FLAG_TRANSFERING    "transfering"

const int TCODE_SAND = 0;
const int TCODE_TOWER = 1;


const int TOWER_TILES = 20;
const int TOWER_TILE_W = 40;
const int TOWER_TILE_H = 70;

const int TOWER_CLOSED = 0;
const int TOWER_CLOSING = 1;
const int TOWER_DEPLOYING = 2;
const int TOWER_DEPLOYED = 3;


const int SAND_TILES = 13;
const int SAND_TILE_W = 20;
const int SAND_TILE_H = 20;




const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int STATE_LOADING = 0;
const int STATE_MENU = 1;
const int STATE_GAME = 2;
const int STATE_RECORDS = 3;
const int STATE_SETTINGS = 4;
const int STATE_PAUSE = 5;
const int STATE_RESULT = 6;

const int LOCALE_AMOUNT = 10;


#endif // CONSTANTS
