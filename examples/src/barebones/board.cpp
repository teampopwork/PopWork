#include "board.hpp"

#include "PopLib/graphics/graphics.hpp"
#include "PopLib/graphics/color.hpp"
#include "PopLib/math/point.hpp"

using namespace PopLib;

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