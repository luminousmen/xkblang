#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <err.h>
#include <X11/XKBlib.h>
#include <stdlib.h> 

void usage(void);

int main(int argc, char* argv[]){

	int ch;
	int sflag = 0, 
		pflag = 0,
		lflag = 0,
		tflag = 0;
	int group_num;
	char * endptr;

	while ( (ch = getopt(argc, argv, "slpt:")) != -1) {
		switch (ch) {
		case 's':
			sflag = 1;
			break;
		case 'p':
			pflag = 1;
			break;
		case 'l':
			lflag = 1;
			break;
		case 't':
			tflag = 1;
			group_num = strtol(optarg, &endptr,10);
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
	if( !display ) {
		errx(1, "X server unreachable");
	}

	keyboard = XkbAllocKeyboard();
	if( !keyboard ) {
		errx(1, "Error creating keyboard description");
	}

	// Obtain symbolic names from the server 
	if ( XkbGetNames(display, XkbGroupNamesMask, keyboard) != Success ) {
		errx(1, "Error obtaining symbolic names");
	}

	if(pflag){
		if( XkbGetState(display, XkbUseCoreKbd, &state) != Success ) {
			errx(1, "Error getting keyboard state");
		}	

		if( sflag ) {
			printf( "%.2s\n", XGetAtomName(display, keyboard->names->groups[state.group]) );
		}
		else {
			printf( "%s\n", XGetAtomName(display, keyboard->names->groups[state.group]) );
		}
	}

	if(lflag){
	    Atom current_group;
	    int i = 0;
	    for (; i < XkbNumKbdGroups; i++) {
	        if ( (current_group = keyboard->names->groups[i]) != 0 ) {
	            char* group_name = XGetAtomName(display, current_group);
	            if (group_name != NULL) {
	            	printf( "%d. %s\n", i, group_name );
	            }
	            XFree(group_name);
	        }
	    }
	}

	if(tflag){
		if (group_num < 0 || group_num > XkbNumKbdGroups){
			errx(1, "Error setting keyboard layout. Group number is not correct.");
		}
		if (XkbNumKbdGroups >= 0) {
		    XkbLockGroup(display, XkbUseCoreKbd, group_num);
		    XkbStateRec state;
	    	if( XkbGetState(display, XkbUseCoreKbd, &state) != Success ){
				errx(1, "Error getting keyboard state");
			}	
	    }
	}

	// Free symbolic names structures 
	XkbFreeNames(keyboard, XkbGroupNamesMask, True);
	return 0;
}

void usage(void){
	printf( "Usage: [options]\n\n"
		"Options:\n"
		"\t-p  - print current keyboard layout\n"
		"\t-s  - short version (just 2 literals)\n"
		"\t-l  - show list of all availible layouts\n"
		"\t-t group_num  - set current layout to 'group_num'\n"

		"\nExamples:\n"
		"\t$ xkblang -ps\n"
		"\t$ En\n\n"
		"\t$ xkblang -l\n"
		"\t0. English (US)\n"
		"\t1. Russian\n\n"
		"\t$ xkblang -t 0\n"
	);
}