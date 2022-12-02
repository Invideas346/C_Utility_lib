#include <stdlib.h>
#include <stdio.h>
#include <cutil.h>

void* print(void** args)
{
    uint32_t* data = (uint32_t*) (*args);
    printf("Hello, new thread %u\n", *data);
}

int main(void)
{
    uint32_t data = 10;
    void** packed_data = thread_pack_data(1, &data);
    LOG_INIT();
    Thread thread = init_thread_stack_func(print);
    thread.args = packed_data;
    thread.start(&thread, NULL);
    LOG_INFO("Test");
    thread.join(&thread, NULL);
    free(packed_data);
    return EXIT_SUCCESS;
}