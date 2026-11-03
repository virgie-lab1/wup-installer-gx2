#ifndef THEME_H_
#define THEME_H_

#include <string>
#include <glm/glm.hpp>
#include "common/types.h"

enum ThemeMode {
    THEME_LIGHT = 0, // Classic Nintendo Wii (White with light blue accents)
    THEME_DARK = 1   // Custom Black Wii theme (Onyx/Charcoal with electric cyan accents)
};

class Theme {
public:
    static Theme & instance();

    ThemeMode getMode() const { return currentMode; }
    void setMode(ThemeMode mode);
    void toggleMode();

    bool isDark() const { return currentMode == THEME_DARK; }

    // Map base image names to themed image names
    std::string getImageFilename(const char * baseFilename) const;

    // Themed Colors
    glm::vec4 getTextColor() const;
    glm::vec4 getTextSecondaryColor() const;
    glm::vec4 getHeaderTextColor() const;
    glm::vec4 getHeaderGlowColor() const;
    glm::vec4 getParticleColor() const;
    glm::vec3 getClearColor() const;

    const char * getThemeName() const;
    const char * getThemeMusic() const;

    void loadConfig();
    void saveConfig();

private:
    Theme();
    ~Theme() {}

    ThemeMode currentMode;
};

#endif // THEME_H_

