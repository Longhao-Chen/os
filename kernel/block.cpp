#include <graph.hpp>
#include <block.hpp>
#include <asm.h>

using namespace BlockSpace;

Block::Block(int x, int y, char color)
	: Graph(x, y, color)
{
	for (int i = 0; i < 4; ++i)
		g[i].setColor(color);
	this->setPosition(x, y);
}

void Block::up(){
	this->setPosition(this->x, this->y - 10);
}

void Block::down()
{
	if(this->noend())
		this->setPosition(this->x, this->y + 10);
}

void Block::left(){
	if(this->noend())
		this->setPosition(this->x-10, y);
}

void Block::right(){
	if(this->noend())
		this->setPosition(this->x+10, y);
}

void Block::RL()
{
	if(!this->noend())
		return;
	status++;
	if (status == 4)
		status = 0;
	this->setPosition(x, y);
}

void Block::RR()
{
	if(!this->noend())
		return;
	status--;
	if (status == -1)
		status = 3;
	this->setPosition(x, y);
}

void Block::render()
{
	for (int i = 0; i < 4; ++i) {
		g[i].render();
	}
}

I::I(char color)
	: I(160, -100, color)
{
}

I::I(int x, int y, char color)
	: Block(x, y, color)
{
}

bool I::noend()
{
	switch (status) {
	case 0:
		if (y + 45 > 200)
			return false;
		return get_color(x + 5, y + 45) == bg_color;
	case 1:
		if (y + 5 > 200)
			return false;
		for (int i = 0; i < 4; ++i) {
			if (get_color(x + 10 * i + 5, y + 15) != bg_color)
				return false;
		}
		return true;
	case 2:
		if (y + 5 > 200)
			return false;
		return get_color(x + 5, y + 5) == bg_color;
	case 3:
		if (y + 15 > 200)
			return false;
		for (int i = 0; i < 4; ++i) {
			if (get_color(x - 10 * i - 5, y + 15) != bg_color)
				return false;
		}
		return true;
	}
	return false;
}

void I::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	if (status == 0) {
		g[0].setPosition(x, y);
		g[1].setPosition(x, y + 10);
		g[2].setPosition(x, y + 20);
		g[3].setPosition(x, y + 30);
	} else if (status == 1) {
		g[0].setPosition(x, y - 10);
		g[1].setPosition(x + 10, y - 10);
		g[2].setPosition(x + 20, y - 10);
		g[3].setPosition(x + 30, y - 10);
	} else if (status == 2) {
		g[0].setPosition(x - 10, y - 10);
		g[1].setPosition(x - 10, y - 20);
		g[2].setPosition(x - 10, y - 30);
		g[3].setPosition(x - 10, y - 40);
	} else if (status == 3) {
		g[0].setPosition(x - 10, y);
		g[1].setPosition(x - 20, y);
		g[2].setPosition(x - 30, y);
		g[3].setPosition(x - 40, y);
	}
}

Z::Z(char color)
	: Z(160, -100, color)
{
}

Z::Z(int x, int y, char color)
	: Block(x, y, color)
{
}

bool Z::noend()
{
	switch (status) {
	case 0:
		if (y + 25 > 200)
			return false;
		if (get_color(x + 5, y + 15) != bg_color)
			return false;
		if (get_color(x + 15, y + 25) != bg_color ||
		    get_color(x + 25, y + 25) != bg_color)
			return false;
		return true;
	case 1:
		if (y + 5 > 200)
			return false;
		if (get_color(x + 5, y + 5) != bg_color)
			return false;
		if (get_color(x + 15, y - 5) != bg_color)
			return false;
		return true;
	case 2:
		if (y + 5 > 200)
			return false;
		if (get_color(x - 5, y + 5) != bg_color)
			return false;
		if (get_color(x - 15, y + 5) != bg_color)
			return false;
		if (get_color(x - 25, y - 5) != bg_color)
			return false;
		return true;
	case 3:
		if (y + 35 > 200)
			return false;
		if (get_color(x - 5, y + 25) != bg_color)
			return false;
		if (get_color(x - 15, y + 35) != bg_color)
			return false;
		return true;
	}
	return false;
}

void Z::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	switch (status) {
	case 0:
		g[0].setPosition(x, y);
		g[1].setPosition(x + 10, y);
		g[2].setPosition(x + 10, y + 10);
		g[3].setPosition(x + 20, y + 10);
		break;
	case 1:
		g[0].setPosition(x, y - 10);
		g[1].setPosition(x, y - 20);
		g[2].setPosition(x + 10, y - 20);
		g[3].setPosition(x + 10, y - 30);
		break;
	case 2:
		g[0].setPosition(x - 10, y - 10);
		g[1].setPosition(x - 20, y - 10);
		g[2].setPosition(x - 20, y - 20);
		g[3].setPosition(x - 30, y - 20);
		break;
	case 3:
		g[0].setPosition(x - 10, y);
		g[1].setPosition(x - 10, y + 10);
		g[2].setPosition(x - 20, y + 10);
		g[3].setPosition(x - 20, y + 20);
		break;
	}
}

S::S(char color)
	: S(160, -100, color)
{
}

S::S(int x, int y, char color)
	: Block(x, y, color)
{
}

bool S::noend()
{
	switch (status) {
	case 0:
		if (y + 25 > 200)
			return false;
		if (get_color(x + 5, y + 25) != bg_color)
			return false;
		if (get_color(x + 15, y + 25) != bg_color)
			return false;
		if (get_color(x + 25, y + 15) != bg_color)
			return false;
		return true;
	case 1:
		if (y + 5 > 200)
			return false;
		if (get_color(x + 15, y + 5) != bg_color)
			return false;
		if (get_color(x + 5, y - 5) != bg_color)
			return false;
		return true;
	case 2:
		if (y + 5 > 200)
			return false;
		if (get_color(x - 5, y - 5) != bg_color)
			return false;
		if (get_color(x - 15, y + 5) != bg_color ||
		    get_color(x - 25, y + 5) != bg_color)
			return false;
		return true;
	case 3:
		if (y + 35 > 200)
			return false;
		if (get_color(x - 15, y + 25) != bg_color)
			return false;
		if (get_color(x - 5, y + 35) != bg_color)
			return false;
		return true;
	}
	return false;
}

void S::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	switch (status) {
	case 0:
		g[0].setPosition(x, y + 10);
		g[1].setPosition(x + 10, y + 10);
		g[2].setPosition(x + 10, y);
		g[3].setPosition(x + 20, y);
		break;
	case 1:
		g[0].setPosition(x + 10, y - 10);
		g[1].setPosition(x + 10, y - 20);
		g[2].setPosition(x, y - 20);
		g[3].setPosition(x, y - 30);
		break;
	case 2:
		g[0].setPosition(x - 10, y - 20);
		g[1].setPosition(x - 20, y - 20);
		g[2].setPosition(x - 20, y - 10);
		g[3].setPosition(x - 30, y - 10);
		break;
	case 3:
		g[0].setPosition(x - 20, y);
		g[1].setPosition(x - 20, y + 10);
		g[2].setPosition(x - 10, y + 10);
		g[3].setPosition(x - 10, y + 20);
		break;
	}
}

L::L(char color)
	: L(160, -100, color)
{
}

L::L(int x, int y, char color)
	: Block(x, y, color)
{
}

bool L::noend()
{
	switch (status) {
	case 0:
		if (y + 35 > 200)
			return false;
		if (get_color(x + 5, y + 35) != bg_color)
			return false;
		if (get_color(x + 15, y + 35) != bg_color)
			return false;
		return true;
	case 1:
		if (y + 5 > 200)
			return false;
		if (get_color(x + 5, y + 5) != bg_color ||
		    get_color(x + 15, y + 5) != bg_color ||
		    get_color(x + 25, y + 5) != bg_color)
			return false;
		return true;
	case 2:
		if (y + 5 > 200)
			return false;
		if (get_color(x - 5, y + 5) != bg_color)
			return false;
		if (get_color(x - 15, y - 15) != bg_color)
			return false;
		return true;
	case 3:
		if (y + 15 > 200)
			return false;
		if (get_color(x - 5, y + 15) != bg_color ||
		    get_color(x - 15, y + 15) != bg_color)
			return false;
		if (get_color(x - 25, y + 25) != bg_color)
			return false;
		return true;
	}
	return false;
}

void L::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	switch (status) {
	case 0:
		g[0].setPosition(x, y);
		g[1].setPosition(x, y + 10);
		g[2].setPosition(x, y + 20);
		g[3].setPosition(x + 10, y + 20);
		break;
	case 1:
		g[0].setPosition(x, y - 10);
		g[1].setPosition(x + 10, y - 10);
		g[2].setPosition(x + 20, y - 10);
		g[3].setPosition(x + 20, y - 20);
		break;
	case 2:
		g[0].setPosition(x - 10, y - 10);
		g[1].setPosition(x - 10, y - 20);
		g[2].setPosition(x - 10, y - 30);
		g[3].setPosition(x - 20, y - 30);
		break;
	case 3:
		g[0].setPosition(x - 10, y);
		g[1].setPosition(x - 20, y);
		g[2].setPosition(x - 30, y);
		g[3].setPosition(x - 30, y + 10);
		break;
	}
}

O::O(char color)
	: O(160, -100, color)
{
}

O::O(int x, int y, char color)
	: Block(x, y, color)
{
}

bool O::noend()
{
	if (y + 25 > 200)
		return false;
	if (get_color(x + 5, y + 25) != bg_color ||
	    get_color(x + 15, y + 25) != bg_color)
		return false;
	return true;
}

void O::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	g[0].setPosition(x, y);
	g[1].setPosition(x + 10, y);
	g[2].setPosition(x, y + 10);
	g[3].setPosition(x + 10, y + 10);
}

T::T(char color)
	: T(160, -100, color)
{
}

T::T(int x, int y, char color)
	: Block(x, y, color)
{
}

bool T::noend()
{
	switch (status) {
	case 0:
		if (y + 25 > 200)
			return false;
		if (get_color(x + 5, y + 15) != bg_color ||
		    get_color(x + 15, y + 25) != bg_color ||
		    get_color(x + 25, y + 15) != bg_color)
			return false;
		return true;
	case 1:
		if (y + 5 > 200)
			return false;
		if (get_color(x + 5, y + 5) != bg_color ||
		    get_color(x + 15, y - 5) != bg_color)
			return false;
		return true;
	case 2:
		if (y + 5 > 200)
			return false;
		if (get_color(x - 5, y + 5) != bg_color ||
		    get_color(x - 15, y + 5) != bg_color ||
		    get_color(x - 25, y + 5) != bg_color)
			return false;
		return true;
	case 3:
		if (y + 35 > 200)
			return false;
		if (get_color(x - 5, y + 35) != bg_color ||
		    get_color(x - 15, y + 25) != bg_color)
			return false;
		return true;
	}
	return false;
}

void T::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	switch (status) {
	case 0:
		g[0].setPosition(x, y);
		g[1].setPosition(x + 10, y);
		g[2].setPosition(x + 20, y);
		g[3].setPosition(x + 10, y + 10);
		break;
	case 1:
		g[0].setPosition(x, y - 10);
		g[1].setPosition(x, y - 20);
		g[2].setPosition(x, y - 30);
		g[3].setPosition(x + 10, y - 20);
		break;
	case 2:
		g[0].setPosition(x - 10, y - 10);
		g[1].setPosition(x - 20, y - 10);
		g[2].setPosition(x - 30, y - 10);
		g[3].setPosition(x - 20, y - 20);
		break;
	case 3:
		g[0].setPosition(x - 10, y);
		g[1].setPosition(x - 10, y + 10);
		g[2].setPosition(x - 10, y + 20);
		g[3].setPosition(x - 20, y + 10);
		break;
	}
}