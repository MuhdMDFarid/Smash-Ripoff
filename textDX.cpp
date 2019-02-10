//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "textDX.h"

//=============================================================================
// Default Constructor
//=============================================================================
TextDX::TextDX()
{
    color = SETCOLOR_ARGB(255,255,255,255); // default to white font

    // set font position
    fontRect.top = 0;
    fontRect.left = 0;
    fontRect.right = GAME_WIDTH;
    fontRect.bottom = GAME_HEIGHT;
    dxFont = NULL;
    angle  = 0;
}

//=============================================================================
// Destructor
//=============================================================================
TextDX::~TextDX()
{
    SAFE_RELEASE(dxFont);
}

//=============================================================================
// Create DirectX Font
//=============================================================================
bool TextDX::initialize(Graphics *g, int height, bool bold, bool italic, 
                        const std::string &fontName)
{
    graphics = g;                   // the graphics system

    UINT weight = FW_NORMAL;
    if(bold)
        weight = FW_BOLD;

    // create DirectX font
    if(FAILED(D3DXCreateFont(graphics->get3Ddevice(), height, 0, weight, 1, italic,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE, fontName.c_str(),
        &dxFont))) return false;

    // Create the tranformation matrix
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, 0.0f, NULL);

    return true;
}

//=============================================================================
// Print text at x,y 
// Return 0 on fail, height of text on success
// pre: spriteBegin()
// post: spriteEnd()
//=============================================================================
int TextDX::print(const std::string &str, int x, int y)
{
    if(dxFont == NULL)
        return 0;
    // set font position
    fontRect.top = y;
    fontRect.left = x;

    // Rotation center
    D3DXVECTOR2 rCenter=D3DXVECTOR2((float)x,(float)y);
    // Setup matrix to rotate text by angle
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);
    // Tell the sprite about the matrix "Hello Neo"
    graphics->getSprite()->SetTransform(&matrix);
    return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_LEFT, color);
}

// print center aligned text
int TextDX::printC(const std::string &str, int x, int y)
{
	if (dxFont == NULL)
		return 0;
	// set font position
	fontRect.top = y;
	fontRect.left = (long)-GAME_WIDTH/2+x;
	fontRect.right = (long)GAME_WIDTH/2+x;

	// Rotation center
	D3DXVECTOR2 rCenter = D3DXVECTOR2((float)x, (float)y);
	// Setup matrix to rotate text by angle
	D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, &rCenter, angle, NULL);
	// Tell the sprite about the matrix "Hello Neo"
	graphics->getSprite()->SetTransform(&matrix);
	return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &fontRect, DT_CENTER, color);
}

//=============================================================================
// Print text inside RECT using DirectX text format
// Return 0 on fail, height of text on success
// pre: spriteBegin()
// post: spriteEnd()
//=============================================================================
int TextDX::print(const std::string &str, RECT &rect, UINT format)
{
    if(dxFont == NULL)
        return 0;

    // Setup matrix to not rotate text
    D3DXMatrixTransformation2D(&matrix, NULL, 0.0f, NULL, NULL, NULL, NULL);
    // Tell the sprite about the matrix "Hello Neo"
    graphics->getSprite()->SetTransform(&matrix);
    return dxFont->DrawText(graphics->getSprite(), str.c_str(), -1, &rect, format, color);
}

//=============================================================================
// called when graphics device is lost
//=============================================================================
void TextDX::onLostDevice()
{
    if(dxFont == NULL)
        return;
    dxFont->OnLostDevice();
}

//=============================================================================
// called when graphics device is reset
//=============================================================================
void TextDX::onResetDevice()
{
    if(dxFont == NULL)
        return;
    dxFont->OnResetDevice();
}