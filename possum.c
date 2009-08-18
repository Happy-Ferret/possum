/* possum by Nick Markwell and Martin Brandenburg
 * Based on TinyWM by Nick Welch <mack@incise.org>
 * This is provided AS IS, with NO WARRANTY.
 * This program is in the public domain.
 */

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
	int xdiff, ydiff;
	Display *dpy;
	Window root;
	XWindowAttributes attr;
	int screenNum;

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
		fprintf(stderr, "Error: cannot open display.\n");
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

	screenNum = DefaultScreen(dpy);

	XSelectInput(dpy, root, SubstructureRedirectMask);

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 2, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);

	while (1) {
		XNextEvent(dpy, &ev);

		switch(ev.type) {
			case KeyPress:
				if(ev.xkey.subwindow != None) 
					/* Raise the window on keypress. */
					XRaiseWindow(dpy, ev.xkey.subwindow);
				break;
			case ButtonPress:
				if(ev.xbutton.subwindow == None)
					break;

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
				break;
			case MotionNotify:

				/* Because we received MotionNotify we are
				 * already in pointer grab mode. */

				/* Loop throught events as to only look at
				 * the most recent event. */
				while(XCheckTypedEvent(dpy, MotionNotify,
							&ev))
					;

				xdiff = ev.xbutton.x_root - start.x_root;
				ydiff = ev.xbutton.y_root - start.y_root;

				if (start.button == 1) {
					XMoveWindow(dpy, ev.xmotion.window,
							attr.x+xdiff, attr.y+ydiff);
				} else if (start.button == 3) {

					/* Only resize the window if it will be
					* greater than 1 by 1. */
					if (attr.width + xdiff >= 1 &&
							attr.height + ydiff >= 1)
						XResizeWindow(dpy,
								ev.xmotion.window,
								attr.width+xdiff,
								attr.height+ydiff);
					else
						XResizeWindow(dpy,
								ev.xmotion.window,
								1, 1);

				}
				break;
			case ButtonRelease:
				/* Again, because we got ButtonRelease, we
				 * can assume the pointer is in grab mode. */
				XUngrabPointer(dpy, CurrentTime);
				break;
			case CirculateRequest:
				XCirculateSubwindows(ev.xcirculate.display,
						ev.xcirculate.window,
						ev.xcirculate.place);
				break;
			case ConfigureRequest:
				{
				XWindowChanges values;
				values.x = ev.xconfigurerequest.x;
				values.y = ev.xconfigurerequest.y;
				values.width = ev.xconfigurerequest.width;
				values.height = ev.xconfigurerequest.height;
				values.border_width =
					ev.xconfigurerequest.border_width;
				values.sibling = 0;
				values.stack_mode = 0;
				XConfigureWindow(ev.xconfigurerequest.display,
						ev.xconfigurerequest.window,
						ev.xconfigurerequest.value_mask,
						&values);
				}
				break;
			case MapRequest:
				{
				Window win;
				XWindowAttributes winAttr;
				XGetWindowAttributes(ev.xmaprequest.display,
						ev.xmaprequest.window,
						&winAttr);
				win = XCreateSimpleWindow(dpy, root,
						winAttr.x,
						winAttr.y,
						winAttr.width + 8,
						winAttr.height + 8,
						0,
						BlackPixel(dpy, screenNum),
						BlackPixel(dpy, screenNum));
				XAddToSaveSet(ev.xmaprequest.display,
					       ev.xmaprequest.window);
				XReparentWindow(ev.xmaprequest.display,
						ev.xmaprequest.window,
						win, 4, 4);
				XMapWindow(ev.xmaprequest.display,
						ev.xmaprequest.window);
				XMapWindow(ev.xmaprequest.display,
						win);
				}
				break;
			default:
				/* What is this you are giving us, Xorg? */
				break;
		}
	}
}
