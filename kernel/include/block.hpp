#ifndef _BLOCK_HPP
#define _BLOCK_HPP
#include <graph.hpp>

namespace BlockSpace
{
class Block : public GraphSpace::Graph {
    public:
	GraphSpace::Square g[4] = { GraphSpace::Square(0, 0, 10, 0x00),
				    GraphSpace::Square(0, 0, 10, 0x00),
				    GraphSpace::Square(0, 0, 10, 0x00),
				    GraphSpace::Square(0, 0, 10, 0x00) };
	// 方块状态，乘90度为逆时针旋转的角度
	char status = 0;
	Block(int x, int y, char color);
    // 向上一格
    void up();
	// 下降一格
	void down();
    // 向左一格
    void left();
    // 向右一格
    void right();
	// 判断是否触底，如果触底，返回false
	virtual bool noend() = 0;

	// 左旋
	void RL();
	// 右旋
	void RR();

	virtual void render();
};

// I形方块
class I : public Block {
    public:
    I(char color);
	I(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

// Z形方块
class Z : public Block {
    public:
    Z(char color);
	Z(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

// S形方块
class S : public Block {
    public:
    S(char color);
	S(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

// L
class L : public Block {
    public:
    L(char color);
	L(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

class O : public Block {
    public:
    O(char color);
	O(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

class T : public Block {
    public:
    T(char color);
	T(int x, int y, char color);
	virtual bool noend();
	virtual void setPosition(int x, int y);
};

};

#endif