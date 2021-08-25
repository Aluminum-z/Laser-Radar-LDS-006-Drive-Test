/**
 * @file    lcd_font.c
 * @brief   字库
 * @author  Alzn
 * @date    2021-08-08
 */

/*------ Includes ---------*/
#include "lcd_font.h"
/*------- Define ----------*/

/*------- Typedef ---------*/

/*------- Variable --------*/
/**
 * @brief ASCII字库
 * 字号: 16
 * 宽度: 8
 * 高度: 14
 * 字体: Consolas
 * */
static const unsigned char lcd_fontData_consolas_16_8x14[] = {
  //U+0020( )
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+0021(!)
  0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x18,0x18,0x00,0x00,0x00,
  //U+0022(")
  0x00,0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+0023(#)
  0x00,0x00,0x24,0x24,0xFE,0x24,0x48,0xFE,0x48,0x48,0x48,0x00,0x00,0x00,
  //U+0024($)
  0x00,0x08,0x3C,0x48,0x50,0x70,0x1C,0x16,0x12,0x12,0x7C,0x10,0x10,0x00,
  //U+0025(%)
  0x00,0x62,0x94,0x9C,0x68,0x10,0x10,0x26,0x69,0x49,0x86,0x00,0x00,0x00,
  //U+0026(&)
  0x00,0x30,0x48,0x48,0x78,0x30,0x74,0x94,0x8C,0x8C,0x76,0x00,0x00,0x00,
  //U+0027(')
  0x00,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+0028(()
  0x00,0x04,0x08,0x10,0x10,0x20,0x20,0x20,0x20,0x20,0x10,0x10,0x08,0x04,
  //U+0029())
  0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,
  //U+002A(*)
  0x00,0x08,0x2A,0x1C,0x1C,0x2A,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+002B(+)
  0x00,0x00,0x00,0x00,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00,0x00,0x00,
  //U+002C(,)
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08,0x30,0x00,
  //U+002D(-)
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+002E(.)
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
  //U+002F(/)
  0x00,0x02,0x04,0x04,0x0C,0x08,0x18,0x10,0x10,0x20,0x20,0x40,0x00,0x00,
  //U+0030(0)
  0x00,0x00,0x3C,0x24,0x42,0x46,0x5A,0x62,0x42,0x24,0x3C,0x00,0x00,0x00,
  //U+0031(1)
  0x00,0x00,0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00,0x00,
  //U+0032(2)
  0x00,0x00,0x3C,0x42,0x02,0x02,0x04,0x0C,0x18,0x30,0x7E,0x00,0x00,0x00,
  //U+0033(3)
  0x00,0x00,0x78,0x04,0x04,0x04,0x38,0x04,0x04,0x04,0x78,0x00,0x00,0x00,
  //U+0034(4)
  0x00,0x00,0x18,0x18,0x28,0x68,0x48,0x88,0xFE,0x08,0x08,0x00,0x00,0x00,
  //U+0035(5)
  0x00,0x00,0x7C,0x40,0x40,0x40,0x78,0x04,0x04,0x0C,0x78,0x00,0x00,0x00,
  //U+0036(6)
  0x00,0x00,0x1C,0x20,0x40,0x5C,0x62,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
  //U+0037(7)
  0x00,0x00,0x7E,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x30,0x00,0x00,0x00,
  //U+0038(8)
  0x00,0x00,0x3C,0x42,0x42,0x66,0x18,0x66,0x42,0x42,0x3C,0x00,0x00,0x00,
  //U+0039(9)
  0x00,0x00,0x3C,0x66,0x42,0x42,0x46,0x3A,0x02,0x04,0x38,0x00,0x00,0x00,
  //U+003A(:)
  0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,
  //U+003B(;)
  0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x08,0x30,0x00,
  //U+003C(<)
  0x00,0x00,0x00,0x04,0x08,0x10,0x20,0x20,0x10,0x08,0x04,0x00,0x00,0x00,
  //U+003D(=)
  0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,
  //U+003E(>)
  0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x08,0x10,0x20,0x40,0x00,0x00,0x00,
  //U+003F(?)
  0x00,0x30,0x08,0x04,0x04,0x04,0x38,0x20,0x00,0x30,0x30,0x00,0x00,0x00,
  //U+0040(@)
  0x00,0x1C,0x22,0x41,0x41,0x9D,0xB5,0xA5,0xA5,0xA5,0xBE,0x80,0x44,0x38,
  //U+0041(A)
  0x00,0x00,0x18,0x28,0x28,0x6C,0x44,0x44,0xFE,0x82,0x82,0x00,0x00,0x00,
  //U+0042(B)
  0x00,0x00,0x7C,0x42,0x42,0x46,0x7C,0x42,0x42,0x42,0x7C,0x00,0x00,0x00,
  //U+0043(C)
  0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x40,0x40,0x22,0x1C,0x00,0x00,0x00,
  //U+0044(D)
  0x00,0x00,0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x00,0x00,0x00,
  //U+0045(E)
  0x00,0x00,0x7C,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C,0x00,0x00,0x00,
  //U+0046(F)
  0x00,0x00,0x7C,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
  //U+0047(G)
  0x00,0x00,0x38,0x44,0x80,0x80,0x9C,0x84,0x84,0x44,0x3C,0x00,0x00,0x00,
  //U+0048(H)
  0x00,0x00,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0x00,0x00,0x00,
  //U+0049(I)
  0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00,
  //U+004A(J)
  0x00,0x00,0x7C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x38,0x00,0x00,0x00,
  //U+004B(K)
  0x00,0x00,0x42,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x42,0x00,0x00,0x00,
  //U+004C(L)
  0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3E,0x00,0x00,0x00,
  //U+004D(M)
  0x00,0x00,0x26,0x66,0x5A,0x5A,0x5A,0x52,0x42,0x42,0x42,0x00,0x00,0x00,
  //U+004E(N)
  0x00,0x00,0x62,0x62,0x52,0x52,0x52,0x4A,0x4A,0x46,0x46,0x00,0x00,0x00,
  //U+004F(O)
  0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,0x00,
  //U+0050(P)
  0x00,0x00,0x7C,0x46,0x42,0x42,0x46,0x78,0x40,0x40,0x40,0x00,0x00,0x00,
  //U+0051(Q)
  0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x78,0x10,0x0E,0x00,
  //U+0052(R)
  0x00,0x00,0x78,0x44,0x44,0x44,0x78,0x48,0x4C,0x44,0x46,0x00,0x00,0x00,
  //U+0053(S)
  0x00,0x00,0x3C,0x40,0x40,0x60,0x1C,0x06,0x02,0x02,0x7C,0x00,0x00,0x00,
  //U+0054(T)
  0x00,0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
  //U+0055(U)
  0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3C,0x00,0x00,0x00,
  //U+0056(V)
  0x00,0x00,0x41,0x41,0x63,0x22,0x22,0x36,0x14,0x14,0x18,0x00,0x00,0x00,
  //U+0057(W)
  0x00,0x00,0x41,0x41,0x41,0x69,0x6B,0x2A,0x3A,0x36,0x36,0x00,0x00,0x00,
  //U+0058(X)
  0x00,0x00,0xC6,0x64,0x28,0x18,0x18,0x38,0x24,0x46,0xC3,0x00,0x00,0x00,
  //U+0059(Y)
  0x00,0x00,0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
  //U+005A(Z)
  0x00,0x00,0x7E,0x04,0x04,0x08,0x18,0x10,0x20,0x20,0x7E,0x00,0x00,0x00,
  //U+005B([)
  0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C,
  //U+005C(\)
  0x00,0x40,0x20,0x20,0x10,0x10,0x18,0x08,0x0C,0x04,0x04,0x02,0x00,0x00,
  //U+005D(])
  0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38,
  //U+005E(^)
  0x00,0x00,0x10,0x28,0x44,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+005F(_)
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
  //U+0060(`)
  0x00,0x60,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  //U+0061(a)
  0x00,0x00,0x00,0x00,0x18,0x24,0x04,0x3C,0x44,0x4C,0x3C,0x00,0x00,0x00,
  //U+0062(b)
  0x00,0x40,0x40,0x40,0x5C,0x66,0x42,0x42,0x42,0x44,0x78,0x00,0x00,0x00,
  //U+0063(c)
  0x00,0x00,0x00,0x00,0x3C,0x20,0x40,0x40,0x40,0x60,0x3C,0x00,0x00,0x00,
  //U+0064(d)
  0x00,0x02,0x02,0x02,0x1E,0x22,0x42,0x42,0x42,0x66,0x3A,0x00,0x00,0x00,
  //U+0065(e)
  0x00,0x00,0x00,0x00,0x3C,0x66,0x42,0x7E,0x40,0x60,0x3E,0x00,0x00,0x00,
  //U+0066(f)
  0x00,0x0E,0x10,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
  //U+0067(g)
  0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x44,0x78,0x40,0x7C,0x42,0x42,0x3C,
  //U+0068(h)
  0x00,0x40,0x40,0x40,0x58,0x64,0x44,0x44,0x44,0x44,0x44,0x00,0x00,0x00,
  //U+0069(i)
  0x00,0x30,0x30,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7E,0x00,0x00,0x00,
  //U+006A(j)
  0x00,0x0C,0x0C,0x00,0x7C,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x0C,0x78,
  //U+006B(k)
  0x00,0x40,0x40,0x40,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0x00,0x00,0x00,
  //U+006C(l)
  0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7E,0x00,0x00,0x00,
  //U+006D(m)
  0x00,0x00,0x00,0x00,0xFE,0xDA,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00,
  //U+006E(n)
  0x00,0x00,0x00,0x00,0x58,0x64,0x44,0x44,0x44,0x44,0x44,0x00,0x00,0x00,
  //U+006F(o)
  0x00,0x00,0x00,0x00,0x3C,0x66,0x42,0x42,0x42,0x66,0x3C,0x00,0x00,0x00,
  //U+0070(p)
  0x00,0x00,0x00,0x00,0x5C,0x66,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,
  //U+0071(q)
  0x00,0x00,0x00,0x00,0x1E,0x22,0x42,0x42,0x42,0x66,0x3A,0x02,0x02,0x02,
  //U+0072(r)
  0x00,0x00,0x00,0x00,0x58,0x64,0x44,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
  //U+0073(s)
  0x00,0x00,0x00,0x00,0x3C,0x40,0x40,0x38,0x04,0x04,0x78,0x00,0x00,0x00,
  //U+0074(t)
  0x00,0x00,0x20,0x20,0xFC,0x20,0x20,0x20,0x20,0x20,0x1C,0x00,0x00,0x00,
  //U+0075(u)
  0x00,0x00,0x00,0x00,0x44,0x44,0x44,0x44,0x44,0x4C,0x34,0x00,0x00,0x00,
  //U+0076(v)
  0x00,0x00,0x00,0x00,0x22,0x22,0x32,0x14,0x14,0x14,0x08,0x00,0x00,0x00,
  //U+0077(w)
  0x00,0x00,0x00,0x00,0x82,0x82,0x92,0xAA,0xAA,0xAA,0x44,0x00,0x00,0x00,
  //U+0078(x)
  0x00,0x00,0x00,0x00,0x66,0x24,0x18,0x18,0x24,0x66,0xC3,0x00,0x00,0x00,
  //U+0079(y)
  0x00,0x00,0x00,0x00,0x22,0x22,0x36,0x14,0x14,0x14,0x08,0x08,0x10,0x70,
  //U+007A(z)
  0x00,0x00,0x00,0x00,0x7C,0x08,0x08,0x10,0x20,0x20,0x7C,0x00,0x00,0x00,
  //U+007B({)
  0x00,0x0C,0x10,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0x10,0x0C,
  //U+007C(|)
  0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
  //U+007D(})
  0x00,0x30,0x08,0x08,0x08,0x08,0x08,0x06,0x08,0x08,0x08,0x08,0x08,0x30,
  //U+007E(~)
  0x00,0x00,0x00,0x00,0x00,0x00,0x62,0x92,0x8C,0x00,0x00,0x00,0x00,0x00,
  //U+007F()
  0x00,0xE0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xA0,0xE0,0x00,0x00,0x00,
};

const lcd_font_t lcd_font_consolas_16_8x14 = {
  .width        = 8,
  .height       = 14,
  .bytePerChar  = 14,
  .byte         = sizeof(lcd_fontData_consolas_16_8x14),
  .charStart    = 0x0020,
  .charEnd      = 0x007F,
  .pData       = lcd_fontData_consolas_16_8x14,
};

/* END OF FILE */