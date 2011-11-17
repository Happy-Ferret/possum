#include <possum.h>

XButtonEvent move_start = {0};
XWindowAttributes attr = {0};

void CoreKeyPress()
{
	ON_ALT(F1) {
		if(event.xkey.subwindow != None)
			XRaiseWindow(event.xkey.display, event.xkey.subwindow);
	}

#ifdef DEVELOPMENT
	ON_CTRL_ALT(Delete) {
		if (PossumRecompile()) {
			PossumRestart();
		} else {
			printf("*** Not restarting\n");
		}
	}
#endif

	ON_SUPER(F2) {
		printf("TADA\n");
	}

	/*ON_ALT(F4) {
		XKillClient(event.xkey.display, event.xkey.window);
	}*/
	
	ON_ALT(Tab) {
		XCirculateSubwindowsDown(event.xkey.display,
			event.xkey.window);
	}
}

void CoreButtonPress()
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

void CoreButtonRelease()
{
	/* Because we got ButtonRelease, we
	 * can assume the pointer is in grab mode. */
	XUngrabPointer(dpy, CurrentTime);
}

void CoreMotionNotify()
{
	int xdiff, ydiff;
	
	// Focus window under the mouse (if any) when mouse is moved,
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
			attr.height + ydiff >= 1) {
			XResizeWindow(dpy,
				event.xmotion.window,
				attr.width+xdiff,
				attr.height+ydiff);
		} else {
			XResizeWindow(dpy,
				event.xmotion.window,
				1, 1);
		}
	}
}

void CoreMapRequest()
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

    XSetWindowBorderWidth(dpy, event.xmaprequest.window, 1);

	XMapWindow(event.xmaprequest.display,
		event.xmaprequest.window);
}

void CoreCirculateRequest()
{
	XCirculateSubwindows(event.xcirculate.display,
		event.xcirculaterequest.window,
		event.xcirculaterequest.place);
}

void CoreConfigureRequest()
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

void CoreRegister()
{
	XSelectInput(dpy, root, SubstructureRedirectMask
			| PointerMotionMask);

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
}

#define HANDLE(X) case X: Core##X(); break

void CoreEventProcess()
{
	switch (event.type) {
		HANDLE(KeyPress);
		HANDLE(ButtonPress);
		HANDLE(ButtonRelease);
		HANDLE(MotionNotify);
		HANDLE(CirculateRequest);
		HANDLE(ConfigureRequest);
		HANDLE(MapRequest);
	}
}
