#include "Locale.h"

#include "Log.h"
#include "Scenery.h"

#include <fstream>

bool Locale::loadLocale(int language) {
    bool success = true;
    std::ifstream file_locale;

    switch (language) {
    case Locale::LANGUAGE_ENG:
        file_locale.open("locales/locale_ENG.dat", std::ios::in);
        break;
    case Locale::LANGUAGE_RU:
        file_locale.open("locales/locale_RU.dat", std::ios::in);
        break;
    default:
        Log::getInstance().i(FLAG_LOADING, "locale: i don't know this locale");
        success = false;
        return success;
    }

    if (!file_locale.is_open()) {
        Log::getInstance().i(FLAG_LOADING, "locale: can't open locale file");

        success = false;
        return success;
    } else {
        Log::getInstance().i(FLAG_LOADING, "locale: opened locale file");
    }

    int i = 0;
    while (!file_locale.eof() && i != LOCALE_AMOUNT) {
        file_locale >> phrases[i++];
    }

    if (i == LOCALE_AMOUNT && !file_locale.eof()) {
        Log::getInstance().i(FLAG_LOADING, "locale: bad locale file");

        success = false;
        return success;
    } else Log::getInstance().i(FLAG_LOADING, "locale: loaded");

    Scenery::getInstance().loadFonts();

    return success;
}

std::string Locale::getPhrase(int index) {
    return phrases[index];
}
