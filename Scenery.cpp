#include "Scenery.h"

#include "constants.h"
#include "Locale.h"
#include "Log.h"

#include <cstdio>

Tower* Scenery::towerStack = NULL;
SDL_Rect** Scenery::tRects = NULL;
ExtendedTexture* Scenery::textures = NULL;
ExtendedTexture* Scenery::titles = NULL;
Scenery* Scenery::instance = NULL;
int Scenery::STATE;

int Scenery::tAmount = 1;

TTF_Font *font = NULL;


Log log;
Locale current_locale;

int towersAmount = 1;
int titlesAmount = 0;

int menu_current = 0;

Scenery::~Scenery() {
    delete towerStack;
    delete textures;
    delete tRects;
    instance = NULL;
}

Scenery& Scenery::getInstance() {
    if (!instance) {
        instance = new Scenery();
        init();
    }
    return *instance;
}

bool Scenery::init() {
    bool success = true;

    tRects = new SDL_Rect*[tAmount];

    /*TODO: Normal t handling */
    tAmount = 1;

    log = Log::getInstance();

    memoryDeploy();

    current_locale.loadLocale(Locale::LANGUAGE_ENG);

    loadTextures();
    loadFonts();

    STATE = STATE_LOADING;

    return success;
}

bool Scenery::memoryDeploy() {
    bool success = true;

    //TRECTS
    for (int i = 0; i < tAmount; i++) {
        tRects[i] = new SDL_Rect[TOWER_TILES];
    }

    //TOWERS
    towerStack = new Tower[1];


    return success;
}

bool Scenery::loadTextures() {
    //TODO: normal reading -.- now there is too much repeatings
    bool success = true;

    textures = new ExtendedTexture[5];

    //TOWER
    int cCode = TCODE_TOWER;

    tRects[cCode] = new SDL_Rect[ TOWER_TILES ];

    if (!textures[ cCode ].loadFromFile(Game::getInstance().renderer, TOWER_PATH)) {
        log.i(FLAG_LOADING, "failed: TOWER textures");
        success = false;
    } else {
        for (int i = 0; i < TOWER_TILES; i++) {
            tRects[cCode][i].w = TOWER_TILE_W;
            tRects[cCode][i].h = TOWER_TILE_H;
            tRects[cCode][i].x = i * TOWER_TILE_W;
            tRects[cCode][i].y = 0;
        }
        log.i(FLAG_LOADING, "success: TOWER textures");
    }

    //SAND
    cCode = TCODE_SAND;
    tRects[cCode] = new SDL_Rect[ SAND_TILES ];
    if (!textures[ cCode ].loadFromFile(Game::getInstance().renderer, SAND_PATH)) {
        log.i(FLAG_LOADING, "failed: SAND textures");
        success = false;
    } else {
        for (int i = 0; i < SAND_TILES; i++) {
            tRects[cCode][i].w = SAND_TILE_W;
            tRects[cCode][i].h = SAND_TILE_H;
            tRects[cCode][i].x = i * SAND_TILE_W;
            tRects[cCode][i].y = 0;
        }
        log.i(FLAG_LOADING, "success: SAND textures");
    }

    return success;
}

bool Scenery::loadFonts() {
    log.i(FLAG_LOADING, "started to load fonts");
    titles = new ExtendedTexture[LOCALE_AMOUNT];

    //Loading success flag
    bool success = true;

    //Open the font
    font = TTF_OpenFont(FONT_MENU_PATH, 50);
    if( font == NULL )
    {
        log.i(FLAG_LOADING, TTF_GetError());
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 200, 0, 0};
        for (int i = 0; i < LOCALE_AMOUNT; i++) {
            if( !titles[i].loadFromRenderedText(font, current_locale.getPhrase(i), textColor ))
            {
                log.i(FLAG_LOADING, TTF_GetError());
                success = false;
            }
        }

    }

    return success;
}

void Scenery::renew(int state) {
    if (state == STATE_LOADING) {
        towerStack[0].deploy();
    }
}

void Scenery::update(int state) {
    switch (state) {
    case STATE_LOADING:
        towerStack[0].x = SCREEN_WIDTH / 2 - TOWER_TILE_W / 2;
        towerStack[0].y = SCREEN_HEIGHT / 2 + TOWER_TILE_H / 2;
        towerStack[0].update();

        SDL_Delay(200);

        if (towerStack[0].isDeployed()) {
            towersAmount = 0;
            STATE = STATE_MENU;
            log.i(FLAG_TRANSFERING, "transfer from LOADING to MENU");
        }
        break;

    case STATE_MENU:

        break;
    default:
        break;

    }
}

void Scenery::render() {
    int title_height = 0;
    int title_width = 0;
    int title_x = 0;
    int title_y = 0;
    int i = 0;

    switch (STATE) {

    case STATE_LOADING:
        for (int i = 0; i < towersAmount; i++) {
            towerStack[i].render();
        }
        break;

    case STATE_MENU:
        title_height = titles[Locale::TITLE_MENU_PLAY].getHeight();
        title_y = SCREEN_HEIGHT / 2 - 2 * title_height;

        title_width = titles[Locale::TITLE_MENU_PLAY    ].getWidth();

        title_x = SCREEN_WIDTH / 2 - title_width / 2;

        if (i++ == menu_current) title_x -= 10;
        titles[Locale::TITLE_MENU_PLAY].render(title_x, title_y);

        title_y += title_height;
        title_width = titles[Locale::TITLE_MENU_RECORDS].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;
        if (i++ == menu_current) title_x -= 10;

        titles[Locale::TITLE_MENU_RECORDS].render(title_x, title_y);


        title_y += title_height;
        title_width = titles[Locale::TITLE_MENU_SETTINGS].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;
        if (i++ == menu_current) title_x -= 10;

        titles[Locale::TITLE_MENU_SETTINGS].render(title_x, title_y);


        title_y += title_height;
        title_width = titles[Locale::TITLE_MENU_EXIT].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;
        if (i++ == menu_current) title_x -= 10;

        titles[Locale::TITLE_MENU_EXIT].render(title_x, title_y);
        break;

    case STATE_GAME:
        title_height = titles[Locale::TITLE_PROCESS_GAME].getHeight();
        title_y = SCREEN_HEIGHT / 2 - title_height / 2;

        title_width = titles[Locale::TITLE_PROCESS_GAME].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;

        titles[Locale::TITLE_PROCESS_GAME].render(title_x, title_y);
        break;

    case STATE_RECORDS:
        title_height = titles[Locale::TITLE_PROCESS_RECORDS].getHeight();
        title_y = SCREEN_HEIGHT / 2 - title_height / 2;

        title_width = titles[Locale::TITLE_PROCESS_RECORDS].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;

        titles[Locale::TITLE_PROCESS_RECORDS].render(title_x, title_y);
        break;
    case STATE_SETTINGS:
        title_height = titles[Locale::TITLE_SETTINGS_LANGUAGE].getHeight();
        title_y = SCREEN_HEIGHT / 2 - 3 * title_height / 2;

        title_width = titles[Locale::TITLE_SETTINGS_LANGUAGE].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;

        titles[Locale::TITLE_SETTINGS_LANGUAGE].render(title_x, title_y);

        title_y += title_height;
        title_width = titles[Locale::TITLE_SETTINGS_LANGUAGE_ENGLISH].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;
        if (i++ == menu_current) title_x -= 10;

        titles[Locale::TITLE_SETTINGS_LANGUAGE_ENGLISH].render(title_x, title_y);


        title_y += title_height;
        title_width = titles[Locale::TITLE_SETTINGS_LANGUAGE_RUSSIAN].getWidth();
        title_x = SCREEN_WIDTH / 2 - title_width / 2;
        if (i++ == menu_current) title_x -= 10;

        titles[Locale::TITLE_SETTINGS_LANGUAGE_RUSSIAN].render(title_x, title_y);
        break;
    default:
        break;
    }
}

int Scenery::getState() {
    return STATE;
}

void Scenery::menuChoose() {
    if (STATE == STATE_MENU) {
        switch (menu_current + 1) {

        case Locale::TITLE_MENU_PLAY:
            menu_current = 0;
            STATE = STATE_GAME;
            log.i(FLAG_TRANSFERING, "transfer from MENU to GAME");
        break;

        case Locale::TITLE_MENU_RECORDS:
            menu_current = 0;
            STATE = STATE_RECORDS;
            log.i(FLAG_TRANSFERING, "transfer from MENU to RECORDS");
            break;

        case Locale::TITLE_MENU_SETTINGS:
            menu_current = 0;
            STATE = STATE_SETTINGS;
            log.i(FLAG_TRANSFERING, "transfer from MENU to SETTINGS");
            break;

        case Locale::TITLE_MENU_EXIT:
            menu_current = 0;
            log.i(FLAG_TRANSFERING, "MENU QUIT");
            Game::getInstance().exit();
        }
    } else if (STATE == STATE_SETTINGS) {
        switch (menu_current + 8) {

        case Locale::TITLE_SETTINGS_LANGUAGE_ENGLISH:
            current_locale.loadLocale(Locale::LANGUAGE_ENG);
            break;

        case Locale::TITLE_SETTINGS_LANGUAGE_RUSSIAN:
            current_locale.loadLocale(Locale::LANGUAGE_RU);
            break;
        default: break;
        }
    }
}

void Scenery::menuDown() {
    if (STATE == STATE_MENU) {
        if (++menu_current == 4) menu_current = 0;
    } else if (STATE == STATE_SETTINGS) {
        if (++menu_current == 2) menu_current = 0;
    }
}

void Scenery::menuUp() {
    if (STATE == STATE_MENU) {
        if (--menu_current == -1) menu_current = 3;
    } else if (STATE == STATE_SETTINGS) {
        if (--menu_current == -1) menu_current = 1;
    }
}

void Scenery::goBack() {
    if (STATE > STATE_MENU && STATE < STATE_PAUSE) {
        STATE = STATE_MENU;
        menu_current = 0;
        log.i(FLAG_TRANSFERING, "transfer to MENU");
    }
}
