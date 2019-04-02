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

typedef struct _tagPosition
{
	float	x, y;

	_tagPosition(float _x = 0.f, float _y = 0.f) :
		x(_x), y(_y)
	{
	}

	_tagPosition(const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	_tagPosition(const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	void operator = (const _tagPosition& pos)
	{
		x = pos.x;
		y = pos.y;
	}

	void operator = (const POINT& pt)
	{
		x = pt.x;
		y = pt.y;
	}

	void operator = (float f[2])
	{
		x = f[0];
		y = f[1];
	}

	// + operators
	_tagPosition operator + (const _tagPosition& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (const POINT& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (float f[2])	const
	{
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}

	_tagPosition operator + (float f)	const
	{
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	void operator += (const _tagPosition& pos)
	{
		x += pos.x;
		y += pos.y;
	}

	// - operators
	_tagPosition operator - (const _tagPosition& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator - (const POINT& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}
	_tagPosition operator - (float f[2])	const
	{
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator - (float f)	const
	{
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	void operator -= (const _tagPosition& pos)
	{
		x -= pos.x;
		y -= pos.y;
	}

	// * operators
	_tagPosition operator * (const _tagPosition& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (const POINT& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (float f[2])	const
	{
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator * (float f)	const
	{
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}

	// / operators
	_tagPosition operator / (const _tagPosition& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (const POINT& pos)	const
	{
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (float f[2])	const
	{
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator / (float f)	const
	{
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}

}POSITION, *pPOSITION, _SIZE, *_pSIZE;