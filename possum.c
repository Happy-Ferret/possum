#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

#include "core.h"
#include "keys.h"

int main(int argc, char const* argv[])
{
	Display *dpy;
	Window root;
	int screenNum;

	XEvent event;
	KeyCodesCommon *KeyCodes = {0};
	KeyCode F1;
	
	if ((dpy = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Error: Could not open default display.\n");
		exit(-1);
	}

	screenNum = DefaultScreen(dpy);
	root = RootWindow(dpy, screenNum);

	/*
	 * The following line results in a segfault:
	 * KeyCodes->F1 = XKeysymToKeycode(dpy, XStringToKeysym("F1"));
	 * The following does not:
	 * F1 = XKeysymToKeycode(dpy, XStringToKeysym("F1"));
	 */
	/* Uncomment this once we determine what causes the above problem
	SetCommonKeys(KeyCodes, dpy);
	GrabCommonKeys(KeyCodes, dpy, root);
	*/

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 2, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);

	CoreRegister(dpy, screenNum, root);

	while (1) {
		XNextEvent(dpy, &event);

		CoreEventProcess(dpy, screenNum, root, event);
	}
	return 0;
}
