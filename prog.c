#include <stdio.h>
#include <X11/XKBlib.h>

int main(int argc, char* argv[]){
	Display *d;
	XkbDescPtr keyboard;
	XkbStateRec	state;

	char* display = getenv("DISPLAY");
	int result;
	// connection to the X server 
	d = XkbOpenDisplay(display, NULL, NULL, NULL, NULL, &result);

	keyboard = XkbAllocKeyboard();
	// Obtain symbolic names from the server 
	XkbGetNames(d, XkbGroupNamesMask, keyboard);
	XkbGetState(d, XkbUseCoreKbd, &state);	

	printf("%s\n", XGetAtomName(d, keyboard->names->groups[state.group]));
	// Free symbolic names structures 
	(void)XkbFreeNames(keyboard, XkbGroupNamesMask, True);
	return 0;
}