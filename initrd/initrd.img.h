const char initrd_img[]={
0x01,0x00,0x00,0x00,0x00,0xbf,0x73,0x6f,0x73,0x68,0x2e,0x62,0x69,0x6e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x91,0x00,0x23,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x33,0x31,0x34,0x33,0x31,0x20,0x00,0x01,0x01,0x00,0x01,0x04,0x00,0x01,0x07
,0x00,0x01,0x39,0x00,0x02,0x3c,0x00,0x01,0x40,0x00,0x02,0x7b,0x00,0x01,0x7f,0x00,0x01,0x83,0x00,0x02,0x8a,0x00,0x01,0x92,0x00,0x02,0xc1,0x00,0x01,0xc6,0x00,0x01
,0xcb,0x00,0x02,0xf8,0x00,0x01,0xfc,0x00,0x01,0x00,0x01,0x01,0x11,0x01,0x02,0x17,0x01,0x01,0x1c,0x01,0x01,0x5e,0x01,0x01,0x86,0x01,0x01,0x99,0x01,0x01,0xbb,0x01
,0x01,0x11,0x02,0x01,0x4b,0x02,0x02,0x4f,0x02,0x02,0x58,0x02,0x02,0x5d,0x02,0x01,0x69,0x02,0x02,0xb3,0x02,0x01,0xb6,0x02,0xcd,0xab,0x02,0xcd,0xea,0x00,0xcd,0x45
,0x02,0x18,0xfb,0xdd,0xe5,0xdd,0x21,0x00,0x00,0xdd,0x39,0x21,0xf9,0xff,0x39,0xf9,0xdd,0x36,0xfc,0x00,0xdd,0x36,0xfd,0x00,0xdd,0x36,0xfb,0x00,0xdd,0x7e,0x06,0xc6
,0xff,0xdd,0x77,0xfe,0xdd,0x7e,0x07,0xce,0xff,0xdd,0x77,0xff,0xdd,0x7e,0xfb,0xb7,0xc2,0xcd,0x00,0x21,0xf6,0x80,0xe5,0xcd,0xe4,0x01,0xf1,0xdd,0x74,0xfa,0xdd,0x75
,0xf9,0xc1,0xc5,0x79,0x3c,0x20,0x04,0x78,0x3c,0x28,0xe1,0x79,0xd6,0x08,0x20,0x03,0xb0,0x28,0x0a,0x79,0xd6,0x0a,0x20,0x3c,0xb0,0x28,0x26,0x18,0x37,0xdd,0x7e,0xfd
,0xdd,0xb6,0xfc,0x28,0xc7,0xdd,0x6e,0xfc,0xdd,0x66,0xfd,0x2b,0xdd,0x75,0xfc,0xdd,0x74,0xfd,0x21,0xfe,0x80,0xe5,0x21,0xe2,0x00,0xe5,0xcd,0x88,0x01,0xf1,0xf1,0x18
,0xab,0x21,0xfe,0x80,0xe5,0x21,0x0a,0x00,0xe5,0xcd,0x2b,0x01,0xf1,0xf1,0xdd,0x36,0xfb,0x01,0x18,0x98,0xdd,0x7e,0xfc,0xdd,0x96,0xfe,0xdd,0x7e,0xfd,0xdd,0x9e,0xff
,0x30,0x8a,0xdd,0x5e,0xfc,0xdd,0x56,0xfd,0xdd,0x34,0xfc,0x20,0x03,0xdd,0x34,0xfd,0xdd,0x6e,0x04,0xdd,0x66,0x05,0x19,0x71,0x21,0xfe,0x80,0xe5,0xc5,0xcd,0x2b,0x01
,0xf1,0xf1,0xc3,0x34,0x00,0xdd,0x7e,0x04,0xdd,0x86,0xfc,0x4f,0xdd,0x7e,0x05,0xdd,0x8e,0xfd,0x47,0xaf,0x02,0xdd,0xf9,0xdd,0xe1,0xc9,0x1b,0x5b,0x44,0x1b,0x5b,0x30
,0x4b,0x00,0xdd,0xe5,0xdd,0x21,0x00,0x00,0xdd,0x39,0x21,0xbf,0xff,0x39,0xf9,0x21,0xfe,0x80,0xe5,0x21,0x28,0x01,0xe5,0xcd,0x88,0x01,0xf1,0xf1,0x21,0x00,0x00,0x39
,0x4d,0x44,0xe5,0x11,0x41,0x00,0xd5,0xc5,0xcd,0x0b,0x00,0xf1,0xf1,0xe1,0x01,0xfe,0x80,0xc5,0xe5,0xcd,0x88,0x01,0xf1,0xf1,0x21,0x00,0x00,0xdd,0xf9,0xdd,0xe1,0xc9
,0x3e,0x20,0x00,0xdd,0xe5,0xdd,0x21,0x00,0x00,0xdd,0x39,0xf5,0x3b,0xdd,0x7e,0x04,0xdd,0x77,0xfd,0x21,0x00,0x00,0x39,0xdd,0x75,0xfe,0xdd,0x74,0xff,0xdd,0x4e,0x06
,0xdd,0x46,0x07,0x69,0x60,0x5e,0x23,0x56,0xc5,0x21,0x01,0x00,0xe5,0xdd,0x6e,0xfe,0xdd,0x66,0xff,0xe5,0xd5,0xcd,0x80,0x01,0xf1,0xf1,0xf1,0xc1,0x7c,0xb5,0x20,0x0e
,0x21,0x06,0x00,0x09,0x36,0x01,0x23,0x36,0x00,0x21,0xff,0xff,0x18,0x05,0xdd,0x6e,0xfd,0x26,0x00,0xdd,0xf9,0xdd,0xe1,0xc9,0x3e,0x23,0x01,0x06,0x00,0xc3,0x4d,0x02
,0xdd,0xe5,0xdd,0x21,0x00,0x00,0xdd,0x39,0xf5,0xdd,0x6e,0x04,0xdd,0x66,0x05,0xe5,0xcd,0x33,0x02,0xf1,0x4d,0x44,0xdd,0x5e,0x04,0xdd,0x56,0x05,0xdd,0x7e,0x06,0xdd
,0x77,0xfe,0xdd,0x7e,0x07,0xdd,0x77,0xff,0xe1,0xe5,0x7e,0x23,0x66,0x6f,0xc5,0xc5,0xd5,0xe5,0xcd,0x80,0x01,0xf1,0xf1,0xf1,0xc1,0xbf,0xed,0x42,0x30,0x16,0xdd,0x7e
,0xfe,0xc6,0x06,0x6f,0xdd,0x7e,0xff,0xce,0x00,0x67,0x36,0x01,0x23,0x36,0x00,0x21,0xff,0xff,0x18,0x03,0x21,0x00,0x00,0xdd,0xf9,0xdd,0xe1,0xc9,0xdd,0xe5,0xdd,0x21
,0x00,0x00,0xdd,0x39,0xf5,0x3b,0x21,0x00,0x00,0x39,0xdd,0x75,0xfe,0xdd,0x74,0xff,0xdd,0x4e,0x04,0xdd,0x46,0x05,0x69,0x60,0x5e,0x23,0x56,0xc5,0x21,0x01,0x00,0xe5
,0xdd,0x6e,0xfe,0xdd,0x66,0xff,0xe5,0xd5,0xcd,0x63,0x02,0xf1,0xf1,0xf1,0xc1,0x7c,0xb5,0x20,0x0e,0x21,0x04,0x00,0x09,0x36,0xff,0x23,0x36,0xff,0x21,0xff,0xff,0x18
,0x05,0xdd,0x6e,0xfd,0x26,0x00,0xdd,0xf9,0xdd,0xe1,0xc9,0x01,0x00,0x00,0xd1,0xe1,0xe5,0xd5,0x7e,0x23,0xb7,0x28,0x03,0x03,0x18,0xf8,0x69,0x60,0xc9,0x3e,0x00,0x01
,0x00,0x00,0xc3,0x4d,0x02,0xe1,0x22,0xf4,0x80,0xed,0x62,0xed,0x7a,0xf7,0xed,0x5b,0xf4,0x80,0xd5,0xd0,0x22,0xf2,0x80,0x21,0xff,0xff,0xc9,0x3e,0x22,0x01,0x06,0x00
,0xc3,0x4d,0x02,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x2c,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x2c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x01,0x40,0x00,0x78,0xb1,0x28,0x08,0x11,0xf6,0x80,0x21,0x6b,0x02,0xed,0xb0,0xc9};