#include "config.h"

#if !_TEST_MODULE
#include <iostream>
#include "music_decrypt.h"
#include "music_get_json.h"

#include <windows.h>
int main()
{
    LoadLibraryA("winhttp.dll");
    DEBUG_EXPR(std::cout << music::MusicJson().get_json(music::MusicDecrypt().paket_body("31830011")) << std::endl;);
}

#endif // _TEST