#include <stdlib.h>
#include <string.h>
#include <keyMap.h>

//TODO: Line 12 dereferencing the pointer leads to the pointer internally also being referneced in the Keypair
//this can lead to a error later on (a own string copy function should be implemented to fix this entire
//reference thing and lifetime thing)
int main(void)
{
    ui32 num = 420;
    string key = init_string_stack("test");
    KeyPair pair = init_keypair_stack(&key, &num, sizeof(ui32));
    KeyMap map = init_keyMap_stack();
    map.add(&map, &pair);
    map.clear(&map);
    key.clear(&key);
    return 0;
}