#ifndef KEYS_H
#define KEYS_H

#include <key_macros.h>

#define KEYCODE(NAME) XKeysymToKeycode(dpy, XStringToKeysym( #NAME ))

typedef struct key_codes_common {
	KeyCode F1;
	KeyCode F2;
	KeyCode F3;
	KeyCode F4;
	KeyCode F5;
	KeyCode F6;
	KeyCode F7;
	KeyCode F8;
	KeyCode F9;
	KeyCode F10;
	KeyCode F11;
	KeyCode F12;
	KeyCode Tab;
	KeyCode Enter;
	KeyCode Delete;
} KeyCodesCommon;

void SetCommonKeys();
void GrabKey(KeyCode key);
void GrabCommonKeys();

#endif
