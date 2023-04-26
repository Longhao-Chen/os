#include <graph.hpp>
#include <asm.h>
using namespace GraphSpace;

Graph::Graph(int x, int y, char color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}

void Graph::setColor(char color){
	this->color = color;
}

void Graph::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

Rectangle::Rectangle(int x, int y, int w, int h, char color)
	: Graph(x, y, color)
{
	this->h = h;
	this->w = w;
}

void Rectangle::render()
{
	for (int i = y; i < y + h; ++i)
		for (int j = x; j < x + w; ++j)
			put_color(color, i * 320 + j);
}

Square::Square(int x, int y, int w, char color)
	: Rectangle(x, y, w, w, color)
{
}

Group::Group(int x, int y)
	: Graph(x, y, 0x00)
{
}

Group &Group::operator<<(Graph &in)
{
	for (int i = 0; i < 10; ++i) {
		if (g[i].graph == nullptr) {
			g[i].graph = &in;
			g[i].dx = in.x - x;
			g[i].dy = in.y - y;
			in.id = i;
			return *this;
		}
	}
	return *this;
}

Group &Group::operator<<(Group &in){
	for(int i=0; i<10; ++i){
		if(in.g[i].graph != nullptr){
			this->operator<<(in>>i);
		}
	}
	return *this;
}

Graph &Group::operator>>(int id)
{
	auto tmp = g[id].graph;
	g[id].graph = nullptr;
	return *tmp;
}

void Group::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	for (int i = 0; i < 10; ++i) {
		if (g[i].graph != nullptr) {
			g[i].graph->setPosition(x + g[i].dx, y + g[i].dy);
		}
	}
}

void Group::render()
{
	for (int i = 0; i < 10; ++i) {
		if (g[i].graph != nullptr)
			g[i].graph->render();
	}
}

int Group::getFree()
{
	int res = 0;
	for (int i = 0; i < 10; ++i) {
		if (g[i].graph == nullptr)
			res++;
	}
	return res;
}