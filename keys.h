#ifndef KEYS_H
#define KEYS_H

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
	KeyCode Enter;
	KeyCode Tab;
} KeyCodesCommon;

void SetCommonKeys();
void GrabKey(KeyCode key);
void GrabCommonKeys();

#endif
