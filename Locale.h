#include "constants.h"

#include <string>

class Locale {
private:
    std::string phrases[LOCALE_AMOUNT];
public:
    static const int TITLE_LOADING = 0;
    static const int TITLE_MENU_PLAY = 1;
    static const int TITLE_MENU_RECORDS = 2;
    static const int TITLE_MENU_SETTINGS = 3;
    static const int TITLE_MENU_EXIT = 4;

    static const int TITLE_PROCESS_GAME = 5;
    static const int TITLE_PROCESS_RECORDS = 6;

    static const int TITLE_SETTINGS_LANGUAGE = 7;
    static const int TITLE_SETTINGS_LANGUAGE_ENGLISH = 8;
    static const int TITLE_SETTINGS_LANGUAGE_RUSSIAN = 9;



    static const int LANGUAGE_ENG = 0;
    static const int LANGUAGE_RU = 1;

    bool loadLocale(int language);
    std::string getPhrase(int index);
};
