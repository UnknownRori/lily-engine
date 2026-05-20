#include <string.h>
#include <ini.h>
#include "lily/reader/ini.h"
#include "lily/assert.h"
#include "lily/memory.h"

#define CONFIG_MAX_ENTRIES 64
#define CONFIG_KEY_LEN     64
#define CONFIG_VAL_LEN     256

// TODO : Use rstb_string_view for better memory usage
typedef struct ini_entry {
    char section[CONFIG_KEY_LEN];
    char key    [CONFIG_KEY_LEN];
    char value  [CONFIG_VAL_LEN];
} ini_entry;

struct lily_ini_t {
    ini_entry   entries[CONFIG_MAX_ENTRIES];
    u8          count;
};

static int _handler(
    void* data,
    const char* section,
    const char* key,
    const char* value
) {
    lily_ini_t* ini = data;
    if (ini->count >= CONFIG_MAX_ENTRIES) return 0;

    ini_entry* e = &ini->entries[ini->count];
    strncpy(e->section  , section   , CONFIG_KEY_LEN);
    strncpy(e->key      , key       , CONFIG_KEY_LEN);
    strncpy(e->value    , value     , CONFIG_VAL_LEN);
}

lily_ini_t* lily_ini_parse      (const char* buffer, bool* status)
{
    lily_ini_t* ini = RORI_CALLOC(1, sizeof(lily_ini_t));
    bool stat = ini_parse_string(buffer, _handler, ini) == 0;
    if (status != NULL) *status = stat;
    return ini;
}
void        lily_ini_free       (lily_ini_t* ini)
{
    RORI_ASSERT(ini != NULL);
    RORI_FREE(ini);
}

static const char* _find(const lily_ini_t* ini, const char* section, const char* key)
{
    for (int i = 0; i < ini->count; i++) {
        if (strcmp(ini->entries[i].section, section) == 0 &&
            strcmp(ini->entries[i].key,     key)     == 0)
            return ini->entries[i].value;
    }
    return NULL;
}

bool                lily_ini_get_bool   (lily_ini_t* ini, const char* section, const char* key, bool fallback)
{
    const char *v = _find(ini, section, key);
    if (!v) return fallback;
    return strcmp(v,"true")==0 || strcmp(v,"1")==0;
}

i32         lily_ini_get_i32    (lily_ini_t* ini, const char* section, const char* key, i32 fallback)
{
    // TODO : Properly parse the integer
    const char *v = _find(ini, section, key);
    return v ? atoi(v) : fallback;
}

f32         lily_ini_get_f32    (lily_ini_t* ini, const char* section, const char* key, f32 fallback)
{
    // TODO : Properly parse the float
    const char *v = _find(ini, section, key);
    return v ? (float)atof(v) : fallback;
}

const char* lily_ini_get_cstr    (lily_ini_t* ini, const char* section, const char* key, const char* fallback)
{
    const char *v = _find(ini, section, key);
    return v ? v : fallback;
}
