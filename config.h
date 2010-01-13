/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]            = "-*-terminus-medium-r-normal-*-14-*-*-*-*-*-*-*";
static const char normbordercolor[] = "#005050";
static const char selbordercolor[]  = "#ff0000";
static const char normbgcolor[]     = "#cccccc";
static const char normfgcolor[]     = "#000000";
static const char selbgcolor[]      = "#8517d2";
static const char selfgcolor[]      = "#ffffff";
static unsigned int borderpx        = 2;        /* border pixel of windows */
static unsigned int snap            = 32;       /* snap pixel */
static Bool showbar                 = True;     /* False means no bar */
static Bool topbar                  = True;     /* False means bottom bar */

/* tagging */
static const char * tags[MAXTAGS] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static Rule rules[] = {
	/* class      instance    title       tags mask     isfloating      Monitor*/
	{ "Gimp",     NULL,       NULL,       0,            False,          -1},
	{ "MPlayer",  NULL, 	    NULL,       0,            True ,          -1},
	{ "Gimmix",   NULL,       NULL,       1<<8,         False,          -1},
	{ "Firefox",  NULL,       NULL, 	    1<<4,         False,          -1},
	{ "Firefox",  NULL,  "Настройки",     0,            True,           -1},
	{ "Firefox",  NULL,   "Загрузки",     0,            True,           -1},
	{ "Firefox",  NULL,   "DownThemAll",  0,            True,           -1},
   { "Thunderbird"    ,NULL, NULL  , 1<<3,            False ,          -1},
	{ "Thunderbird",NULL,"Настройки", 0,            True ,          -1},
	{ "Thunderbird",NULL,"Составление", 0,            True ,          -1},
	{ "Thunderbird",NULL,"Поиск", 0,            True ,          -1},
	{ "Gajim", 	  NULL, 	    NULL,       1<<5,         False,          -1},
	{ "Tkabber",  NULL,       NULL,       1<<5,         False,          -1},
	{ "SAPGUI",   NULL,       NULL,       0,            True,           -1},
	{ "VirtualBox",NULL,      NULL,       0,            True,           -1},
	{ NULL, "gtk_file_chooser",NULL,      0,            True,           -1},
	{ "Vncviewer", NULL,      NULL,       0,            True,           -1},
	{ "nxclient", NULL,       NULL,       0,            True,           -1},
	{ "Ario",     NULL,       NULL,       1<<8,         False,          -1},
	{ "Pidgin",   NULL,       NULL,       1<<5,         False,          -1},
	{ "qemu",     NULL,       NULL,       0,            True,           -1},
	{ "XTerm",    NULL,  "NXclient",      0,            True,           -1}
};

/* layout(s) */
static Bool resizehints = True; /* False means respect size hints in tiled resizals */

static Layout layouts[] = {
	/* symbol     arrange function */
	{ "<--",      tilel},
	{ "-->",      tiler },
	{ "/|\\",      tileu },
	{ "\\|/",     tiled },
	{ "\\\\\\",      NULL },
	{ "[M]",      monocle },
	{ "=-=",      accordion}
};
#define TILE_ACCORDION (&layouts[6])
#define TILE_LEFT (&layouts[0])
#define TILE_RIGHT (&layouts[1])
#define TILE_TOP (&layouts[2])
#define TILE_BOTTOM (&layouts[3])

static TagItem tagitems[] = {

		// layout           mfact    mainarea
		[0] = { TILE_ACCORDION,      0.8 ,    1}, 
		[1] = { TILE_ACCORDION,      0.8 ,    1},
		[2] = { TILE_TOP      ,      0.55,    1},
		[3] = { TILE_TOP      ,      0.55,    1},
		[4] = { TILE_TOP      ,      0.55,    1},
		[5] = { TILE_LEFT     ,      0.65,    1},
		[6] = { TILE_TOP      ,      0.55,    1},
		[7] = { TILE_TOP      ,      0.55,    1},
		[8] = { TILE_LEFT     ,      0.42,    1} 
};

//static TagItem DefaultTagItem = { TILE_LEFT, 0.6, 1};


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
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "uxterm", "-tn", "xterm-256color", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_h,      setmainarea,    {.i = -1}  },
	{ MODKEY|ControlMask,           XK_l,      setmainarea,    {.i = +1} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_a,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[6]} },
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
	{ MODKEY,                       XK_q,      restart,        {0} }
};

/* button definitions */
/* click can be a tag number (starting at 0),
 * ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

