#pragma once
class VECTOR2
{
public:

	int x,
		y;
	//‘ã“ü‰‰Zq
	VECTOR2& operator = (const VECTOR2& vec);

	//”äŠr‰‰Zq
	bool operator == (const VECTOR2& vec) const;
	bool operator == (const int& i) const;
	bool operator != (const VECTOR2& vec) const;
	bool operator != (const int& i) const;

	//’P€‰‰Zq
	VECTOR2& operator += (const VECTOR2& vec);
	VECTOR2& operator -= (const VECTOR2& vec);
	VECTOR2& operator *= (int i);
	VECTOR2& operator /= (int i);

	VECTOR2 operator + () const;
	VECTOR2 operator - () const;

	//“Y‚¦š‰‰Zq
	int& operator [] (int i);

	VECTOR2();
	VECTOR2(int x, int y);
	~VECTOR2();
};


//ƒxƒNƒgƒ‹‚Ì‰‰Z
//VECTOR2+VECTOR2

VECTOR2 operator+(const VECTOR2 vec1, const int x);
VECTOR2 operator+(const VECTOR2 vec1, const VECTOR2 vec2);

VECTOR2 operator-(const VECTOR2 vec1, const int x);
VECTOR2 operator-(const VECTOR2 vec1, const VECTOR2 vec2);

// int * VECTOR2
VECTOR2 operator*(int i, const VECTOR2 vec);
//Vector3D * int
VECTOR2 operator*(const VECTOR2 vec, int i);
//Vector3D / int
VECTOR2 operator/(const VECTOR2 vec, int i);

VECTOR2 operator%(const VECTOR2 vec, int i);
