#ifndef _GRAPH_HPP
#define _GRAPH_HPP
namespace GraphSpace
{
class Graph {
    public:
	// 左上点坐标
	int x;
	int y;
	char color;
	int id; // 图形id
	Graph(int x, int y, char color);
	void setColor(char color);
	virtual void setPosition(int x, int y);
	virtual void render() = 0;
};

class Rectangle : public Graph {
    private:
	int w;
	int h;

    public:
	// 左上点坐标和宽度、高度
	Rectangle(int x, int y, int w, int h, char color);
	virtual void render();
};

class Square : public Rectangle {
    public:
	Square(int x, int y, int w, char color);
};

class Group: public Graph{
	struct graphNode
	{
		graphNode(){
			this->graph = nullptr;
		};
		Graph *graph;
		int dx;	// 图形坐标-图形组坐标
		int dy;
	};
	
    private:
	graphNode g[10];

    public:
	Group(int x, int y);
	Group &operator<<(Graph &in);
	Group &operator<<(Group &in);
	Graph &operator>>(int id);
	virtual void setPosition(int x, int y);
	virtual void render();
	// 获取剩余空间
	int getFree();
};
};

#endif