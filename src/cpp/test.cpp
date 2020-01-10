#include "config.h"

#if _TEST_MODULE
#define BOOST_TEST_MODULE music_test
#include <boost/test/included/unit_test.hpp>
#include <boost/log/trivial.hpp>

#include "music_decrypt.h"
#include "music_get_json.h"

// 全局测试夹具
class global_fixture
{
public:
    global_fixture() {
        std::cout << "开始准备测试数据------->" << std::endl;
    }
    virtual~global_fixture() {
        std::cout << "清理测试环境<---------" << std::endl;
    }
};

BOOST_GLOBAL_FIXTURE(global_fixture);
BOOST_AUTO_TEST_CASE(TestCase_4_aes_encrypt)
{
    auto enc_text = music::MusicDecrypt().aes_encrypt(u8"{\"ids\":\"[28949499]\",\"level\":\"standard\",\"encodeType\":\"aac\",\"csrf_token\":\"\"}");

    BOOST_LOG_TRIVIAL(info) << "开始测试 aes_encrypt";
    BOOST_TEST(enc_text == "g1N6YybxFdV98P/fGY0407hwjh0evx5kPtxXR0nPd/WPPFsi9Lf67vFfjUnM3MDahHpqkyZMS+9goaszbHF+i1fIufNBu+8BbSvBCJSVfEU=");
    
    BOOST_TEST(music::MusicDecrypt().aes_encrypt(enc_text, u8"GR1dIlooUjX3zmY1") ==
        "9R0jh8yE6/JTTwoH4ujCacPMOwJdbXk39BlG3ODTNe+rHMLAOSHDlp/Mza7+15lOi8bvPMtLnA6gCOujDj5iuVBJF2a2DJVkNLtrTtgl+AXpsR5hSh0+EOfuads7lq41B9EpYKktwB72zOy+kafalQ=="
    );
    BOOST_LOG_TRIVIAL(info) << "结束测试 aes_encrypt";
}

BOOST_AUTO_TEST_CASE(TestCase_4_rsa_encrypt)
{
    BOOST_LOG_TRIVIAL(info) << "开始测试 rsa_encrypt";
    BOOST_TEST(music::MusicDecrypt().rsa_encrypt(u8"GR1dIlooUjX3zmY1") ==
        "abc2e11cd93268085180aace6208c0caed01b7c2af641999a79adf362fb778a3fba5117f9c06541a5620d4dccd628085b53c1b22d971068a458e1ac16d831860ab2f1da4c7c8342f8bb815c6ab6c6c335cc797a4273124ff4846c9d58b0015691f933323fe080b8d026836880af99e918c7ace1813356b8bc327a52dcc24050a"
    );
    BOOST_LOG_TRIVIAL(info) << "结束测试 rsa_encrypt";
}

BOOST_AUTO_TEST_CASE(TestCase_4_paket_body)
{
    BOOST_LOG_TRIVIAL(info) << "开始测试 paket_body";
    BOOST_TEST(music::MusicDecrypt().paket_body(u8"28949499", u8"GR1dIlooUjX3zmY1") == 
        "params=9R0jh8yE6%2fJTTwoH4ujCacPMOwJdbXk39BlG3ODTNe%2brHMLAOSHDlp%2fMza7%2b15lOi8bvPMtLnA6gCOujDj5iuT1EbsfNRzJrzZm6oIqgWhVsWcO%2bhrLFCHDHgyIYGdXOBmuWBRRiDCyMUFJAq3yrVw%3d%3d&encSecKey=abc2e11cd93268085180aace6208c0caed01b7c2af641999a79adf362fb778a3fba5117f9c06541a5620d4dccd628085b53c1b22d971068a458e1ac16d831860ab2f1da4c7c8342f8bb815c6ab6c6c335cc797a4273124ff4846c9d58b0015691f933323fe080b8d026836880af99e918c7ace1813356b8bc327a52dcc24050a"
    );
    BOOST_LOG_TRIVIAL(info) << "结束测试 paket_body";
}

BOOST_AUTO_TEST_CASE(TestCase_4_get_json)
{
    BOOST_LOG_TRIVIAL(info) << "开始测试 get_json";
    BOOST_TEST(music::MusicJson().get_json(
        "params=9R0jh8yE6%2fJTTwoH4ujCacPMOwJdbXk39BlG3ODTNe%2brHMLAOSHDlp%2fMza7%2b15lOi8bvPMtLnA6gCOujDj5iuT1EbsfNRzJrzZm6oIqgWhVsWcO%2bhrLFCHDHgyIYGdXOBmuWBRRiDCyMUFJAq3yrVw%3d%3d&encSecKey=abc2e11cd93268085180aace6208c0caed01b7c2af641999a79adf362fb778a3fba5117f9c06541a5620d4dccd628085b53c1b22d971068a458e1ac16d831860ab2f1da4c7c8342f8bb815c6ab6c6c335cc797a4273124ff4846c9d58b0015691f933323fe080b8d026836880af99e918c7ace1813356b8bc327a52dcc24050a"
    ) != "");
    BOOST_LOG_TRIVIAL(info) << "结束测试 get_json";
}

#endif  // _TEST_MODULE
