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

void CoreButtonRelease(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	/* Because we got ButtonRelease, we
	 * can assume the pointer is in grab mode. */
	XUngrabPointer(dpy, CurrentTime);
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

void CoreMapRequest(Display *dpy, int screenNum, Window root,
	XEvent event)
{
/*	Window win;
	XWindowAttributes winAttr;
	XGetWindowAttributes(event.xmaprequest.display,
		event.xmaprequest.window,
		&winAttr);
	win = XCreateSimpleWindow(dpy, root,
			winAttr.x,
			winAttr.y,
			winAttr.width + 8,
			winAttr.height + 8,
			0,
			//BlackPixel(dpy, screenNum),
			//BlackPixel(dpy, screenNum));
			WhitePixel(dpy, screenNum),
			WhitePixel(dpy, screenNum));
	XAddToSaveSet(event.xmaprequest.display,
		event.xmaprequest.window);
	XReparentWindow(event.xmaprequest.display,
		event.xmaprequest.window,
		win, 4, 4);
	XMapWindow(event.xmaprequest.display,
		event.xmaprequest.window);
	XMapWindow(event.xmaprequest.display,
		win);*/

	XMapWindow(event.xmaprequest.display,
		event.xmaprequest.window);
}

void CoreCirculateRequest(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	XCirculateSubwindows(event.xcirculate.display,
		event.xcirculaterequest.window,
		event.xcirculaterequest.place);
}

void CoreConfigureRequest(Display *dpy, int screenNum, Window root,
	XEvent event)
{
	XWindowChanges values;
	
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
	switch (event.type) {
	case KeyPress:
		CoreKeyPress(dpy, screenNum, root, event);
		break;
	case ButtonPress:
		CoreButtonPress(dpy, screenNum, root, event);
		break;
	case ButtonRelease:
		CoreButtonRelease(dpy, screenNum, root, event);
		break;
	case MotionNotify:
		CoreMotionNotify(dpy, screenNum, root, event);
		break;
	case CirculateRequest:
		CoreCirculateRequest(dpy, screenNum, root, event);
		break;
	case ConfigureRequest:
		CoreConfigureRequest(dpy, screenNum, root, event);
		break;
	case MapRequest:
		CoreMapRequest(dpy, screenNum, root, event);
		break;
	}
}
