import base64
import binascii
import random
import string
import unittest
import urllib
from enum import Enum

from Crypto.Cipher import AES


class MusicDecrypt(unittest.TestCase):
    randKey = ''

    def __init__(self, methodName='runTest'):
        super(MusicDecrypt, self).__init__(methodName)
        self.randKey = ''.join(random.sample(
            string.ascii_letters + string.digits, 16))

    def packet_body(self, id):
        enc_text = self.aes_encrypt(
            s='{"ids":"[' + id + ']","level":"standard","encodeType":"mp3","csrf_token":""}',
            k="0CoJUm6Qyw8W8jud",
        )
        enc_text = self.aes_encrypt(
            s=enc_text,
            k=self.randKey,
        )
        enc_sec_key = self.rsa_encrypt(
            p=self.randKey,
            e="010001",
            m="00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e417629ec4ee341f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575cce10b424d813cfe4875d3e82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7"
        )

        return ('params=' + urllib.parse.quote(enc_text) +
                '&encSecKey=' + enc_sec_key)

    #
    # AES
    # CBC
    # pkcs5padding
    # 128bit
    #
    def aes_encrypt(self, s, k, iv="0102030405060708"):
        l = 16 - len(s) % 16
        # pkcs5padding
        s += + l * chr(l)
        self.assertEqual(len(s) % 16, 0)

        return base64.b64encode(AES.new(k.encode("utf-8"), AES.MODE_CBC, iv.encode("utf-8")).encrypt(s.encode("utf-8"))).decode()

    def test_aes_encrypt(self):

        enc = self.aes_encrypt(
            s='{"ids":"[28949499]","level":"standard","encodeType":"aac","csrf_token":""}',
            k="0CoJUm6Qyw8W8jud",
        )
        self.assertEqual(
            enc,
            "g1N6YybxFdV98P/fGY0407hwjh0evx5kPtxXR0nPd/WPPFsi9Lf67vFfjUnM3MDahHpqkyZMS+9goaszbHF+i1fIufNBu+8BbSvBCJSVfEU="
        )
        self.assertEqual(
            self.aes_encrypt(
                s=enc,
                k="GR1dIlooUjX3zmY1",
            ),
            "9R0jh8yE6/JTTwoH4ujCacPMOwJdbXk39BlG3ODTNe+rHMLAOSHDlp/Mza7+15lOi8bvPMtLnA6gCOujDj5iuVBJF2a2DJVkNLtrTtgl+AXpsR5hSh0+EOfuads7lq41B9EpYKktwB72zOy+kafalQ=="
        )

    #
    # reverse p: p = p[::-1]
    # power e of p, and modular m : [p^e] % m
    #
    def rsa_encrypt(self, p, e, m):
        p = binascii.hexlify(p[::-1].encode("utf-8"))
        rs = int(p, 16)**int(e, 16) % int(m, 16)
        return format(rs, 'x').zfill(256)

    def test_rsa_encrypt(self):
        self.assertEqual(
            self.rsa_encrypt(
                p="GR1dIlooUjX3zmY1",
                e="010001",
                m="00e0b509f6259df8642dbc35662901477df22677ec152b5ff68ace615bb7b725152b3ab17a876aea8a5aa76d2e417629ec4ee341f56135fccf695280104e0312ecbda92557c93870114af6c9d05c4f7f0c3685b7a46bee255932575cce10b424d813cfe4875d3e82047b97ddef52741d546b8e289dc6935b3ece0462db0a22b8e7"
            ),
            "abc2e11cd93268085180aace6208c0caed01b7c2af641999a79adf362fb778a3fba5117f9c06541a5620d4dccd628085b53c1b22d971068a458e1ac16d831860ab2f1da4c7c8342f8bb815c6ab6c6c335cc797a4273124ff4846c9d58b0015691f933323fe080b8d026836880af99e918c7ace1813356b8bc327a52dcc24050a"
        )


if __name__ == "__main__":
    #unittest.main()

    print(MusicDecrypt()
          .packet_body('1297747756'))


# PacketType = Enum("PacketType",("lrc", "music", "pic"))
# MusicLevel = Enum("MusicLevel",("standard"))
# EncodeType = Enum("EncodeType", ("aac", "mp3"))