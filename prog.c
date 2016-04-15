#include <stdio.h>
#include <X11/XKBlib.h>

int main(int argc, char* argv[]){
	Display *display;
	XkbDescPtr keyboard;
	XkbStateRec	state;
	int result;

	// connection to the X server 
	display = XkbOpenDisplay( getenv("DISPLAY") , NULL, NULL, NULL, NULL, &result );
	if(!display){
		printf("X server unreachable");
		return -1;
	}

	keyboard = XkbAllocKeyboard();
	if(!keyboard){
		printf("Error creating keyboard description");
		return -1;
	}
	// Obtain symbolic names from the server 
	if ( XkbGetNames(display, XkbGroupNamesMask, keyboard) != Succes ){
		printf("Error obtaining symbolic names");
		return -1;
	}
	printf("%s\n", Succes);


	if( XkbGetState(display, XkbUseCoreKbd, &state) != Succes ){
		printf("Error getting keyboard state");
		return -1;
	}	

	printf("%s\n", XGetAtomName(d, keyboard->names->groups[state.group]));
	
	// Free symbolic names structures 
	XkbFreeNames(keyboard, XkbGroupNamesMask, True);
	return 0;
}