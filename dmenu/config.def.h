/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {	"Product Sans:size=11", "Stick:size=11", "Material Design Icons:size=11", "JetBrains Mono Nerd Font:pixelsize=15"};
static const char nord_fg[]         = "#D8DEE9";
static const char nord_bg[]         = "#2E3440";
static const char nord_blue[]       = "#81A1C1";

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { nord_fg,   nord_bg},
	[SchemeSel]  = { nord_bg,   nord_blue},
	[SchemeOut] = { "#000000", "#00ffff" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;
/* -h option; minimum height of a menu line */
static unsigned int lineheight = 24;
static unsigned int min_lineheight = 10;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
