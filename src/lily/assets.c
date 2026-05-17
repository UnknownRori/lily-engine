#include <raylib.h>
#include <ini.h>
#include <stdio.h>
#include <string.h>
#include "lily/types.h"
#include "lily/zip.h"

#define DATA_ZIP "data.zip"
#define LILY_MAX_IMAGES    64
#define LILY_MAX_TEXTURES  64
#define LILY_MAX_FONTS     4
#define LILY_MAX_SOUNDS    64
#define LILY_MAX_MUSIC     16
#define LILY_MAX_TEXTS     64
#define LILY_MAX_NAME      64

typedef struct { char name[LILY_MAX_NAME]; Image     asset; } lily_image_slot_t;
typedef struct { char name[LILY_MAX_NAME]; Texture2D asset; } lily_texture_slot_t;
typedef struct { char name[LILY_MAX_NAME]; Font      asset; } lily_font_slot_t;
typedef struct { char name[LILY_MAX_NAME]; Sound     asset; } lily_sound_slot_t;
typedef struct { char name[LILY_MAX_NAME]; Music     asset; } lily_music_slot_t;
typedef struct { char name[LILY_MAX_NAME]; char*     asset; } lily_text_slot_t;

static struct {
    Image img_fallback;

    lily_image_slot_t   images[LILY_MAX_IMAGES];     int image_count;
    lily_texture_slot_t textures[LILY_MAX_TEXTURES]; int texture_count;
    lily_font_slot_t    fonts[LILY_MAX_FONTS];       int font_count;
    lily_sound_slot_t   sounds[LILY_MAX_SOUNDS];     int sound_count;
    lily_music_slot_t   music[LILY_MAX_MUSIC];       int music_count;
    lily_text_slot_t    texts[LILY_MAX_TEXTS];       int text_count;
} s_global_assets = {0};

static int parse_arts_ini(
    void* data, 
    const char* section, 
    const char* name, 
    const char* value
);

rori_status_t lily_assets_load()
{
    memset(&s_global_assets, 0, sizeof(s_global_assets));
    if (lily_load_zip(DATA_ZIP)) {
        TraceLog(LOG_FATAL, "ASSETS: Failed to load " DATA_ZIP);
        return RORI_FAIL;
    }

    char* assets = lily_load_zip_text("assets.ini");
    if (assets == NULL) {
        TraceLog(LOG_WARNING, "Failed to read");
        return RORI_FAIL;
    }
    ini_parse_string(assets, parse_arts_ini, &s_global_assets);
    UnloadFileText(assets);

    s_global_assets.img_fallback = GenImageChecked(32, 32, 8, 8, DARKPURPLE, PURPLE);

    lily_unload_zip();
    return RORI_SUCCESS;
}

void lily_assets_unload()
{
    for (int i = 0; i < s_global_assets.image_count;   i++) 
        UnloadImage(s_global_assets.images[i].asset);
    for (int i = 0; i < s_global_assets.texture_count; i++) 
        UnloadTexture(s_global_assets.textures[i].asset);
    for (int i = 0; i < s_global_assets.font_count;    i++) 
        UnloadFont(s_global_assets.fonts[i].asset);
    for (int i = 0; i < s_global_assets.sound_count;   i++) 
        UnloadSound(s_global_assets.sounds[i].asset);
    for (int i = 0; i < s_global_assets.music_count;   i++) 
        UnloadMusicStream(s_global_assets.music[i].asset);
    for (int i = 0; i < s_global_assets.text_count;    i++)
        if (s_global_assets.texts[i].asset != NULL)
            UnloadFileText(s_global_assets.texts[i].asset);

    memset(&s_global_assets, 0, sizeof(s_global_assets));
}

Image     lily_get_image(const char* name)
{
    for (int i = 0; i < s_global_assets.image_count; i++)
        if (strcmp(s_global_assets.images[i].name, name) == 0)
            return s_global_assets.images[i].asset;
    TraceLog(LOG_WARNING, "Image not found: %s", name);
    return s_global_assets.img_fallback;
}

Texture2D lily_get_texture2d(const char* name)
{
    for (int i = 0; i < s_global_assets.texture_count; i++)
        if (strcmp(s_global_assets.textures[i].name, name) == 0)
            return s_global_assets.textures[i].asset;
    TraceLog(LOG_WARNING, "Texture not found: %s", name);
    
    return LoadTextureFromImage(s_global_assets.img_fallback);
}

Font      lily_get_font(const char* name)
{
    for (int i = 0; i < s_global_assets.font_count; i++)
        if (strcmp(s_global_assets.fonts[i].name, name) == 0)
            return s_global_assets.fonts[i].asset;
    TraceLog(LOG_WARNING, "Font not found: %s", name);
    
    return GetFontDefault();
}

Sound     lily_get_sound(const char* name)
{
    for (int i = 0; i < s_global_assets.sound_count; i++)
        if (strcmp(s_global_assets.sounds[i].name, name) == 0)
            return s_global_assets.sounds[i].asset;
    TraceLog(LOG_WARNING, "Sound not found: %s", name);
    
    return (Sound) {0};
}
Music     lily_get_music(const char* name)
{
    for (int i = 0; i < s_global_assets.music_count; i++)
        if (strcmp(s_global_assets.music[i].name, name) == 0)
            return s_global_assets.music[i].asset;
    TraceLog(LOG_WARNING, "Music not found: %s", name);
    
    return (Music) {0};
}

char*     lily_get_text(const char* name)
{
    for (int i = 0; i < s_global_assets.text_count; i++)
        if (strcmp(s_global_assets.texts[i].name, name) == 0)
            return s_global_assets.texts[i].asset;
    TraceLog(LOG_WARNING, "Text not found: %s", name);

    return NULL;
}

static void parse_font_value(const char* value, char* path_out, usize path_cap, int* size_out) {
    *size_out = 0;
 
    char buf[512];
    snprintf(buf, sizeof(buf), "%s", value);
 
    char* p = buf;
    if (*p == '"') {
        p++;
        while (*p && *p != '"') p++;
        if (*p) p++;
    }
 
    char* comma = strchr(p, ',');
    if (comma) {
        *comma    = '\0';
        *size_out = TextToInteger(comma + 1);
    }
 
    char* path = buf;
    usize len  = strlen(path);
    if (len >= 2 && path[0] == '"' && path[len - 1] == '"') {
        path[len - 1] = '\0';
        path++;
    }
    snprintf(path_out, path_cap, "%s", path);
}

static int parse_arts_ini(
    void* data, 
    const char* section, 
    const char* name, 
    const char* value
)
{
    (void) data;
    char path[512];
    snprintf(path, sizeof(path), "%s", value);
    usize plen   = strlen(path);
    char* pstart = path;
    if (plen >= 2 && path[0] == '"' && path[plen - 1] == '"') {
        path[plen - 1] = '\0';
        pstart = path + 1;
    }

    #define MATCH(s) strcmp(section, s) == 0
    if (MATCH("Image")) {
        if (s_global_assets.image_count >= LILY_MAX_IMAGES) return 1;
        lily_image_slot_t* slot = &s_global_assets.images[s_global_assets.image_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        slot->asset = lily_load_zip_image(pstart);
    }
    if (MATCH("Texture")) {
        if (s_global_assets.texture_count >= LILY_MAX_TEXTURES) return 1;
        lily_texture_slot_t* slot = &s_global_assets.textures[s_global_assets.texture_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        slot->asset = lily_load_zip_texture2d(pstart);
    }
    if (MATCH("Font")) {
        if (s_global_assets.font_count >= LILY_MAX_FONTS) return 1;
        char fpath[512]; int fsize;
        parse_font_value(value, fpath, sizeof(fpath), &fsize);
        if (fsize == 0) {
            TraceLog(LOG_WARNING, "Font: %s -> Skipped missing size (lily=\"./lily.ttf\", 8)", name);
            return 1;
        }
        lily_font_slot_t* slot = &s_global_assets.fonts[s_global_assets.font_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        TraceLog(LOG_INFO, "Font loaded: %s", name);
        slot->asset = lily_load_zip_font(fpath, (u8)fsize);
    }
    if (MATCH("Sound")) {
        if (s_global_assets.sound_count >= LILY_MAX_SOUNDS) return 1;
        lily_sound_slot_t* slot = &s_global_assets.sounds[s_global_assets.sound_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        slot->asset = lily_load_zip_sound(pstart);
    }
    if (MATCH("Music")) {
        if (s_global_assets.music_count >= LILY_MAX_MUSIC) return 1;
        lily_music_slot_t* slot = &s_global_assets.music[s_global_assets.music_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        slot->asset = lily_load_zip_music(pstart);
    }
    if (MATCH("Text")) {
        if (s_global_assets.text_count >= LILY_MAX_TEXTS) return 1;
        lily_text_slot_t* slot = &s_global_assets.texts[s_global_assets.text_count++];
        snprintf(slot->name, LILY_MAX_NAME, "%s", name);
        slot->asset = lily_load_zip_text(pstart);
    }
    return 1;
}
