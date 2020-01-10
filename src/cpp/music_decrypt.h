#pragma once

#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

#include <cryptopp/cryptlib.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/rsa.h>
#include <cryptopp/randpool.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/hex.h>

#include <cpr/util.h>



namespace music{

class MusicDecrypt
{
public:
    
    MusicDecrypt() {
        // 构造 e
        std::srand(static_cast<std::uint32_t>(std::time(nullptr)));
        for (std::uint8_t i = 0; i < 16; i++) {
            rsa_p.push_back(original_seq[rand() % original_seq.length()]);
        }
    };
    ~MusicDecrypt() {};

public:

    auto aes_encrypt(std::string s, std::string k = "0CoJUm6Qyw8W8jud", std::string iv = "0102030405060708") {
        std::string cipher_text;

        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption cbc_enc(reinterpret_cast<const std::uint8_t*>(k.data()), k.length(), reinterpret_cast<const std::uint8_t*>(iv.data()));

        CryptoPP::StringSource _(s, true, 
        new CryptoPP::StreamTransformationFilter(
            cbc_enc,                                              // cbc 编码
            new CryptoPP::Base64Encoder(                          // base64解码 参数2置为false表示不换行
                new CryptoPP::StringSink(cipher_text),false),     // 不需要 delete, 里面包装了 https://www.cryptopp.com/wiki/StringSource 
            CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING)        // PKCS_PADDING 填充
        );
        return cipher_text;
    }

    auto rsa_encrypt(std::string p, std::string e = "", std::string m = "") {
        if (e.empty())
            e = default_e;
        if (m.empty())
            m = default_m;

        std::string ps = "0x";
        std::reverse(p.begin(), p.end());
        CryptoPP::StringSource _(p, true,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(ps),
                true,
                0,
                "0x"
            ) // HexEncoder
        ); // StringSource

        CryptoPP::Integer ni(m.c_str()), ei(e.c_str()), pi(ps.c_str());

        CryptoPP::RSA::PublicKey pubKey;
        pubKey.Initialize(ni, ei);

        CryptoPP::RSAES_OAEP_SHA_Encryptor pub(pubKey);

        return CryptoPP::IntToString(pubKey.ApplyFunction(pi), 16);
    }

    auto paket_body(std::string id, std::string k = "") {
        auto enc_text = u8"{\"ids\":\"[" +
            id +
            "]\",\"level\":\"standard\",\"encodeType\":\"mp3\",\"csrf_token\":\"\"}";

        if (!k.empty())
            rsa_p = k;

        enc_text = aes_encrypt(enc_text);
        enc_text = aes_encrypt(enc_text, rsa_p);
        auto enc_sec_key = rsa_encrypt(rsa_p);

        return "params=" + cpr::util::urlEncode(enc_text) +
            "&encSecKey=" + enc_sec_key;
    }

private:
    std::string rsa_p;

private:
    // 字符序列
    static const std::string original_seq;
    static const std::string default_e;
    static const std::string default_m;
}; // MusicDecrypt

const std::string MusicDecrypt::original_seq = u8"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string MusicDecrypt::default_e = u8"0x010001";
const std::string MusicDecrypt::default_m = u8"0x00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e417629ec4ee341f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575cce10b424d813cfe4875d3e82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7";

}  // music