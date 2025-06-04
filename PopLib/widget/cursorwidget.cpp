#include "cursorwidget.hpp"
#include "graphics/image.hpp"

using namespace PopLib;

CursorWidget::CursorWidget()
{
	mImage = NULL;
	mMouseVisible = false;
}

void CursorWidget::Draw(Graphics *g)
{
	if (mImage)
		g->DrawImage(mImage, 0, 0);
}

void CursorWidget::SetImage(Image *theImage)
{
	mImage = theImage;
	if (mImage)
		Resize(mX, mY, theImage->mWidth, theImage->mHeight);
}

Point CursorWidget::GetHotspot()
{
	if (mImage == NULL)
		return Point(0, 0);
	return Point(mImage->GetWidth() / 2, mImage->GetHeight() / 2);
}
