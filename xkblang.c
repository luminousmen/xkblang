#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <X11/XKBlib.h>


void usage();

int main(int argc, char* argv[]){

	int ch, sflag = 0;

	while ((ch = getopt(argc, argv, "s")) != -1) {
		switch (ch) {
		case 's':
			sflag = 1;
			break;
		default:
			usage();
			return 0;
		}
	}
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

	if(sflag){
		printf( "%.2s\n", XGetAtomName(display, keyboard->names->groups[state.group]) );
	}
	else {
		printf( "%s\n", XGetAtomName(display, keyboard->names->groups[state.group]) );
	}

	// Free symbolic names structures 
	XkbFreeNames(keyboard, XkbGroupNamesMask, True);
	
	return 0;
}


void usage(){
	printf("Usage: [options]\n\n"
		"Options:\n"
		"\t-s  - short version (just 2 literals)\n");
}