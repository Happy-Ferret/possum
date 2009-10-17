#ifndef CORE_H
#define CORE_H

void CoreRegister(Display *dpy, int screenNum, Window root);
void CoreEventProcess(Display *dpy, int screenNum, Window root,
	XEvent event);

void CoreKeyPress(Display *dpy, int screenNum, Window root,
	XEvent event);
void CoreButtonPress(Display *dpy, int screenNum, Window root,
	XEvent event);
void CoreRegister(Display *dpy, int screenNum, Window root);
void CoreMotionNotify(Display *dpy, int screenNum, Window root,
	XEvent event);
void CoreMapRequest(Display *dpy, int screenNum, Window root,
	XEvent event);

#endif
