#pragma once
#include <cpr/cpr.h>

namespace music {

class MusicJson {
public:
    MusicJson() {}
    ~MusicJson() {}

public:
    auto get_json(std::string packet_body) {
        auto r = cpr::Post(cpr::Url{ "https://music.163.com/weapi/song/enhance/player/url/v1?csrf_token=" },
            cpr::Body{ packet_body },
            cpr::Header{ {"Content-Type", "application/x-www-form-urlencoded"},{"Connection", "close"} });

        return  r.text;
    }
}; // MusicJson

}  // music