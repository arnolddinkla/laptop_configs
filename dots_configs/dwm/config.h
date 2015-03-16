/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-tamsyn-bold-r-*-*-13-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#d4d0cd";
static const char normbgcolor[]     = "#d4d0cd"; /* bg color of tags */
static const char normfgcolor[]     = "grey47"; /* color of text in tags */
static const char selbordercolor[]  = "PaleVioletRed4";
static const char selbgcolor[]      = "#d4d0cd"; /* color of selected tag */
static const char selfgcolor[]      = "PaleVioletRed4"; /* bg color of selected tag orange was ff6600  */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gap pixel between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

/* tagging */
static const char *tags[] = { "term", "web", "file", "film", "music" };

static const Rule rules[] = {
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "Google-chrome",     NULL,       NULL,       1 << 1,       False,       -1 },
	{ "mpv",               NULL,       NULL,       1 << 3,       False,       -1 },
	{ NULL,                NULL,       "MOC",      1 << 4,       False,       -1 },
};

/* layout(s) */
static const float mfact      = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[  t  ]",      tile },    /* first entry is default */
	{ "[  f  ]",      NULL },    /* no layout function means floating behavior */
	{ "[  m  ]",      monocle },
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
static const char *dmenucmd[]    = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", normbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]     = { "xterm", NULL };
static const char *webcmd[]      = { "google-chrome-stable", NULL };
static const char *tmuxcmd[]     = { "tmux", NULL };
static const char *URxvtcmd[]    = { "urxvt", NULL };
static const char *rangercmd[]   = { "Ranger", NULL };
static const char *nanocmd[]     = { "Nano", NULL };
static const char *pvidcmd[]     = { "Mpv", NULL };
static const char *pmuscmd[]     = { "Mocp", NULL };
static const char *menucmd[]     = { "Menu", NULL };
static const char *logoutcmd[]   = { "Logout", NULL };
static const char *rebootcmd[]   = { "Reboot", NULL };
static const char *shutdowncmd[] = { "Shutdown", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = tmuxcmd } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = URxvtcmd } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = rangercmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = nanocmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = pvidcmd } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = pmuscmd } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = menucmd } },
	{ MODKEY|ControlMask,           XK_l,      spawn,          {.v = logoutcmd } },
	{ MODKEY|ControlMask,           XK_r,      spawn,          {.v = rebootcmd } },
	{ MODKEY|ControlMask,           XK_s,      spawn,          {.v = shutdowncmd } },
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
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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
