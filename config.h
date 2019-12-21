/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define GRUVBOX_DARK

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char *fonts[]          = { "Hack Nerd Font:size=10" };
static const char dmenufont[]       = "Hack Nerd Font:size=10";

#ifdef SOLARIZED_DARK

static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char s_base03[]        = "#002b36";
static const char s_base02[]        = "#073642";
static const char s_base01[]        = "#586e75";
static const char s_base00[]        = "#657b83";
static const char s_base0[]         = "#839496";
static const char s_base1[]         = "#93a1a1";
static const char s_base2[]         = "#eee8d5";
static const char s_base3[]         = "#fdf6e3";
static const char s_blue[]          = "#268bd2";
static const char s_yellow[]        = "#b58900";
static const char s_red[]           = "#dc322f";
static const char s_organge[]       = "#cb4b16";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	//[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	//[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeNorm] = { s_base1, s_base03, s_base01 },
	[SchemeSel]  = { s_blue, s_base03, s_blue },
    [SchemeUrgent] = { s_red, s_base03, s_red },
	//[SchemeSel]  = { s_base0, s_base02, s_blue },
};

static const char *dmenu_nb = s_base03;
static const char *dmenu_nf = s_base1;
static const char *dmenu_sb = s_base02;
static const char *dmenu_sf = s_base0;

#endif

#ifdef GRUVBOX_DARK

static const char dark0_hard[]      = "#1D2021";
static const char dark0[]           = "#282828";
static const char dark0_soft[]      = "#32302F";
static const char dark1[]           = "#3c3836";
static const char dark2[]           = "#504945";
static const char dark3[]           = "#665C54";
static const char dark4[]           = "#7C6F64";

static const char gray_245[]        = "#928374";
static const char gray_244[]        = "#928374";

static const char light0_hard[]     = "#F9F5D7";
static const char light0[]          = "#FBF1C7";
static const char light0_soft[]     = "#F2E5BC";
static const char light1[]          = "#EBDBB2";
static const char light2[]          = "#D5C4A1";
static const char light3[]          = "#BDAE93";
static const char light4[]          = "#A89984";

static const char bright_red[]      = "#FB4934";
static const char bright_green[]    = "#B8BB26";
static const char bright_yellow[]   = "#FABD2F";
static const char bright_blue[]     = "#83A598";
static const char bright_purple[]   = "#D3869B";
static const char bright_aqua[]     = "#8EC07C";
static const char bright_orange[]   = "#FE8019";

static const char neutral_red[]     = "#CC241D";
static const char neutral_green[]   = "#98971A";
static const char neutral_yellow[]  = "#D79921";
static const char neutral_blue[]    = "#458588";
static const char neutral_purple[]  = "#B16286";
static const char neutral_aqua[]    = "#689D6A";
static const char neutral_orange[]  = "#D65D0E";

static const char faded_red[]       = "#9D0006";
static const char faded_green[]     = "#79740E";
static const char faded_yellow[]    = "#B57614";
static const char faded_blue[]      = "#076678";
static const char faded_purple[]    = "#8F3F71";
static const char faded_aqua[]      = "#427B58";
static const char faded_orange[]    = "#AF3A03";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { light0, dark0, gray_244 },
	[SchemeSel]  = { neutral_blue, dark0, light0 },
    [SchemeUrgent] = { neutral_red, dark0, neutral_red },
};

static const char *dmenu_nb = dark0;
static const char *dmenu_nf = gray_244;
static const char *dmenu_sb = dark1;
static const char *dmenu_sf = light0;
#endif

static const char *nutags[][9]      = {
    [SchemeNorm] = { "", "", "", "", "", "", "", "", "" },
    [SchemeSel]  = { "", "", "", "", "", "", "", "", "" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", dark0, "-nf", gray_244, "-sb", dark4, "-sf", light0, NULL };
static const char *termcmd[]  = { "st", NULL };

//static const char *volup[]   = { "amixer", "sset", "Master", "5%+", NULL };
//static const char *voldown[] = { "amixer", "sset", "Master", "5%-", NULL };
//static const char *volmute[] = { "amixer", "sset", "Master", "toggle", NULL };
static const char *volup[]   = { "vol_up", NULL };
static const char *voldown[] = { "vol_down", NULL };
static const char *volmute[] = { "vol_toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volup} },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldown} },
    { 0,                            XF86XK_AudioMute,        spawn, {.v = volmute} },

	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

