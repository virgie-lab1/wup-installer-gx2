#include "Theme.h"
#include <stdio.h>
#include <string.h>
#include "video/CVideo.h"

#define THEME_CONFIG_PATH "fs:/vol/external01/wiiu/apps/wup_installer_gx2/theme.cfg"
#define THEME_CONFIG_ALT_PATH "wiiu/apps/wup_installer_gx2/theme.cfg"

Theme & Theme::instance() {
    static Theme s_instance;
    return s_instance;
}

Theme::Theme()
    : currentMode(THEME_LIGHT)
{
    loadConfig();
}

void Theme::setMode(ThemeMode mode) {
    currentMode = mode;
    glm::vec3 clearCol = getClearColor();
    CVideo::setClearColor(clearCol.r, clearCol.g, clearCol.b);
    saveConfig();
}

void Theme::toggleMode() {
    setMode(currentMode == THEME_LIGHT ? THEME_DARK : THEME_LIGHT);
}

const char * Theme::getThemeName() const {
    return currentMode == THEME_LIGHT ? "Wii (Light)" : "Black (Dark)";
}

std::string Theme::getImageFilename(const char * baseFilename) const {
    if (!baseFilename)
        return "";

    if (currentMode == THEME_DARK) {
        if (strcmp(baseFilename, "titleHeader.png") == 0) return "titleHeader_dark.png";
        if (strcmp(baseFilename, "choiceUncheckedRectangle.png") == 0) return "choiceUncheckedRectangle_dark.png";
        if (strcmp(baseFilename, "choiceCheckedRectangle.png") == 0) return "choiceCheckedRectangle_dark.png";
        if (strcmp(baseFilename, "choiceSelectedRectangle.png") == 0) return "choiceSelectedRectangle_dark.png";
        if (strcmp(baseFilename, "select_button.png") == 0) return "select_button_dark.png";
        if (strcmp(baseFilename, "select_buttonSelected.png") == 0) return "select_buttonSelected_dark.png";
        if (strcmp(baseFilename, "messageBox.png") == 0) return "messageBox_dark.png";
        if (strcmp(baseFilename, "messageBoxButton.png") == 0) return "messageBoxButton_dark.png";
        if (strcmp(baseFilename, "messageBoxButtonSelected.png") == 0) return "messageBoxButtonSelected_dark.png";
        if (strcmp(baseFilename, "progressWindow.png") == 0) return "progressWindow_dark.png";
        if (strcmp(baseFilename, "progressBar.png") == 0) return "progressBar_dark.png";
    }

    return baseFilename;
}

glm::vec4 Theme::getTextColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec4(0.95f, 0.95f, 0.96f, 1.0f); // Crisp white
    } else {
        return glm::vec4(0.18f, 0.22f, 0.27f, 1.0f); // Wii dark slate
    }
}

glm::vec4 Theme::getTextSecondaryColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec4(0.0f, 0.90f, 1.0f, 1.0f);  // Electric cyan
    } else {
        return glm::vec4(0.0f, 0.58f, 0.88f, 1.0f);  // Wii light blue
    }
}

glm::vec4 Theme::getHeaderTextColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        return glm::vec4(0.15f, 0.18f, 0.22f, 1.0f);
    }
}

glm::vec4 Theme::getHeaderGlowColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec4(0.0f, 0.85f, 1.0f, 0.70f);
    } else {
        return glm::vec4(1.0f, 1.0f, 1.0f, 0.85f);
    }
}

glm::vec4 Theme::getParticleColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec4(0.0f, 0.95f, 1.0f, 0.65f); // Glowing cyan particles
    } else {
        return glm::vec4(0.0f, 0.62f, 0.92f, 0.40f); // Soft Wii blue bubbles
    }
}

glm::vec3 Theme::getClearColor() const {
    if (currentMode == THEME_DARK) {
        return glm::vec3(0.06f, 0.07f, 0.09f); // Sleek Black Wii
    } else {
        return glm::vec3(0.95f, 0.96f, 0.98f); // Classic White Wii
    }
}

void Theme::loadConfig() {
    FILE * fp = fopen(THEME_CONFIG_PATH, "r");
    if (!fp) {
        fp = fopen(THEME_CONFIG_ALT_PATH, "r");
    }
    if (fp) {
        char buf[32] = {0};
        if (fgets(buf, sizeof(buf), fp)) {
            if (strstr(buf, "dark") || strstr(buf, "1")) {
                currentMode = THEME_DARK;
            } else {
                currentMode = THEME_LIGHT;
            }
        }
        fclose(fp);
    }
}

void Theme::saveConfig() {
    FILE * fp = fopen(THEME_CONFIG_PATH, "w");
    if (!fp) {
        fp = fopen(THEME_CONFIG_ALT_PATH, "w");
    }
    if (fp) {
        fprintf(fp, "%s\n", currentMode == THEME_DARK ? "dark" : "light");
        fclose(fp);
    }
}

