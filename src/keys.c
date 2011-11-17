#include <possum.h>

void SetCommonKeys()
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
	KeyCodes->Tab = KEYCODE(Tab);
	KeyCodes->Enter = KEYCODE(Enter);
	KeyCodes->Delete = KEYCODE(Delete);
}

void GrabKey(KeyCode key)
{
	// Alt-*
	XGrabKey(dpy, key, _ALT, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _ALT_SHIFT, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _ALT_CTRL, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _ALT|_CTRL|_SHIFT, root, True,
		GrabModeAsync, GrabModeAsync);

	// Super-*
	XGrabKey(dpy, key, _SUPER, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _SUPER_SHIFT, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _SUPER_CTRL, root, True,
		GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, key, _SUPER|_CTRL|_SHIFT, root, True,
		GrabModeAsync, GrabModeAsync);
}

void GrabCommonKeys()
{
	GrabKey(KeyCodes->F1);
	GrabKey(KeyCodes->F2);
	GrabKey(KeyCodes->F3);
	GrabKey(KeyCodes->F4);
	GrabKey(KeyCodes->F5);
	GrabKey(KeyCodes->F6);
	GrabKey(KeyCodes->F7);
	GrabKey(KeyCodes->F8);
	GrabKey(KeyCodes->F9);
	GrabKey(KeyCodes->F10);
	GrabKey(KeyCodes->F11);
	GrabKey(KeyCodes->F12);
	GrabKey(KeyCodes->Tab);
	GrabKey(KeyCodes->Enter);
	GrabKey(KeyCodes->Delete);
}
