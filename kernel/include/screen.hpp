#ifndef _SCREEN_HPP
#define _SCREEN_HPP
#include <graph.hpp>
class Screen {
    private:
	// 指向图形的指针
	GraphSpace::Graph *g[60] = { nullptr };

    public:
	Screen();

    void clean();

	// 将图形附加到屏幕
	Screen &operator<<(GraphSpace::Graph &in);

    // 删除图形
    GraphSpace::Graph &operator>>(int id);
    void render();
    int getFree();
};
#endif