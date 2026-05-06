#include "lily/engine.h"
int main()
{
    lily_engine_init(
        .width  = 800,
        .height = 600,
        .fps    = 60,
    );

    lily_engine_run();
}
