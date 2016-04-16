#include <stdio.h>
#include <err.h>
#include <X11/XKBlib.h>

int main(int argc, char* argv[]){
	Display *display;
	XkbDescPtr keyboard;
	XkbStateRec	state;
	int result;

	// connection to the X server 
	display = XkbOpenDisplay( getenv("DISPLAY") , NULL, NULL, NULL, NULL, &result );
	if(!display){
		errx(1, "X server unreachable");
	}

	keyboard = XkbAllocKeyboard();
	if(!keyboard){
		errx(1, "Error creating keyboard description");
	}

	// Obtain symbolic names from the server 
	if ( XkbGetNames(display, XkbGroupNamesMask, keyboard) != Success ){
		errx(1, "Error obtaining symbolic names");
	}

	if( XkbGetState(display, XkbUseCoreKbd, &state) != Success ){
		errx(1, "Error getting keyboard state");
	}	

	printf("%s\n", XGetAtomName(display, keyboard->names->groups[state.group]));

	// Free symbolic names structures 
	XkbFreeNames(keyboard, XkbGroupNamesMask, True);
	
	return 0;
}