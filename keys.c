#include "possum.h"
#include "keys.h"

void SetCommonKeys(KeyCodesCommon *KeyCodes, Display *dpy)
{
	KeyCodes->F1 = KEYCODE(F1);
	KeyCodes->F2 = KEYCODE(F2);
	KeyCodes->F3 = KEYCODE(F3);
	KeyCodes->F4 = KEYCODE(F4);
	KeyCodes->F5 = KEYCODE(F5);
	KeyCodes->F6 = KEYCODE(F6);
	KeyCodes->F7 = KEYCODE(F7);
	KeyCodes->F8 = KEYCODE(F8);
	KeyCodes->F9 = KEYCODE(F9);
	KeyCodes->F10 = KEYCODE(F10);
	KeyCodes->F11 = KEYCODE(F11);
	KeyCodes->F12 = KEYCODE(F12);
	KeyCodes->Enter = KEYCODE(Enter);
}

void GrabKey(KeyCode key, Display *dpy, Window root)
{
	XGrabKey(dpy, key, Mod1Mask, root, True,
		GrabModeAsync, GrabModeAsync);
}

void GrabCommonKeys(KeyCodesCommon *KeyCodes, Display *dpy, Window root)
{
	KEYGRAB(KeyCodes->F1);
	KEYGRAB(KeyCodes->F2);
	KEYGRAB(KeyCodes->F3);
	KEYGRAB(KeyCodes->F4);
	KEYGRAB(KeyCodes->F5);
	KEYGRAB(KeyCodes->F6);
	KEYGRAB(KeyCodes->F7);
	KEYGRAB(KeyCodes->F8);
	KEYGRAB(KeyCodes->F9);
	KEYGRAB(KeyCodes->F10);
	KEYGRAB(KeyCodes->F11);
	KEYGRAB(KeyCodes->F12);
	KEYGRAB(KeyCodes->Enter);
}
