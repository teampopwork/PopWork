// This file is included by SWTri.cpp and should not be built directly by the project.

int aType = (blend ? 1 : 0) | (global_argb ? 2 : 0) | (mod_argb ? 4 : 0) | (talpha ? 8 : 0) | (textured ? 16 : 0);
switch (thePixelFormat)
{
case 0x8888:
	aType |= 0 << 5;
	break;
case 0x888:
	aType |= 1 << 5;
	break;
case 0x565:
	aType |= 2 << 5;
	break;
case 0x555:
	aType |= 3 << 5;
	break;
}

switch (aType)
{
case 0:
	DrawTriangle_8888_TEX0_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 1:
	DrawTriangle_8888_TEX0_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 2:
	DrawTriangle_8888_TEX0_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 3:
	DrawTriangle_8888_TEX0_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 4:
	DrawTriangle_8888_TEX0_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 5:
	DrawTriangle_8888_TEX0_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 6:
	DrawTriangle_8888_TEX0_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 7:
	DrawTriangle_8888_TEX0_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 8:
	DrawTriangle_8888_TEX0_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 9:
	DrawTriangle_8888_TEX0_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 10:
	DrawTriangle_8888_TEX0_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 11:
	DrawTriangle_8888_TEX0_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 12:
	DrawTriangle_8888_TEX0_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 13:
	DrawTriangle_8888_TEX0_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 14:
	DrawTriangle_8888_TEX0_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 15:
	DrawTriangle_8888_TEX0_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 16:
	DrawTriangle_8888_TEX1_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 17:
	DrawTriangle_8888_TEX1_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 18:
	DrawTriangle_8888_TEX1_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 19:
	DrawTriangle_8888_TEX1_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 20:
	DrawTriangle_8888_TEX1_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 21:
	DrawTriangle_8888_TEX1_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 22:
	DrawTriangle_8888_TEX1_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 23:
	DrawTriangle_8888_TEX1_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 24:
	DrawTriangle_8888_TEX1_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 25:
	DrawTriangle_8888_TEX1_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 26:
	DrawTriangle_8888_TEX1_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 27:
	DrawTriangle_8888_TEX1_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 28:
	DrawTriangle_8888_TEX1_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 29:
	DrawTriangle_8888_TEX1_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 30:
	DrawTriangle_8888_TEX1_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 31:
	DrawTriangle_8888_TEX1_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 32:
	DrawTriangle_0888_TEX0_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 33:
	DrawTriangle_0888_TEX0_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 34:
	DrawTriangle_0888_TEX0_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 35:
	DrawTriangle_0888_TEX0_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 36:
	DrawTriangle_0888_TEX0_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 37:
	DrawTriangle_0888_TEX0_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 38:
	DrawTriangle_0888_TEX0_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 39:
	DrawTriangle_0888_TEX0_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 40:
	DrawTriangle_0888_TEX0_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 41:
	DrawTriangle_0888_TEX0_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 42:
	DrawTriangle_0888_TEX0_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 43:
	DrawTriangle_0888_TEX0_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 44:
	DrawTriangle_0888_TEX0_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 45:
	DrawTriangle_0888_TEX0_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 46:
	DrawTriangle_0888_TEX0_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 47:
	DrawTriangle_0888_TEX0_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 48:
	DrawTriangle_0888_TEX1_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 49:
	DrawTriangle_0888_TEX1_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 50:
	DrawTriangle_0888_TEX1_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 51:
	DrawTriangle_0888_TEX1_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 52:
	DrawTriangle_0888_TEX1_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 53:
	DrawTriangle_0888_TEX1_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 54:
	DrawTriangle_0888_TEX1_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 55:
	DrawTriangle_0888_TEX1_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 56:
	DrawTriangle_0888_TEX1_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 57:
	DrawTriangle_0888_TEX1_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 58:
	DrawTriangle_0888_TEX1_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 59:
	DrawTriangle_0888_TEX1_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 60:
	DrawTriangle_0888_TEX1_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 61:
	DrawTriangle_0888_TEX1_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 62:
	DrawTriangle_0888_TEX1_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 63:
	DrawTriangle_0888_TEX1_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 64:
	DrawTriangle_0565_TEX0_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 65:
	DrawTriangle_0565_TEX0_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 66:
	DrawTriangle_0565_TEX0_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 67:
	DrawTriangle_0565_TEX0_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 68:
	DrawTriangle_0565_TEX0_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 69:
	DrawTriangle_0565_TEX0_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 70:
	DrawTriangle_0565_TEX0_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 71:
	DrawTriangle_0565_TEX0_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 72:
	DrawTriangle_0565_TEX0_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 73:
	DrawTriangle_0565_TEX0_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 74:
	DrawTriangle_0565_TEX0_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 75:
	DrawTriangle_0565_TEX0_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 76:
	DrawTriangle_0565_TEX0_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 77:
	DrawTriangle_0565_TEX0_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 78:
	DrawTriangle_0565_TEX0_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 79:
	DrawTriangle_0565_TEX0_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 80:
	DrawTriangle_0565_TEX1_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 81:
	DrawTriangle_0565_TEX1_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 82:
	DrawTriangle_0565_TEX1_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 83:
	DrawTriangle_0565_TEX1_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 84:
	DrawTriangle_0565_TEX1_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 85:
	DrawTriangle_0565_TEX1_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 86:
	DrawTriangle_0565_TEX1_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 87:
	DrawTriangle_0565_TEX1_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 88:
	DrawTriangle_0565_TEX1_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 89:
	DrawTriangle_0565_TEX1_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 90:
	DrawTriangle_0565_TEX1_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 91:
	DrawTriangle_0565_TEX1_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 92:
	DrawTriangle_0565_TEX1_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 93:
	DrawTriangle_0565_TEX1_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 94:
	DrawTriangle_0565_TEX1_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 95:
	DrawTriangle_0565_TEX1_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 96:
	DrawTriangle_0555_TEX0_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 97:
	DrawTriangle_0555_TEX0_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 98:
	DrawTriangle_0555_TEX0_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 99:
	DrawTriangle_0555_TEX0_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 100:
	DrawTriangle_0555_TEX0_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 101:
	DrawTriangle_0555_TEX0_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 102:
	DrawTriangle_0555_TEX0_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 103:
	DrawTriangle_0555_TEX0_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 104:
	DrawTriangle_0555_TEX0_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 105:
	DrawTriangle_0555_TEX0_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 106:
	DrawTriangle_0555_TEX0_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 107:
	DrawTriangle_0555_TEX0_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 108:
	DrawTriangle_0555_TEX0_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 109:
	DrawTriangle_0555_TEX0_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 110:
	DrawTriangle_0555_TEX0_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 111:
	DrawTriangle_0555_TEX0_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 112:
	DrawTriangle_0555_TEX1_TALPHA0_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 113:
	DrawTriangle_0555_TEX1_TALPHA0_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 114:
	DrawTriangle_0555_TEX1_TALPHA0_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 115:
	DrawTriangle_0555_TEX1_TALPHA0_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 116:
	DrawTriangle_0555_TEX1_TALPHA0_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 117:
	DrawTriangle_0555_TEX1_TALPHA0_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 118:
	DrawTriangle_0555_TEX1_TALPHA0_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 119:
	DrawTriangle_0555_TEX1_TALPHA0_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 120:
	DrawTriangle_0555_TEX1_TALPHA1_MOD0_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 121:
	DrawTriangle_0555_TEX1_TALPHA1_MOD0_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 122:
	DrawTriangle_0555_TEX1_TALPHA1_MOD0_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 123:
	DrawTriangle_0555_TEX1_TALPHA1_MOD0_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 124:
	DrawTriangle_0555_TEX1_TALPHA1_MOD1_GLOB0_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 125:
	DrawTriangle_0555_TEX1_TALPHA1_MOD1_GLOB0_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 126:
	DrawTriangle_0555_TEX1_TALPHA1_MOD1_GLOB1_BLEND0(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
case 127:
	DrawTriangle_0555_TEX1_TALPHA1_MOD1_GLOB1_BLEND1(pVerts, pFrameBuffer, bytepitch, textureInfo, globalDiffuse);
	break;
}
