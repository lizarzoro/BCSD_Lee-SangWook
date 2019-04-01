#pragma once

typedef struct _tagResolution
{
	unsigned int iW = 1280;
	unsigned int iH = 720; // ÇØ»óµµ

	_tagResolution() :
		iW(0), iH(0) {}

	_tagResolution(int x, int y) :
		iW(x), iH(y) {}
}RESOLUTION, *PRESOLUTION;