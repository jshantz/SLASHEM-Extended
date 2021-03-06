/*	SCCS Id: @(#)objects.c	3.4	2002/07/31	*/
/* Copyright (c) Mike Threepoint, 1989.				  */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef OBJECTS_PASS_2_
/* first pass */
struct monst { struct monst *dummy; };	/* lint: struct obj's union */
#include "config.h"
#include "obj.h"
#include "objclass.h"
#include "prop.h"
#include "skills.h"
#include "skills.h"

#else	/* !OBJECTS_PASS_2_ */
/* second pass */
#include "color.h"
#  define COLOR_FIELD(X) X,
#endif	/* !OBJECTS_PASS_2_ */



/* objects have symbols: ) [ = " ( % ! ? + / $ * ` 0 _ . */

/*
 *	Note:  OBJ() and BITS() macros are used to avoid exceeding argument
 *	limits imposed by some compilers.  The ctnr field of BITS currently
 *	does not map into struct objclass, and is ignored in the expansion.
 *	The 0 in the expansion corresponds to oc_pre_discovered, which is
 *	set at run-time during role-specific character initialization.
 */

#ifndef OBJECTS_PASS_2_
/* first pass -- object descriptive text */
# define OBJ(name,desc) name,desc
# define OBJECT(obj,bits,prp,sym,prob,dly,wt,cost,sdam,ldam,oc1,oc2,nut,color) \
	{obj}

NEARDATA struct objdescr obj_descr[] = {
#else
/* second pass -- object definitions */

# define BITS(nmkn,mrg,uskn,ctnr,mgc,chrg,uniq,nwsh,big,tuf,dir,sub,mtrl) \
	nmkn,mrg,uskn,0,mgc,chrg,uniq,nwsh,big,tuf,dir,mtrl,sub /* SCO ODT 1.1 cpp fodder */
# define OBJECT(obj,bits,prp,sym,prob,dly,wt,cost,sdam,ldam,oc1,oc2,nut,color) \
	{0, 0, (char *)0, bits, prp, sym, dly, COLOR_FIELD(color) \
	 prob, wt, cost, sdam, ldam, oc1, oc2, nut}
# ifndef lint
#  define HARDGEM(n) (n >= 8)
# else
#  define HARDGEM(n) (0)
# endif

NEARDATA struct objclass objects[] = {
#endif
/* dummy object[0] -- description [2nd arg] *must* be NULL */
	OBJECT(OBJ("strange object",(char *)0), BITS(1,0,0,0,0,0,0,0,0,0,0,0,0),
			0, ILLOBJ_CLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),

/* weapons ... */
#define WEAPON(name,app,kn,mg,bi,prob,wt,cost,sdam,ldam,hitbon,typ,sub,metal,color) \
	OBJECT( \
		OBJ(name,app), BITS(kn,mg,1,0,0,1,0,0,bi,0,typ,sub,metal), 0, \
		WEAPON_CLASS, prob, 0, \
		wt, cost, sdam, ldam, hitbon, 0, wt, color )
#define PROJECTILE(name,app,kn,prob,wt,cost,sdam,ldam,hitbon,metal,sub,color) \
	OBJECT( \
		OBJ(name,app), BITS(kn,1,1,0,0,1,0,0,0,0,PIERCE,sub,metal), 0, \
		WEAPON_CLASS, prob, 0, \
		wt, cost, sdam, ldam, hitbon, WP_GENERIC, wt, color )
#define BOW(name,app,kn,bi,prob,wt,cost,hitbon,metal,sub,color) \
	OBJECT( \
		OBJ(name,app), BITS(kn,0,1,0,0,1,0,0,bi,0,0,sub,metal), 0, \
		WEAPON_CLASS, prob, 0, \
		wt, cost, 0, 0, hitbon, WP_GENERIC, wt, color )
#define BULLET(name,app,kn,prob,wt,cost,sdam,ldam,hitbon,ammotyp,typ,metal,sub,color) \
	OBJECT( \
		OBJ(name,app), BITS(kn,1,1,0,0,1,0,0,0,0,typ,sub,metal), 0, \
		WEAPON_CLASS, prob, 0, \
		wt, cost, sdam, ldam, hitbon, ammotyp, wt, color )
#define GUN(name,app,kn,bi,prob,wt,cost,range,rof,hitbon,ammotyp,metal,sub,color) \
	OBJECT( \
		OBJ(name,app), BITS(kn,0,1,0,0,1,0,0,bi,0,0,sub,metal), 0, \
		WEAPON_CLASS, prob, 0, \
		wt, cost, range, rof, hitbon, ammotyp, wt, color )

/* Note: for weapons that don't do an even die of damage (ex. 2-7 or 3-18)
 * the extra damage is added on in weapon.c, not here! */

#define P PIERCE
#define S SLASH
#define B WHACK
#define E EXPLOSION

/* Daggers */
WEAPON("orcish dagger", "crude dagger",
	0, 1, 0,  25, 4,  4,  2,  1, 1, P,   P_DAGGER, IRON, CLR_BLACK),
WEAPON("dagger", (char *)0,
	1, 1, 0,  45, 4,  4,  3,  2, 1, P,   P_DAGGER, IRON, HI_METAL),
WEAPON("athame", (char *)0,
	1, 1, 0,  10, 4,  4,  4,  3, 1, S,   P_DAGGER, IRON, HI_METAL),
WEAPON("silver dagger", (char *)0,
	1, 1, 0,  10, 4, 40,  3,  2, 1, P,   P_DAGGER, SILVER, HI_SILVER),
	/* STEPHEN WHITE'S NEW CODE */
	/* WAC silver dagger now pierces, to be same as other daggers
        allows it to be thrown without penalty as well*/
WEAPON("elven dagger", "runed dagger",
	0, 1, 0,  30, 4,  4,  3,  3, 1, P,   P_DAGGER, WOOD, HI_METAL),
WEAPON("dark elven dagger", "black runed dagger",
	0, 1, 0,  10, 4,  4,  4,  4, 1, P,   P_DAGGER, WOOD, CLR_BLACK),
WEAPON("wooden stake", (char *)0,
	1, 0, 0,  10, 8, 50,  4,  3, 1, P,   P_DAGGER, WOOD, HI_WOOD),
	/* STEPHEN WHITE'S NEW CODE */
    /* Base for artifact (Stake of Van Helsing) */
WEAPON("great dagger", (char *)0,
	1, 0, 0,  10, 8,500,  5,  4, 1, P,   P_DAGGER, METAL, CLR_BLACK),
	/* STEPHEN WHITE'S NEW CODE */
	/* for necromancer artifact... */

/* Knives */
WEAPON("worm tooth", (char *)0,
	1, 0, 0,  10, 2,  2,  2,  2, 0, 0,   P_KNIFE, 0, CLR_WHITE),
WEAPON("knife", (char *)0,
	1, 1, 0,  35,  2,  4,  3,  2, 0, P|S, P_KNIFE, IRON, HI_METAL),
WEAPON("stiletto", (char *)0,
	1, 1, 0,  25,  2,  4,  3,  2, 1, P|S, P_KNIFE, IRON, HI_METAL),
WEAPON("scalpel", (char *)0,
	1, 1, 0,  14,  2,  4,  3,  3, 2, S,   P_KNIFE, METAL, HI_METAL),
WEAPON("crysknife", (char *)0,
	1, 0, 0,  10, 2,100, 20, 30, 3, P,   P_KNIFE, MINERAL, CLR_WHITE),

WEAPON("tooth of an algolian suntiger",	"very sharp tooth",
	0, 0, 0,  1, 10,500, 15, 15, 5, 0, P_KNIFE, MINERAL, CLR_WHITE),

	/* [Tom] increased crysknife damage from d10/d10 */
	/* to d20/d30 (otherwise, it's useless to make them...) */

/* Axes */
WEAPON("axe", (char *)0,
	1, 0, 0, 175, 24,  8,  8,  4, 0, S,   P_AXE, IRON, HI_METAL),
WEAPON("battle-axe", "double-headed axe", /* "double-bitted" ? */
	0, 0, 1, 50, 48, 40,  12,  9, 0, S,   P_AXE, IRON, HI_METAL),

/* Pick-axes */
/* (also weptool pick-axe) */
WEAPON("dwarvish mattock", "broad pick",
	0, 0, 1, 65, 48, 50, 18,  12,0, B,   P_PICK_AXE, IRON, HI_METAL),

/* Short swords */
WEAPON("orcish short sword", "crude short sword",
	0, 0, 0, 15, 12, 10,  5,  8, 0, P,   P_SHORT_SWORD, IRON, CLR_BLACK),
WEAPON("short sword", (char *)0,
	1, 0, 0, 30, 12, 10,  6,  8, 0, P,   P_SHORT_SWORD, IRON, HI_METAL),
WEAPON("silver short sword", (char *)0,
	1, 0, 0, 10, 12, 50,  6,  8, 0, P,   P_SHORT_SWORD, SILVER, HI_SILVER),
	/* STEPHEN WHITE'S NEW CODE */
WEAPON("dwarvish short sword", "broad short sword",
	0, 0, 0, 10, 12, 10,  7,  8, 0, P,   P_SHORT_SWORD, IRON, HI_METAL),
WEAPON("elven short sword", "runed short sword",
	0, 0, 0, 10, 12, 10,  8,  8, 0, P,   P_SHORT_SWORD, WOOD, HI_METAL),
WEAPON("dark elven short sword", "black runed short sword",
	0, 0, 0, 10, 12, 10,  9,  9, 0, P,   P_SHORT_SWORD, WOOD, CLR_BLACK),

/* Broadswords */
WEAPON("broadsword", (char *)0,
	1, 0, 0, 90, 30, 10,  7,  10, 0, S,   P_BROAD_SWORD, IRON, HI_METAL),
						/* +d4 small, +1 large */
WEAPON("runesword", "runic broadsword",
	0, 0, 0,  5, 30,300,  7,  10, 0, S,   P_BROAD_SWORD, IRON, CLR_BLACK),
	/* +d4 small, +1 large; base for artifact (Stormbringer) */
	/* +5d2 +d8 from level drain */
WEAPON("elven broadsword", "runed broadsword",
	0, 0, 0, 25, 30, 10,  10,  10, 0, S,   P_BROAD_SWORD, WOOD, HI_METAL),
						/* +d4 small, +1 large */

/* Long swords */
WEAPON("long sword", (char *)0,
	1, 0, 0, 229, 16, 15,  8, 12, 0, S,   P_LONG_SWORD, IRON, HI_METAL),
WEAPON("silver long sword", (char *)0,
	1, 0, 0, 10, 16, 75,  8, 12, 0, S,   P_LONG_SWORD,SILVER, HI_SILVER),
	/* STEPHEN WHITE'S NEW CODE */
WEAPON("katana", "samurai sword",
	0, 0, 0, 20, 16, 80, 10, 12, 1, S,   P_LONG_SWORD, IRON, HI_METAL),
WEAPON("electric sword", (char *)0,
	1, 0, 0,  1, 16,200, 12, 16, 2, S,   P_LONG_SWORD, IRON, HI_METAL),

/* Two-handed swords */
WEAPON("two-handed sword", (char *)0,
	1, 0, 1, 125,60, 50, 18,  9, 0, S,   P_TWO_HANDED_SWORD, IRON, HI_METAL),
	/* +2d6 large */
WEAPON("tsurugi", "long samurai sword",
	0, 0, 1, 10, 24,500, 24,  12, 2, S,   P_TWO_HANDED_SWORD, METAL, HI_METAL),
	/* +2d6 large; base for artifact (T of Muramasa) */

/* Scimitars */
WEAPON("scimitar", "curved sword",
	0, 0, 0, 65, 16, 15,  8,  8, 0, S,   P_SCIMITAR, IRON, HI_METAL),
WEAPON("bent sable", "bent sword",
	0, 0, 0, 10, 16, 15,  12,  12, 0, S,   P_SCIMITAR, IRON, HI_METAL),

/* Sabers */
WEAPON("rapier", (char *)0,
	1, 0, 0, 10, 12, 40,  6,  8,  0, P,  P_SABER, METAL, CLR_BLACK),
	/* STEPHEN WHITE'S NEW CODE */
	/* Base for artifact (Scalpel) */
WEAPON("silver saber", (char *)0,
	1, 0, 0, 115, 12, 75,  8,  8, 0, S,   P_SABER, SILVER, HI_SILVER),
WEAPON("golden saber", (char *)0,
	1, 0, 0, 10, 12, 75,  10,  10, 0, S,   P_SABER, GOLD, CLR_YELLOW),

/* Clubs */
WEAPON("club", (char *)0,
	1, 0, 0, 60, 12,  3,  6,  3, 0, B,   P_CLUB, WOOD, HI_WOOD),
WEAPON("aklys", "thonged club",
	0, 0, 0, 50, 7,  4,  7,  3, 0, B,   P_CLUB, IRON, HI_METAL),
WEAPON("baseball bat", (char *)0,
	1, 0, 0, 20, 12, 50,  8,  6, 0, B,   P_CLUB, WOOD, HI_WOOD),
WEAPON("metal club", "heavy club",
	0, 0, 0, 5, 7,  4,  10,  8, 0, B,   P_CLUB, IRON, HI_METAL),

	/* STEPHEN WHITE'S NEW CODE */
	/* Base for artifact */

/* Paddles */
/* Good to-hit and small damage, but low large damage */
WEAPON("fly swatter", (char *)0,
	1, 0, 0,  50, 4,  3, 15,  2, 2, B,   P_PADDLE, PLASTIC, CLR_GREEN),
WEAPON("insect squasher", (char *)0,
	1, 0, 0,  5, 4,  3, 30,  2, 4, B,   P_PADDLE, PLASTIC, CLR_GREEN),

/* Maces */
WEAPON("silver mace", (char *)0,
	1, 0, 0, 60, 12, 65,  6,  7, 0, B,   P_MACE, SILVER, HI_SILVER),
	/* STEPHEN WHITE'S NEW CODE */
WEAPON("mace", (char *)0,
	1, 0, 0, 165, 12,  5,  6,  7, 0, B,   P_MACE, IRON, HI_METAL),
	/* +1 small */

WEAPON("flanged mace", (char *)0,
	1, 0, 0, 15, 12,  5,  8,  9, 0, B,   P_MACE, IRON, HI_METAL),

/* Morning stars */
WEAPON("morning star", (char *)0,
	1, 0, 0, 100,48, 10,  4, 12, 0, B,   P_MORNING_STAR, IRON, HI_METAL),
						/* +d4 small, +1 large */

WEAPON("jagged star", (char *)0,
	1, 0, 0, 20,48, 10,  7,  15, 0, B,   P_MORNING_STAR, IRON, HI_METAL),

WEAPON("devil star", (char *)0,
	1, 0, 0, 5,48, 10,  12,  18, 0, B,   P_MORNING_STAR, IRON, HI_METAL),

/* Flails */
WEAPON("flail", (char *)0,
	1, 0, 0, 150, 7,  4,  6,  4, 1, B,   P_FLAIL, IRON, HI_METAL),
	/* +1 small, +1d4 large */

WEAPON("knout", (char *)0,
	1, 0, 0, 30, 7,  4,  9,  6, 2, B,   P_FLAIL, IRON, HI_METAL),

WEAPON("obsid", (char *)0,
	1, 0, 0,  5, 7,  4,  12,  8, 3, B,   P_FLAIL, IRON, HI_METAL),

/* Hammers */
WEAPON("war hammer", (char *)0,
	1, 0, 0, 120, 20,  5,  7,  7, 0, B,   P_HAMMER, IRON, HI_METAL),
	/* +1 small */
WEAPON("heavy hammer", (char *)0,
	1, 0, 0, 10, 24,500, 10, 10, 0, B,   P_HAMMER, METAL, HI_METAL),
	/* STEPHEN WHITE'S NEW CODE */
	/* Base for artifact */

WEAPON("mallet", (char *)0,
	1, 0, 0,  5, 20,500, 14, 14, 0, B,   P_HAMMER, WOOD, HI_WOOD),

/* Yes, these are melee weapons for whacking enemies to death. Hammer skill, for obvious reasons. --Amy */
WEAPON("wedged little-girl sandal", (char *)0,
	1, 0, 0, 5, 1,  5,  4,  4, 2, B,   P_HAMMER, MINERAL, CLR_WHITE),
WEAPON("soft girl sneaker", (char *)0,
	1, 0, 0, 5, 2,  100,  2,  2, 5, B,   P_HAMMER, LEATHER, CLR_RED),
WEAPON("sturdy plateau boot for girls", (char *)0,
	1, 0, 0, 5, 10,  200,  6,  6, 1, B,   P_HAMMER, METAL, CLR_BRIGHT_BLUE),
WEAPON("hugging boot", (char *)0,
	1, 0, 0, 5, 5,  100,  9,  8, 0, B,   P_HAMMER, MITHRIL, CLR_ORANGE),
WEAPON("block-heeled combat boot", (char *)0,
	1, 0, 0, 5, 5,  100,  11,  3, 0, B,   P_HAMMER, LEATHER, CLR_BLACK),
/* Some of these are expensive because they're supposed to be brands like Nike, Adidas etc. */
/* We won't use those brand names in-game though. */

/* adult versions - these do more damage, but monsters will rarely start with them in their inventory */
WEAPON("wooden geta", (char *)0,
	1, 0, 0, 5, 1,  5,  10,  10, 0, B,   P_HAMMER, WOOD, CLR_BROWN),
WEAPON("lacquered dancing shoe", (char *)0,
	1, 0, 0, 5, 2,  75,  6,  11, 0, B,   P_HAMMER, MINERAL, CLR_BLACK),
WEAPON("high-heeled sandal", (char *)0,
	1, 0, 0, 5, 1,  10,  9,  7, 0, B,   P_HAMMER, MINERAL, CLR_WHITE),
WEAPON("sexy leather pump", (char *)0,
	1, 0, 0, 5, 2,  50,  8, 10, 4, B,   P_HAMMER, LEATHER, CLR_BRIGHT_MAGENTA),
WEAPON("spiked battle boot", (char *)0,
	1, 0, 0, 5, 5,  150,  9,  9, 2, B,   P_HAMMER, METAL, HI_METAL),

/* Quarterstaves */
WEAPON("quarterstaff", "staff",
	0, 0, 1, 60, 16,  5,  9,  9, 0, B,   P_QUARTERSTAFF, WOOD, HI_WOOD),
WEAPON("battle staff", (char *)0,
	0, 0, 1, 5, 16,  5,  15,  15, 0, B,   P_QUARTERSTAFF, METAL, HI_METAL),

/* Polearms */
/* (also weptool fishing pole) */
/* spear-type */
WEAPON("partisan", "vulgar polearm",
	0, 0, 1,  15, 32, 10, 10,  9, 0, P,   P_POLEARMS, IRON, HI_METAL),
						/* +1 large */
WEAPON("glaive", "single-edged polearm",
	0, 0, 1,  20, 32,  6,  9, 15, 2, S,   P_POLEARMS, IRON, HI_METAL),
WEAPON("spetum", "forked polearm",
	0, 0, 1,  15, 20,  5,  9,  9, 1, P,   P_POLEARMS, IRON, HI_METAL),
						/* +1 small, +d6 large */
WEAPON("ranseur", "hilted polearm",
	0, 0, 1,  15, 20,  6,  6,  6, 3, P,   P_POLEARMS, IRON, HI_METAL),
	/* +d4 both */
/* axe-type */
WEAPON("bardiche", "long poleaxe",
	0, 0, 1,  10,48,  7,  6,  6, 0, S,   P_POLEARMS, IRON, HI_METAL),
						/* +1d4 small, +2d4 large */
WEAPON("voulge", "pole cleaver",
	0, 0, 1,  10,48,  5,  6,  6, 1, S,   P_POLEARMS, IRON, HI_METAL),
						/* +d4 both */
WEAPON("halberd", "angled poleaxe",
	0, 0, 1,  20,60, 10, 15,  9, 0, P|S, P_POLEARMS, IRON, HI_METAL),
	/* +1d6 large */
/* curved/hooked */
WEAPON("fauchard", "pole sickle",
	0, 0, 1,  15, 24,  5,  9,  12, 1, P|S, P_POLEARMS, IRON, HI_METAL),
WEAPON("guisarme", "pruning hook",
	0, 0, 1,  15, 32,  5,  6,  13, 1, S,   P_POLEARMS, IRON, HI_METAL),
						/* +1d4 small */
WEAPON("bill-guisarme", "hooked polearm",
	0, 0, 1,  10,48,  7,  6, 15, 1, P|S, P_POLEARMS, IRON, HI_METAL),
						/* +1d4 small */
/* other */
WEAPON("lucern hammer", "pronged polearm",
	0, 0, 1,  15,60,  7,  6,  16, 0, B|P, P_POLEARMS, IRON, HI_METAL),
						/* +1d4 small */
WEAPON("bec de corbin", "beaked polearm",
	0, 0, 1,  10,40,  8,  15,  9, 2, B|P, P_POLEARMS, IRON, HI_METAL),

/* Spears */
WEAPON("orcish spear", "crude spear",
	0, 1, 0, 50, 12,  3,  5,  8, 0, P,   P_SPEAR, IRON, CLR_BLACK),
WEAPON("spear", (char *)0,
	1, 1, 0, 130, 12,  3,  6,  8, 0, P,   P_SPEAR, IRON, HI_METAL),
WEAPON("silver spear", (char *)0,
	1, 1, 0, 15, 12, 40,  6,  8, 0, P,   P_SPEAR, SILVER, HI_SILVER),
	/* STEPHEN WHITE'S NEW CODE */
WEAPON("elven spear", "runed spear",
	0, 1, 0, 35, 12,  3,  7,  8, 0, P,   P_SPEAR, WOOD, HI_METAL),
WEAPON("dwarvish spear", "stout spear",
	0, 1, 0, 45, 12,  3,  8,  8, 0, P,   P_SPEAR, IRON, HI_METAL),

/* Javelins */
WEAPON("javelin", "throwing spear",
	0, 1, 0, 75, 8,  3,  6,  6, 1, P,   P_JAVELIN, IRON, HI_METAL),
WEAPON("spirit thrower", (char *)0,
	0, 1, 0, 25, 8,  3,  10,  10, 1, P,   P_JAVELIN, IRON, HI_METAL),
WEAPON("torpedo", (char *)0,
	0, 1, 0, 5, 8,  3,  16,  16, 1, P,   P_JAVELIN, IRON, HI_METAL),

/* Tridents */
WEAPON("trident", (char *)0,
	1, 0, 0,  60, 10,  5,  6,  4, 1, P,   P_TRIDENT, IRON, HI_METAL),
	/* +1 small, +2d4 large */

WEAPON("stygian pike", (char *)0,
	1, 0, 0,  5, 10,  5,  13,  11, 4, P,   P_TRIDENT, IRON, HI_METAL),

/* Lances */
WEAPON("lance", (char *)0,
	1, 0, 0,  5,75, 10,  6,  8, 0, P,   P_LANCE, IRON, HI_METAL),

/* Bows (and arrows) */
/* KMH, balance patch -- damage of launchers restored to d2 big and small */
BOW("orcish bow", "crude bow",	0, 1, 50, 12, 60, 0, WOOD, P_BOW, CLR_BLACK),
BOW("bow", (char *)0,			1, 1, 105, 12, 60, 0, WOOD, P_BOW, HI_WOOD),
BOW("elven bow", "runed bow",	0, 1, 60, 12, 60, 0, WOOD, P_BOW, HI_WOOD),
BOW("dark elven bow",  "black runed bow", 0, 1, 10, 12, 60, 1, WOOD, P_BOW, CLR_BLACK),
BOW("yumi", "long bow",			0, 1, 10, 12, 60, 0, WOOD, P_BOW, HI_WOOD),
BOW("droven bow", "spider-legged bow",	1, 0, 5, 12, 60, 5, GLASS, P_BOW, CLR_BLACK),
PROJECTILE("orcish arrow", "crude arrow",
	0, 75, 0, 2, 6, 6, 0, IRON, -P_BOW, CLR_BLACK),
PROJECTILE("arrow", (char *)0,
	1, 215, 0, 2, 7, 7, 0, IRON, -P_BOW, HI_METAL),
PROJECTILE("silver arrow", (char *)0,
	1, 75, 0, 5, 8, 8, 0, SILVER, -P_BOW, HI_SILVER),
PROJECTILE("elven arrow", "runed arrow",
	0, 115, 0, 2, 9, 9, 0, WOOD, -P_BOW, HI_METAL),
PROJECTILE("dark elven arrow", "black runed arrow",
	0, 10, 0, 2, 10, 10, 1, WOOD, -P_BOW, CLR_BLACK),
PROJECTILE("ya", "bamboo arrow",
	0, 50, 0, 4, 9, 9, 2, METAL, -P_BOW, HI_METAL),
PROJECTILE("droven arrow", "obsidian arrow",
	0, 5, 0, 6, 15, 15, 3, GLASS, -P_BOW, CLR_BLACK),

/* Slings */
BOW("sling", (char *)0,		1, 0, 200,  2, 20, 2, WOOD, P_SLING, HI_LEATHER),

/* Firearms */
#ifdef FIREARMS
GUN("pistol", (char *)0,	   1,  0, 5,  8,  100, 15,  0,  4, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("submachine gun", (char *)0,   1,  0, 5,  8,  250, 10,  3, 3, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("heavy machine gun", (char *)0,1,  1, 5, 200, 2000, 14,  8, 0, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("rifle", (char *)0,		   1,  1, 5,  12,  150, 25, -1,  5, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("assault rifle", (char *)0,	   1,  0, 5,  16, 1000, 12,  5, 2, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("sniper rifle", (char *)0,	   1,  1, 5,  20, 4000, 35, -3,  8, WP_BULLET, IRON, P_FIREARM, HI_METAL),
GUN("shotgun", (char *)0,	   1,  0, 5,  15,  200,  3, -1,  7,  WP_SHELL, IRON, P_FIREARM, HI_METAL),
GUN("auto shotgun", (char *)0,	   1,  1, 5,  24, 1500,  3,  2,  4,  WP_SHELL, IRON, P_FIREARM, HI_METAL),
GUN("rocket launcher", (char *)0,  1,  1, 5, 250, 3500, 20, -5, 0, WP_ROCKET, IRON, P_FIREARM, HI_METAL),
GUN("grenade launcher", (char *)0, 1,  1, 5,  25, 1500,  6, -3, 1,WP_GRENADE, IRON, P_FIREARM, HI_METAL),
BULLET("bullet", (char *)0,
	1,  5,   0,   5, 24, 36, 1, WP_BULLET,   P,   IRON, -P_FIREARM, HI_METAL),
BULLET("silver bullet", (char *)0,
	1,  5,   0,  15, 24, 36, 3, WP_BULLET,   P, SILVER, -P_FIREARM, HI_SILVER),
BULLET("shotgun shell", (char *)0,
	1,  5,   0,  10, 35, 55, 2,  WP_SHELL,   P,   IRON, -P_FIREARM, CLR_RED),
BULLET("rocket", (char *)0,
	1,  5, 0, 450, 60, 90, 5, WP_ROCKET, P|E,   IRON, -P_FIREARM, CLR_BRIGHT_BLUE),
BULLET("frag grenade", (char *)0,
	1,  5,  0, 350, 0, 0, 2,  WP_GRENADE, B|E,   IRON, -P_FIREARM, CLR_GREEN),
BULLET("gas grenade", (char *)0,
	1,  5,  0, 350, 0, 0, 2,  WP_GRENADE, B|E,   IRON, -P_FIREARM, CLR_ORANGE),
BULLET("stick of dynamite", "red stick",
	0,  5,  0, 150, 0, 0, 2,  WP_GENERIC,   B,   PLASTIC, P_NONE, CLR_RED),
#endif

/* Crossbows (and bolts) */
/* Crossbow range is now independant of strength */
GUN("crossbow", (char *)0,				0, 1, 200, 20, 40, 12, -1, 1, WP_GENERIC, WOOD, P_CROSSBOW, HI_WOOD),
GUN("droven crossbow", "spider-legged crossbow", 0, 0, 25, 30, 120, 12, -1, 5, WP_GENERIC, GLASS, P_CROSSBOW, CLR_BLACK), 
PROJECTILE("crossbow bolt", (char *)0,
	1, 215, 0, 2, 14, 14, 1, IRON, -P_CROSSBOW, HI_METAL),
PROJECTILE("droven bolt", "obsidian bolt",
	0, 5, 1, 2, 24, 24, 2, GLASS, -P_CROSSBOW, CLR_BLACK), 

/* Darts */
/* (also weptoool spoon) */
WEAPON("dart", (char *)0,
	1, 1, 0, 265,  0,  4,  5,  2, 0, P,   -P_DART, IRON, HI_METAL),

/* Shurikens */
WEAPON("shuriken", "throwing star",
	0, 1, 0, 125,  0,  5,  8,  6, 2, P,   -P_SHURIKEN, IRON, HI_METAL),

/* Boomerangs */
WEAPON("boomerang", (char *)0,
	1, 1, 0, 75,  0, 20,  9,  9, 3, 0,   -P_BOOMERANG, WOOD, HI_WOOD),

/* Whips */


WEAPON("bullwhip", (char *)0,
	1, 0, 0, 45, 8,  4,  5,  3, 2, 0,   P_WHIP, LEATHER, CLR_BROWN),

WEAPON("steel whip", (char *)0,
	1, 0, 0,  5, 8,  4,  10,  6, 4, 0,   P_WHIP, METAL, HI_METAL),

#ifdef KOPS
WEAPON("rubber hose", (char *)0,
	1, 0, 0, 15, 8,  3,  4,  3, 5, B,   P_WHIP, PLASTIC, CLR_BROWN),
#endif

/* With shuffled appearances... */
#undef P
#undef S
#undef B
#undef E

#undef WEAPON
#undef PROJECTILE
#undef BOW
#undef BULLET
#undef GUN

/* armor ... */
/* IRON denotes ferrous metals, including steel.
 * Only IRON weapons and armor can rust.
 * Only COPPER (including brass) corrodes.
 * Some creatures are vulnerable to SILVER.
 */
#define ARMOR(name,desc,kn,mgc,blk,power,prob,delay,wt,cost,ac,can,sub,metal,c) \
	OBJECT( \
		OBJ(name,desc), BITS(kn,0,1,0,mgc,1,0,0,blk,0,0,sub,metal), power, \
		ARMOR_CLASS, prob, delay, wt, cost, \
		0, 0, 10 - ac, can, wt, c )
#define CLOAK(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c) \
	ARMOR(name,desc,kn,mgc,0,power,prob,delay,wt,cost,ac,can,ARM_CLOAK,metal,c)
#define HELM(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c) \
	ARMOR(name,desc,kn,mgc,0,power,prob,delay,wt,cost,ac,can,ARM_HELM,metal,c)
#define GLOVES(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c) \
	ARMOR(name,desc,kn,mgc,0,power,prob,delay,wt,cost,ac,can,ARM_GLOVES,metal,c)
#define SHIELD(name,desc,kn,mgc,blk,power,prob,delay,wt,cost,ac,can,metal,c) \
	ARMOR(name,desc,kn,mgc,blk,power,prob,delay,wt,cost,ac,can,ARM_SHIELD,metal,c)
#define BOOTS(name,desc,kn,mgc,power,prob,delay,wt,cost,ac,can,metal,c) \
	ARMOR(name,desc,kn,mgc,0,power,prob,delay,wt,cost,ac,can,ARM_BOOTS,metal,c)

#ifdef TOURIST
/* Shirts */
ARMOR("Hawaiian shirt", (char *)0,
	1, 0, 0, 0,	30, 0,	 2,   3, 10, 0, ARM_SHIRT, CLOTH, CLR_MAGENTA),
ARMOR("T-shirt", (char *)0,
	1, 0, 0, 0,	15, 0,	 2,   2, 10, 0, ARM_SHIRT, CLOTH, CLR_WHITE),
#endif /* TOURIST */
# ifdef CONVICT
ARMOR("striped shirt", (char *)0,
	1, 0, 0, 0,	10, 0,	 5,   2, 10, 0, ARM_SHIRT, CLOTH, CLR_GRAY),
# endif /* CONVICT */
/*Ruffled shirts are little different from other shirts*/
ARMOR("ruffled shirt", (char *)0,
	1, 0, 0, 0,	10, 0,	 5,   2, 10, 0, ARM_SHIRT, CLOTH, CLR_WHITE),
/* victorian underwear, on the other hand, inflicts a penalty to AC but grants MC 3 */
ARMOR("victorian underwear", (char *)0,
	1, 0, 0, 0,	10, 5,	 5,   2, 10, 3, ARM_SHIRT, CLOTH, CLR_WHITE),

/* Suits of armor */
ARMOR("plate mail", (char *)0,
	1, 0, 1, 0,	210, 5, 200, 600,  3, 2, ARM_SUIT, IRON, HI_METAL),
#ifdef JEDI
ARMOR("plasteel armor", (char *)0,
	1, 0, 1, 0, 25, 5, 50,  80,  4, 0, ARM_SUIT, PLASTIC, CLR_WHITE),
#endif
ARMOR("crystal plate mail", (char *)0,
	1, 0, 1, 0,	52, 5, 200, 820,  3, 2, ARM_SUIT, GLASS, CLR_WHITE),
#ifdef TOURIST
ARMOR("bronze plate mail", (char *)0,
	1, 0, 1, 0,	135, 5, 200, 400,  4, 0, ARM_SUIT, COPPER, HI_COPPER),
#else
ARMOR("bronze plate mail", (char *)0,
	1, 0, 1, 0,	185, 5, 200, 400,  4, 0, ARM_SUIT, COPPER, HI_COPPER),
#endif
ARMOR("splint mail", (char *)0,
	1, 0, 1, 0,	330, 5, 160,  80,  4, 1, ARM_SUIT, IRON, HI_METAL),
ARMOR("banded mail", (char *)0,
	1, 0, 1, 0,	330, 5, 160,  90,  4, 0, ARM_SUIT, IRON, HI_METAL),
ARMOR("dwarvish mithril-coat", (char *)0,
	1, 0, 0, 0,	50, 1, 60, 240,  5, 3, ARM_SUIT, MITHRIL, HI_METAL),
ARMOR("dark elven mithril-coat", (char *)0,
	1, 0, 0, 0, 10, 1, 60, 240,  3, 3, ARM_SUIT, MITHRIL, CLR_BLACK),
ARMOR("elven mithril-coat", (char *)0,
	1, 0, 0, 0,	75, 1, 60, 240,  4, 3, ARM_SUIT, MITHRIL, HI_METAL),
ARMOR("gnomish suit", "little blue vest",
	0, 0, 0, 0,	5, 0, 20,  10,  9, 0, ARM_SUIT, CLOTH, CLR_BRIGHT_BLUE),
ARMOR("chain mail", (char *)0,
	1, 0, 0, 0,	360, 5, 120,  75,  5, 1, ARM_SUIT, IRON, HI_METAL),
ARMOR("orcish chain mail", "crude chain mail",
	0, 0, 0, 0,	100, 5, 120,  75,  6, 1, ARM_SUIT, IRON, CLR_BLACK),
ARMOR("scale mail", (char *)0,
	1, 0, 0, 0,	285, 5, 100,  45,  6, 0, ARM_SUIT, IRON, HI_METAL),
ARMOR("studded leather armor", (char *)0,
	1, 0, 0, 0,	350, 3, 80,  15,  7, 1, ARM_SUIT, LEATHER, HI_LEATHER),
ARMOR("ring mail", (char *)0,
	1, 0, 0, 0,	310, 5, 100, 100,  7, 0, ARM_SUIT, IRON, HI_METAL),
ARMOR("orcish ring mail", "crude ring mail",
	0, 0, 0, 0,	100, 5, 100,  80,  8, 1, ARM_SUIT, IRON, CLR_BLACK),
ARMOR("leather armor", (char *)0,
	1, 0, 0, 0,	335, 3, 60,   5,  8, 0, ARM_SUIT, LEATHER, HI_LEATHER),
ARMOR("leather jacket", (char *)0,
	1, 0, 0, 0,	65, 0,	12,  10,  9, 0, ARM_SUIT, LEATHER, CLR_BLACK),

/* Robes */
/* STEPHEN WHITE'S NEW CODE */
ARMOR("robe", "red robe",
	0, 0, 0, 0,		5, 1,  16,  50,  9, 0, ARM_SUIT, LEATHER, CLR_RED),
ARMOR("robe of protection", "blue robe",
	0, 1, 0, PROTECTION,	5, 1,  16,  50,  5, 0, ARM_SUIT, LEATHER, CLR_BRIGHT_BLUE),
ARMOR("robe of power", "orange robe",
	0, 1, 0, 0,		5, 1,  16,  50,  9, 0, ARM_SUIT, LEATHER, CLR_ORANGE),
ARMOR("robe of weakness", "green robe",
	0, 1, 0, STUNNED,		5, 1,  16,  50,  9, 0, ARM_SUIT, LEATHER, CLR_GREEN),

/*
 * Dragon suits
 * There is code in polyself.c that assumes (1) and (2).
 * There is code in obj.h, objnam.c, mon.c, read.c that assumes (2).
 *
 *	(1) The dragon scale mails and the dragon scales are together.
 *	(2) That the order of the dragon scale mail and dragon scales is the
 *	    the same defined in monst.c.
 */
#define DRGN_ARMR(name,mgc,power,cost,ac,color) \
	ARMOR(name,(char *)0,1,mgc,1,power,1,5,20,cost,ac,0,ARM_SUIT,DRAGON_HIDE,color)
/* 3.4.1: dragon scale mail reclassified as "magic" since magic is
   needed to create them */
DRGN_ARMR("gray dragon scale mail",   1, ANTIMAGIC,  1500, 1, CLR_GRAY),
DRGN_ARMR("silver dragon scale mail", 1, REFLECTING, 1500, 1, SILVER),
DRGN_ARMR("shimmering dragon scale mail", 1, DISPLACED, 1200, 1, CLR_CYAN),
DRGN_ARMR("deep dragon scale mail",   1, DRAIN_RES,  1200, 1, CLR_MAGENTA),
DRGN_ARMR("red dragon scale mail",    1, FIRE_RES,    900, 1, CLR_RED),
DRGN_ARMR("white dragon scale mail",  1, COLD_RES,    900, 1, CLR_WHITE),
DRGN_ARMR("orange dragon scale mail", 1, SLEEP_RES,   900, 1, CLR_ORANGE),
DRGN_ARMR("black dragon scale mail",  1, DISINT_RES, 1200, 1, CLR_BLACK),
DRGN_ARMR("blue dragon scale mail",   1, SHOCK_RES,   900, 1, CLR_BRIGHT_BLUE),
DRGN_ARMR("green dragon scale mail",  1, POISON_RES,  900, 1, CLR_GREEN),
DRGN_ARMR("golden dragon scale mail",  1, SICK_RES,  900, 1, CLR_YELLOW),
DRGN_ARMR("stone dragon scale mail",  1, STONE_RES,  900, 1, CLR_GRAY),
DRGN_ARMR("cyan dragon scale mail", 1, FEAR_RES, 900, 1, CLR_CYAN),
DRGN_ARMR("yellow dragon scale mail", 1, ACID_RES,    900, 1, CLR_YELLOW),

/* For now, only dragons leave these. */
/* 3.4.1: dragon scales left classified as "non-magic"; they confer
   magical properties but are produced "naturally" */
DRGN_ARMR("gray dragon scales",   0, ANTIMAGIC,  800, 5, CLR_GRAY),
DRGN_ARMR("silver dragon scales", 0, REFLECTING, 800, 5, SILVER),
DRGN_ARMR("shimmering dragon scales", 0, DISPLACED,  700, 5, CLR_CYAN),
DRGN_ARMR("deep dragon scales",   0, DRAIN_RES,  700, 5, CLR_MAGENTA),
DRGN_ARMR("red dragon scales",    0, FIRE_RES,   500, 5, CLR_RED),
DRGN_ARMR("white dragon scales",  0, COLD_RES,   500, 5, CLR_WHITE),
DRGN_ARMR("orange dragon scales", 0, SLEEP_RES,  500, 5, CLR_ORANGE),
DRGN_ARMR("black dragon scales",  0, DISINT_RES, 700, 5, CLR_BLACK),
DRGN_ARMR("blue dragon scales",   0, SHOCK_RES,  500, 5, CLR_BRIGHT_BLUE),
DRGN_ARMR("green dragon scales",  0, POISON_RES, 500, 5, CLR_GREEN),
DRGN_ARMR("golden dragon scales",   0, SICK_RES,  500, 5, CLR_YELLOW),
DRGN_ARMR("stone dragon scales",  0, STONE_RES, 500, 5, CLR_GRAY),
DRGN_ARMR("cyan dragon scales",  0, FEAR_RES, 500, 5, CLR_CYAN),
DRGN_ARMR("yellow dragon scales", 0, ACID_RES,   500, 5, CLR_YELLOW),
#undef DRGN_ARMR

/* Cloaks */
/*  'cope' is not a spelling mistake... leave it be */
CLOAK("mummy wrapping", (char *)0,
		1, 0,	0,	    5, 0,  2,  2, 10, 1, CLOTH, CLR_GRAY),
CLOAK("orcish cloak", "coarse mantelet",
		0, 0,	0,	   30, 0, 4, 40, 10, 2, CLOTH, CLR_BLACK),
CLOAK("dwarvish cloak", "hooded cloak",
		0, 0,	0,	   35, 0, 4, 50, 10, 2, CLOTH, HI_CLOTH),
CLOAK("oilskin cloak", "slippery cloak",
		0, 0,	0,	   40, 0, 4, 50,  9, 3, CLOTH, HI_CLOTH),
CLOAK("elven cloak", "faded pall",
		0, 1,	STEALTH,   45, 0, 4, 60,  9, 3, CLOTH, CLR_BLACK),
CLOAK("lab coat", "white coat",
		0, 1,   POISON_RES, 50, 0, 4, 60,  9, 3, CLOTH, CLR_WHITE),
CLOAK("leather cloak", (char *)0,
		1, 0,	0,	   35, 0, 7, 40,  9, 1, LEATHER, CLR_BROWN),
CLOAK("plasteel cloak", (char *)0,
		1, 0,	0,	    5, 0, 7, 70,  8, 2, PLASTIC, CLR_WHITE),
#if 0
CLOAK("robe", (char *)0,
		1, 1,	0,	    3, 0, 7, 50,  8, 3, CLOTH, CLR_RED),
CLOAK("alchemy smock", "apron",
		0, 1,	POISON_RES, 9, 0, 4, 50,  9, 1, CLOTH, CLR_WHITE),
#endif
/* With shuffled appearances... */
CLOAK("cloak of protection", "tattered cape",
		0, 1,	PROTECTION, 45, 0, 4, 50,  7, 3, CLOTH, HI_CLOTH),
CLOAK("poisonous cloak", "dirty rag",
		0, 1,   0,         10, 0, 4, 50, 10, 3, CLOTH, CLR_GREEN),
CLOAK("cloak of invisibility", "opera cloak",
		0, 1,	INVIS,	  45, 0, 4, 50,  9, 2, CLOTH, CLR_BRIGHT_MAGENTA),
CLOAK("cloak of fumbling", "shaking cloak",
		0, 1,	FUMBLING,	  5, 0, 4, 50,  5, 3, CLOTH, CLR_GRAY),
CLOAK("cloak of magic resistance", "ornamental cope",
		0, 1,	ANTIMAGIC, 20, 0, 4, 50,  9, 3, CLOTH, CLR_WHITE),
CLOAK("cloak of reflection", "funeral cloak",
		0, 1,	REFLECTING, 10, 0, 4, 50,  9, 3, CLOTH, CLR_BRIGHT_GREEN),
CLOAK("manacloak", "dragonhide cloak",
		0, 1,	ENERGY_REGENERATION,  5, 0, 4, 50,  7, 3, DRAGON_HIDE, CLR_BRIGHT_BLUE),
CLOAK("cloak of confusion", "ripped cloak",
		0, 1,	CONFUSION,  5, 0, 4, 50,  6, 3, LEATHER, CLR_BLACK),
CLOAK("cloak of warmth", "metal cloak",
		0, 1,	COLD_RES,  5, 0, 4, 50,  7, 3, METAL, CLR_GRAY),
CLOAK("cloak of grounding", "granite cloak",
		0, 1,	SHOCK_RES,  5, 0, 4, 50,  8, 2, MINERAL, CLR_GRAY),
CLOAK("cloak of quenching", "asbestos cloak",
		0, 1,	FIRE_RES,  5, 0, 4, 50,  9, 3, MITHRIL, CLR_ORANGE),
CLOAK("cloak of displacement", "piece of cloth",
		0, 1,	DISPLACED, 35, 0, 4, 50,  9, 2, CLOTH, HI_CLOTH),
/* Helmets */
HELM("elven leather helm", "leather hat",
		0, 0, 0,			25, 1,  2,   8, 8, 0, LEATHER, HI_LEATHER),
HELM("gnomish helm", "little red hat",
		0, 0,  0,			5, 1,  1,   8, 10, 0, CLOTH, CLR_RED),
HELM("orcish helm", "iron skull cap",
		0, 0, 0,			20, 1, 12,  10, 9, 0, IRON, CLR_BLACK),
HELM("dwarvish iron helm", "hard hat",
		0, 0, 0,			30, 1, 16,  20, 8, 0, IRON, HI_METAL),
HELM("fedora", (char *)0,
		1, 0, 0,			5, 0,  2,   1,10, 0, CLOTH, CLR_BROWN),
HELM("cornuthaum", "conical hat",
		0, 1, CLAIRVOYANT,	15, 1,  2,  80,10, 2, CLOTH, CLR_BRIGHT_BLUE),
HELM("dunce cap", "conical hat",
		0, 1, 0,			15, 1,  2,  80,10, 0, CLOTH, CLR_BRIGHT_BLUE),
HELM("dented pot", (char *)0,
		1, 0, 0,			10, 0, 4,   8, 9, 0, IRON, CLR_BLACK),
#ifdef JEDI
HELM("plasteel helm", (char *)0,
		1, 0, 0,                 5, 1,  2,  20, 7, 9, PLASTIC, CLR_WHITE),
#endif
/* ...with shuffled appearances */
HELM("helmet", "plumed helmet",
		0, 0, 0,		   30, 1, 20,  50, 9, 0, IRON, HI_METAL),
HELM("helm of brilliance", "etched helmet",
		0, 1, 0,			20, 1, 20,  50, 9, 0, IRON, CLR_GREEN),
HELM("helm of opposite alignment", "crested helmet",
		0, 1, 0,			20, 1, 20,  50, 9, 0, IRON, HI_METAL),
HELM("helm of detect monsters", "golden helmet",
		0, 1, DETECT_MONSTERS,	5, 1, 20,  50, 10, 0, IRON, HI_METAL),
HELM("helm of storms", "padded helmet",
		0, 1, STORM_HELM,		5, 1, 20,  50, 7, 0, METAL, HI_METAL),
HELM("helm of steel", "steel helmet",
		0, 1, 0,			5, 1, 20,  50, 6, 0, MITHRIL, CLR_ORANGE),
HELM("helm of drain resistance", "black helmet",
		0, 1, DRAIN_RES,		5, 1, 20,  50, 8, 0, DRAGON_HIDE, CLR_BLACK),
HELM("helm of fear", "horned helmet",
		0, 1, FEARED,		5, 1, 20,  50, 5, 3, METAL, CLR_GRAY),
HELM("helm of hunger", "winged helmet",
		0, 1, HUNGER,		5, 1, 20,  50, 5, 3, MINERAL, CLR_WHITE),
HELM("helm of discovery", "viking helmet", 
		0, 1, SEARCHING,	5, 1, 20,  50, 9, 0, IRON, HI_METAL),
HELM("helm of telepathy", "visored helmet",
		0, 1, TELEPAT,		10, 1, 20,  50, 9, 0, IRON, HI_METAL),

/* Gloves */
/* these have their color but not material shuffled, so the IRON must stay
 * CLR_BROWN (== HI_LEATHER)
 */
#ifdef JEDI
GLOVES("plasteel gloves", "white gloves",
		0, 0,  0,                        5, 1,  2, 25,  8, 0, PLASTIC, CLR_WHITE),
#endif
GLOVES("leather gloves", "old gloves",
		0, 0,  0,			60, 1, 4,  50,  9, 0, LEATHER, HI_LEATHER),
GLOVES("gauntlets of fumbling", "padded gloves",
		0, 1,  FUMBLING,	40, 1, 4, 50,  9, 0, LEATHER, HI_LEATHER),
GLOVES("gauntlets of slowing", "ice-cold gloves",
		0, 1,  FROZEN,	5, 1, 4, 50,  4, 0, MINERAL, CLR_CYAN),
GLOVES("oilskin gloves", "slippery gloves",
		0, 1,  GLIB,	5, 1, 4, 50,  7, 3, LEATHER, CLR_ORANGE),
GLOVES("gauntlets of power", "riding gloves",
		0, 1,  0,			35, 1, 4, 50,  9, 0, IRON, CLR_BROWN),
GLOVES("gauntlets of typing", "brand-new gloves",
		0, 1, 0, 			5, 1, 4,  50,  8, 0, LEATHER, HI_LEATHER),
GLOVES("gauntlets of steel", "steel gloves",
		0, 1,  0,			5, 1, 4, 50,  7, 0, MITHRIL, CLR_ORANGE),
GLOVES("gauntlets of swimming", "black gloves",
		0, 1,  SWIMMING,	40, 1, 4, 50,  9, 0, LEATHER, HI_LEATHER),
GLOVES("gauntlets of reflection", "mirrored gloves",
		0, 1,  REFLECTING,	5, 1, 4, 50,  8, 0, SILVER, CLR_CYAN),
GLOVES("gauntlets of dexterity", "fencing gloves",
		0, 1,  0,			40, 1, 4, 50,  9, 0, LEATHER, HI_LEATHER),

/* Shields */
SHIELD("small shield", (char *)0,
		1, 0, 0, 0,	     30, 0, 12,	3,  8, 0, WOOD, HI_WOOD),
/* Elven ... orcish shields can't be differentiated by feel */
SHIELD("elven shield", "blue and green shield",
		0, 0, 0, 0,	     10, 0, 20,	7,  7, 0, WOOD, CLR_GREEN),
SHIELD("Uruk-hai shield", "white-handed shield",
		0, 0, 0, 0,	     10, 0, 20,	7,  6, 0, IRON, HI_METAL),
SHIELD("orcish shield", "red-eyed shield",
		0, 0, 0, 0,	     10, 0, 20,	7,  6, 0, IRON, CLR_RED),
SHIELD("steel shield", (char *)0,
		1, 0, 0, 0,	     5, 0, 120,	10,  5, 0, GOLD, CLR_YELLOW),
SHIELD("large shield", (char *)0,
		1, 0, 1, 0,	     30, 0,40, 10,  5, 0, IRON, HI_METAL),
SHIELD("dwarvish roundshield", "large round shield",
		0, 0, 0, 0,	     20, 0,40, 10,  5, 0, IRON, HI_METAL),
SHIELD("flame shield", "dark red shield",
		0, 1, 0, FIRE_RES,	 5, 0, 20, 300, 8, 0, IRON, CLR_RED),
SHIELD("ice shield", "dark blue shield",
		0, 1, 0, COLD_RES,	 5, 0, 20, 300, 8, 0, IRON, CLR_BRIGHT_BLUE),
SHIELD("lightning shield", "dull yellow shield",
		0, 1, 0, SHOCK_RES,	 5, 0, 20, 300, 8, 0, IRON, CLR_YELLOW),
SHIELD("venom shield", "dark green shield",
		0, 1, 0, POISON_RES,	 5, 0, 20, 300, 8, 0, IRON, CLR_GREEN),
SHIELD("shield of light", "shiny shield",
		0, 1, 0, INFRAVISION,	 5, 0, 20, 300, 8, 0, IRON, CLR_YELLOW),
SHIELD("shield of mobility", "slippery shield",
		0, 1, 0, FREE_ACTION, 5, 0, 20, 300, 9, 0, IRON, HI_METAL),
SHIELD("shield of reflection", "polished silver shield",
		0, 1, 0, REFLECTING, 15, 0, 20, 50,  4, 0, SILVER, HI_SILVER),

/* Boots */
#ifdef JEDI
BOOTS("plasteel boots", "white boots", /* these things were crashing the game for binders and certain other chars! */
		0, 0,  0,          5, 2, 2,  25,  8, 9, PLASTIC, CLR_WHITE),
#endif
BOOTS("low boots", "walking shoes",
		0, 0,  0,	  80, 2, 4,  8,  9, 0, LEATHER, HI_LEATHER),
BOOTS("iron shoes", "hard shoes",
		0, 0,  0,	  35, 2, 20, 16,  8, 0, IRON, HI_METAL),
BOOTS("gnomish boots", "little black boots",
		0, 0,  0,	   5, 2, 4, 16,  10, 0, LEATHER, CLR_BLACK),
BOOTS("high boots", "jackboots",
		0, 0,  0,	  60, 2, 8, 12,  8, 0, LEATHER, HI_LEATHER),
BOOTS("wedge sandals", "heeled sandals",
		0, 0,  0,          5, 5, 2,  25,  10, 0, MINERAL, CLR_WHITE),
BOOTS("dancing shoes", "soft footwear", /* not high-heeled - transvestites won't benefit from wearing this pair! --Amy */
		0, 0,  0,          5, 1, 1,  80,   8, 0, LEATHER, CLR_BRIGHT_BLUE),
BOOTS("sweet mocassins", "womens footwear", /* not high-heeled*/
		0, 0,  0,          5, 1, 1,  50,   9, 0, LEATHER, CLR_ORANGE),
BOOTS("soft sneakers", "light footwear", /* not high-heeled*/
		0, 0,  0,          5, 2, 2,  150,   8, 0, LEATHER, CLR_WHITE),
BOOTS("feminine pumps", "female footwear",
		0, 0,  0,          5, 2, 4,  100,  10, 0, LEATHER, CLR_ORANGE),
BOOTS("leather peep-toes", "asian footwear",
		0, 0,  0,          5, 3, 4,  200,   9, 0, LEATHER, CLR_BLACK),
BOOTS("hippie heels", "red overknees",
		0, 0,  HALLUC,          5, 3, 5,  200,  5, 0, DRAGON_HIDE, CLR_ORANGE),
BOOTS("combat stilettos", "heeled boots",
		0, 0,  0,          5, 5, 10,  250,  9, 0, DRAGON_HIDE, CLR_BLACK),
/* ...with shuffled appearances */
BOOTS("speed boots", "combat boots",
		0, 1,  FAST,	  60, 2, 8, 50,  9, 0, LEATHER, HI_LEATHER),
/* With shuffled appearances... */
BOOTS("boots of molasses", "thigh boots",
		0, 1,  FROZEN,	  5, 2, 8, 50, 9, 0, LEATHER, CLR_BLACK),
BOOTS("water walking boots", "jungle boots",
		0, 1,  WWALKING,  60, 2, 8, 50,  9, 0, LEATHER, HI_LEATHER),
BOOTS("jumping boots", "hiking boots",
		0, 1,  JUMPING,   55, 2, 8, 50,  9, 0, LEATHER, HI_LEATHER),
BOOTS("flying boots", "battle boots",
		0, 1,  FLYING,   5, 2, 8, 50,  9, 0, SILVER, CLR_GRAY),
BOOTS("boots of acid resistance", "buckled boots",
		0, 1,  ACID_RES,   5, 2, 8, 50,  9, 0, WAX, CLR_YELLOW),
BOOTS("elven boots", "mud boots",
		0, 1,  STEALTH,   60, 2, 8,  50,  9, 0, LEATHER, HI_LEATHER),
BOOTS("kicking boots", "steel boots",
		0, 1,  0,         60, 2, 8,  50,  9, 0, IRON, CLR_BROWN),
BOOTS("fumble boots", "riding boots",
		0, 1,  FUMBLING,  55, 2, 8, 50,  9, 0, LEATHER, HI_LEATHER),
BOOTS("zipper boots", "persian boots",
		0, 1,  WOUNDED_LEGS,  5, 2, 8, 50,  6, 3, DRAGON_HIDE, CLR_YELLOW),
BOOTS("fire boots", "hot boots",
		0, 1,  BURNED,  5, 2, 8, 50,  3, 3, DRAGON_HIDE, CLR_RED),
BOOTS("levitation boots", "snow boots",
		0, 1,  LEVITATION,60, 2, 8, 50,  9, 0, LEATHER, HI_LEATHER),

#undef HELM
#undef CLOAK
#undef SHIELD
#undef GLOVES
#undef BOOTS
#undef ARMOR

/* rings ... */
/* [Tom] looks like there are no probs to change... */
#define RING(name,power,stone,cost,prob,mgc,spec,mohs,metal,color) OBJECT( \
		OBJ(name,stone), \
		BITS(0,0,spec,0,mgc,spec,0,0,0,HARDGEM(mohs),0,0,metal), \
		power, RING_CLASS, prob, 0, 0, cost, 0, 0, 0, 0, 15, color )
RING("adornment", ADORNED, "wooden",        300, 105, 1, 1, 2, WOOD, HI_WOOD),
RING("hunger",     HUNGER,     "topaz",     300, 90, 1, 0, 8, GEMSTONE, CLR_CYAN),
RING("disarming",     GLIB,     "wet",     300,  25, 1, 0, 1, VEGGY, CLR_BRIGHT_BLUE),
RING("numbness",  NUMBED,  "constricting", 300,  25, 1, 0, 1, METAL, CLR_CYAN),
RING("hallucination",  HALLUC,  "rainbow", 300,  5, 1, 0, 5, METAL, CLR_BRIGHT_MAGENTA),
RING("curse",  ITEMCURSING,  "color changing", 300,  5, 1, 0, 8, MINERAL, CLR_WHITE),
RING("mood",       0,          "ridged",    300, 115, 1, 0, 8, IRON, HI_METAL),
RING("protection", PROTECTION, "black onyx",300, 165, 1, 1, 7, MINERAL, CLR_BLACK),
RING("protection from shape changers", PROT_FROM_SHAPE_CHANGERS, "shiny",
					    					300, 165, 1, 0, 5, IRON, CLR_BRIGHT_CYAN),
RING("sleeping",   SLEEPING,   "wedding",   300, 115, 1, 0, 7, GEMSTONE, CLR_WHITE),
RING("stealth", STEALTH, "jade",            300, 165, 1, 0, 6, GEMSTONE, CLR_GREEN),
RING("sustain ability", FIXED_ABIL, "bronze",
					    300, 165, 1, 0, 4, COPPER, HI_COPPER),
RING("warning",    WARNING,    "diamond",   300, 165, 1, 0,10, GEMSTONE, CLR_WHITE),
RING("aggravate monster", AGGRAVATE_MONSTER, "sapphire",
					    300, 115, 1, 0, 9, GEMSTONE, CLR_BRIGHT_BLUE),
RING("cold resistance", COLD_RES, "brass",  300, 115, 1, 0, 4, COPPER, HI_COPPER),
RING("fear resistance", FEAR_RES, "branching",  300, 25, 1, 0, 1, WOOD, CLR_GREEN),
RING("gain constitution", 0,   "opal",      300, 140, 1, 1, 7, MINERAL,  HI_MINERAL),
RING("gain dexterity",  0,     "obsidian",  300, 165, 1, 1, 7, GEMSTONE, CLR_BLACK),
RING("gain intelligence", 0,   "plain",     300, 165, 1, 1, 7, MINERAL,  HI_MINERAL),
RING("gain strength", 0,       "granite",   300, 165, 1, 1, 7, MINERAL, HI_MINERAL),
RING("gain wisdom",     0,     "glass",     300, 165, 1, 1, 7, MINERAL,  CLR_CYAN),
RING("timely backup",	  0,	"rusty",	  300, 25,  1, 1, 4, IRON,     CLR_BROWN),
RING("increase accuracy", 0,   "clay",      300, 165, 1, 1, 4, MINERAL, CLR_RED),
RING("increase damage", 0,     "coral",     300, 165, 1, 1, 4, MINERAL, CLR_ORANGE),
RING("slow digestion",  SLOW_DIGESTION, "steel",
					    300, 165, 1, 0, 8, IRON, HI_METAL),
RING("invisibility", INVIS,    "wire",      300, 165, 1, 0, 5, IRON, HI_METAL),
RING("poison resistance", POISON_RES, "pearl",
					    300, 115, 1, 0, 4, IRON, CLR_WHITE),
RING("see invisible", SEE_INVIS, "engagement",
											300, 165, 1, 0, 5, IRON, HI_METAL),
RING("shock resistance", SHOCK_RES, "copper",
					    300, 115, 1, 0, 3, COPPER, HI_COPPER),
RING("sickness resistance", SICK_RES, "fragile",
					    300, 50, 1, 0, 3, GLASS, HI_COPPER),
RING("fire resistance", FIRE_RES, "iron",   300, 115, 1, 0, 5, IRON, HI_METAL),
RING("free action",     FREE_ACTION, "twisted",
					    300, 165, 1, 0, 6, IRON, HI_METAL),
/*RING("infravision", 0, "zinc",              300, 165, 1, 0, 5, MITHRIL, HI_METAL),*/
RING("levitation", LEVITATION, "agate",     300, 165, 1, 0, 7, GEMSTONE, CLR_RED),
RING("regeneration", REGENERATION, "moonstone",
											300, 165, 1, 0, 6, MINERAL, HI_MINERAL),
RING("searching",  SEARCHING,  "tiger eye", 300, 115, 1, 0, 6, GEMSTONE, CLR_BROWN),
RING("teleportation", TELEPORT, "silver",   300, 165, 1, 0, 3, SILVER, HI_SILVER),
RING("conflict",   CONFLICT, "ruby",        300, 115, 1, 0, 9, GEMSTONE, CLR_RED),
RING("polymorph", POLYMORPH, "ivory",       300, 165, 1, 0, 4, BONE, CLR_WHITE),
RING("polymorph control", POLYMORPH_CONTROL, "emerald",
					    300, 165, 1, 0, 8, GEMSTONE, CLR_BRIGHT_GREEN),
RING("teleport control", TELEPORT_CONTROL, "gold",
											300, 170, 1, 0, 3, GOLD, HI_GOLD),
RING((char *)0, 0,  "quartz", 0, 0, 0, 0, 7, GLASS, HI_GLASS),
RING((char *)0, 0,  "porcelain", 0, 0, 0, 0, 8, GLASS, HI_MINERAL),
RING((char *)0, 0,  "ceramic", 0, 0, 0, 0, 8, GLASS, HI_MINERAL),
RING((char *)0, 0,  "rigged", 0, 0, 0, 0, 8, IRON, HI_METAL),
RING((char *)0, 0,  "high", 0, 0, 0, 0, 7, GEMSTONE, CLR_WHITE),
RING((char *)0, 0,  "mithril", 0, 0, 0, 0, 5, SILVER, HI_SILVER),
RING((char *)0, 0,  "platinum", 0, 0, 0, 0, 3, PLATINUM, HI_METAL),
RING((char *)0, 0,  "jacinth", 0, 0, 0, 0, 9, GEMSTONE, CLR_ORANGE),
RING((char *)0, 0,  "citrine", 0, 0, 0, 0, 6, GEMSTONE, CLR_ORANGE),
RING((char *)0, 0,  "amber", 0, 0, 0, 0, 2, GEMSTONE, CLR_BROWN),
RING((char *)0, 0,  "jet", 0, 0, 0, 0, 7, GEMSTONE, CLR_BLACK),
RING((char *)0, 0,  "chrysoberyl", 0, 0, 0, 0, 5, GEMSTONE, CLR_YELLOW),
RING((char *)0, 0,  "plastic", 0, 0, 0, 0, 1, PLASTIC, CLR_BRIGHT_MAGENTA),
RING((char *)0, 0,  "cameo", 0, 0, 0, 0, 3, PLASTIC, CLR_BRIGHT_MAGENTA),
RING((char *)0, 0,  "intaglio", 0, 0, 0, 0, 3, PLASTIC, CLR_BRIGHT_MAGENTA),
RING((char *)0, 0,  "dazzling", 0, 0, 0, 0, 3, PLASTIC, CLR_BRIGHT_GREEN),
RING((char *)0, 0,  "deep", 0, 0, 0, 0, 3, PLASTIC, CLR_BRIGHT_BLUE),
RING((char *)0, 0,  "lighting", 0, 0, 0, 0, 3, PLASTIC, CLR_YELLOW),
RING((char *)0, 0,  "bright", 0, 0, 0, 0, 3, PLASTIC, CLR_ORANGE),
RING((char *)0, 0,  "pretty", 0, 0, 0, 0, 3, PLASTIC, CLR_BRIGHT_CYAN),
RING((char *)0, 0,  "amethyst", 0, 0, 0, 0, 3, GEMSTONE, CLR_BRIGHT_MAGENTA),
RING((char *)0, 0,  "alexandrite", 0, 0, 0, 0, 4, GEMSTONE, CLR_BROWN),
RING((char *)0, 0,  "carnelian", 0, 0, 0, 0, 3, GEMSTONE, CLR_BROWN),
RING((char *)0, 0,  "germanium", 0, 0, 0, 0, 2, MINERAL, CLR_WHITE),
RING((char *)0, 0,  "garnet", 0, 0, 0, 0, 5, GEMSTONE, CLR_RED),
RING((char *)0, 0,  "kryptonite", 0, 0, 0, 0, 4, MINERAL, CLR_BLACK),
RING((char *)0, 0,  "lapis lazuli", 0, 0, 0, 0, 7, GEMSTONE, CLR_BRIGHT_BLUE),
RING((char *)0, 0,  "peridot", 0, 0, 0, 0, 7, GEMSTONE, CLR_BRIGHT_GREEN),
RING((char *)0, 0,  "stibotantalite", 0, 0, 0, 0, 6, MINERAL, CLR_GRAY),
RING((char *)0, 0,  "taaffeite", 0, 0, 0, 0, 4, MINERAL, CLR_ORANGE),
RING((char *)0, 0,  "zircon", 0, 0, 0, 0, 5, GEMSTONE, CLR_BRIGHT_CYAN),
RING((char *)0, 0,  "aquamarine", 0, 0, 0, 0, 6, GEMSTONE, CLR_CYAN),
RING((char *)0, 0,  "azurite", 0, 0, 0, 0, 6, GEMSTONE, CLR_BRIGHT_BLUE),
RING((char *)0, 0,  "beryl", 0, 0, 0, 0, 8, GEMSTONE, CLR_BRIGHT_GREEN),
RING((char *)0, 0,  "bloodstone", 0, 0, 0, 0, 5, GEMSTONE, CLR_RED),
RING((char *)0, 0,  "calcite", 0, 0, 0, 0, 6, GEMSTONE, CLR_WHITE),
RING((char *)0, 0,  "conundrum", 0, 0, 0, 0, 3, MINERAL, CLR_BRIGHT_GREEN),
RING((char *)0, 0,  "jasper", 0, 0, 0, 0, 5, GEMSTONE, CLR_RED),
RING((char *)0, 0,  "malachite", 0, 0, 0, 0, 6, GEMSTONE, CLR_BRIGHT_GREEN),
RING((char *)0, 0,  "marble", 0, 0, 0, 0, 5, MINERAL, HI_MINERAL),
RING((char *)0, 0,  "rhodonite", 0, 0, 0, 0, 6, GEMSTONE, CLR_ORANGE),
RING((char *)0, 0,  "tortoise shell", 0, 0, 0, 0, 5, MINERAL, CLR_CYAN),
RING((char *)0, 0,  "geode", 0, 0, 0, 0, 9, MINERAL, CLR_BRIGHT_CYAN),
/* More descriptions: cameo, intaglio */
#undef RING

/* amulets ... - THE Amulet comes last because it is special */
#define AMULET(name,desc,power,prob,metal,color) OBJECT( \
		OBJ(name,desc), BITS(0,0,0,0,1,0,0,0,0,0,0,0,metal), power, \
		AMULET_CLASS, prob, 0, 0, 150, 0, 0, 0, 0, 20, color )
AMULET("amulet of change",        "square",     0,          550,	IRON,	CLR_BLACK),
AMULET("amulet of drain resistance","warped",   DRAIN_RES,  300, 	IRON,	CLR_GRAY),
AMULET("amulet of ESP",           "circular",   TELEPAT,    550, 	IRON,	CLR_WHITE),
AMULET("amulet of undead warning", "occult",   WARN_UNDEAD,  25, 	MITHRIL,	CLR_BLACK),
AMULET("amulet of own race warning", "cabbalist",   0,  25, PLASTIC,	CLR_CYAN),
AMULET("amulet of poison warning", "splatted",   0,  25, LIQUID,	CLR_BRIGHT_GREEN),
AMULET("amulet of covetous warning", "egyptian",   0,  25, GOLD,	CLR_MAGENTA),
AMULET("amulet of flying",        "convex",     FLYING,     250, MINERAL,	CLR_RED),
AMULET("amulet of life saving",   "spherical",  LIFESAVED,  300, GLASS,	CLR_BRIGHT_BLUE),
AMULET("amulet of magical breathing", "octagonal", MAGICAL_BREATHING, 250, GEMSTONE,	CLR_GREEN),
AMULET("amulet of reflection",    "hexagonal",  REFLECTING, 300, GEMSTONE,	CLR_BRIGHT_GREEN),
AMULET("amulet of restful sleep", "triangular", SLEEPING,   500, GEMSTONE,	CLR_MAGENTA),
AMULET("amulet of blindness", "radiant", BLINDED,   50, DRAGON_HIDE,	CLR_WHITE),
AMULET("amulet of strangulation", "oval",       STRANGLED, 450, PLASTIC,	CLR_BRIGHT_MAGENTA),
AMULET("amulet of unchanging",    "concave",    UNCHANGING,	250, MINERAL,	CLR_CYAN),
AMULET("amulet versus poison",    "pyramidal",  POISON_RES, 500, GEMSTONE,	CLR_BRIGHT_CYAN),
AMULET("amulet versus stone",     "lunate",   /*STONE_RES*/0,250, COPPER,	CLR_BRIGHT_MAGENTA),
AMULET("amulet of depetrify",     "charmed",   STONE_RES,50, BONE,	CLR_RED),
AMULET("amulet of magic resistance",     "rare",   ANTIMAGIC,5, PAPER,	CLR_ORANGE),
AMULET("amulet of sickness resistance",     "sparkling",   SICK_RES,45, GLASS,	CLR_BRIGHT_GREEN),
AMULET("amulet of swimming",     "watery",   SWIMMING,50, LIQUID,	CLR_BRIGHT_BLUE),
AMULET("amulet of disintegration resistance",     "hardrock",   DISINT_RES,25, MINERAL,	CLR_BLACK),
AMULET("amulet of acid resistance",     "venomous",   ACID_RES,25, LIQUID,	CLR_GREEN),
AMULET("amulet of regeneration",     "vivid",   REGENERATION,25, CLOTH,	CLR_BRIGHT_CYAN),
AMULET("amulet of conflict",     "sounding",   CONFLICT,25, METAL,	CLR_WHITE),
AMULET("amulet of fumbling",     "clumsy",   FUMBLING,25, LEATHER,	CLR_ORANGE),
AMULET("amulet of second chance", "tetraedical",SECOND_CHANCE, 25, GEMSTONE,	CLR_BRIGHT_BLUE),
AMULET("amulet of data storage",  "icosaedrical", 0,		25, GEMSTONE,	CLR_BRIGHT_GREEN),
AMULET("amulet of waterwalking",     "rubber",   WWALKING,25, PLASTIC,	CLR_BRIGHT_BLUE),
AMULET("amulet of hunger",     "gleaming",   HUNGER,25, WAX,	CLR_BRIGHT_MAGENTA),
AMULET("amulet of power",			 "bloody",		ENERGY_REGENERATION,  25, FLESH, CLR_RED),
AMULET((char *)0,                     "rotated",     0, 0, METAL,	CLR_ORANGE),
AMULET((char *)0,                     "rounded",     0, 0, METAL,	CLR_YELLOW),
AMULET((char *)0,                     "moony",     0, 0, COPPER,	CLR_MAGENTA),
AMULET((char *)0,                     "spiked",     0, 0, SILVER,	CLR_BROWN),
AMULET((char *)0,                     "rectangular",0, 0, METAL,	CLR_GREEN),
AMULET((char *)0,                     "elliptic",   0, 0, IRON,	CLR_BRIGHT_BLUE),
AMULET((char *)0,                     "rhomboedric",   0, 0, METAL,	CLR_ORANGE),
AMULET((char *)0,                     "radiating",     0, 0, DRAGON_HIDE,	CLR_ORANGE),
AMULET((char *)0,                     "powerful",     0, 0, GOLD,	CLR_BRIGHT_CYAN),
AMULET((char *)0,                     "burdening",     0, 0, BONE,	CLR_RED),
AMULET((char *)0,                     "worthless",     0, 0, WOOD,	CLR_BROWN),
AMULET((char *)0,                     "dark",     0, 0, SILVER,	CLR_MAGENTA),
AMULET((char *)0,                     "ghostly",     0, 0, PLATINUM,	CLR_GRAY),
AMULET((char *)0,                     "black",     0, 0, PLATINUM,	CLR_BLACK),
AMULET((char *)0,                     "bright",     0, 0, BONE,	CLR_WHITE),
AMULET((char *)0,                     "tetragonal",     0, 0, GEMSTONE,	CLR_BRIGHT_GREEN),
AMULET((char *)0,                     "edged",   0, 0, GLASS,	CLR_BRIGHT_BLUE),
AMULET((char *)0,                     "glaring",     0, 0, GLASS,	CLR_YELLOW),
AMULET((char *)0,                     "illusionary",0, 0, MINERAL,	CLR_GREEN),
AMULET((char *)0,                     "standard",     0, 0, MINERAL,	CLR_CYAN),
AMULET((char *)0,                     "hidden",     0, 0, GOLD,	CLR_CYAN),
AMULET((char *)0,                     "remote",     0, 0, PLATINUM,	CLR_GRAY),
AMULET((char *)0,                     "secluded",     0, 0, MITHRIL,	CLR_BLACK),
AMULET((char *)0,                     "Yendorian",     0, 0, GOLD,	CLR_WHITE),
AMULET((char *)0,                     "adamant",     0, 0, METAL,	CLR_BRIGHT_GREEN),
AMULET((char *)0,                     "agate",     0, 0, GEMSTONE,	CLR_GRAY),
AMULET((char *)0,                     "amber",     0, 0, GEMSTONE,	CLR_YELLOW),
AMULET((char *)0,                     "azure",     0, 0, GEMSTONE,	CLR_CYAN),
AMULET((char *)0,                     "bone",     0, 0, BONE,	CLR_WHITE),
AMULET((char *)0,                     "brass",     0, 0, COPPER,	CLR_CYAN),
AMULET((char *)0,                     "carved oak",     0, 0, WOOD,	CLR_BROWN),
AMULET((char *)0,                     "crystal",     0, 0, GLASS,	CLR_WHITE),
AMULET((char *)0,                     "driftwood",     0, 0, WOOD,	CLR_ORANGE),
AMULET((char *)0,                     "ivory",     0, 0, BONE,	CLR_WHITE),
AMULET((char *)0,                     "sea shell",     0, 0, BONE,	CLR_BRIGHT_CYAN),
OBJECT(OBJ("cheap plastic imitation of the Amulet of Yendor",
	"Amulet of Yendor"), BITS(0,0,1,0,0,0,0,0,0,0,0,0,PLASTIC), 0,
	AMULET_CLASS, 0, 0, 0,    0, 0, 0, 0, 0,  1, HI_METAL), /* must give exactly 1 point of nutrition, see makedefs.c */
OBJECT(OBJ("Amulet of Yendor",	/* note: description == name */
	"Amulet of Yendor"), BITS(0,0,1,0,1,0,1,1,0,0,0,0,MITHRIL), 0,
	AMULET_CLASS, 0, 0, 0, 30000, 0, 0, 0, 0, 20, HI_METAL),
#undef AMULET
/* since there are plastic amulets now, the makedefs routine no longer recognizes the fake amulet just because it's
 * made of plastic, so we need another distinction; I chose the nutritional value, which is 20 for every other amulet
 * but 1 for the fake. --Amy */

/* tools ... */
/* tools with weapon characteristics come last */
#define TOOL(name,desc,kn,mrg,mgc,chg,prob,wt,cost,mat,color) \
	OBJECT( OBJ(name,desc), \
		BITS(kn,mrg,chg,0,mgc,chg,0,0,0,0,0,P_NONE,mat), \
		0, TOOL_CLASS, prob, 0, \
		wt, cost, 0, 0, 0, 0, wt, color )
#define CONTAINER(name,desc,kn,mgc,chg,bi,prob,wt,cost,mat,color) \
	OBJECT( OBJ(name,desc), \
		BITS(kn,0,chg,1,mgc,chg,0,0,bi,0,0,P_NONE,mat), \
		0, TOOL_CLASS, prob, 0, \
		wt, cost, 0, 0, 0, 0, wt, color )
#define WEPTOOL(name,desc,kn,mgc,chg,bi,prob,wt,cost,sdam,ldam,hitbon,typ,sub,mat,clr) \
	OBJECT( OBJ(name,desc), \
		BITS(kn,0,1,chg,mgc,1,0,0,bi,0,typ,sub,mat), \
		0, TOOL_CLASS, prob, 0, \
		wt, cost, sdam, ldam, hitbon, 0, wt, clr )
/* Containers */
CONTAINER("large box", (char *)0,       1, 0, 0, 1, 175,30,   8, WOOD, HI_WOOD),
CONTAINER("chest", (char *)0,           1, 0, 0, 1, 175,60,  16, WOOD, HI_WOOD),
CONTAINER("ice box", (char *)0,         1, 0, 0, 1,  50,90,  42, PLASTIC, CLR_WHITE),
CONTAINER("sack", "bag",                0, 0, 0, 0, 150, 5, 100, CLOTH, HI_CLOTH),
CONTAINER("oilskin sack", "bag",        0, 0, 0, 0, 100, 5, 100, CLOTH, HI_CLOTH),
CONTAINER("bag of holding", "bag",      0, 1, 0, 0, 100, 5, 100, CLOTH, HI_CLOTH),
CONTAINER("bag of digestion","bag",     0, 1, 0, 0,  25, 5, 100, CLOTH, HI_CLOTH),
CONTAINER("bag of tricks", "bag",       0, 1, 1, 0, 100, 5, 100, CLOTH, HI_CLOTH),

/* Unlocking tools */
TOOL("skeleton key", "key",     0, 0, 0, 0, 375,  0,  10, IRON, HI_METAL),
#ifdef TOURIST
TOOL("lock pick", (char *)0,    1, 0, 0, 0, 300,  0,  20, IRON, HI_METAL),
TOOL("credit card", (char *)0,  1, 0, 0, 0,  75,  0,  10, PLASTIC, CLR_WHITE),
#else
TOOL("lock pick", (char *)0,    1, 0, 0, 0, 375,  0,  20, IRON, HI_METAL),
#endif

/* Light sources */
/* [Tom] made candles cheaper & more common */
TOOL("tallow candle", "candle", 0, 1, 0, 0, 250,  0, 100, WAX, CLR_WHITE),
TOOL("wax candle", "candle",    0, 1, 0, 0, 200,  0, 100, WAX, CLR_WHITE),
TOOL("magic candle",  "candle", 0, 1, 1, 0,  25,  0, 100, WAX, CLR_WHITE),
TOOL("oil lamp", "lamp",        0, 0, 0, 0, 125, 0,  100, COPPER, CLR_YELLOW),
TOOL("brass lantern", (char *)0,1, 0, 0, 0,  75, 0,  100, COPPER, CLR_YELLOW),
TOOL("magic lamp", "lamp",      0, 0, 1, 0,  50, 0,100, COPPER, CLR_YELLOW),

/* Instruments */
/* KMH -- made less common */
TOOL("tin whistle", "whistle",  0, 0, 0, 0, 260,  0,  10, METAL, HI_METAL),
TOOL("magic whistle", "whistle",0, 0, 1, 0, 125,  0,  10, METAL, HI_METAL),
/* "If tin whistles are made out of tin, what do they make foghorns out of?" */
TOOL("wooden flute", "flute",   0, 0, 0, 0,  10,  0,  50, WOOD, HI_WOOD),
TOOL("magic flute", "flute",    0, 0, 1, 1,   5,  0,  50, WOOD, HI_WOOD),
TOOL("tooled horn", "horn",     0, 0, 0, 0,  10, 0,  50, BONE, CLR_WHITE),
TOOL("frost horn", "horn",      0, 0, 1, 1,   5, 0,  50, BONE, CLR_WHITE),
TOOL("fire horn", "horn",       0, 0, 1, 1,   5, 0,  50, BONE, CLR_WHITE),
TOOL("horn of plenty", "horn",  0, 0, 1, 1,   5, 0,  50, BONE, CLR_WHITE),
TOOL("wooden harp", "harp",     0, 0, 0, 0,  10, 0,  50, WOOD, HI_WOOD),
TOOL("magic harp", "harp",      0, 0, 1, 1,   5, 0,  50, WOOD, HI_WOOD),
TOOL("bell", (char *)0,         1, 0, 0, 0,   5, 0,  50, COPPER, HI_COPPER),
TOOL("bugle", (char *)0,        1, 0, 0, 0,  10, 0,  15, COPPER, HI_COPPER),
TOOL("leather drum", "drum",    0, 0, 0, 0,  10, 0,  25, LEATHER, HI_LEATHER),
TOOL("drum of earthquake", "drum",
                                0, 0, 1, 1,   5, 0,  25, LEATHER, HI_LEATHER),

/* Traps */
TOOL("land mine",(char *)0,     1, 0, 0, 0,   5,30, 180, IRON, CLR_RED),
TOOL("beartrap", (char *)0,     1, 0, 0, 0,   5,20,  60, IRON, HI_METAL),

/* Weapon-tools */
# ifdef P_SPOON
/* Added by Tsanth, in homage to Final Fantasy 2 */
/* KMH -- Not randomly generated (no damage!) */
WEPTOOL("spoon", (char *)0,
	1, 0, 0, 0,  5,  1, 5000,  0,  0, 0, WHACK,  -P_DART, PLATINUM, HI_METAL),
# endif /* P_SPOON */
#ifdef LIGHTSABERS
# ifdef D_SABER
WEPTOOL("pick-axe", (char *)0,
	1, 0, 0, 0, 175, 32,   50,  6,  3, 0, WHACK,  P_PICK_AXE, IRON, HI_METAL),
# else
WEPTOOL("pick-axe", (char *)0,
	1, 0, 0, 0, 180, 32,   50,  6,  3, 0, WHACK,  P_PICK_AXE, IRON, HI_METAL),
# endif
#else	/* LIGHTSABERS */
WEPTOOL("pick-axe", (char *)0,
	1, 0, 0, 0, 195, 32,   50,  6,  3, 0, WHACK,  P_PICK_AXE, IRON, HI_METAL),
#endif
WEPTOOL("fishing pole", (char *)0,
	1, 0, 0, 0, 25,  12,  50,  2,  6, 0, WHACK,  P_POLEARMS, METAL, HI_METAL),
WEPTOOL("grappling hook", "iron hook",
	0, 0, 0, 0, 25,  12,  50,  4,  8, 0, WHACK,  P_FLAIL, IRON, HI_METAL),
/* 3.4.1: unicorn horn left classified as "magic" */
WEPTOOL("unicorn horn", (char *)0,
	1, 1, 0, 1,  5,  8, 100, 12, 12, 0, PIERCE, P_UNICORN_HORN, BONE, CLR_WHITE),
/* WEPTOOL("torch", (char *)0,
	   1, 0, 0,  1,  8, 8, 5, 2, WHACK, P_CLUB, WOOD, HI_WOOD), */

OBJECT(OBJ("torch", (char *)0),
	BITS(1,1,1,0,0,1,0,0,0,0,WHACK,P_CLUB,WOOD),
	0, TOOL_CLASS, 125, 0,
	20, 8, 2, 5, WHACK, 0, 20, HI_WOOD ),

#ifdef LIGHTSABERS
/* [WAC]
 * Lightsabers are -3 to hit 
 * Double lightsaber is -4 to hit (only red)
 * DMG is increased: 10.5/15.5
 * green :9 + d3, 13 + d5
 * blue : 8 + d5, 12 + d7
 * red :  6 + d9, 10 + d11
 * red double: 6 + d9 + d9, 10 + d11 + d11  (15/21) in double mode
 */
WEPTOOL("green lightsaber", "lightsaber",
	0, 0, 1, 0,  5, 24, 500, 3,  5, 0, SLASH, P_LIGHTSABER, PLASTIC, HI_METAL),
# ifdef D_SABER
WEPTOOL("blue lightsaber",  "lightsaber",
	0, 0, 1, 0,  5, 24, 500, 5,  7, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),
# endif /* D_SABER */
WEPTOOL("red lightsaber",  "lightsaber",
	0, 0, 1, 0,  5, 24, 500, 9,  11, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),
WEPTOOL("red double lightsaber",  "double lightsaber",
	0, 0, 1, 1,  5, 24,1000, 15, 20, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),

WEPTOOL("laser swatter",  (char *)0,
	0, 0, 1, 0,  10, 24, 500, 40,  10, 5, WHACK, P_PADDLE, PLATINUM, CLR_BRIGHT_MAGENTA),

# ifdef D_SABER
#if 0 // just an idea...
WEPTOOL("yellow lightsaber",  "lightsaber",
	0, 0, 1, 0,  0, 60, 500, 5,  7, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),
WEPTOOL("violet lightsaber",  "lightsaber",
	0, 0, 1, 0,  0, 60, 500, 5,  7, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),
WEPTOOL("white lightsaber",  "lightsaber",
	0, 0, 1, 0,  0, 60, 500, 5,  7, 0, SLASH, P_LIGHTSABER, PLATINUM, HI_METAL),
# endif /* D_SABER */
#endif
#endif	/* LIGHTSABERS */

/* Other tools */
#ifdef TOURIST
TOOL("expensive camera", (char *)0,
				1, 0, 0, 1,  50, 0, 200, PLASTIC, CLR_BLACK),
TOOL("mirror", "looking glass", 0, 0, 0, 0,  150, 0,  10, GLASS, HI_SILVER),
#else
TOOL("mirror", "looking glass", 0, 0, 0, 0,  200, 0,  10, GLASS, HI_SILVER),
#endif
TOOL("crystal ball", "glass orb",
								0, 0, 1, 1,  50,0,  60, GLASS, HI_GLASS),
#if 0
/* STEPHEN WHITE'S NEW CODE */
/* KMH -- removed because there's potential for abuse */
TOOL("orb of enchantment", "glass orb",
				0, 0, 1, 1,   5, 0, 750, GLASS, HI_GLASS),
TOOL("orb of charging", "glass orb",
				0, 0, 1, 1,   5, 0, 750, GLASS, HI_GLASS),
TOOL("orb of destruction", "glass orb",
				0, 0, 0, 0,   5, 0, 750, GLASS, HI_GLASS),
#endif
TOOL("lenses", (char *)0,	1, 0, 0, 0,   25,  0,  80, GLASS, HI_GLASS),
TOOL("blindfold", (char *)0,    1, 0, 0, 0, 250,  0,  20, CLOTH, CLR_BLACK),
TOOL("towel", (char *)0,        1, 0, 0, 0, 100,  0,  50, CLOTH, CLR_MAGENTA),
#ifdef STEED
TOOL("saddle", (char *)0,       1, 0, 0, 0, 175,0, 150, LEATHER, HI_LEATHER),
TOOL("leash", (char *)0,        1, 0, 0, 0,  70, 0,  20, LEATHER, HI_LEATHER),
#else
TOOL("leash", (char *)0,        1, 0, 0, 0, 245, 0,  20, LEATHER, HI_LEATHER),
#endif
TOOL("stethoscope", (char *)0,  1, 0, 0, 0, 125,  0,  75, IRON, HI_METAL),
TOOL("tinning kit", (char *)0,  1, 0, 0, 1,  75, 0,  30, IRON, HI_METAL),
CONTAINER("medical kit", "leather bag",
				0, 0, 0, 0,  50, 0, 500, LEATHER, HI_LEATHER),
TOOL("tin opener", (char *)0,   1, 0, 0, 0, 125,  0,  30, IRON, HI_METAL),
TOOL("can of grease", (char *)0,1, 0, 0, 1,  75, 0,  20, IRON, HI_METAL),
TOOL("figurine", (char *)0,     1, 0, 1, 0, 275, 0,  80, MINERAL, HI_MINERAL),
TOOL("magic marker", (char *)0, 1, 0, 1, 1,  75,  0,  50, PLASTIC, CLR_RED),

TOOL("switcher", (char *)0, 1, 0, 1, 0,  5,  0,  2000, METAL, CLR_BRIGHT_GREEN),

TOOL("Hitchhiker's Guide To The Galaxy", "highly-complicated electronic device",
				0, 0, 0, 0,   0, 42,  1000, IRON, HI_METAL),
TOOL("diode",		"two-wired thing",
				0, 1, 0, 0,   5,  1,    50, IRON, CLR_WHITE),
TOOL("transistor",	"three-wired thing",
				0, 1, 0, 0,   5,  1,   100, IRON, CLR_WHITE),
TOOL("IC",              "many-wired thing",
				0, 1, 0, 0,   5,  1,  5000, IRON, CLR_WHITE),
TOOL("pack of floppies",	"box containing little plastic cards",
				0, 1, 0, 0,   5,  3,   300,PLASTIC, CLR_RED),
TOOL("god-o-meter",	"highly-complicated electronic device",
				0, 0, 0, 0,   5,  5,   500, IRON, HI_METAL),
TOOL("relay",		"four-wired thing",	
				0, 1, 0, 0,   5,  2,   100, IRON, CLR_WHITE),
TOOL("bottle",		NULL,
				1, 1, 0, 0,  50,  1,     5, GLASS, HI_METAL),
TOOL("chemistry set",	"box of obscure-looking glass devices",
				0, 0, 0, 1,  25, 20,   500, GLASS, CLR_ORANGE),

/* Two pseudo tools. These can never exist outside of medical kits. */
OBJECT(OBJ("bandage", (char *)0),
		BITS(1,1,0,0,0,0,0,1,0,0,0,P_NONE,CLOTH), 0,
		TOOL_CLASS, 0, 0, 1, 1, 0, 0, 0, 0, 0, CLR_WHITE),
OBJECT(OBJ("phial", (char *)0),
		BITS(1,1,0,0,0,0,0,1,0,0,0,P_NONE,GLASS), 0,
		TOOL_CLASS, 0, 0, 2, 1, 0, 0, 0, 0, 1, HI_GLASS),

/* Two special unique artifact "tools" */
OBJECT(OBJ("Candelabrum of Invocation", "candelabrum"),
		BITS(0,0,1,0,1,0,1,1,0,0,0,0,GOLD), 0,
		TOOL_CLASS, 0, 0,10, 5000, 0, 0, 0, 0, 200, HI_GOLD),
OBJECT(OBJ("Bell of Opening", "silver bell"),
		BITS(0,0,1,0,1,1,1,1,0,0,0,0,SILVER), 0,
		TOOL_CLASS, 0, 0,10, 5000, 0, 0, 0, 0, 50, HI_SILVER),
#undef TOOL
#undef CONTAINER
#undef WEPTOOL


/* Comestibles ... */
#define FOOD(name,prob,delay,wt,unk,tin,nutrition,color) OBJECT( \
		OBJ(name,(char *)0), BITS(1,1,unk,0,0,0,0,0,0,0,0,0,tin), 0, \
		FOOD_CLASS, prob, delay, \
		wt, nutrition/20 + 5, 0, 0, 0, 0, nutrition, color )
/* all types of food (except tins & corpses) must have a delay of at least 1. */
/* delay on corpses is computed and is weight dependant */
/* dog eats foods 0-4 but prefers tripe rations above all others */
/* fortune cookies can be read */
/* carrots improve your vision */
/* +0 tins contain monster meat */
/* +1 tins (of spinach) make you stronger (like Popeye) */
/* food CORPSE is a cadaver of some type */
/* meatballs/sticks/rings are only created from objects via stone to flesh */

/* banana cures hallucination, melon cures confusion, pear cures stun, asian pear cures both confusion and stun --Amy */
/* apple cures numbness, orange cures freezing, cream pie cures burn, lemon cures fear */

/* Meat */
FOOD("tripe ration",       1000, 2, 0, 0, FLESH, 250, CLR_BROWN),
FOOD("corpse",              250, 1,  0, 0, FLESH,   0, CLR_BROWN),
FOOD("egg",                 350, 1,  0, 1, FLESH,  100, CLR_WHITE),
FOOD("meatball",             5, 1,  0, 0, FLESH,   10, CLR_BROWN),
FOOD("meat stick",           5, 1,  0, 0, FLESH,   10, CLR_BROWN),
FOOD("huge chunk of meat",   5,20,0, 0, FLESH,2000, CLR_BROWN),
/* special case because it's not mergable */
OBJECT(OBJ("meat ring", (char *)0),
    BITS(1,0,0,0,0,0,0,0,0,0,0,0,FLESH),
    0, FOOD_CLASS, 0, 1, 5, 1, 0, 0, 0, 0, 5, CLR_BROWN),


/* Body parts.... eeeww */
FOOD("eyeball",              0, 1,  0, 0, FLESH,  10, CLR_WHITE),
FOOD("severed hand",         0, 1,  0, 0, FLESH,  40, CLR_BROWN),

/* Fruits & veggies */
FOOD("kelp frond",           5, 1,  0, 0, VEGGY,  75, CLR_GREEN),
FOOD("eucalyptus leaf",     45, 1,  0, 0, VEGGY, 100, CLR_GREEN),
FOOD("clove of garlic",     85, 1,  0, 0, VEGGY,  50, CLR_WHITE),
FOOD("sprig of wolfsbane",  85, 1,  0, 0, VEGGY,  50, CLR_GREEN),
FOOD("apple",               215, 1,  0, 0, VEGGY, 100, CLR_RED),
FOOD("carrot",              175, 1,  0, 0, VEGGY,  75, CLR_ORANGE),
FOOD("pear",                95, 1,  0, 0, VEGGY, 100, CLR_BRIGHT_GREEN),
FOOD("asian pear",          55, 1,  0, 0, VEGGY, 150, CLR_BRIGHT_GREEN),
FOOD("lemon",               50, 1,  0, 0, VEGGY, 200, CLR_YELLOW),
FOOD("banana",              100, 1,  0, 0, VEGGY, 120, CLR_YELLOW),
FOOD("orange",              100, 1,  0, 0, VEGGY, 120, CLR_ORANGE),
FOOD("mushroom",             5, 1,  0, 0, VEGGY, 130, CLR_BLACK),
FOOD("melon",               95, 1,  0, 0, VEGGY, 175, CLR_BRIGHT_GREEN),
FOOD("slime mold",          375, 1,  0, 0, VEGGY, 250, HI_ORGANIC),
FOOD("peanut bag",	     25, 3,  0, 0, VEGGY, 800, HI_ORGANIC),

/* People food */
FOOD("lump of royal jelly",  5, 1,  0, 0, VEGGY, 200, CLR_YELLOW),
FOOD("cream pie",           50, 1, 0, 0, VEGGY, 100, CLR_WHITE),
FOOD("sandwich",            50, 1, 0, 0, FLESH, 100, CLR_WHITE),
FOOD("candy bar",           65, 1,  0, 0, VEGGY, 100, CLR_BROWN),
FOOD("fortune cookie",     325, 1,  0, 0, VEGGY,  40, CLR_YELLOW),
FOOD("pancake",             65, 2,  0, 0, VEGGY, 200, CLR_YELLOW),
FOOD("tortilla",             5, 2,  0, 0, VEGGY,  80, CLR_WHITE),
/* special "food" by Amy */
FOOD("ugh memory to create inventory window",             5, 1,  0, 0, VEGGY,  0, CLR_WHITE),
/* [Tom] more food.... taken off pancake (25) */
FOOD("cheese",              50, 2,  0, 0, FLESH, 250, CLR_YELLOW),
FOOD("pill",                 5, 1,  0, 0, VEGGY,   0, CLR_BRIGHT_MAGENTA),
FOOD("holy wafer",          35, 1,  0, 0, VEGGY, 400, CLR_WHITE),
FOOD("lembas wafer",       100, 2,  0, 0, VEGGY, 800, CLR_WHITE),
FOOD("cram ration",        100, 3, 0, 0, VEGGY, 750, HI_ORGANIC),
FOOD("food ration",        500, 5, 0, 0, VEGGY, 1000, HI_ORGANIC),
FOOD("Hacker's Food",	     5, 1, 0, 0, VEGGY, 800, HI_METAL),
FOOD("K-ration",             5, 1, 0, 0, VEGGY, 400, HI_ORGANIC),
FOOD("C-ration",             5, 1, 0, 0, VEGGY, 300, HI_ORGANIC),
FOOD("tin",                500, 0, 0, 1, METAL,   0, HI_METAL),
#undef FOOD

/* potions ... */
#define POTION(name,desc,mgc,power,prob,cost,color) OBJECT( \
		OBJ(name,desc), BITS(0,1,0,0,mgc,0,0,0,0,0,0,0,GLASS), power, \
		POTION_CLASS, prob, 0, 0, cost, 0, 0, 0, 0, 10, color )
POTION("booze", "brown",                0, 0,          140, 300, CLR_BROWN),
POTION("fruit juice", "dark",           0, 0,          170, 300, CLR_BLACK),
POTION("see invisible", "magenta",      1, SEE_INVIS,  165, 300, CLR_MAGENTA),
POTION("sickness", "fizzy",             0, 0,          125, 300, CLR_CYAN),
POTION("sleeping",  "effervescent",     1, 0,          100, 300, CLR_GRAY),
POTION("clairvoyance","luminescent",    1, 0,          100, 300, CLR_WHITE),
POTION("confusion", "orange",           1, CONFUSION,  150, 300, CLR_ORANGE),
POTION("hallucination", "sky blue",     1, HALLUC,     125, 300, CLR_CYAN),
POTION("healing", "purple-red",         1, 0,          275, 300, CLR_MAGENTA),
POTION("extra healing", "puce",         1, 0,          225, 300, CLR_RED),
POTION("restore ability", "pink",       1, 0,          200, 300, CLR_BRIGHT_MAGENTA),
POTION("blindness", "yellow",           1, BLINDED,    165, 300, CLR_YELLOW),
POTION("ESP", "muddy",                  1, TELEPAT,    100, 300, CLR_BROWN),
POTION("gain energy", "cloudy",         1, 0,          175, 300, CLR_WHITE),
POTION("gain health", "iridescent",     1, 0,          25, 300, CLR_ORANGE),
POTION("banishing fear", "voluminous",  1, 0,          25, 300, CLR_CYAN),
POTION("ice", "ice-cold",  		    1, 0,          25, 300, CLR_BRIGHT_CYAN),
POTION("fire", "simmering",  		    1, 0,          25, 300, CLR_ORANGE),
POTION("fear", "bewitched",  		    1, 0,          25, 300, CLR_MAGENTA),
POTION("stunning", "viscous",     	    1, 0,          25, 300, CLR_RED),
POTION("numbness", "flowing",		    1, 0,          25, 300, CLR_ORANGE),
POTION("slime", "slimy",  		    1, 0,          5, 300, CLR_BRIGHT_GREEN),
POTION("urine", "manky",  		    1, 0,          5, 300, CLR_YELLOW),
POTION("cancellation", "sparkly",	    1, 0,          5, 300, CLR_CYAN),
POTION("invisibility", "brilliant blue",1, INVIS,      175, 300, CLR_BRIGHT_BLUE),
POTION("monster detection", "bubbly",   1, 0,          190, 300, CLR_WHITE),
POTION("object detection", "smoky",     1, 0,          165, 300, CLR_GRAY),
POTION("enlightenment", "swirly",       1, 0,          100, 300, CLR_BROWN),
POTION("full healing",  "black",        1, 0,          175, 300, CLR_BLACK),
POTION("levitation", "cyan",            1, LEVITATION, 190, 300, CLR_CYAN),
POTION("polymorph", "golden",           1, 0,          50, 300, CLR_YELLOW),
POTION("speed", "dark green",           1, FAST,       190, 300, CLR_GREEN),
POTION("acid", "white",                 0, 0,          100, 300, CLR_WHITE),
POTION("oil", "murky",                  0, 0,          150, 300, CLR_BROWN),
POTION("salt water",	"polka-dot",    0, 0,		 25, 300, CLR_RED),
POTION("gain ability", "ruby",          1, 0,          190, 300, CLR_RED),
POTION("gain level", "milky",           1, 0,          100, 300, CLR_WHITE),
POTION("invulnerability", "icy",        1, 0,          25, 300, CLR_BRIGHT_BLUE),
POTION("paralysis", "emerald",          1, 0,          190, 300, CLR_BRIGHT_GREEN),
POTION("extreme power",	"turquoise",    1, 0, 	        25, 300, CLR_CYAN),
POTION("recovery",	"reddish",      1, 0,           25, 300, CLR_RED),
POTION("heroism",	    "tan",	          1, 0,           25, 300, CLR_BROWN),
POTION("cyanide",	    "vermillion",     0, 0,           25, 300, CLR_RED),
POTION("radium",	    "crimson",        0, 0,           25, 300, CLR_RED),
POTION("Jolt Cola",	    "illegal",  0, 0,           25, 300, CLR_BROWN),
POTION("Pan Galactic Gargle Blaster",
			    "radiating",	    0, 0,           25, 300, CLR_WHITE),
POTION((char *)0, "thaumaturgic",              0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "shining",          0, 0,           0,   0, CLR_CYAN),
POTION((char *)0, "incandescent",        0, 0,           0,   0, CLR_WHITE),
POTION((char *)0, "freezing",                0, 0,           0,   0, CLR_BRIGHT_BLUE),
POTION((char *)0, "squishy",            0, 0,           0,   0, CLR_GREEN),
POTION((char *)0, "greasy",             0, 0,           0,   0, CLR_BLACK),
POTION((char *)0, "slimy",              0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "soapy",              0, 0,           0,   0, CLR_RED),
POTION((char *)0, "ochre",              0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "steamy",             0, 0,           0,   0, CLR_WHITE),
POTION((char *)0, "gooey",              0, 0,           0,   0, CLR_MAGENTA),
POTION((char *)0, "silver",             0, 0,           0,   0, HI_SILVER),
POTION((char *)0, "dangerous",          0, 0,           0,   0, CLR_RED),
POTION((char *)0, "creepy",             0, 0,           0,   0, CLR_GREEN),
POTION((char *)0, "distilled",             0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "warping",             0, 0,           0,   0, CLR_BRIGHT_BLUE),
POTION((char *)0, "unnatural",             0, 0,           0,   0, CLR_MAGENTA),
POTION((char *)0, "venomous",             0, 0,           0,   0, CLR_CYAN),
POTION((char *)0, "colorless",             0, 0,           0,   0, CLR_GRAY),
POTION((char *)0, "alchemical",             0, 0,           0,   0, CLR_BLACK),
POTION((char *)0, "fluorescent",             0, 0,           0,   0, CLR_ORANGE),
POTION((char *)0, "illuminated",             0, 0,           0,   0, CLR_YELLOW),
POTION((char *)0, "bright",             0, 0,           0,   0, CLR_WHITE),
POTION((char *)0, "carcinogenic",             0, 0,           0,   0, CLR_BRIGHT_CYAN),
POTION((char *)0, "liquid",             0, 0,           0,   0, CLR_BRIGHT_GREEN),
POTION((char *)0, "buzzing",             0, 0,           0,   0, CLR_BRIGHT_BLUE),
POTION((char *)0, "concocted",             0, 0,           0,   0, CLR_BRIGHT_MAGENTA),
POTION((char *)0, "amber",             0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "aquamarine",             0, 0,           0,   0, CLR_CYAN),
POTION((char *)0, "blue",             0, 0,           0,   0, CLR_BRIGHT_BLUE),
POTION((char *)0, "ecru",             0, 0,           0,   0, CLR_MAGENTA),
POTION((char *)0, "green",             0, 0,           0,   0, CLR_GREEN),
POTION((char *)0, "gray",             0, 0,           0,   0, CLR_GRAY),
POTION((char *)0, "plaid",             0, 0,           0,   0, CLR_WHITE),
POTION((char *)0, "purple",             0, 0,           0,   0, CLR_BRIGHT_MAGENTA),
POTION((char *)0, "red",             0, 0,           0,   0, CLR_RED),
POTION((char *)0, "tangerine",             0, 0,           0,   0, CLR_ORANGE),
POTION((char *)0, "topaz",             0, 0,           0,   0, CLR_YELLOW),
POTION((char *)0, "violet",             0, 0,           0,   0, CLR_BRIGHT_MAGENTA),
POTION((char *)0, "ghostly",             0, 0,           0,   0, CLR_GRAY),
POTION((char *)0, "hallowed",             0, 0,           0,   0, CLR_BLACK),
POTION((char *)0, "spiritual",             0, 0,           0,   0, CLR_WHITE),
POTION((char *)0, "vapor",             0, 0,           0,   0, CLR_BROWN),
POTION((char *)0, "fuming",             0, 0,           0,   0, CLR_BLACK),
POTION((char *)0, "sizzling",             0, 0,           0,   0, CLR_ORANGE),
POTION("water", "clear",                0, 0,          275, 300, CLR_CYAN),
POTION("blood", "blood-red",            0, 0,          25, 300, CLR_RED),
POTION("vampire blood", "blood-red",    1, 0,          25, 300, CLR_RED),
POTION("amnesia", "sparkling",          1, 0,          80, 300, CLR_CYAN),
#undef POTION

/* scrolls ... */
#define SCROLL(name,text,sub,mgc,prob,cost,color) OBJECT( \
		OBJ(name,text), BITS(0,1,0,0,mgc,0,0,0,0,0,0,sub,PAPER), 0, \
		SCROLL_CLASS, prob, 0, 0, cost, 0, 0, 0, 0, 6, color )
/* Attack */
SCROLL("create monster",        "LEP GEX VEN ZEA",      P_ATTACK_SPELL, 1, 120, 300, CLR_RED),
SCROLL("summon undead",        "NO SPACE",      P_ATTACK_SPELL, 1,   25, 300, CLR_WHITE),
/* Enchantment */
SCROLL("taming",                "PRIRUTSENIE",          P_ENCHANTMENT_SPELL, 1,  175, 300, CLR_WHITE),
/* Divination */
SCROLL("light",                 "VERR YED HORRE",       P_DIVINATION_SPELL, 1,  75, 300, CLR_BLACK),
SCROLL("food detection",        "YUM YUM",              P_DIVINATION_SPELL, 1,  75, 300, CLR_YELLOW),
SCROLL("gold detection",        "THARR",                P_DIVINATION_SPELL, 1, 115, 300, CLR_BROWN),
SCROLL("identify",              "KERNOD WEL",           P_DIVINATION_SPELL, 1, 1000, 300, CLR_GREEN),
SCROLL("inventory id",              "NOW YOU SEE IT",           P_DIVINATION_SPELL, 1,  25, 300, CLR_YELLOW),
SCROLL("magic mapping",         "ELAM EBOW",            P_DIVINATION_SPELL, 1,  175, 300, CLR_CYAN),
SCROLL("flood",                 "AQUE BRAGH",           P_DIVINATION_SPELL, 1,   25, 300, CLR_BRIGHT_BLUE),
SCROLL("gain mana",         "DAMN IT",            P_DIVINATION_SPELL, 1,  25, 300, CLR_BRIGHT_MAGENTA),
/* Enchantment */
SCROLL("confuse monster",       "NR 9",                 P_ENCHANTMENT_SPELL,  1,  90, 300, CLR_MAGENTA),
SCROLL("scare monster",         "XIXAXA XOXAXA XUXAXA", P_ENCHANTMENT_SPELL,  1,  175, 300, CLR_BRIGHT_BLUE),
SCROLL("enchant weapon",        "DAIYEN FOOELS",        P_ENCHANTMENT_SPELL,  1,  465, 300, CLR_RED),
SCROLL("enchant armor",         "ZELGO MER",            P_ENCHANTMENT_SPELL,  1,  315, 300, CLR_GREEN),
/* Protection */
SCROLL("remove curse",          "PRATYAVAYAH",          P_PROTECTION_SPELL, 1, 300, 300, CLR_BRIGHT_MAGENTA),
/* Body */
SCROLL("teleportation",         "VENZAR BORGAVVE",      P_BODY_SPELL, 1,  295, 300, CLR_BROWN),
SCROLL("tele level",         "GON GET YA",      P_BODY_SPELL, 1,  25, 300, CLR_BRIGHT_CYAN),
SCROLL("warping",         "MY SPUTA WILL FLOW DOWN",      P_BODY_SPELL, 1,  25, 300, CLR_BRIGHT_CYAN),
/* Matter */
SCROLL("fire",                  "ANDOVA BEGARIN",       P_MATTER_SPELL, 1,  115, 300, CLR_WHITE),
SCROLL("earth",                 "KIRJE",                P_MATTER_SPELL, 1,  100, 300, CLR_CYAN),

SCROLL("destroy armor",         "JUYED AWK YACC",       P_NONE, 1,  100, 300, CLR_YELLOW),
SCROLL("amnesia",               "DUAM XNAHT",           P_NONE, 1,  25, 300, CLR_BRIGHT_BLUE),
SCROLL("bad effect",               "LITTLE STRAWBERRY ME BABY",           P_NONE, 1,  25, 300, CLR_ORANGE),
SCROLL("healing",               "LIFE RESTORATION",           P_NONE, 1,   5, 300, CLR_BRIGHT_CYAN),
SCROLL("mana",               "I WANT TO SEE URANUS TOO",           P_NONE, 1,   5, 300, CLR_BRIGHT_BLUE),
SCROLL("cure",               "SPARKLING EDWARD CULLEN",           P_NONE, 1,   5, 300, CLR_BRIGHT_BLUE),
SCROLL("trap disarming",               "CHRISTIAN GREY KILLED ALL HIS SUBS",    P_NONE, 1,   25, 300, CLR_BRIGHT_MAGENTA),
SCROLL("standard id",               "WHAT THE FUCK IS THIS",           P_NONE, 1,   5, 300, CLR_ORANGE),
SCROLL("charging",              "HACKEM MUCHE",         P_NONE, 1,  145, 300, CLR_GREEN),
SCROLL("genocide",              "ELBIB YLOH",           P_NONE, 1,  75, 300, CLR_MAGENTA),
SCROLL("punishment",            "VE FORBRYDERNE",       P_NONE, 1,  75, 300, CLR_GRAY),
SCROLL("stinking cloud",	"VELOX NEB",            P_NONE, 1,  75, 300, CLR_GRAY),
SCROLL("trap detection",	"HOYO HOYO",            P_NONE, 1,  25, 300, CLR_YELLOW),
SCROLL("acquirement",	"THE RESULT IS THE FRUIT",            P_NONE, 1,  25, 300, CLR_GRAY),
SCROLL("proof armor",         "I AM THE KING",       P_NONE, 1,  25, 300, CLR_ORANGE),
SCROLL("proof weapon",         "YOU ARE DOOMED",       P_NONE, 1,  25, 300, CLR_GRAY),
SCROLL("mass murder",		"ENEMATZU MEMALEZU",	P_NONE,  1,  25, 300, CLR_BLACK),
SCROLL("undo genocide",		"42",			      P_NONE,  1,  25, 300, CLR_ORANGE),
SCROLL("reverse identify",	"OH CAPTAIN MY CAPTAIN",P_NONE,  1,  25, 300, CLR_RED),
SCROLL("wishing",		"TRICK 13",		      P_NONE,  1,  25, 300, CLR_WHITE),
SCROLL("consecration",		"MAY THE FORCE BE WITH YOU",
								      P_NONE,  1,  25, 300, CLR_BRIGHT_CYAN),
SCROLL("enthronization",		"XUS MODA",	      P_NONE,  1,  25, 300, CLR_BLACK),
SCROLL("fountain building",		"XOR ME HSALS",	      P_NONE,  1,  25, 300, CLR_YELLOW),
SCROLL("sinking",		"SPORKHACK ASCENSION",	      P_NONE,  1,  25, 300, CLR_CYAN),
SCROLL("WC",		"LETS PLAY NETHACK",	      P_NONE,  1,  25, 300, CLR_WHITE),
SCROLL("lava",		"LETS FAIL AND ROLL",	      P_NONE,  1,  25, 300, CLR_GRAY),
SCROLL("growth",		"WELCOME TO ANGBAND",	      P_NONE,  1,  25, 300, CLR_BRIGHT_GREEN),
SCROLL("ice",		"IMMORTAL DUNGEON",	      P_NONE,  1,  25, 300, CLR_GREEN),
SCROLL("clouds",		"VOLARE",	      P_NONE,  1,  25, 300, CLR_BRIGHT_BLUE),
SCROLL("barrhing",		"CONVICT PATCH",	      P_NONE,  1,  25, 300, CLR_BRIGHT_MAGENTA),
SCROLL("lockout",		"WE WILL HURT YOU",	      P_NONE,  1,  25, 300, CLR_ORANGE),
SCROLL("stoning",		"CURSED TIN OF COCKATRICE MEAT",	      P_NONE,  1,  5, 300, CLR_BLACK),
SCROLL("root password detection","XYZZY",		      P_NONE,  1,  25, 300, CLR_GRAY),
SCROLL("trap creation","TOP SECRET DO NOT READ",      P_NONE,  1,  25, 300, CLR_BLACK),
SCROLL("sleep","I AM SO FUCKING TIRED",         P_NONE, 1,   25, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,		"FOOBIE BLETCH",        P_NONE, 1,   0, 300, CLR_CYAN),
SCROLL((char *)0,		"TEMOV",                P_NONE, 1,   0, 300, CLR_BLACK),
SCROLL((char *)0,		"GARVEN DEH",           P_NONE, 1,   0, 300, CLR_GREEN),
SCROLL((char *)0,		"READ ME",              P_NONE, 1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "ETAOIN SHRDLU",   P_NONE,      1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "LOREM IPSUM",     P_NONE,      1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "FNORD",           P_NONE,      1,   0, 300, CLR_BROWN), /* Illuminati */
SCROLL((char *)0,               "KO BATE",         P_NONE,      1,   0, 300, CLR_RED), /* Kurd Lasswitz */
SCROLL((char *)0,               "ACHAT SHTAYIM SHALOSH",P_NONE, 1,   0, 300, CLR_BRIGHT_BLUE), /* Uri Geller */
SCROLL((char *)0,               "ABRA KA DABRA",     P_NONE,    1,   0, 300, CLR_BLACK), /* traditional incantation */
SCROLL((char *)0,               "ASHPD",          P_NONE,       1,   0, 300, CLR_BLACK), /* Portal */
SCROLL((char *)0,               "SODALG",          P_NONE,      1,   0, 300, CLR_RED), /* Portal */
SCROLL((char *)0,               "ZLORFIK",         P_NONE,      1,   0, 300, CLR_ORANGE), /* Zak McKracken */
SCROLL((char *)0,               "GNIK SISI VLE",     P_NONE,    1,   0, 300, CLR_GREEN), /* Zak McKracken */
SCROLL((char *)0,               "HAPAX LEGOMENON",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "HZLRC KSTSBD MPFNG", P_NONE,   1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "EIRIS SAZUN IDISI",  P_NONE,   1,   0, 300, CLR_BRIGHT_GREEN), /* Merseburg Incantations */
SCROLL((char *)0,               "PHOL ENDE WODAN",   P_NONE,    1,   0, 300, CLR_GRAY), /* Merseburg Incantations */
SCROLL((char *)0,               "GHOTI",             P_NONE,    1,   0, 300, CLR_BRIGHT_BLUE), /* pronounced as 'fish', George Bernard Shaw */
SCROLL((char *)0,               "MAPIRO MAHAMA DIROMAT",P_NONE, 1,   0, 300, CLR_BRIGHT_MAGENTA), /* Wizardry */
SCROLL((char *)0,               "VAS CORP BET MANI", P_NONE,    1,   0, 300, CLR_GRAY), /* Ultima */
/* these must come last because they have special descriptions */
SCROLL((char *)0,               "CLONE MONSTER",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "RESURRECTION",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "APOCALYPSE",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "WORLD FALL",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "CATACLYSM",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "HAHAHAHAHAHAHA",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "LA VIVME",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "U FOKIENG SUK",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "SIR I HAVE TO TAKE A SHIT",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "YOU DONT STAND A CHANCE",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "VUS AS CORIUMA",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "SE FERSE PARUM",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "ABOR EFECTOR",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "ALIUS PRA",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "AM PO COLVATIO",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "CO APPESTUS",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "CONE ALACIO",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "CRIAEDO",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "DEVIENEX COER",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "DUCTUM ADIS",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "INE IGO PIO",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "INQUE COMUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "INS CUBITOR",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "IUSTIO QUE PIS",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "LAM EQUENUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "LENS ALITUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "MA MILLOCOR",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "NIOQUO TARGO",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "NONO STENTUM",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "PAS DIO LEO",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "PONUS MOSTAS",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "PRIUS SA",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "PROR PERPERCA",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "PUTIUS CONSIO",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "PUTO FER LO",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "REQUICO SIDES",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "SALIQUAS",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "SERO GRIUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "OXHE SRIAN",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "SEVER OPEROFOR",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "SUS COMNITUS",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "SUS QUO SUM",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SUSY THENSE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "TO DO CANCENUS",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "TRAETOR HORIGO",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "UTOR COMPERIO",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "VITIO PUS RO",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "VITIO SUS",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "VO AMMITAM SA",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "VO FACIAM",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "WIZZY LABOR CO",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "KAME HAME HA",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SECTUM SEMPRA",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "EYGOORTS TOGAAL JEZEHH",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "YOU WILL DIE A SLOW SLOW DEATH",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "BLUE SCREEN OF DEATH",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SEE IF I CARE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "VIRUS INFECTION DETECTED",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "INTRUDER ALERT",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "USER DEATH IMMINENT",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "I HERE SOMETHING",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "GOT SOMETHING FOUR YOU",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "MY PRIVATE IS TENMETERS ACROSS",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ECNETOPINMO",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "SUTSI",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "YIK MECH SHEGOTH",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "KAPOW",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "YNORI ERUP",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "REGNAD",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "ODIV",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "ZTORF",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "HITME",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "MANANNANMACLIR",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "MEAD NI NAJAP",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "MKMNFST",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "DOGO FUTSF",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "MANUALIRK GLEKNOW MIZK",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "KLATHA DATHA NY ARYATHA",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "IAZNAB",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "WOPAK",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "HCUO",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "ENO OWT EERHT",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "GNOZAB",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "ABABILA",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "MUNCH MUNCH",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "FROTZ",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "EDEVESH HANAGASH",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "YIKES",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "IDNUM AIROLG TISNART CIS",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "RAMBA ZAMBA",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "KTTDLWRGT",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "GNAY GNIY",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "CARPE DIEM",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "CUTME",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "FOO BAR",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "FPMAM",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "FOX NAWAGU",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "YTTOCS PU EM MAEB",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "NADSIL SEETRURA",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "ACME",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "CHUTZPAH",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "TLASFO SENIL",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "RW NW PRT M HRW",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "MORPH BALL",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "TUOE DISNI",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "FASUN SEEEEP",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "KATNISS SHOT PEETA IN THE HEAD",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "SNAPE KILLED DUMBLEDORE",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "HERMIONE CASTS AVADA KEDAVRA AT UMBRIDGE",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "GANDALF GOT EATEN BY A BLAROG",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "LLIYLLATNEMTONMAI",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "MULY SA CITA NUL",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "KNIRHS YMEV OLI",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SGURDNOEDAMTONSAWEMAGSIHT",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "CRAPPITY CRAP",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "INTEGER DIVIDE BY ZERO",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "PURE VIRTUAL FUNCTION CALL",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "SUDDENLY THE DUNGEON COLLAPSES",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SEGMENTATION FAULT",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SIGNAL 11 WAS RAISED",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "ADOM CRASHES AND ERASES YOUR SAVEGAME",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SLASHEM EXTENDED WANTS YOU DEAD",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "ASCENSION IS IMPOSSIBLE",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "COCKATRICE CORPSES ARE DELICIOUS",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "ADA ILIKET",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "CLITUS DISCUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "EX PROTEO",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "INEMPTIO",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SO INFERO NO",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "VIA FERO DEO",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "BUSTER HYMEN",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "ADE EXPIRIUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "YOU REALLY BECOME STRONGER",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "I AM VERY DISGUSTED WITH THE TRASHY MAN",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "I HEARD YOU WERE SLEEPING THERE",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SORRY NISI",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "DONT STARE ME ALWAYS",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "AS IF FEEL SOMETHING",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "EY REFLECT EFF INT",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "ENSSICIBZ EDUDO",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "HOUOU SUIKUN CHARCOLT MILLENUM",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "ELF GRANDFATHER RESEARCH LAB",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "TRY HARD",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "GO AWAY",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "A WILD STEELIX APPEARED",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "DEJIZ FRADO",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "ENSSNAKE F FIGHTAH",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "MIXING FUCK",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "NUMB ENEMY BY LICKING CIRCLE",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "YOUR INSIDE IS MADE OF MUD",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "THE ENEMY RUN AWAY BY BELLOW",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "BODY KNOCK ON EARTH WILL HURT",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "CHANGED CELLS TO BE LIKE AS ELF",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "LITTLE INJURED DOUBLE PAY",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "FIRST ATTACK LOSED SO IS LATER",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "STIFFEN BODY TO ADD POWER",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "ATTACK BY MOVING FAST",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "RENEW TIME DIFFER SO QUANTITY",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "TO MENY SHOTING TO BE AVOID",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "OLD HIT CONTINUE OR WILL LOSE CONTINUE",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "V RATE RISE BY DISTURB",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "MYS SKIN WITH ACID",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "ATTACK BY THROW A GOLD COIN",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "NUMB IF HITTED SERIOUS IF HURT",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "MESSED AFTER RUSH AND WHIRLING",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SAVE SOME POWER AFTER BEATTACK",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "ATTACK WITH NUGGEL DEFENCE FALL",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "MOVE FINGERS TO DISTUB BY STUNTS",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "STUNT PROTECTED HAS NO SUPESTATE",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "CUT ENEMY BY HAMME OR NAIL",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "HIT THE KEY BY VACUUM LEAF",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "FRINDS ELF ATTACK",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SPRING NO HAPPEN",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "STUNT OF GHOST IS DIFFER",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "DIFFER SEX CANT USE STUNTS",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "OWERED HITTING BY LOOK SOUP",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ADD STRENGTHS DIVIDE EVENLY",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "RAGE CAN ADD POWER",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "VOMIT TO MELT ENEMY",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "SLITHLY ATTACKING IS MORE STRONGER DONT HOLD PROP",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "STRESS PRESSING TO VERY BOOSTING",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "CHANGED WITH OPPOSITE ABILITYPERSON",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "RISE DEFENCE BY FOGET ALL THE MOMENLOWERED HITING BY",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "FASTLY JUMP TO ENEMY WITH INVISIBLES FISRTLY",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "COVERED VILE DISAPPER",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "TRUE RISE BY STRANGE SMELL",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "RECOVER BY SMEEL",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "QUICKER USED THE STUNT OF ELF",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "NO FAIL ATTACKING BY SUMMER",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "THROW BODY MAKED LIGHTLY SHARP SPEE WORK",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "LOOK EN WITH EYES TO LOW ATTACK",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "GOOD IS ALLOW AFTER TO HAVE THE TRAY ONLY USE IT",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "SUPER BURNINATE ENEMY WITH VERY TIRED",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "WIDE ARM  ENEMYAND IT CANNT ESCAPE",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "BEAUTY FLAME ATTACK WITH BLUE AND BURNED",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "RUSH ENEMY ON FIRE WITH SHOCK MAYBE NUMBED",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "JUMPING UP AND DOWN TO NUMBED ENEMY",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "FOLDING WING ATLITUDE VERY DAMAGE USED",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "CHOP CAN BREAKED THE BARRIER",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "BIG NOISE BY SHAKE WING MAYBE LOW SP",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "POWER PERFORATO AS BARET",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "SEED SHOTED AS GUN 25 TIME",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ELF IS FESTIVE FOR SPECIAL DAY",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "REDUC ENEMY POWER BY COQUETRY",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "ATTACK BY SOUND WORD LEARN MESSED CAN DO",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "ELF USED TO TELL SECRET TO EN LOSE SIGHT OF WHY COMPETE",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "CROWDED OF BODY IN FLUFFY WATAGE",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SLARSHING HARD HAMME DEFENCE LOWED",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "CRUSH ENEMY BY APPEAL OF LAST HAIL OR 2",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "FROM THE BODY FILLED FEARFUL AURA GONE BE ABLE SCARE UP",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "DIBING TO ATTACK NEXT",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "MAKE LAND EXPLODE MAY LOWED DEFEND",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "ATTACK BY UNKNOWABLES MAYBE CANT DO",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "HITTING EVEN USED HAT MELO",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "IMOLATEING TO ATTACK ENEMY SPEE RISE",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "TO CAJOLE TO AT SAME TIME GIVE UP SO LOOKS",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "LEAF STUNT UP HIGH BLAZE MINISTRIES BRUNT FLINCH AND ASK",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "CATCHES ERYONES EYE",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "HEAVY ELF CANT FLEW",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "HIGH RATE LOWER VOLTAGE IS LOW",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "FIST HEAVY BIG DAMAGE SPEE WORK",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "MAKE THE PRIZE TWICE USED",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "AMAZING AFRO HEAD RUSH ATTACK",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "LIFE RISK JAM ALSO DAMAGED",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "5 TURN SPECIAL SPACE PREVENT HP RECOVER BY IT",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "HEAL A WOUND BY CALLING MANSERVENT",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "SHOOT A HAYMAKER AND WITHOUT BY LOVELY GESTURE",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "EMPLY MENTAL TO SWITCH STATUS",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "ATTACK BY BURN BODY POWER MORE AS HEAVY VACANT",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "NURSE THE NAIL THE ATTACK IS STRONGER",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "RECOVER DEAD BY SCREAM",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "WINDING FIERCE TO ATTACK MESS ENEMY",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "ROLL IS 5 AND BECOME STRONGER",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "ALL FREEZE FURIOUS 2 TURN BAGGAGE ENEMY MAYBE FREEZE",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "BITING WITH COOL TUSK MAYBE FREEZED",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "WRAP STUNT ENEMY IN FEIRCE FIRES WANT TO BURN STATE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "CANT ESCAP BY GOAL IS INFEST FOR 45 LAPS",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "DEF STAND PROTECT THE ATTACK LOWED IS HARSH",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "KNOCK THE PROP CANNT BE USE",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SLARSHING SHARP A LEAVE AT KEY",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "YELL AT SKY PREVENT KEY FOR 5",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "USED IT FALLED BUT ELF HEAL NEXT",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "FLOAT BY SHOCK MAGNET 5",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "FLASHING POLISH SHOTTED FROM BODY AVOID HIT",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "MUD BODY TO SHOCK RESIST",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "POWER RAISED BY THINK FOR",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "USING FRUITS TO ATTACK",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "HIT SHIFTLY AND GHOS WHEN USED",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "FLURRY GRUESOME ABILITY OF ALL RISED",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "THREATS APART TO EXCHANGE AND LOW ATTACK MORAL",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "BLOW FLOWER VIOLENT AROUND",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "TO LATHER DO ITSELF AND SEEM THRUST POISON THERE",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "SCATTER TO CAUSE ENEMY TO EXPLODE IF F-STUNT",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "DIV HALF BY ADD MORAL AND ATTACK BY MENTAL",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "MENTAL TRICK THE FORC AND DEFEN",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "SPIRITUAL PROMOTION",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "TAKE FOR FALLED FRIENDLY POWERS IS RISIED",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "CUTE DRAG BODY REDUCIVES TO RISE SPEE",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "GROUP SING MAKE MORE DAMAGED",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "PUNCH FROM INVISIBLES NEVER MISS HITING",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "ATTACK BY POLYGONAL",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "BEARK THE SHELL TO LOWED DEFEND BUR RISED OTHER",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "PERFORATORUP AS SKY",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "6 TIME",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "MAKED FLOT STONE TO HURTED ENEMYTRAP",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "SHIFTLY ITEM TRICK HIT CONTINUE",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ATTACKED SMAE TYPE BY STRANGED WAVE",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "POWER IS GREATER THE BASE IS LESS",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "WHIRL WITH VACUUM PERFORATO TO FIRST",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "REQUIRE THE FLAME RISED POWER RAINBOW IN SKY",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "STRENGHT ATTACK HEAVERYDUTY ENEMY NO WORRY 25",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "WET WITH WATER",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "POWER DAMAGE BY HEALTH POINT",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "STRANGED PLACE BY MIND DEEND SP IS SWITCH",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SLAM ROBUSTNESS BODY TO ENEMY SERIOUS",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "THROW ANNOYING SEED TO MAKE WIRED",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "MAKE ENEMY BAD THEN SNORING NEXT",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "NOM STYL STUNT IS FLY STYL",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "ELF EXPLODE WHEN FALL",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "IGNORANT WEATHER",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "FORC RISE WHEN KEY IS HIT",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ELF FELLOW PROTECTION LIMITATION STUNT USE",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "FLOW ABLES IS BACKWARD",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "EN SNORING HEALTHITS LOWERED",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "FIREWALL STUNT IS MORE POWERE WHEN TIRED",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "STAT CANT DEBASE BY EN",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "ELF VERY ACCURASY",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "MAYBE S-WAVE BECAUSE HIT",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "MAYBE LOVELY WHEN TOUCH",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "EVIL STUNT IS MORE POWER",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "RAIN FALL FROM SKY",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "SUN FALL FROM SKY",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "HP LOWED BY HOT AND HEAL BY WATE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "AWAKED FASTLY",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "MAYBE NUMBED CANNT DO OR SNORING BY HIT",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "GENIE STUNT IS MORE POWER",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "TOUCH ELF MAYBE BURN",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "MORAL RISE WHEN BURN",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "ALL TEAM ELFS IS MORE POWER IN SUNNY",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "FELLOW LEAF ELF STAT CANNT LOWED",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "WEATHER GH-KISS",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "TELL EN MOVE WHAT HAVE",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "CAN SEE WHAT ITEM",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "PHYSIC STUNT DAMAGE SMALLERS",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "BIRD STUNT IS BETTER",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "EAT FRUIT FASTLY",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "SPEE WORK WHEN TOUCH",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "CAN EAT FRUITMORE",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "ELF FIND HONEY SOMEWHERE",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "STATUS DISAPER WHEN RAIN",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "HP RECOVERY BY GRAUP",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "ELF CANT TO BE POISONING",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "IGNORE SHELL BLOC RING",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "ELF DONT CANNT",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "SUN STOP STATUS",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "GRO STUNT NO EFFECTIVE",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "DRAW SHOCK STUNT",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "EN DRAIN STUNT HURT EN",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "FLOW AND WAVE MOVES IS MORE POWER",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "MORAL IS RISED WITH PRAS",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "RANDOM STAT CHANGE MANY",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "FULL HEALTHHY HALF DAMAGE",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "TYPE CHANGING BY SLATE",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "DAD AND BABY ATTACKING",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "STAT STUNT IS MORE IMPORTANT",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "EN PHYSIC POINTS IS USEMORE",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "EDGE PROTECTION",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "MAKE ATTACK WHEN BATTLE",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "EFFECT MORE APPEARING",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "SECOND EFFECTIVE STUNT IS MORE POWER BUT NO EFFECT",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "SHELL PROTECT KEY",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "STAT IS WILD CHANGELY",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "NOISY STUNT NO EFFECTIVE",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "MOVE RISED SLOW",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "ELF CHANGE FORME BY STUNT",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "MOVE RAISED BY FEARED",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "DRAW WAT STUNT",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "ELF IS DOUBLEQUICKER WHEN RAIN",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "MAYBE GIVE FELLOW THE PROP",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "WEAK STUNT IS MORE POWER",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "ONE RESULT IS MORE POWER",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "FELLOW ELF STUNT IS MORE HITTING",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "ONLY EFFECTIVE STUNT IS HITTING",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "MAYBE PROTECT FROM SERIOUS STATUS",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "XIAO CAOMEI WO DE BAOBEI",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "SHUOHUA KAI LI",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "WA DO SHITAI NODESU KA",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "NIIN VOIMME TOIMIA",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "IK WIL JE SNIPER GEWEER MET MUNITIE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "ANDA PENCURI LICIK MEMBERIKAN AMUNISI LAGI",  P_NONE,     1,   0, 300, CLR_GREEN),
SCROLL((char *)0,               "DE AZTAN A FEGYVER LOSZER NELKUL",  P_NONE,     1,   0, 300, CLR_BROWN),
SCROLL((char *)0,               "AHORA HE ENCONTRADO MUNICIONES",  P_NONE,     1,   0, 300, CLR_MAGENTA),
SCROLL((char *)0,               "AJMO TO UCINITI",  P_NONE,     1,   0, 300, CLR_CYAN),
SCROLL((char *)0,               "LONG YU DE LILIANG",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "NOUS DEVONS GAGNER NOTRE RACE",  P_NONE,     1,   0, 300, CLR_ORANGE),
SCROLL((char *)0,               "CEST UNE OCCASION UNIQUE DETRE LE PREMIER",  P_NONE,     1,   0, 300, CLR_BRIGHT_GREEN),
SCROLL((char *)0,               "CHE NON SONO IO",  P_NONE,     1,   0, 300, CLR_YELLOW),
SCROLL((char *)0,               "QUESTO DEVE ESSERE QUALCUN ALTRO",  P_NONE,     1,   0, 300, CLR_BRIGHT_BLUE),
SCROLL((char *)0,               "CHTO VY KHOTITE DOSTICH",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "NUVVEMI CESTUNNAVU",  P_NONE,     1,   0, 300, CLR_BRIGHT_CYAN),
SCROLL((char *)0,               "LAD OS GA TIL CITADELLET",  P_NONE,     1,   0, 300, CLR_WHITE),
SCROLL((char *)0,               "VARFOR PRATAR DU SA OM MIN FLICKVAN",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "NIE MOGE DLUZEJ TRZYMAC WKROTCE",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "SEE YA CUNT",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "BYE BITCH",  P_NONE,     1,   0, 300, CLR_BRIGHT_MAGENTA),
SCROLL((char *)0,               "THIS SLING IS RETARDED",  P_NONE,     1,   0, 300, CLR_GRAY),
SCROLL((char *)0,               "I WILL FUCK YOU UP YOU FUCKING FUCKTARD",  P_NONE,     1,   0, 300, CLR_BLACK),
SCROLL((char *)0,               "RTFM",  P_NONE,     1,   0, 300, CLR_RED),
SCROLL((char *)0,               "KLAATU BARADA NIKTO",  P_NONE,     1,   0, 300, CLR_GREEN),



#ifdef MAIL
SCROLL("mail",                  "stamped",              P_NONE, 0,   0,   0, CLR_BRIGHT_BLUE),
#endif
SCROLL("blank paper",           "unlabeled",            P_NONE, 0, 140, 300, CLR_GRAY),
#undef SCROLL

/* spell books ... */
#define SPELL(name,desc,sub,prob,delay,level,mgc,dir,color) OBJECT( \
		OBJ(name,desc), BITS(0,0,1,0,mgc,1,0,0,0,0,dir,sub,PAPER), 0, \
		SPBOOK_CLASS, prob, delay, \
		0, level*100, 0, 0, 0, level, 20, color )
/* Attack spells */
SPELL("force bolt",      "red",         P_ATTACK_SPELL, 120,  2, 1, 1, IMMEDIATE, CLR_RED),
SPELL("create monster",  "turquoise",   P_ATTACK_SPELL, 100,  3, 2, 1, NODIR,     CLR_BRIGHT_CYAN),
SPELL("drain life",      "velvet",      P_ATTACK_SPELL, 50,  4, 3, 1, IMMEDIATE, CLR_MAGENTA),
  /* NEEDS TILE */ /* WAC -- probs from force bolt and extra healing */
SPELL("command undead",  "dark",        P_ATTACK_SPELL, 50,  7, 5, 1, IMMEDIATE, CLR_BLACK),
SPELL("summon undead",   "black",       P_ATTACK_SPELL, 50,  7, 5, 1, IMMEDIATE, CLR_BLACK),

SPELL("disintegration",      "solid",      P_ATTACK_SPELL, 5,  30, 8, 1, IMMEDIATE, CLR_BLACK),

/* Healing spells */
SPELL("stone to flesh",	 "thick",       P_HEALING_SPELL, 70,  1, 3, 1, IMMEDIATE, HI_PAPER),
SPELL("healing",         "white",       P_HEALING_SPELL, 125,  2, 1, 1, IMMEDIATE, CLR_WHITE),
SPELL("cure blindness",  "yellow",      P_HEALING_SPELL, 90,  2, 2, 1, IMMEDIATE, CLR_YELLOW),
SPELL("cure numbness",  "opaque",      P_HEALING_SPELL, 5,  2, 2, 1, IMMEDIATE, CLR_BROWN),
SPELL("blind self", 	 "irritating",  P_HEALING_SPELL, 5,  2, 2, 1, IMMEDIATE, CLR_YELLOW),
SPELL("cure sickness",   "indigo",      P_HEALING_SPELL, 100,  3, 3, 1, NODIR,     CLR_BRIGHT_BLUE),
SPELL("cure hallucination", "glowing",  P_HEALING_SPELL, 70,  3, 3, 1, NODIR,     CLR_YELLOW),
SPELL("cure confusion",   "moldy",      P_HEALING_SPELL, 70,  3, 3, 1, NODIR,     CLR_BROWN),
SPELL("cure burn",   "fiery",           P_HEALING_SPELL, 5,  3, 3, 1, NODIR,     CLR_RED),
SPELL("confuse self",   "many-paged",   P_HEALING_SPELL, 5,  3, 3, 1, NODIR,     CLR_BROWN),
SPELL("cure stun",   "fat",      	    P_HEALING_SPELL, 70,  3, 3, 1, NODIR,     CLR_BRIGHT_MAGENTA),
SPELL("stun self",   "trembling",	    P_HEALING_SPELL, 5,  3, 3, 1, NODIR,     CLR_BRIGHT_MAGENTA),
SPELL("extra healing",   "plaid",       P_HEALING_SPELL, 70,  5, 3, 1, IMMEDIATE, CLR_GREEN),
SPELL("full healing",   "heretical",       P_HEALING_SPELL, 25,  8, 6, 1, IMMEDIATE, CLR_BRIGHT_MAGENTA),
SPELL("restore ability", "light brown", P_HEALING_SPELL, 75,  5, 4, 1, NODIR,     CLR_BROWN),
SPELL("banishing fear", "fearsome", P_HEALING_SPELL,  5,  5, 4, 1, NODIR,     CLR_BRIGHT_MAGENTA),
SPELL("cure freeze", "snowy", P_HEALING_SPELL,  5,  5, 4, 1, NODIR,     CLR_BRIGHT_CYAN),
SPELL("create familiar", "glittering",  P_HEALING_SPELL, 50,  7, 6, 1, NODIR,     CLR_WHITE),
/* Divination spells */
SPELL("light",           "cloth",       P_DIVINATION_SPELL, 65,  1, 1, 1, NODIR,     HI_CLOTH),
SPELL("darkness",           "colluded",       P_DIVINATION_SPELL, 5,  1, 1, 1, NODIR,     HI_CLOTH),
SPELL("detect monsters", "leather",     P_DIVINATION_SPELL, 75,  5, 4, 1, NODIR,     HI_LEATHER),
SPELL("detect food",     "cyan",        P_DIVINATION_SPELL, 15,  3, 2, 1, NODIR,     CLR_CYAN),
SPELL("dissolve food",     "hungry",        P_DIVINATION_SPELL, 5,  3, 2, 1, NODIR,     CLR_CYAN),
SPELL("detect armor enchantment",     "armored",        P_DIVINATION_SPELL, 5,  3, 2, 1, NODIR,     CLR_CYAN),
SPELL("clairvoyance",    "dark blue",   P_DIVINATION_SPELL, 75,  3, 3, 1, NODIR,     CLR_BRIGHT_BLUE),
SPELL("detect unseen",   "violet",      P_DIVINATION_SPELL, 75,  4, 3, 1, NODIR,     CLR_MAGENTA),
SPELL("identify",        "bronze",      P_DIVINATION_SPELL, 150,  8, 5, 1, NODIR,     HI_COPPER),
SPELL("detect treasure", "gray",        P_DIVINATION_SPELL, 75,  5, 4, 1, NODIR,     CLR_GRAY),
SPELL("magic mapping",   "dusty",       P_DIVINATION_SPELL, 75,  7, 5, 1, NODIR,     HI_PAPER),
SPELL("entrapping",    "scintillating", P_DIVINATION_SPELL, 25,  7, 6, 1, NODIR,     CLR_BRIGHT_MAGENTA),
SPELL("finger",		 "old",	    P_DIVINATION_SPELL,	25,  3, 2, 1, IMMEDIATE, HI_PAPER),
SPELL("chemistry",	 "brand-new",   P_DIVINATION_SPELL,	50, 10, 1, 1, NODIR,     HI_PAPER),
SPELL("detect foot",	 "stinking",  P_DIVINATION_SPELL,	25,  2, 7, 1, NODIR, CLR_GREEN),
SPELL("forbidden knowledge",	 "uninscribed",  P_DIVINATION_SPELL,	5,  1, 7, 1, NODIR, CLR_WHITE),
/* Enchantment spells */
SPELL("confuse monster", "orange",      P_ENCHANTMENT_SPELL, 45,  2, 2, 1, IMMEDIATE, CLR_ORANGE),
SPELL("slow monster",    "light green", P_ENCHANTMENT_SPELL, 125,  2, 2, 1, IMMEDIATE, CLR_BRIGHT_GREEN),
SPELL("cause fear",      "light blue",  P_ENCHANTMENT_SPELL, 50,  3, 3, 1, NODIR,     CLR_BRIGHT_BLUE),
SPELL("charm monster",   "magenta",     P_ENCHANTMENT_SPELL, 50,  3, 3, 1, IMMEDIATE, CLR_MAGENTA),
SPELL("enchant weapon",  "dull",        P_ENCHANTMENT_SPELL, 75,  8, 7, 1, NODIR,     CLR_WHITE),
SPELL("enchant armor",   "thin",        P_ENCHANTMENT_SPELL, 75,  8, 7, 1, NODIR,     CLR_WHITE),
SPELL("charging",   "stellar",          P_ENCHANTMENT_SPELL, 25,   8, 7, 1, NODIR,     CLR_WHITE),
SPELL("genocide",   "extraordinary",    P_ENCHANTMENT_SPELL, 5,   16, 8, 1, NODIR,     CLR_WHITE),
/* Protection spells */
SPELL("protection",      "wide",        P_PROTECTION_SPELL,  25,  3, 1, 1, NODIR,     HI_PAPER),
SPELL("resist poison",   "big",         P_PROTECTION_SPELL, 50,  2, 1, 1, NODIR,     CLR_GRAY),
SPELL("resist sleep",    "fuzzy",       P_PROTECTION_SPELL, 75,  2, 1, 1, NODIR,     CLR_BROWN),
SPELL("endure cold",     "deep",        P_PROTECTION_SPELL, 50,  3, 2, 1, NODIR,     HI_PAPER),
SPELL("endure heat",     "spotted",     P_PROTECTION_SPELL, 50,  3, 2, 1, NODIR,     HI_PAPER),
SPELL("insulate",        "long",        P_PROTECTION_SPELL, 50,  3, 2, 1, NODIR,     HI_PAPER),
SPELL("remove curse",    "wrinkled",    P_PROTECTION_SPELL, 120,  5, 5, 1, NODIR,     HI_PAPER),
SPELL("remove blessing",    "light cyan",    P_PROTECTION_SPELL, 5,  5, 5, 1, NODIR,     CLR_BRIGHT_CYAN),
SPELL("turn undead",     "copper",      P_PROTECTION_SPELL, 75,  8, 6, 1, IMMEDIATE, HI_COPPER),
SPELL("anti disintegration",        "doorstopping",        P_PROTECTION_SPELL, 25,  6, 6, 1, NODIR,     CLR_GREEN),
SPELL("botox resist",        "leafy",   P_PROTECTION_SPELL, 25,  6, 6, 1, NODIR,     CLR_BRIGHT_GREEN),
SPELL("acidshield",        "acidic",   P_PROTECTION_SPELL, 25,  6, 6, 1, NODIR,     CLR_BRIGHT_GREEN),
SPELL("godmode",        "heavenly",   P_PROTECTION_SPELL, 25,  10, 8, 1, NODIR,     CLR_BRIGHT_CYAN),
SPELL("resist petrification",        "rocky",   P_PROTECTION_SPELL, 25,  8, 7, 1, NODIR,     CLR_GRAY),
/* Body spells */
SPELL("jumping",         "torn",        P_BODY_SPELL, 70,  3, 1, 1, IMMEDIATE, HI_PAPER),
SPELL("haste self",      "purple",      P_BODY_SPELL, 25,  4, 3, 1, NODIR,     CLR_MAGENTA),
SPELL("enlighten",       "faded",       P_BODY_SPELL, 75,  5, 4, 1, NODIR,     CLR_GRAY),
SPELL("invisibility",    "dark brown",  P_BODY_SPELL, 45,  5, 4, 1, NODIR,     CLR_BROWN),
SPELL("aggravate monster",    "grating",  P_BODY_SPELL, 5,  5, 4, 1, NODIR,     CLR_BROWN),
SPELL("levitation",      "tan",         P_BODY_SPELL, 75,  4, 4, 1, NODIR,     CLR_BROWN),
SPELL("teleport away",   "gold",        P_BODY_SPELL, 75,  6, 6, 1, IMMEDIATE, HI_GOLD),
SPELL("passwall",        "ochre",       P_BODY_SPELL, 25,  7, 6, 1, NODIR,     CLR_YELLOW),
SPELL("polymorph",       "silver",      P_BODY_SPELL, 75,  8, 6, 1, IMMEDIATE, HI_SILVER),
SPELL("levelport",       "unavailable", P_BODY_SPELL,  5,  24, 8, 1, NODIR,    CLR_WHITE),
/* Matter spells */
SPELL("knock",           "pink",        P_MATTER_SPELL, 120,  1, 1, 1, IMMEDIATE, CLR_BRIGHT_MAGENTA),
SPELL("flame sphere",    "canvas",      P_MATTER_SPELL, 100,  2, 1, 1, NODIR, CLR_BROWN),
SPELL("freeze sphere",   "hardcover",   P_MATTER_SPELL, 100,  2, 1, 1, NODIR, CLR_BROWN),
SPELL("shocking sphere", "insulated",   P_MATTER_SPELL, 25,   2, 1, 1, NODIR, CLR_YELLOW),
SPELL("acid sphere", "corroded",   P_MATTER_SPELL, 25,   2, 1, 1, NODIR, CLR_YELLOW),
SPELL("wizard lock",     "dark green",  P_MATTER_SPELL, 120,  3, 2, 1, IMMEDIATE, CLR_GREEN),
SPELL("dig",             "parchment",   P_MATTER_SPELL, 100,  6, 5, 1, RAY,       HI_PAPER),
SPELL("cancellation",    "shining",     P_MATTER_SPELL, 25,  8, 7, 1, IMMEDIATE, CLR_WHITE),
SPELL("reflection",	 "withered",    P_MATTER_SPELL, 25,  7, 6, 1, IMMEDIATE, CLR_BROWN),
SPELL("paralysis",	 "shivering",   P_MATTER_SPELL,  5,  7, 6, 1, IMMEDIATE, CLR_MAGENTA),
SPELL("repair armor",	 "pergament",   P_MATTER_SPELL, 20,  6, 3, 1, IMMEDIATE, HI_PAPER),
SPELL("corrode metal",	 "metal-colored",   P_MATTER_SPELL, 5,  6, 3, 1, IMMEDIATE, HI_PAPER),
SPELL("petrify",    "petrified",     P_MATTER_SPELL, 5,  40, 8, 1, IMMEDIATE, CLR_BLACK),

/* Ray type spells are all here.  Kludge for zap.c */
SPELL("magic missile",   "vellum",      P_ATTACK_SPELL, 200,  4, 3, 1, RAY,       HI_PAPER),
SPELL("fireball",        "ragged",      P_MATTER_SPELL, 75,  6, 4, 1, RAY,       HI_PAPER),
SPELL("cone of cold",    "dog eared",   P_MATTER_SPELL, 75,  8, 5, 1, RAY,       HI_PAPER),
SPELL("sleep",           "mottled",     P_ENCHANTMENT_SPELL, 175,  3, 2, 1, RAY,  HI_PAPER),
SPELL("finger of death", "stained",     P_ATTACK_SPELL, 25, 10, 7, 1, RAY,       HI_PAPER),
SPELL("lightning",       "rainbow",     P_MATTER_SPELL, 50,  7, 4, 1, RAY,       HI_PAPER),
SPELL("poison blast",    "tattered",    P_ATTACK_SPELL, 50,  7, 4, 1, RAY,       HI_PAPER),
SPELL("acid stream",     "colorful",    P_MATTER_SPELL, 50,  7, 4, 1, RAY,       HI_PAPER),
SPELL("solar beam",     "mirroring",    P_MATTER_SPELL, 25,  10, 6, 1, RAY,       CLR_BRIGHT_CYAN),
/* Description placeholders and special spellbooks */
SPELL((char *)0,		 "tartan",      P_NONE,  0,  0, 0, 1, 0,         CLR_RED),
SPELL((char *)0,		 "stylish",     P_NONE,  0,  0, 0, 1, 0,         HI_PAPER),
SPELL((char *)0,		 "psychedelic", P_NONE,  0,  0, 0, 1, 0,         CLR_BRIGHT_MAGENTA),
SPELL((char *)0,		 "spiral-bound",P_NONE,  0,  0, 0, 1, 0,         HI_PAPER),
SPELL((char *)0,		 "left-handed", P_NONE,  0,  0, 0, 1, 0,         HI_PAPER),
SPELL((char *)0,		 "stapled",     P_NONE,  0,  0, 0, 1, 0,         HI_PAPER),
SPELL((char *)0,		 "ancient",     P_NONE,  0,  0, 0, 1, 0,         CLR_BRIGHT_GREEN),
SPELL((char *)0,         "chartreuse",  P_NONE, 0, 0, 0, 1, 0, CLR_GREEN),
SPELL((char *)0,         "decrepit",    P_NONE, 0, 0, 0, 1, 0, CLR_BROWN),
SPELL((char *)0,         "paperback",   P_NONE, 0, 0, 0, 1, 0, HI_PAPER),
SPELL((char *)0,         "crimson",     P_NONE, 0, 0, 0, 1, 0, CLR_RED),
SPELL((char *)0,         "charcoal",    P_NONE, 0, 0, 0, 1, 0, CLR_BLACK),
SPELL((char *)0,         "cryptic",    P_NONE, 0, 0, 0, 1, 0, CLR_BLACK),
SPELL((char *)0,         "encrypted",    P_NONE, 0, 0, 0, 1, 0, CLR_BLACK),
SPELL("blank paper",	 "plain",		P_NONE, 75,  0, 0, 0, 0,         HI_PAPER),
	/* ...Blank spellbook must come last because it retains its description */
OBJECT(OBJ("Book of the Dead", "papyrus"),
	BITS(0,0,1,0,1,0,1,1,0,0,0,0,PAPER), 0,
	SPBOOK_CLASS, 0, 0,20, 10000, 0, 0, 0, 7, 20, HI_PAPER),
	/* ...A special, one of a kind, spellbook */
#undef SPELL

/* wands ... */
#define WAND(name,typ,prob,cost,mgc,dir,metal,color) OBJECT( \
		OBJ(name,typ), BITS(0,0,1,0,mgc,1,0,0,0,0,dir,0,metal), 0, \
		WAND_CLASS, prob, 0, 0, cost, 0, 0, 0, 0, 30, color )
WAND("light",          "glass",    170, 500, 1, NODIR,     GLASS,    HI_GLASS),
WAND("nothing",        "oak",      25, 500, 0, IMMEDIATE, WOOD,     HI_WOOD),
WAND("enlightenment",  "crystal",  150, 500, 1, NODIR,     GLASS,    HI_GLASS),
WAND("healing",        "bamboo",   250, 500, 1, IMMEDIATE, WOOD,     CLR_YELLOW),
WAND("locking",        "aluminum", 125, 500, 1, IMMEDIATE, METAL,    HI_METAL),
WAND("make invisible", "marble",   100, 500, 1, IMMEDIATE, MINERAL,  HI_MINERAL),
WAND("make visible", "interplanar",   25, 500, 1, IMMEDIATE, IRON,  CLR_YELLOW),
WAND("identify",       "wedged",   25, 500, 1, NODIR,     WOOD,     CLR_BRIGHT_GREEN),
WAND("remove curse",   "wiry",     25, 500, 1, NODIR,     METAL,    CLR_GRAY),
WAND("punishment",     "edgy",     25, 500, 1, NODIR,     PAPER,    CLR_WHITE),
WAND("opening",        "zinc",     120, 500, 1, IMMEDIATE, METAL,    HI_METAL),
WAND("probing",        "uranium",  100, 500, 1, IMMEDIATE, METAL,    HI_METAL),
WAND("secret door detection", "balsa",
                                   75, 500, 1, NODIR,     WOOD,     HI_WOOD),
WAND("trap disarming", "elysium",
                                   25, 500, 1, NODIR,     GOLD,     CLR_YELLOW),
WAND("entrapping",   "blasted", 25, 500, 1, NODIR,     MITHRIL,  CLR_BRIGHT_MAGENTA),
WAND("trap creation",   "weird", 25, 500, 1, NODIR,     BONE,  CLR_WHITE),
WAND("darkness",   "obscure", 25, 500, 1, NODIR,     SILVER,  CLR_BLACK),
WAND("magic mapping",   "shapeless", 25, 500, 1, NODIR,     DRAGON_HIDE,  CLR_BRIGHT_GREEN),
WAND("detect monsters", "exploding", 25, 500, 1, NODIR,     WOOD,     CLR_GREEN),
WAND("objection", "cinnabar", 25, 500, 1, NODIR,     SILVER,   CLR_ORANGE),
WAND("slow monster",   "tin",     225, 500, 1, IMMEDIATE, METAL,    HI_METAL),
WAND("speed monster",  "brass",   170, 500, 1, IMMEDIATE, COPPER,   HI_COPPER),
WAND("haste monster",  "royal",    25, 500, 1, IMMEDIATE, GOLD,   CLR_ORANGE),
WAND("striking",       "ebony",   290, 500, 1, IMMEDIATE, WOOD,     HI_WOOD),
WAND("paralysis",       "automatic",   5, 500, 1, IMMEDIATE, MINERAL,     CLR_BRIGHT_CYAN),
WAND("disintegration",  "stable",   5, 500, 1, IMMEDIATE, DRAGON_HIDE,     CLR_BLACK),
WAND("stoning", "petrified",     5, 500, 1, IMMEDIATE,     MINERAL,     CLR_GRAY),
WAND("undead turning", "copper",  225, 500, 1, IMMEDIATE, COPPER,   HI_COPPER),
WAND("draining",       "ceramic", 120, 500, 1, IMMEDIATE, MINERAL,  HI_MINERAL),
		/* KMH -- 15/1000 probability from light */
WAND("cancellation",   "platinum", 175, 500, 1, IMMEDIATE, PLATINUM, CLR_WHITE),
WAND("create monster", "maple",    125, 500, 1, NODIR,     WOOD,     HI_WOOD),
WAND("bad effect", "pebble",     25, 500, 1, NODIR,     MINERAL,     CLR_ORANGE),
WAND("curse items", "fake",     5, 500, 1, NODIR,     WAX,     CLR_MAGENTA),
WAND("amnesia", "acrylic",     5, 500, 1, NODIR,     VEGGY,     CLR_GREEN),
WAND("bad luck", "acyclic",     5, 500, 1, NODIR,     PLASTIC,     CLR_BLACK),
WAND("remove resistance", "cyclic",     5, 500, 1, NODIR,     SILVER,     HI_SILVER),
WAND("corrosion", "heavy metal",     5, 500, 1, NODIR,     METAL,     CLR_RED),
WAND("fumbling", "trippy",     5, 500, 1, NODIR,     WOOD,     CLR_BRIGHT_GREEN),
WAND("starvation", "underestimated",     5, 500, 1, NODIR,     PAPER,     CLR_BROWN),
WAND("summon undead", "shining",     25, 500, 1, NODIR,     GEMSTONE,     CLR_YELLOW),
WAND("fear",           "rusty",    100, 500, 1, IMMEDIATE, IRON,     CLR_RED),
WAND("wind",           "timber",     25, 500, 1, IMMEDIATE, WOOD,     CLR_BROWN),
WAND("polymorph",      "silver",   205, 500, 1, IMMEDIATE, SILVER,   HI_SILVER),
WAND("teleportation",  "iridium",  225, 500, 1, IMMEDIATE, METAL,    CLR_BRIGHT_CYAN),
WAND("banishment",  "cocky",   25, 500, 1, IMMEDIATE, METAL,    CLR_BRIGHT_GREEN),
WAND("create horde",   "black",     25, 500, 1, NODIR,     PLASTIC,  CLR_BLACK),
WAND("extra healing",  "bronze",   150, 500, 1, IMMEDIATE, COPPER,   CLR_YELLOW),
WAND("full healing",   "hawthorn",  25, 500, 1, IMMEDIATE, LEATHER,  CLR_BROWN),
WAND("wonder",	"elven-lettered", 25, 500, 1, NODIR,     IRON,	 HI_METAL),
WAND("bugging",	"wooden",		25, 500, 1, NODIR,     WOOD,	 HI_METAL),
WAND("wishing",        "pine",      25, 500, 1, NODIR,     WOOD,     HI_WOOD),
WAND("acquirement",   "important",  25, 500, 1, NODIR,     SILVER,     CLR_CYAN),
WAND("clone monster",  "radiating", 25, 500, 1, IMMEDIATE, GOLD,    CLR_BRIGHT_GREEN),
WAND("charging", "buzzing",     25, 500, 1, NODIR,     METAL,     CLR_BRIGHT_CYAN),
/* Ray wands have to come last, and in this order. */
/* This is extremely kludgy, but that's what zap.c expects. */
WAND("digging",        "iron",    250, 500, 1, RAY,       IRON,     HI_METAL),
WAND("magic missile",  "steel",   250, 500, 1, RAY,       IRON,     HI_METAL),
WAND("fire",           "hexagonal",125, 500, 1, RAY,       IRON,     HI_METAL),
WAND("cold",           "short",    150, 500, 1, RAY,       IRON,     HI_METAL),
WAND("sleep",          "runed",    250, 500, 1, RAY,       IRON,     HI_METAL),
WAND("death",          "long",      25, 500, 1, RAY,       IRON,     HI_METAL),
WAND("lightning",      "curved",   100, 500, 1, RAY,       IRON,     HI_METAL),
WAND("fireball",       "octagonal", 25, 500, 1, RAY,       IRON,     HI_METAL),
WAND("acid",		"measured",	25, 500, 1, RAY,       METAL,	 HI_METAL),
WAND("solar beam",	"beaming",	25, 500, 1, RAY,       METAL,	 CLR_BRIGHT_CYAN),
WAND((char *)0,        "forked",    0, 500, 1, 0,         WOOD,     HI_WOOD),
WAND((char *)0,        "spiked",    0, 500, 1, 0,         IRON,     HI_METAL),
WAND((char *)0,        "jeweled",   0, 500, 1, 0,         IRON,     HI_MINERAL),
WAND((char *)0,        "porcelain", 0, 500, 1, 0,         GLASS,    HI_MINERAL),
WAND((char *)0,        "quartz",    0, 500, 1, 0,         GLASS,    HI_GLASS),
WAND((char *)0,        "metal",    0, 500, 1, 0,         COPPER,   HI_COPPER),
WAND((char *)0,        "decayed",     0, 500, 1, 0,         IRON,     CLR_RED),
WAND((char *)0,        "dodecagonal", 0, 500, 1, 0,         IRON,     HI_METAL),
WAND((char *)0,        "stoutwood",    0, 500, 1, 0,         WOOD,     CLR_YELLOW),
WAND((char *)0,        "walnut",    0, 500, 1, 0,         WOOD,     HI_WOOD),
WAND((char *)0,        "mahogany",  0, 500, 1, 0,         WOOD,     HI_WOOD),
WAND((char *)0,        "cedar",     0, 500, 1, 0,         WOOD,     HI_WOOD),
WAND((char *)0,        "chrome",    0, 500, 1, 0,         METAL,    HI_SILVER),
WAND((char *)0,        "titanium",  0, 500, 1, 0,         METAL,    HI_METAL),
WAND((char *)0,        "nickel",    0, 500, 1, 0,         METAL,    HI_METAL),
WAND((char *)0,        "mithril",   0, 500, 1, 0,         MITHRIL,  HI_SILVER),
WAND((char *)0,        "grooved",   0, 500, 1, 0,         WOOD,     HI_WOOD),
WAND((char *)0,        "bent",      0, 500, 1, 0,         METAL,    CLR_BRIGHT_GREEN),
WAND((char *)0,        "plastic",   0, 500, 1, 0,         PLASTIC,  CLR_BRIGHT_GREEN),
WAND((char *)0,        "bone",      0, 500, 1, 0,         BONE,     CLR_WHITE),
WAND((char *)0,        "alabaster", 0, 500, 1, 0,         MINERAL,  CLR_BROWN),
WAND((char *)0,        "orichalcum",0, 500, 1, 0,         METAL,    HI_METAL),
WAND((char *)0,        "electrum",  0, 500, 1, 0,         METAL,    HI_GOLD),
WAND((char *)0,        "conundrum",0, 500, 1, 0,         METAL,    CLR_BRIGHT_GREEN),
WAND((char *)0,        "lavender",0, 500, 1, 0,         METAL,    CLR_BRIGHT_MAGENTA),
WAND((char *)0,        "viridian",0, 500, 1, 0,         METAL,    CLR_GREEN),
WAND((char *)0,        "cerulean",0, 500, 1, 0,         METAL,    CLR_BRIGHT_BLUE),
WAND((char *)0,        "saffron",0, 500, 1, 0,         METAL,    CLR_ORANGE),
WAND((char *)0,        "fuchsia",0, 500, 1, 0,         METAL,    CLR_RED),
WAND((char *)0,        "pallet",0, 500, 1, 0,         METAL,    CLR_MAGENTA),
WAND((char *)0,        "cyan",0, 500, 1, 0,         METAL,    CLR_CYAN),
WAND((char *)0,        "rusting",0, 500, 1, 0,         METAL,    CLR_GRAY),
WAND((char *)0,        "ominous",0, 500, 1, 0,         METAL,    CLR_BLACK),
WAND((char *)0,        "golden",0, 500, 1, 0,         METAL,    CLR_YELLOW),
WAND((char *)0,        "iridescent",0, 500, 1, 0,         METAL,    CLR_BRIGHT_CYAN),
WAND((char *)0,        "tetragonal", 0, 500, 1, 0,         IRON,     CLR_BRIGHT_GREEN),
WAND((char *)0,        "trigonal",0, 500, 1, 0,         METAL,    CLR_BRIGHT_MAGENTA),
WAND((char *)0,        "cubic",0, 500, 1, 0,         METAL,    CLR_RED),
WAND((char *)0,        "orthorhombic",0, 500, 1, 0,         METAL,    CLR_BRIGHT_MAGENTA),
WAND((char *)0,        "skew",0, 500, 1, 0,         METAL,    CLR_BLACK),
WAND((char *)0,        "oblique",0, 500, 1, 0,         METAL,    CLR_BRIGHT_CYAN),
WAND((char *)0,        "monoclinic",0, 500, 1, 0,         METAL,    CLR_ORANGE),
WAND((char *)0,        "triclinic",0, 500, 1, 0,         METAL,    CLR_YELLOW),
WAND((char *)0,        "angular",0, 500, 1, 0,         METAL,    CLR_YELLOW),
WAND((char *)0,        "pentagonal",0, 500, 1, 0,         METAL,    CLR_ORANGE),
WAND((char *)0,        "circular",0, 500, 1, 0,         METAL,    CLR_BRIGHT_GREEN),
WAND((char *)0,        "round",0, 500, 1, 0,         METAL,    CLR_BLACK),
WAND((char *)0,        "shaped",0, 500, 1, 0,         METAL,    CLR_BRIGHT_MAGENTA),
WAND((char *)0,        "deformed",0, 500, 1, 0,         METAL,    CLR_GRAY),
WAND((char *)0,        "teaching",0, 500, 1, 0,         WOOD,    CLR_RED),
WAND((char *)0,        "archmage",0, 500, 1, 0,         MITHRIL,    CLR_BRIGHT_CYAN),
WAND((char *)0,        "avocadowood",0, 500, 1, 0,         WOOD,    CLR_GREEN),
WAND((char *)0,        "banyan",0, 500, 1, 0,         WOOD,    CLR_RED),
WAND((char *)0,        "birch",0, 500, 1, 0,         WOOD,    CLR_YELLOW),
WAND((char *)0,        "cherry",0, 500, 1, 0,         WOOD,    CLR_ORANGE),
WAND((char *)0,        "cypress",0, 500, 1, 0,         WOOD,    CLR_YELLOW),
WAND((char *)0,        "dogwood",0, 500, 1, 0,         WOOD,    CLR_WHITE),
WAND((char *)0,        "driftwood",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "elm",0, 500, 1, 0,         WOOD,    CLR_GREEN),
WAND((char *)0,        "eucalyptus",0, 500, 1, 0,         WOOD,    CLR_BRIGHT_GREEN),
WAND((char *)0,        "fall",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "hemlock",0, 500, 1, 0,         WOOD,    CLR_RED),
WAND((char *)0,        "holly",0, 500, 1, 0,         WOOD,    CLR_BRIGHT_MAGENTA),
WAND((char *)0,        "ironwood",0, 500, 1, 0,         WOOD,    CLR_CYAN),
WAND((char *)0,        "kukui wood",0, 500, 1, 0,         WOOD,    CLR_BLACK),
WAND((char *)0,        "manzanita",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "persimmon wood",0, 500, 1, 0,         WOOD,    CLR_GREEN),
WAND((char *)0,        "pecan",0, 500, 1, 0,         WOOD,    CLR_YELLOW),
WAND((char *)0,        "wintry",0, 500, 1, 0,         WOOD,    CLR_BRIGHT_CYAN),
WAND((char *)0,        "poplar",0, 500, 1, 0,         WOOD,    CLR_WHITE),
WAND((char *)0,        "willow",0, 500, 1, 0,         WOOD,    CLR_WHITE),
WAND((char *)0,        "redwood",0, 500, 1, 0,         WOOD,    CLR_RED),
WAND((char *)0,        "rosewood",0, 500, 1, 0,         WOOD,    CLR_MAGENTA),
WAND((char *)0,        "spruce",0, 500, 1, 0,         WOOD,    CLR_GREEN),
WAND((char *)0,        "teak",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "zebrawood",0, 500, 1, 0,         WOOD,    CLR_BLACK),
WAND((char *)0,        "beryllium",0, 500, 1, 0,         METAL,    CLR_BRIGHT_GREEN),
WAND((char *)0,        "lead",0, 500, 1, 0,         PLATINUM,    CLR_GRAY),
WAND((char *)0,        "magnesium",0, 500, 1, 0,         MINERAL,    CLR_WHITE),
WAND((char *)0,        "mercury",0, 500, 1, 0,         COPPER,    CLR_GRAY),
WAND((char *)0,        "pewter",0, 500, 1, 0,         IRON,    CLR_GRAY),
WAND((char *)0,        "silicon",0, 500, 1, 0,         MINERAL,    CLR_WHITE),
WAND((char *)0,        "titanium",0, 500, 1, 0,         METAL,    CLR_ORANGE),
WAND((char *)0,        "tungsten",0, 500, 1, 0,         METAL,    CLR_BLACK),
WAND((char *)0,        "aspen",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "cottonwood",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "locust",0, 500, 1, 0,         VEGGY,    CLR_BROWN),
WAND((char *)0,        "mistletoe",0, 500, 1, 0,         WOOD,    CLR_GREEN),
WAND((char *)0,        "mulberry",0, 500, 1, 0,         WOOD,    CLR_RED),
WAND((char *)0,        "sycamore",0, 500, 1, 0,         WOOD,    CLR_BROWN),
WAND((char *)0,        "hickory",0, 500, 1, 0,         WOOD,    CLR_BLACK),
WAND((char *)0,        "cast iron",0, 500, 1, 0,         IRON,    CLR_CYAN),
WAND((char *)0,        "molybdenum",0, 500, 1, 0,         METAL,    CLR_GRAY),
WAND((char *)0,        "planar",0, 500, 1, 0,         IRON,    CLR_WHITE),

#undef WAND

/* coins ... - so far, gold is all there is */
#define COIN(name,prob,metal,worth) OBJECT( \
		OBJ(name,(char *)0), BITS(0,1,0,0,0,0,0,0,0,0,0,P_NONE,metal), 0, \
		COIN_CLASS, prob, 0, 1, worth, 0, 0, 0, 0, 0, HI_GOLD )
	COIN("gold piece",      5000, GOLD,1),
#undef COIN

/* gems ... - includes stones and rocks but not boulders */
#define GEM(name,desc,prob,wt,gval,nutr,mohs,glass,color) OBJECT( \
	    OBJ(name,desc), \
	    BITS(0,1,0,0,0,0,0,0,0,HARDGEM(mohs),0,-P_SLING,glass), 0, \
	    GEM_CLASS, prob, 0, 1, gval, 12, 12, 0, 0, nutr, color )
#define ROCK(name,desc,kn,prob,wt,gval,sdam,ldam,mgc,nutr,mohs,glass,color) OBJECT( \
	    OBJ(name,desc), \
	    BITS(kn,1,0,0,mgc,0,0,0,0,HARDGEM(mohs),0,-P_SLING,glass), 0, \
	    GEM_CLASS, prob, 0, wt, gval, sdam, ldam, 0, 0, nutr, color )
GEM("dilithium crystal", "white",      1,  0, 4500, 15,  5, GEMSTONE, CLR_WHITE),
GEM("diamond", "white",                2,  0, 4000, 15, 10, GEMSTONE, CLR_WHITE),
GEM("ruby", "red",                     3,  0, 3500, 15,  9, GEMSTONE, CLR_RED),
GEM("jacinth", "orange",               3,  0, 3250, 15,  9, GEMSTONE, CLR_ORANGE),
GEM("sapphire", "blue",                3,  0, 3000, 15,  9, GEMSTONE, CLR_BRIGHT_BLUE),
GEM("black opal", "black",             4,  0, 2500, 15,  8, GEMSTONE, CLR_BLACK),
GEM("emerald", "green",                4,  0, 2500, 15,  8, GEMSTONE, CLR_GREEN),
GEM("turquoise", "green",              4,  0, 2000, 15,  6, GEMSTONE, CLR_GREEN),
GEM("citrine", "yellow",               5,  0, 1500, 15,  6, GEMSTONE, CLR_YELLOW),
GEM("aquamarine", "green",             5,  0, 1500, 15,  8, GEMSTONE, CLR_GREEN),
GEM("amber", "yellowish brown",        5,  0, 1000, 15,  2, GEMSTONE, CLR_BROWN),
GEM("topaz", "yellowish brown",        6,  0,  900, 15,  8, GEMSTONE, CLR_BROWN),
GEM("jet", "black",                    6,  0,  850, 15,  7, GEMSTONE, CLR_BLACK),
GEM("opal", "white",                   6,  0,  800, 15,  6, GEMSTONE, CLR_WHITE),
GEM("chrysoberyl", "yellow",           7,  0,  700, 15,  5, GEMSTONE, CLR_YELLOW),
GEM("garnet", "red",                   7,  0,  700, 15,  7, GEMSTONE, CLR_RED),
GEM("amethyst", "violet",              8,  0,  600, 15,  7, GEMSTONE, CLR_MAGENTA),
GEM("jasper", "red",                   8,  0,  500, 15,  7, GEMSTONE, CLR_RED),
GEM("fluorite", "violet",              9,  0,  400, 15,  4, GEMSTONE, CLR_MAGENTA),
GEM("obsidian", "black",               9,  0,  200, 15,  6, GEMSTONE, CLR_BLACK),
GEM("agate", "orange",                 10,  0,  200, 15,  6, GEMSTONE, CLR_ORANGE),
GEM("jade", "green",                   10,  0,  300, 15,  6, GEMSTONE, CLR_GREEN),
GEM("worthless piece of white glass", "white",   280, 0, 0, 6, 5, GLASS, CLR_WHITE),
GEM("worthless piece of blue glass", "blue",     280, 0, 0, 6, 5, GLASS, CLR_BRIGHT_BLUE),
GEM("worthless piece of red glass", "red",       280, 0, 0, 6, 5, GLASS, CLR_RED),
GEM("worthless piece of yellowish brown glass", "yellowish brown",
												 280, 0, 0, 6, 5, GLASS, CLR_BROWN),
GEM("worthless piece of orange glass", "orange", 280, 0, 0, 6, 5, GLASS, CLR_ORANGE),
GEM("worthless piece of yellow glass", "yellow", 280, 0, 0, 6, 5, GLASS, CLR_YELLOW),
GEM("worthless piece of black glass",  "black",  280, 0, 0, 6, 5, GLASS, CLR_BLACK),
GEM("worthless piece of green glass", "green",   280, 0, 0, 6, 5, GLASS, CLR_GREEN),
GEM("worthless piece of violet glass", "violet", 280, 0, 0, 6, 5, GLASS, CLR_MAGENTA),

/* Placement note: there is a wishable subrange for   
 * "gray stones" in the o_ranges[] array in objnam.c  
 * that is currently everything between luckstones and flint (inclusive).
 */
ROCK("luckstone", "gray",			0, 30,  0,   60, 15, 15, 1, 10, 7, MINERAL, CLR_GRAY),
ROCK("healthstone", "gray",			0, 40,  0,   60, 15, 15, 1, 10, 7, MINERAL, CLR_GRAY),
ROCK("manastone", "gray",			0, 5,   0,   60, 15, 15, 1, 10, 4, MINERAL, CLR_GRAY),
ROCK("stone of magic resistance", "gray",	0, 5,   0,   60, 35, 35, 1, 10, 8, MINERAL, CLR_GRAY),
ROCK("sleepstone", "gray",			0, 5,   0,   60, 25, 25, 1, 10, 5, MINERAL, CLR_GRAY),
ROCK("loadboulder", "gray",			0, 5,  6000, 60, 75, 75, 1, 6000, 7, MINERAL, CLR_GRAY),
ROCK("loadstone", "gray",			0, 40, 1200, 60, 40, 40, 1, 1200, 6, MINERAL, CLR_GRAY),
ROCK("touchstone", "gray",			0, 30,  0,   60, 15, 15, 1, 10, 6, MINERAL, CLR_GRAY),
ROCK("salt chunk", "gray", 		   	0, 25,  0,   60, 17, 17, 0, 10, 2, MINERAL, CLR_GRAY),
ROCK("whetstone", "gray",			0, 10,  0,   60, 15, 15, 1, 10, 7, MINERAL, CLR_GRAY),
ROCK("flint", "gray",				0, 60,  0,   60, 20, 20, 0, 10, 7, MINERAL, CLR_GRAY),
ROCK("rock", (char *)0,				1,2100, 0,    0, 10, 10, 0, 10, 7, MINERAL, CLR_GRAY),
#undef GEM
#undef ROCK

/* miscellaneous ... */
/* Note: boulders and rocks are not normally created at random; the
 * probabilities only come into effect when you try to polymorph them.
 * Boulders weigh more than MAX_CARR_CAP; statues use corpsenm to take
 * on a specific type and may act as containers (both affect weight).
 */
OBJECT(OBJ("boulder",(char *)0), BITS(1,0,0,0,0,0,0,0,1,0,0,P_NONE,MINERAL), 0,
		ROCK_CLASS,   500, 0, 6000,  0, 20, 20, 0, 0, 1000, HI_MINERAL),
OBJECT(OBJ("statue", (char *)0), BITS(1,0,0,1,0,0,0,0,0,0,0,P_NONE,MINERAL), 0,
		ROCK_CLASS,  4500, 0, 2500,  0, 20, 20, 0, 0, 200, CLR_WHITE),

OBJECT(OBJ("heavy iron ball", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		BALL_CLASS,  4445, 0,  1200, 10, 25, 25, 0, 0,  200, HI_METAL),
						/* +d4 when "very heavy" */
OBJECT(OBJ("quite heavy iron ball", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		BALL_CLASS,  500, 0,  1600, 10, 35, 35, 0, 0,  200, CLR_GREEN),
OBJECT(OBJ("really heavy iron ball", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		BALL_CLASS,  50, 0,  2000, 10, 45, 45, 0, 0,  200, CLR_RED),
OBJECT(OBJ("extremely heavy iron ball", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		BALL_CLASS,  5, 0,  2400, 10, 55, 55, 0, 0,  200, CLR_ORANGE),

OBJECT(OBJ("iron chain", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		CHAIN_CLASS, 4445, 0,  120,  0,  4,  4, 0, 0,  200, HI_METAL),
						/* +1 both l & s */
OBJECT(OBJ("rotating chain", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		CHAIN_CLASS, 500, 0,  240,  0,  8,  8, 0, 0,  200, CLR_BRIGHT_BLUE),
OBJECT(OBJ("scourge", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
		CHAIN_CLASS, 50, 0,  360,  0,  15,  15, 0, 0,  200, CLR_BRIGHT_MAGENTA),
OBJECT(OBJ("nunchiaku", (char *)0), BITS(1,0,0,0,0,0,0,0,0,0,WHACK,P_FLAIL,IRON), 0,
/* spelled wrong on purpose, as the samurai has another item with that name --Amy */
		CHAIN_CLASS, 5, 0,  480,  0,  24,  24, 0, 0,  200, CLR_BRIGHT_GREEN),
/* extra balls and chains for convict mainly (he can advance flail skill by swinging them) --Amy */

OBJECT(OBJ("blinding venom", "splash of venom"),
		BITS(0,1,0,0,0,0,0,1,0,0,0,P_NONE,LIQUID), 0,
		VENOM_CLASS,  2490, 0,	 1,  0,  0,  0, 0, 0,	 0, HI_ORGANIC),
OBJECT(OBJ("tail spikes", "splash of venom"),
		BITS(0,1,0,0,0,0,0,1,0,0,0,P_NONE,LIQUID), 0,
		VENOM_CLASS,  10, 0,	 1,  0,  6,  6, 0, 0,	 0, CLR_BLACK),
OBJECT(OBJ("faerie floss rhing", "splash of venom"),
		BITS(0,1,0,0,0,0,0,1,0,0,0,P_NONE,LIQUID), 0,
		VENOM_CLASS,  10, 0,	 1,  0,  0,  0, 0, 0,	 0, CLR_BRIGHT_MAGENTA),
OBJECT(OBJ("acid venom", "splash of venom"),
		BITS(0,1,0,0,0,0,0,1,0,0,0,P_NONE,LIQUID), 0,
		VENOM_CLASS,  2490, 0,	 1,  0,  6,  6, 0, 0,	 0, HI_ORGANIC),
		/* +d6 small or large */

/* fencepost, the deadly Array Terminator -- name [1st arg] *must* be NULL */
	OBJECT(OBJ((char *)0,(char *)0), BITS(0,0,0,0,0,0,0,0,0,0,0,P_NONE,0), 0,
		ILLOBJ_CLASS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
}; /* objects[] */

#ifndef OBJECTS_PASS_2_

/* perform recursive compilation for second structure */
#  undef OBJ
#  undef OBJECT
#  define OBJECTS_PASS_2_
#include "objects.c"

void NDECL(objects_init);

/* dummy routine used to force linkage */
void
objects_init()
{
    return;
}

#endif	/* !OBJECTS_PASS_2_ */

/*objects.c*/
