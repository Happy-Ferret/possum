#include "possum.h"
#include "core.h"
#include "keys.h"

int main(int argc, char const* argv[])
{
	KeyCodes = malloc(sizeof(KeyCodesCommon));
	
	if ((dpy = XOpenDisplay(NULL)) == NULL) {
		fprintf(stderr, "Error: Could not open default display.\n");
		exit(-1);
	}

	screenNum = DefaultScreen(dpy);
	root = RootWindow(dpy, screenNum);

	SetCommonKeys();
	GrabCommonKeys();

	XGrabButton(dpy, 1, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 2, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);
	XGrabButton(dpy, 3, Mod1Mask, root, True, ButtonPressMask,
			GrabModeAsync, GrabModeAsync, None, None);

	CoreRegister();

	while (1) {
		XNextEvent(dpy, &event);

		CoreEventProcess();
	}
	
	PossumExit();

	return 0;
}

void PossumExit() {
	XCloseDisplay(dpy);
	printf("\n*** Exiting possum\n");
	exit(0);
}

void PossumRestart() {
	pid_t pid;
	int ret;

	printf("\n*** Restarting possum\n");

	pid = fork();
	if (pid == 0)
		ret = execl ("./possum", "./possum", NULL);
	else
		PossumExit();
}
