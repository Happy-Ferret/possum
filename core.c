#include <X11/Xlib.h>

void CoreRegister(Display *dpy, int screenNum, Window root)
{
	XSelectInput(dpy, root, SubstructureRedirectMask
			| PointerMotionMask);

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
}

void CoreEventProcess(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	XWindowChanges values;

	switch (event.type) {
	case MotionNotify:
		if (event.xmotion.subwindow != None)
			XRaiseWindow(dpy, event.xmotion.subwindow);
		break;
	case CirculateRequest:
		XCirculateSubwindows(event.xcirculate.display,
				event.xcirculaterequest.window,
				event.xcirculaterequest.place);
		break;
	case ConfigureRequest:
		values.x = event.xconfigurerequest.x;
		values.y = event.xconfigurerequest.y;
		values.width = event.xconfigurerequest.width;
		values.height = event.xconfigurerequest.width;
		values.border_width = event.xconfigurerequest.border_width;
		values.sibling = 0;
		values.stack_mode = 0;
		XConfigureWindow(event.xconfigurerequest.display,
				event.xconfigurerequest.window,
				event.xconfigurerequest.value_mask,
				&values);
		break;
	case MapRequest:
		XMapWindow(event.xmaprequest.display,
				event.xmaprequest.window);
		break;
	}
}
