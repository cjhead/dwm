/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx        = 1;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
    "Hack Nerd Font:size=10:antialias=true:autohint=true",
    "JoyPixels:pixelsize=12:antialias=true:autohint=true" };
static char dmenufont[]             = "Hack Nerd Font:size=10:antialias=true:autohint=true";
static char col0[]                  = "#ffffff";
static char col1[]                  = "#ffffff";
static char col2[]                  = "#ffffff";
static char col3[]                  = "#ffffff";
static char col4[]                  = "#ffffff";
static char col5[]                  = "#ffffff";
static char col6[]                  = "#ffffff";
static char col7[]                  = "#ffffff";
static char col8[]                  = "#ffffff";
static char col9[]                  = "#ffffff";
static char col10[]                 = "#ffffff";
static char col11[]                 = "#ffffff";
static char col12[]                 = "#ffffff";
static char col13[]                 = "#ffffff";
static char col14[]                 = "#ffffff";
static char col15[]                 = "#ffffff";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";

static char *colors[][3] = {
       /*               fg           bg           border   */
    [SchemeNorm]  = { normfgcolor, normbgcolor, normbordercolor }, /* \x0b white        */
    [SchemeSel]   = { selfgcolor,  selbgcolor,  selbordercolor  }, /* \x0c              */
    [SchemeCol0]  = { col0,        normbgcolor, normbordercolor }, /* \x0d black        */
    [SchemeCol1]  = { col1,        normbgcolor, normbordercolor }, /* \x0e red          */
    [SchemeCol2]  = { col2,        normbgcolor, normbordercolor }, /* \x0f light green  */
    [SchemeCol3]  = { col3,        normbgcolor, normbordercolor }, /* \x10 yellow       */
    [SchemeCol4]  = { col4,        normbgcolor, normbordercolor }, /* \x11 white        */
    [SchemeCol5]  = { col5,        normbgcolor, normbordercolor }, /* \x12 magenta      */
    [SchemeCol6]  = { col6,        normbgcolor, normbordercolor }, /* \x13 white        */
    [SchemeCol7]  = { col7,        normbgcolor, normbordercolor }, /* \x14 white        */
    [SchemeCol8]  = { col8,        normbgcolor, normbordercolor }, /* \x15 black        */
    [SchemeCol9]  = { col8,        normbgcolor, normbordercolor }, /* \x16 black        */
    [SchemeCol10] = { col10,       normbgcolor, normbordercolor }, /* \x17 light green  */
    [SchemeCol11] = { col11,       normbgcolor, normbordercolor }, /* \x18 yellow       */
    [SchemeCol12] = { col12,       normbgcolor, normbordercolor }, /* \x19 light blue   */
    [SchemeCol13] = { col13,       normbgcolor, normbordercolor }, /* \x1a magenta      */
    [SchemeCol14] = { col14,       normbgcolor, normbordercolor }, /* \x1b lighter blue */
    [SchemeCol15] = { col15,       normbgcolor, normbordercolor }, /* \x1c white        */
 };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",      NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox",   NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "St",        NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "Brave",     NULL,     NULL,           0,         0,          0,           1,        -1 },
    { "Tk",        NULL,     NULL,           0,         1,          0,           1,        -1 },
    { "python3.9", NULL,     NULL,           0,         1,          0,           1,        -1 },
	{ NULL,        NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static float mfact              = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster              = 1;    /* number of clients in master area */
static int resizehints          = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints     = 1;    /* 1 means respect decoration hints */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, "-l", "20", "-c",  NULL };
static const char *termcmd[]  = { "st", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		// { "font",               STRING,  &font },
		{ "dmenufont",          STRING,  &dmenufont },
		// { "normbgcolor",        STRING,  &normbgcolor },
		// { "normbordercolor",    STRING,  &normbordercolor },
		// { "normfgcolor",        STRING,  &normfgcolor },
		// { "selbgcolor",         STRING,  &selbgcolor },
		// { "selbordercolor",     STRING,  &selbordercolor },
		// { "selfgcolor",         STRING,  &selfgcolor },
        { "background",         STRING,  &normbgcolor },
        { "background",         STRING,  &normbordercolor },
        { "foreground",         STRING,  &normfgcolor },
        { "color0",             STRING,  &col0 },
        { "color1",             STRING,  &col1 },
        { "color2",             STRING,  &col2 },
        { "color3",             STRING,  &col3 },
        { "color4",             STRING,  &selbgcolor },
        { "color5",             STRING,  &col5 },
        { "color6",             STRING,  &selbordercolor },
        { "color7",             STRING,  &col7 },
        { "color8",             STRING,  &col8 },
        { "color9",             STRING,  &col9 },
        { "color10",            STRING,  &col10 },
        { "color11",            STRING,  &col11 },
        { "color12",            STRING,  &col12 },
        { "color13",            STRING,  &col13 },
        { "color14",            STRING,  &col14 },
        { "color15",            STRING,  &col15 },
        { "background",         STRING,  &selfgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "snap",          		INTEGER, &snap },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",          	INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",      	 	FLOAT,   &mfact },
};

#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("passmenu") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },

    { 0,                            XK_Print,  spawn,          SHCMD("maimfull") },
    { ShiftMask,                    XK_Print,  spawn,          SHCMD("maimclip") },
    { 0, XF86XK_AudioMute,                     spawn,          SHCMD("pamixer -t; sigdwmblocks 1") },
    { 0, XF86XK_AudioRaiseVolume,              spawn,          SHCMD("pamixer -i 5; sigdwmblocks 1") },
    { 0, XF86XK_AudioLowerVolume,              spawn,          SHCMD("pamixer -d 5; sigdwmblocks 1") },
    { MODKEY|ShiftMask,             XK_Right,  spawn,          SHCMD("brightnessctl -q set +10%") },
    { MODKEY|ShiftMask,             XK_Left,   spawn,          SHCMD("brightnessctl -q set 10%-") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
    { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
    { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
