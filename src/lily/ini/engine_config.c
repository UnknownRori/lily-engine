#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"
#include "lily/memory.h"
#include "lily/types.h"
#include "raylib.h"

typedef struct {
    char** title;
    u32*    width;
    u32*    height;
    u8*     fps;
    bool*   vsync;
} ini_config;

static int handler(
    void* data, 
    const char* section, 
    const char* name, 
    const char* value
)
{

    ini_config* config = data;
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("Display", "Title")) {
        char* data = RORI_MALLOC(TextLength(value));
        TextCopy(data, value);
        *config->title = data;
    } else if (MATCH("Display", "Width")) {
        *config->width = (u32)atoi(value);
    } else if (MATCH("Display", "Height")) {
        *config->height = (u32)atoi(value);
    } else if (MATCH("Display", "VSYNC")) {
        *config->vsync = (u32)atoi(value) > 0 ? true : false;
    } else if (MATCH("Display", "FPS")) {
        u32 fps = (u32)atoi(value);
        if (fps > 255) {
            fps = 60;
        }
        *config->fps = fps;
    }

    return 1;
}

bool engine_ini_parse(
    char**  title,
    u32*    width,
    u32*    height,
    u8*     fps,
    bool*   vsync
) {
    ini_config config = (ini_config) {
        .title  = title,
        .height = height,
        .width  = width,
        .fps    = fps,
        .vsync  = vsync,
    };
    char* data = LoadFileText("lily.ini");
    if (data == NULL) {
        TraceLog(LOG_WARNING, "Failed to load engine configuration file");
        return false;
    }

    ini_parse_string(data, handler, &config);
    UnloadFileText(data);
    return true;
}
