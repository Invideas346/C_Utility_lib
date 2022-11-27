#include <stdlib.h>
#include <stdio.h>
#include <cutil.h>

void* print(void* args)
{
    uint32_t* data = (uint32_t*) args;
    printf("Hello, new thread %u\n", *data);
}

int main(void)
{
    LOG_INIT();
    Thread thread = init_thread_stack_func(print);
    thread.start(&thread, NULL);
    LOG_INFO("Test");
    thread.join(&thread, NULL);
    return EXIT_SUCCESS;
}