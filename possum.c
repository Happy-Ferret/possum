/* possum is copyright Nick Markwell, 2009.
 * Based on TinyWM by Nick Welch <mack@incise.org>
 * and is provided AS IS, with NO WARRANTY. */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

#define KEYCODEDECL(NAME) KeyCode kc_##NAME;
#define KEYCODECODE(NAME) kc_##NAME = \
		XKeysymToKeycode(dpy, XStringToKeysym( #NAME ));

#define KEYGRAB(NAME) XGrabKey(dpy, kc_##NAME, Mod1Mask, root, True, \
		GrabModeAsync, GrabModeAsync);

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {
	Display *dpy;
	Window root;
	XWindowAttributes attr;

	XButtonEvent start = {0};

	XEvent ev;

	KEYCODEDECL(F1)
	KEYCODEDECL(F2)
	KEYCODEDECL(F3)
	KEYCODEDECL(F4)
	KEYCODEDECL(F5)
	KEYCODEDECL(F6)
	KEYCODEDECL(F7)
	KEYCODEDECL(F8)
	KEYCODEDECL(F9)
	KEYCODEDECL(F10)
	KEYCODEDECL(F11)
	KEYCODEDECL(F12)
	KEYCODEDECL(Enter)

	if(!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Error: cannot open display.");
		exit(1);
	}

	root = DefaultRootWindow(dpy);

	/* keysym.h defines XK_[key] constants too. */
	KEYCODECODE(F1)
	KEYCODECODE(F2)
	KEYCODECODE(F3)
	KEYCODECODE(F4)
	KEYCODECODE(F5)
	KEYCODECODE(F6)
	KEYCODECODE(F7)
	KEYCODECODE(F8)
	KEYCODECODE(F9)
	KEYCODECODE(F10)
	KEYCODECODE(F11)
	KEYCODECODE(F12)
	KEYCODECODE(Enter)
	KEYGRAB(F1)
	KEYGRAB(F2)
	KEYGRAB(F3)
	KEYGRAB(F4)
	KEYGRAB(F5)
	KEYGRAB(F6)
	KEYGRAB(F7)
	KEYGRAB(F8)
	KEYGRAB(F9)
	KEYGRAB(F10)
	KEYGRAB(F11)
	KEYGRAB(F12)
	KEYGRAB(Enter)

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 2, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);

	while (1) {
		XNextEvent(dpy, &ev);

		if(ev.type == KeyPress && ev.xkey.subwindow != None) {
			/* Raise the window on keypress. */
			XRaiseWindow(dpy, ev.xkey.subwindow);
		} else if(ev.type == ButtonPress &&
				ev.xbutton.subwindow != None) {
			XRaiseWindow(dpy, ev.xbutton.subwindow);
			
			/* Look for motion and button releases. */
			XGrabPointer(dpy, ev.xbutton.subwindow, True,
					PointerMotionMask|ButtonReleaseMask,
					GrabModeAsync, GrabModeAsync, None,
					None, CurrentTime);

			/* Record start location of window movement. */
			XGetWindowAttributes(dpy, ev.xbutton.subwindow,
					&attr);
			start = ev.xbutton;
		} else if(ev.type == MotionNotify) {
			int xdiff, ydiff;

			/* Because we received MotionNotify we are already
			 * in pointer grab mode. */

			/* Loop throught events as to only look at the most
			 * recent event. */
			while(XCheckTypedEvent(dpy, MotionNotify, &ev))
				;

			xdiff = ev.xbutton.x_root - start.x_root;
			ydiff = ev.xbutton.y_root - start.y_root;

			if (start.button == 1) {
				XMoveWindow(dpy, ev.xmotion.window,
						attr.x, attr.y);
			} else {
				/* Because we got an event, it has to be
				 * from button 3. */

				/* Only resize the window if it will be
				 * greater than 1 by 1. */
				if (attr.width + xdiff => 1 &&
						attr.height + ydiff => 1)
					XResizeWindow(dpy,
							ev.xmotion.window,
							attr.width+xdiff,
							attr.height+ydiff);
				else
					XResizeWindow(dpy,
							ev.xmotion.window,
							1, 1);

			}
		}
		else if(ev.type == ButtonRelease)
			/* Again, because we got ButtonRelease, we can
			 * assume the pointer is in grab mode. */
			if (ev.xbutton.subwindow != None)
				XUngrabPointer(dpy, CurrentTime);
	}
}
