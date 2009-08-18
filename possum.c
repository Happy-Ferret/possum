#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>

void CoreRegister(Display *dpy, int screenNum, Window root);
void CoreEventProcess(Display *dpy, int screenNum, Window root,
	XEvent event);

int main(int argc, char const* argv[])
{
	Display *dpy;
	Window root;
	int screenNum;

	XEvent event;

	if ((dpy = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Error: Could not open default display.\n");
		exit(-1);
	}

	screenNum = DefaultScreen(dpy);
	root = RootWindow(dpy, screenNum);

	CoreRegister(dpy, screenNum, root);

	while (1) {
		XNextEvent(dpy, &event);

		CoreEventProcess(dpy, screenNum, root, event);
	}
	return 0;
}
