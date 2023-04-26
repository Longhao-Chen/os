#include <tetris.hpp>
#include <graph.hpp>
#include <block.hpp>
#include <screen.hpp>
#include <timer.hpp>
#include <keyboard.hpp>

using namespace TetrisSpace;

const int BlockArraySize = 10;
const float sleepTime = 0.5;

static BlockSpace::Block *curr;
static Screen *scr;

static void kup(){
    curr->up();
    scr->render();
}

static void kdown(){
    curr->down();
    scr->render();
}

static void kleft(){
    curr->left();
    scr->render();
}

static void kright(){
    curr->right();
    scr->render();
}

static void kL(){
    curr->RL();
    scr->render();
}

static void kR(){
    curr->RR();
    scr->render();
}

void TetrisSpace::runTetris()
{
	Screen screen;
    scr = &screen;
	BlockSpace::I Bi[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };
	BlockSpace::Z Bz[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };
	BlockSpace::S Bs[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };
	BlockSpace::L Bl[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };
	BlockSpace::O Bo[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };
	BlockSpace::T Bt[BlockArraySize] = { 0x1, 0x2, 0x3, 0x4, 0x5,
					     0x6, 0x7, 0x9, 0x1, 0x2 };

	// 指向方块数组中当前可用的方块
	char iBi = 0, iBz = 0, iBs = 0, iBl = 0, iBo = 0, iBt = 0;

    // 设置键盘
    setKeyFun(0, kup);
    setKeyFun(1, kdown);
    setKeyFun(2, kleft);
    setKeyFun(3, kright);
    setKeyFun(4, kL);
    setKeyFun(5, kR);
	while (iBt < 10) {
		Bi[iBi].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bi[iBi];
		screen.render();
        curr = &Bi[iBi];
		while (Bi[iBi].noend()) {
			sleep(sleepTime);

            Bi[iBi].down();
			screen.render();
		}
		iBi++;

		Bz[iBz].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bz[iBz];
		screen.render();
        curr = &Bz[iBz];
		while (Bz[iBz].noend()) {
			sleep(sleepTime);

            Bz[iBz].down();
			screen.render();
		}
		iBz++;

		Bs[iBs].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bs[iBs];
		screen.render();
        curr = &Bs[iBs];
		while (Bs[iBs].noend()) {
			sleep(sleepTime);

            Bs[iBs].down();
			screen.render();
		}
		iBs++;

		Bl[iBl].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bl[iBl];
		screen.render();
        curr = &Bl[iBl];
		while (Bl[iBl].noend()) {
			sleep(sleepTime);

            Bl[iBl].down();
			screen.render();
		}
		iBl++;

		Bo[iBo].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bo[iBo];
		screen.render();
        curr = &Bo[iBo];
		while (Bo[iBo].noend()) {
			sleep(sleepTime);

            Bo[iBo].down();
			screen.render();
		}
		iBo++;

		Bt[iBt].setPosition(10 * (get_time() % 10) + 110, 0);
		screen << Bt[iBt];
		screen.render();
        curr = &Bt[iBt];
		while (Bt[iBt].noend()) {
			sleep(sleepTime);

            Bt[iBt].down();
			screen.render();
		}
		iBt++;
	}
}