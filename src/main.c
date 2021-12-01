#include <stdio.h>
#include <keyMap.h>
#include <manchester.h>

int main(void)
{
    ui32 num = 420;
    KeyPair pair = init_keypair_stack_cstr("test", &num, sizeof(ui32));
    KeyPair pair1 = init_keypair_stack_cstr("test1", &num, sizeof(ui32));
    KeyMap map = init_keyMap_stack();
    map.add(&map, &pair);
    map.add(&map, &pair1);
    map.remove_index(&map, 0);
    pair.clear(&pair);
    pair1.clear(&pair1);
    map.clear(&map);
    return 0;
}