#include "lily/types.h"
#include "lily/zip.h"
#include <raylib.h>

#define DATA_ZIP "data.zip"

static struct {

} global_assets = {0};

rori_status_t lily_assets_load()
{
    if (lily_load_zip(DATA_ZIP)) {
        TraceLog(LOG_FATAL, "ASSETS: Failed to load " DATA_ZIP);
        return RORI_FAIL;
    }

    lily_unload_zip();
    return RORI_SUCCESS;
}

void lily_assets_unload()
{

}

Image     lily_get_image(const char* name);
Texture2D lily_get_texture2d(const char* name);
Font      lily_get_font(const char* name);
Sound     lily_get_sound(const char* name);
Music     lily_get_music(const char* name);
