#include <raylib.h>
#include "lily/assert.h"
#include "lily/reader/ini.h"

#include "config.h"

static lily_ini_t* s_config = NULL;

int engine_ini_parse()
{
    char* data = LoadFileText("lily.ini");
    if (data == NULL) {
        TraceLog(LOG_WARNING, "Failed to load engine configuration file");
        return false;
    }

    bool stat = false;
    s_config = lily_ini_parse(data, &stat);
    UnloadFileText(data);
    return stat;
}

bool        lily_config_get_bool    (const char* section, const char* key, bool fallback)
{
    RORI_ASSERT(s_config != NULL);
    return lily_ini_get_bool(s_config, section, key, fallback);
}

i32         lily_config_get_i32     (const char* section, const char* key, i32 fallback)
{
    RORI_ASSERT(s_config != NULL);
    return lily_ini_get_i32(s_config, section, key, fallback);
}

f32         lily_config_get_f32     (const char* section, const char* key, f32 fallback)
{
    RORI_ASSERT(s_config != NULL);
    return lily_ini_get_f32(s_config, section, key, fallback);
}

const char* lily_config_get_cstr    (const char* section, const char* key, const char* fallback)
{
    RORI_ASSERT(s_config != NULL);
    return lily_ini_get_cstr(s_config, section, key, fallback);
}
