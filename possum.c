/* possum is copyright Nick Markwell, 2009.
 * Based on TinyWM by Nick Welch <mack@incise.org>
 * and is provided AS IS, with NO WARRANTY. */

/* most X stuff will be included with Xlib.h, but a few things require other
 * headers, like Xmd.h, keysym.h, etc.
 */
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

/* Yay for a macro that lets you use KEYCODE("key") to generate the definition... 
 * KEYCODE("F1")
 * ->
 * KeyCode kc_F1 = XKeysymToKeycode(dpy, XStringToKeysym("F1"));
 */
#define KEYCODEDECL(NAME) KeyCode kc_##NAME;
#define KEYCODECODE(NAME) kc_##NAME = XKeysymToKeycode(dpy, XStringToKeysym( #NAME ));
#define KEYGRAB(NAME) XGrabKey(dpy, kc_##NAME, Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main()
{
	Display * dpy;
	Window root;
	XWindowAttributes attr;

	/* we use this to save the pointer's state at the beginning of the
	 * move/resize.
	 */
	XButtonEvent start;

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

	/* Return error code if the display cant be opened
	 * But even with just:
	 * dpy = XOpenDisplay(display_str);
	 * it likes to say: "warning: ISO C90 forbids mixed declarations and code"
	 */
	if(!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "Error: cannot open display.");
		exit(1);
	}

	root = DefaultRootWindow(dpy);

	/* you could also include keysym.h and use the XK_F1 constant instead of
	 * the call to XStringToKeysym, but this method is more "dynamic."  imagine
	 * you have config files which specify key bindings.  instead of parsing
	 * the key names and having a huge table or whatever to map strings to XK_*
	 * constants, you can just take the user-specified string and hand it off
	 * to XStringToKeysym.  XStringToKeysym will give you back the appropriate
	 * keysym or tell you if it's an invalid key name.
	 *
	 * a keysym is basically a platform-independent numeric representation of a
	 * key, like "F1", "a", "b", "L", "5", "Shift", etc.  a keycode is a
	 * numeric representation of a key on the keyboard sent by the keyboard
	 * driver (or something along those lines -- i'm no hardware/driver expert)
	 * to X.  so we never want to hard-code keycodes, because they can and will
	 * differ between systems.
	 */
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
	/*XGrabKey(dpy, kc_Enter, Mod1Mask, root, True, GrabModeAsync, GrabModeAsync);*/

	/* XGrabKey and XGrabButton are basically ways of saying "when this
	 * combination of modifiers and key/button is pressed, send me the events."
	 * so we can safely assume that we'll receive Alt+F1 events, Alt+Button1
	 * events, and Alt+Button3 events, but no others.  You can either do
	 * individual grabs like these for key/mouse combinations, or you can use
	 * XSelectInput with KeyPressMask/ButtonPressMask/etc to catch all events
	 * of those types and filter them as you receive them.
	 */
	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask, GrabModeAsync,
			GrabModeAsync, None, None);
	XGrabButton(dpy, 2, Mod1Mask, root, True, ButtonPressMask, GrabModeAsync,
			GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, root, True, ButtonPressMask, GrabModeAsync,
			GrabModeAsync, None, None);

	for(;;)
	{
		/* this is the most basic way of looping through X events; you can be
		 * more flexible by using XPending(), or ConnectionNumber() along with
		 * select() (or poll() or whatever floats your boat).
		 */
		XNextEvent(dpy, &ev);

		/* this is our keybinding for raising windows.  as i saw someone
		 * mention on the ratpoison wiki, it is pretty stupid; however, i
		 * wanted to fit some sort of keyboard binding in here somewhere, and
		 * this was the best fit for it.
		 *
		 * i was a little confused about .window vs. .subwindow for a while,
		 * but a little RTFMing took care of that.  our passive grabs above
		 * grabbed on the root window, so since we're only interested in events
		 * for its child windows, we look at .subwindow.  when subwindow
		 * None, that means that the window the event happened in was the same
		 * window that was grabbed on -- in this case, the root window.
		 */
		if(ev.type == KeyPress && ev.xkey.subwindow != None)
			XRaiseWindow(dpy, ev.xkey.subwindow);
		else if(ev.type == ButtonPress && ev.xbutton.subwindow != None)
		{
			/* Raise the window */
			XRaiseWindow(dpy, ev.xbutton.subwindow);
			
			/* now we take command of the pointer, looking for motion and
			 * button release events.
			 */
			XGrabPointer(dpy, ev.xbutton.subwindow, True,
					PointerMotionMask|ButtonReleaseMask, GrabModeAsync,
					GrabModeAsync, None, None, CurrentTime);

			/* we "remember" the position of the pointer at the beginning of
			 * our move/resize, and the size/position of the window.  that way,
			 * when the pointer moves, we can compare it to our initial data
			 * and move/resize accordingly.
			 */
			XGetWindowAttributes(dpy, ev.xbutton.subwindow, &attr);
			start = ev.xbutton;
		}
		/* the only way we'd receive a motion notify event is if we already did
		 * a pointer grab and we're in move/resize mode, so we assume that. */
		else if(ev.type == MotionNotify)
		{
			int xdiff, ydiff;

			/* here we "compress" motion notify events.  if there are 10 of
			 * them waiting, it makes no sense to look at any of them but the
			 * most recent.  in some cases -- if the window is really big or
			 * things are just acting slowly in general -- failing to do this
			 * can result in a lot of "drag lag."
			 *
			 * for window managers with things like desktop switching, it can
			 * also be useful to compress EnterNotify events, so that you don't
			 * get "focus flicker" as windows shuffle around underneath the
			 * pointer.
			 */
			while(XCheckTypedEvent(dpy, MotionNotify, &ev));

			/* now we use the stuff we saved at the beginning of the
			 * move/resize and compare it to the pointer's current position to
			 * determine what the window's new size or position should be.
			 *
			 * if the initial button press was button 1, then we're moving.
			 * otherwise it was 3 and we're resizing.
			 *
			 * we also make sure not to go negative with the window's
			 * dimensions, resulting in "wrapping" which will make our window
			 * something ridiculous like 65000 pixels wide (often accompanied
			 * by lots of swapping and slowdown).
			 *
			 * even worse is if we get "lucky" and hit a width or height of
			 * exactly zero, triggering an X error.  so we specify a minimum
			 * width/height of 1 pixel.
			 */
			xdiff = ev.xbutton.x_root - start.x_root;
			ydiff = ev.xbutton.y_root - start.y_root;
			XMoveResizeWindow(dpy, ev.xmotion.window,
				attr.x + (start.button==1 ? xdiff : 0),
				attr.y + (start.button==1 ? ydiff : 0),
				MAX(1, attr.width + (start.button==3 ? xdiff : 0)),
				MAX(1, attr.height + (start.button==3 ? ydiff : 0)));
		}
		/* like motion notifies, the only way we'll receive a button release is
		 * during a move/resize, due to our pointer grab.  this ends the
		 * move/resize.
		 */
		else if(ev.type == ButtonRelease)
			if ( ev.xbutton.subwindow != None )
			XUngrabPointer(dpy, CurrentTime);
	}
}
