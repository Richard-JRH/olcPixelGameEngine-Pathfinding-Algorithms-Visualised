#ifndef _VECTOR_2_H
#define _VECTOR_2_H

class Vector2
{
public:
	int x;
	int y;
public:
	Vector2();
	Vector2(int _val);
	Vector2(int _x, int _y);
	~Vector2();

	void SetXY(int _x, int _y);

	Vector2 UpLeft()   const;
	Vector2 Up()	   const;
	Vector2 UpRight()  const;
	Vector2 Right()	   const;
	Vector2 BotRight() const;
	Vector2 Down()	   const;
	Vector2 BotLeft()  const;
	Vector2 Left()	   const;
	Vector2 Zero()	   const;

	Vector2 operator+(const Vector2 &rhs) const;
};

#endif

