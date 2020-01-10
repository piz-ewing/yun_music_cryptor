#include "config.h"

#if !_TEST_MODULE
#include <iostream>
#include "music_decrypt.h"
#include "music_get_json.h"


int main()
{
    /*
    {
        "data": [{
            "id": 31830011,
            "url": "http://m10.music.126.net/20200110200142/11aca00e0f0c4a1a09d711fbd30aed52/ymusic/b218/f5e6/f02e/4f6a504cee0b5aecb3aae0d6aa53abd4.mp3",
            "br": 128000,
            "size": 3186145,
            "md5": "4f6a504cee0b5aecb3aae0d6aa53abd4",
            "code": 200,
            "expi": 1200,
            "type": "mp3",
            "gain": 0.0,
            "fee": 0,
            "uf": null,
            "payed": 0,
            "flag": 0,
            "canExtend": false,
            "freeTrialInfo": null,
            "level": "standard",
            "encodeType": "mp3"
        }],
        "code": 200
    }
    */
    DEBUG_EXPR(std::cout << music::MusicJson().get_json(music::MusicDecrypt().paket_body("31830011")) << std::endl;);
}

#endif  // _TEST_MODULE