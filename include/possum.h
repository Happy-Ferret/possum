#ifndef POSSUM_H
#define POSSUM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <X11/Xlib.h>

#include <core.h>
#include <keys.h>

void PossumExit();
void PossumRecompile();
void PossumRestart();

// These next 5 vars are to avoid hilarious amounts of redundancy

Display *dpy;
Window root;
int screenNum;

XEvent event;

KeyCodesCommon *KeyCodes;

#endif
