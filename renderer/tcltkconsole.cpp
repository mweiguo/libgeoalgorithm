#include <locale.h>
#include "tclapi.h"
#include "tcltkconsole.h"

void WishPanic( CONST char *format, ...)
{
    va_list argList;
    char buf[1024];

    va_start(argList, format);
    vsprintf(buf, format, argList);
}

int Tcl_AppInit( Tcl_Interp *interp)
{
    Tcl_Init(interp);
    Tk_Init(interp);
    Tcl_StaticPackage(interp, "Tk", Tk_Init, Tk_SafeInit);

    Tk_InitConsoleChannels(interp);
    Tk_CreateConsoleWindow(interp);

    Tcl_SetVar(interp, "tcl_rcFileName", "./.rc", TCL_GLOBAL_ONLY);

    createcommands ( interp );
    return TCL_OK;
}

void Tk_MainThread ( int argc, char **argv )
{
    char *p;
    //Tcl_SetPanicProc(WishPanic);

    /*
     * Set up the default locale to be standard "C" locale so parsing is
     * performed correctly.
     */
    setlocale(LC_ALL, "C");

    /*
     * Forward slashes substituted for backslashes.
     */
    for (p = argv[0]; *p != '\0'; p++) {
	if (*p == '\\') {
	    *p = '/';
	}
    }

#ifdef TK_LOCAL_MAIN_HOOK
    TK_LOCAL_MAIN_HOOK(&argc, &argv);
#endif
    Tk_Main(argc, argv, Tcl_AppInit);
}
