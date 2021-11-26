#include <stdio.h>
#include <keyMap.h>
#include <manchester.h>

int main(void)
{
    ui64 encValue = man_enc_32(0x2BA1EFF3, LSB_LEFT);
    ui32 decValue = man_dec_32(encValue, LSB_LEFT);
    printf("%x\n\n", decValue);
    ui32 num = 420;
    KeyPair pair = init_keypair_stack_cstr("test", &num, sizeof(ui32));
    KeyMap map = init_keyMap_stack();
    map.add(&map, &pair);
    pair.clear(&pair);
    KeyPair* index_1 = map.at(&map, 0);
    printf("Key: %s \nValue: %d\n", index_1->key.value, *(ui32 *)index_1->data);
    map.clear(&map);
    return 0;
}