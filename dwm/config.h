#include <X11/XF86keysym.h>

/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 14;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int user_bh           = 23;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

static const char *fonts[]          = { "Product Sans:size=11", "Stick:size=11", "Material Design Icons:size=11", "JetBrains Mono Nerd Font:pixelsize=15" };
static const char dmenufont[]       = {"monospace:size=11"};

static const unsigned int gappx     = 11;        /* gaps between windows */



static const char fg[]              = "#ffffff";
static const char nord_fg[]         = "#D8DEE9";
static const char one_bg[]          = "#1C1B1D";
static const char nord_bg[]         = "#2E3440";
static const char one_green[]       = "#98c379";
static const char nord_blue[]       = "#81A1C1";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { nord_fg,   nord_bg,   nord_bg   },
	[SchemeSel]  = { nord_bg,   nord_blue, nord_blue },
};




/* staticstatus */
static const int statmonval = 0;

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance     title           tags mask   isfloating  isterminal  noswallow  monitor */
	{ "Alacritty",NULL,       NULL,           0,            0,        1,          0,         -1 },
	{ "discord",  NULL,       NULL,           1 << 3,       0,        0,          0,         -1 },
	{ NULL,       NULL,       "Event Tester", 0,            0,        0,          1,         -1 }, /* xev */
	{ "Dolphin",  NULL,				NULL,						1 << 1,				0,				0,					0,				 -1 },
};

/* Bar rules allow you to configure what is shown where on the bar, as well as
 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */
/*static const BarRule barrules[] = {
//	{ -1,       0,     BAR_ALIGN_LEFT,   width_tags,            draw_tags,            click_tags,         "tags" },
//	{ -1,       0,     BAR_ALIGN_LEFT,   width_ltsymbol,        draw_ltsymbol,        click_ltsymbol,     "layout" },
//	{ 'A',      0,     BAR_ALIGN_RIGHT,  width_status,          draw_status,          click_status,       "status" },
//	{ -1,       0,     BAR_ALIGN_NONE,   width_wintitle,        draw_wintitle,        click_wintitle,     "wintitle" },
//};

 * introducing your own bar modules.
 *
 *    monitor:
 *      -1  show on all monitors
 *       0  show on monitor 0
 *      'A' show on active monitor (i.e. focused / selected) (or just -1 for active?)
 *    bar - bar index, 0 is default, 1 is extrabar
 *    alignment - how the module is aligned compared to other modules
 *    widthfunc, drawfunc, clickfunc - providing bar module width, draw and click functions
 *    name - does nothing, intended for visual clue and for logging / debugging
 */


/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
//	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *rofi[] = { "rofi", "-show", "drun", "-modi", "drun", "-display-drun", "", NULL };
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *pavu[]     = { "pavucontrol", NULL };

static const char *suspend[]    = { "systemctl", "suspend", NULL };
static const char *restart[]  = { "reboot", NULL };
static const char *shutdown[] = { "shutdown", "now", NULL };


static const char *vol_up[]   = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+2%", NULL };
static const char *vol_down[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-2%", NULL };
static const char *vol_mute[] = { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *play_tggl[]= { "playerctl", "play-pause", NULL };
static const char *play_next[]= { "playerctl", "next", NULL };
static const char *play_prev[]= { "playerctl", "previous", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,				                XK_w,      killclient,     {0} }, // kill window
	{ MODKEY|ShiftMask,             XK_q,      quit,     	   {0} }, // quit dwm

	// restart, shutdown, and sleep controls
	{ MODKEY|ShiftMask,		XK_s,	   spawn,	   {.v = suspend } },
	{ MODKEY|ShiftMask,		XK_r,	   spawn,	   {.v = restart } },
	{ MODKEY|ShiftMask,		XK_a,	   spawn,	   {.v = shutdown } },
	// open programs
	{ MODKEY,                       XK_d,      spawn,          {.v = rofi } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,												XK_f,      spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,           XK_p,      spawn,            {.v = pavu } },

	// laptop audio control
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = vol_up } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = vol_down } },
	{ 0,                            XF86XK_AudioMute       , spawn, {.v = vol_mute } },
	{ 0,                            XF86XK_AudioPlay       , spawn, {.v = play_tggl } },
	{ 0,                            XF86XK_AudioNext       , spawn, {.v = play_next } },
	{ 0,                            XF86XK_AudioPrev       , spawn, {.v = play_prev } },

	// window layout and control
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },                // toggle float per window
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tiling
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} }, // decrease master size
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} }, // increase master size
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } }, // focus down
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } }, // focus up

	{ MODKEY,                       XK_b,      togglebar,      {0} }, // show bar

	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } }, // more master nodes
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } }, // less measter nodes

	{ MODKEY,                       XK_z,      zoom,           {0} }, // zoom on selected window

	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, // focus monitor left
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, // focus monitor right
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, // tag monitor left
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, // tag monitor right
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
 
	{ MODKEY,                       XK_Tab,    view,           {0} }, // view last tag
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } }, // view all tags
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
//	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
//	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
//	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
//	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
//	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
//	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
//	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

