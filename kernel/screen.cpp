#include <screen.hpp>
#include <asm.h>
using namespace GraphSpace;

Screen::Screen()
{
	clean();
}

void Screen::clean()
{
	for (int i = 0; i < 320 * 200; ++i)
		put_color(bg_color, i);
}
Screen &Screen::operator<<(Graph &in)
{
	for (int i = 0; i < 60; ++i) {
		if (g[i] == nullptr) {
			g[i] = &in;
			in.id = i;
			return *this;
		}
	}
	// 如果满了，则无法附加图形，可以通过图形组来实现
	return *this;
}

Graph &Screen::operator>>(int id)
{
	auto tmp = g[id];
	g[id] = nullptr;
	return *tmp;
}

void Screen::render()
{
	clean();
	for (int i = 0; i < 60; ++i) {
		if (g[i] != nullptr) {
			g[i]->render();
		}
	}
}

int Screen::getFree()
{
	int res = 0;
	for (int i = 0; i < 60; ++i) {
		if (g[i] == nullptr)
			res++;
	}
	return res;
}