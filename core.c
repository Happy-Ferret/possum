#include <X11/Xlib.h>

XButtonEvent move_start = {0};
XWindowAttributes attr = {0};

void CoreKeyPress(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	/* Raise the window on keypress. */
	if(event.xkey.subwindow != None) 
		XRaiseWindow(dpy, event.xkey.subwindow);
}

void CoreButtonPress(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	if(event.xbutton.subwindow == None)
		return;
	
	XRaiseWindow(dpy, event.xbutton.subwindow);
	
	/* Look for motion and button releases. */
	XGrabPointer(dpy, event.xbutton.subwindow, True,
		PointerMotionMask|ButtonReleaseMask,
		GrabModeAsync, GrabModeAsync, None,
		None, CurrentTime);
	
	/* Record start location of window movement. */
	XGetWindowAttributes(dpy, event.xbutton.subwindow,
		&attr);
	move_start = event.xbutton;
}

void CoreMotionNotify(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	int xdiff, ydiff;
	/*if (event.xmotion.subwindow != None)
		XRaiseWindow(dpy, event.xmotion.subwindow);*/
		
	/* Because we received MotionNotify we are
	 * already in pointer grab mode. */
 
	/* Loop throught events as to only look at
	 * the most recent event. */
	while(XCheckTypedEvent(dpy, MotionNotify, &event))
	;
 
 	xdiff = event.xbutton.x_root - move_start.x_root;
	ydiff = event.xbutton.y_root - move_start.y_root;
 
	if (move_start.button == 1) {
		XMoveWindow(dpy, event.xmotion.window,
		attr.x+xdiff, attr.y+ydiff);
	} else if (move_start.button == 3) {

		/* Only resize the window if it will be
		* greater than 1 by 1. */
		if (attr.width + xdiff >= 1 &&
			attr.height + ydiff >= 1)
			XResizeWindow(dpy,
				event.xmotion.window,
				attr.width+xdiff,
				attr.height+ydiff);
		else
			XResizeWindow(dpy,
				event.xmotion.window,
				1, 1); 
	}
}

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
	case KeyPress:
		CoreKeyPress(dpy, screenNum, root, event);
		break;
	case ButtonPress:
		CoreButtonPress(dpy, screenNum, root, event);
		break;
	case ButtonRelease:
		/* Because we got ButtonRelease, we
		 * can assume the pointer is in grab mode. */
		XUngrabPointer(dpy, CurrentTime);
		break;
	case MotionNotify:
		CoreMotionNotify(dpy, screenNum, root, event);
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
