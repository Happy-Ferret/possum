#include "possum.h"
#include "core.h"
#include "keys.h"

int main(int argc, char const* argv[])
{
	Display *dpy;
	Window root;
	int screenNum;

	XEvent event;
	KeyCodesCommon *KeyCodes = malloc(sizeof(KeyCodesCommon));
	
	if ((dpy = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Error: Could not open default display.\n");
		exit(-1);
	}

	screenNum = DefaultScreen(dpy);
	root = RootWindow(dpy, screenNum);

	SetCommonKeys(KeyCodes, dpy);
	GrabCommonKeys(KeyCodes, dpy, root);

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
