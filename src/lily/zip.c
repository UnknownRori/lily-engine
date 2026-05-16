#include <raylib.h>
#include <miniz.h>
#include <miniz_zip.h>

#include "lily/zip.h"
#include "lily/memory.h"
#include "lily/types.h"

static mz_zip_archive loaded_zip = {0};
u8* loaded_data = NULL;

rori_status_t   lily_load_zip(const char* path)
{
    i32 size = 0;
    loaded_data = LoadFileData(path, &size);
    if (!mz_zip_reader_init_mem(&loaded_zip, loaded_data, size, 0)) {
        TraceLog(LOG_ERROR, "ZIP: Cannot open %s", path);
        return 1;
    }
    return 0;
    return 0;
}
void            lily_unload_zip()
{
    mz_zip_reader_end(&loaded_zip);
    UnloadFileData(loaded_data);
    loaded_data = NULL;
}

u8*             lily_load_zip_file(const char* file, usize* out_size)
{
    int idx = mz_zip_reader_locate_file(&loaded_zip, file, NULL, 0);
    if (idx < 0) {
        TraceLog(LOG_ERROR, "ZIP: Entry not found: %s", file);
        return NULL;
    }

    mz_zip_archive_file_stat stat;
    mz_zip_reader_file_stat(&loaded_zip, idx, &stat);
    *out_size = (size_t)stat.m_uncomp_size;

    // Extract into a heap buffer
    u8* buf = (unsigned char*)RORI_MALLOC(*out_size);
    if (!mz_zip_reader_extract_to_mem(&loaded_zip, idx, buf, *out_size, 0)) {
        TraceLog(LOG_ERROR, "ZIP: Failed to extract: %s", file);
        RORI_FREE(buf);
        return RORI_ALLOCATION_FAIL;
    }

    return buf;
}

char*           lily_load_zip_text(const char* file)
{
    size_t size = 0;
    u8* data = lily_load_zip_file(file, &size);
    if (!data) {
        TraceLog(LOG_WARNING, "LoadTextFromZip: Failed to load text '%s'", file);
        return RORI_ALLOCATION_FAIL;
    }

    char* text = (char*)RORI_MALLOC(size + 1);
    if (!text) {
        RORI_FREE(data);
        return RORI_ALLOCATION_FAIL;
    }

    memcpy(text, data, size);
    text[size] = '\0';

    RORI_FREE(data);
    return text;
}

Image           lily_load_zip_image(const char* file)
{
    size_t size = 0;
    u8* data = lily_load_zip_file(file, &size);
    if (!data) {
        TraceLog(LOG_WARNING, "LoadImageFromZip: Failed to load image '%s'", file);
        return (Image){0};
    }

    const char* ext = GetFileExtension(file);
    Image img = LoadImageFromMemory(ext, data, (int)size);
    RORI_FREE(data);
    return img;
}

Texture2D       lily_load_zip_texture2d(const char* file)
{
    Image img = lily_load_zip_image(file);
    if (img.width == 0 || img.height == 0) {
        TraceLog(LOG_WARNING, "LoadTextureFromZip: Failed to load image '%s'", file);
        return (Texture2D){0};
    }

    return LoadTextureFromImage(img);
}

Font            lily_load_zip_font(const char* file, u8 font_size)
{
    size_t size = 0;
    u8* data = lily_load_zip_file(file, &size);
    if (!data) {
        TraceLog(LOG_WARNING, "LoadFontFromZip: Failed to load font '%s'", file);
        return (Font){0};
    }

    const char* ext = GetFileExtension(file);
    Font font = LoadFontFromMemory(ext, data, size, font_size, NULL, 0);
    RORI_FREE(data);

    return font;
}

Wave            lily_load_zip_wave(const char* file)
{
    size_t size = 0;
    u8* data = lily_load_zip_file(file, &size);
    if (!data) {
        TraceLog(LOG_WARNING, "LoadWaveFromZip: Failed to load wave file '%s'", file);
        return (Wave){0};
    }

    const char* ext = GetFileExtension(file);
    Wave wave = LoadWaveFromMemory(ext, data, size);
    RORI_FREE(data);

    return wave;
}

Sound           lily_load_zip_sound(const char* file)
{
    Wave wave = lily_load_zip_wave(file);
    if (wave.data == NULL) {
        TraceLog(LOG_WARNING, "LoadSoundFromZip: Failed to load wave file '%s'", file);
        return (Sound){0};
    }

    return LoadSoundFromWave(wave);
}

Music           lily_load_zip_music(const char* file)
{
    size_t size = 0;
    u8* data = lily_load_zip_file(file, &size);
    if (!data) {
        TraceLog(LOG_WARNING, "LoadMusicFromZip: Failed to load wave file '%s'", file);
        return (Music){0};
    }

    const char* ext = GetFileExtension(file);
    Music wave = LoadMusicStreamFromMemory(ext, data, size);
    RORI_FREE(data);

    return wave;
}
