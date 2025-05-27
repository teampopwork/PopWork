#include "board.hpp"

#include "PopWork/graphics/graphics.hpp"
#include "PopWork/graphics/color.hpp"
#include "PopWork/math/point.hpp"

using namespace PopWork;

Board::Board(GameApp *theApp)
{
	mApp = theApp;
}

Board::~Board()
{
}

void Board::Update()
{
	Widget::Update();

	// put your update loop code in here

	MarkDirty();
}

void Board::Draw(Graphics *g)
{
	g->SetColor(Color(0, 0, 0));		// 0,0,0 = black, simple RGB
	g->FillRect(0, 0, mWidth, mHeight); // fill the screen

	// put your draw code in here
}