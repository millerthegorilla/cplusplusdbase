#include "Icon.h"
// (c) Bartosz Milewski 2000
using namespace Win;

void Icon::Load (HINSTANCE hInst, int id, int dx, int dy, unsigned flag)
{
    _h = reinterpret_cast<HICON> (
        ::LoadImage (hInst, 
                     MAKEINTRESOURCE (id), 
                     IMAGE_ICON, 
                     dx, dy, 
                     flag));
    if (_h == 0)
        throw "Icon load image failed";
}

Icon::~Icon ()
{
    ::DestroyIcon (_h);
}

void SmallIcon::Load (HINSTANCE hInst, int id)
{
    Icon::Load (hInst, id, 
            ::GetSystemMetrics (SM_CXSMICON),
            ::GetSystemMetrics (SM_CYSMICON));
}

void StdIcon::Load (HINSTANCE hInst, int id)
{
    Icon::Load (hInst, id, 
            ::GetSystemMetrics (SM_CXICON),
            ::GetSystemMetrics (SM_CYICON));
}
