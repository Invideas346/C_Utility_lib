#include <stdlib.h>
#include <stdio.h>
#include <cutil.h>

int main(void)
{
    LOG_INIT();
    LOG_INFO("INFO");
    LOG_TRACE("TRACE");
    LOG_DEBUG("DEBUG");
    LOG_WARNING("WARNING");
    LOG_ERROR("ERROR");
    return EXIT_SUCCESS;
}