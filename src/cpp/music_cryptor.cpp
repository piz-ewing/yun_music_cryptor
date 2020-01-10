#include "config.h"

#if !_TEST_MODULE
#include <iostream>
#include "music_decrypt.h"
#include "music_get_json.h"


int main()
{
    DEBUG_EXPR(std::cout << music::MusicJson().get_json(music::MusicDecrypt().paket_body("31830011")) << std::endl;);
}

#endif  // _TEST_MODULE
