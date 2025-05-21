#include "res.hpp"
#include "PopWork/resources/resourcemanager.hpp"
#include <cstdint>

using namespace PopWork;

#pragma warning(disable : 4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool PopWork::ExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName, "Game") == 0)
		return ExtractGameResources(theManager);
	if (strcmp(theName, "Hungarr") == 0)
		return ExtractHungarrResources(theManager);
	if (strcmp(theName, "Init") == 0)
		return ExtractInitResources(theManager);
	if (strcmp(theName, "TitleScreen") == 0)
		return ExtractTitleScreenResources(theManager);
	return false;
}

PopWork::ResourceId PopWork::GetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string, int> MyMap;
	static MyMap aMap;
	if (aMap.empty())
	{
		for (int i = 0; i < RESOURCE_ID_MAX; i++)
			aMap[GetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId)anItr->second;
}

// Game Resources
Image *PopWork::IMAGE_BG0;
Image *PopWork::IMAGE_BG1;
Image *PopWork::IMAGE_BG2;
Image *PopWork::IMAGE_BUTTON_DOWN;
Image *PopWork::IMAGE_BUTTON_NORMAL;
Image *PopWork::IMAGE_BUTTON_OVER;
Image *PopWork::IMAGE_CHECKBOX;
Image *PopWork::IMAGE_DIALOG_BOX;
Image *PopWork::IMAGE_DIALOG_BUTTON;
Image *PopWork::IMAGE_ROBOTROBOT;
Image *PopWork::IMAGE_SLIDER_THUMB;
Image *PopWork::IMAGE_SLIDER_TRACK;
Image *PopWork::IMAGE_TESTPIXEL;
int PopWork::SOUND_MUTATOR;
int PopWork::SOUND_TIMER;

bool PopWork::ExtractGameResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BG0 = aMgr.GetImageThrow("IMAGE_BG0");
		IMAGE_BG1 = aMgr.GetImageThrow("IMAGE_BG1");
		IMAGE_BG2 = aMgr.GetImageThrow("IMAGE_BG2");
		IMAGE_BUTTON_DOWN = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN");
		IMAGE_BUTTON_NORMAL = aMgr.GetImageThrow("IMAGE_BUTTON_NORMAL");
		IMAGE_BUTTON_OVER = aMgr.GetImageThrow("IMAGE_BUTTON_OVER");
		IMAGE_CHECKBOX = aMgr.GetImageThrow("IMAGE_CHECKBOX");
		IMAGE_DIALOG_BOX = aMgr.GetImageThrow("IMAGE_DIALOG_BOX");
		IMAGE_DIALOG_BUTTON = aMgr.GetImageThrow("IMAGE_DIALOG_BUTTON");
		IMAGE_ROBOTROBOT = aMgr.GetImageThrow("IMAGE_ROBOTROBOT");
		IMAGE_SLIDER_THUMB = aMgr.GetImageThrow("IMAGE_SLIDER_THUMB");
		IMAGE_SLIDER_TRACK = aMgr.GetImageThrow("IMAGE_SLIDER_TRACK");
		IMAGE_TESTPIXEL = aMgr.GetImageThrow("IMAGE_TESTPIXEL");
		SOUND_MUTATOR = aMgr.GetSoundThrow("SOUND_MUTATOR");
		SOUND_TIMER = aMgr.GetSoundThrow("SOUND_TIMER");
	}
	catch (ResourceManagerException &)
	{
		return false;
	}
	return true;
}

// Hungarr Resources
Image *PopWork::IMAGE_ATOMIC_EXPLOSION;
Image *PopWork::IMAGE_BOMB_RADIAL_DEATH;
Image *PopWork::IMAGE_HUNGARR_BEAM_DOWN;
Image *PopWork::IMAGE_HUNGARR_BEAM_LEFT;
Image *PopWork::IMAGE_HUNGARR_BEAM_RIGHT;
Image *PopWork::IMAGE_HUNGARR_BEAM_UP;
Image *PopWork::IMAGE_HUNGARR_HORIZ;
Image *PopWork::IMAGE_HUNGARR_SMALL;
Image *PopWork::IMAGE_HUNGARR_VERT;
Image *PopWork::IMAGE_PARTICLE_LIGHTNING;
Image *PopWork::IMAGE_PLANETS;
Image *PopWork::IMAGE_SPARK;
int PopWork::SOUND_BEAM_HIT;
int PopWork::SOUND_BEAM_MOVING;
int PopWork::SOUND_BUTTON;
int PopWork::SOUND_EXPLOSION;
int PopWork::SOUND_GAME_OVER_CLICK;
int PopWork::SOUND_GAME_OVER_RESTART;
int PopWork::SOUND_GAME_OVER_STATS;
int PopWork::SOUND_GAME_OVER_TEXT;
int PopWork::SOUND_LEVEL_UP1;
int PopWork::SOUND_LEVEL_UP2;
int PopWork::SOUND_LEVEL_UP3;
int PopWork::SOUND_LEVEL_UP4;
int PopWork::SOUND_MAGZAP;
int PopWork::SOUND_PLANET;
int PopWork::SOUND_PLANET_HIT;
int PopWork::SOUND_REGION_FILLED;

bool PopWork::ExtractHungarrResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ATOMIC_EXPLOSION = aMgr.GetImageThrow("IMAGE_ATOMIC_EXPLOSION");
		IMAGE_BOMB_RADIAL_DEATH = aMgr.GetImageThrow("IMAGE_BOMB_RADIAL_DEATH");
		IMAGE_HUNGARR_BEAM_DOWN = aMgr.GetImageThrow("IMAGE_HUNGARR_BEAM_DOWN");
		IMAGE_HUNGARR_BEAM_LEFT = aMgr.GetImageThrow("IMAGE_HUNGARR_BEAM_LEFT");
		IMAGE_HUNGARR_BEAM_RIGHT = aMgr.GetImageThrow("IMAGE_HUNGARR_BEAM_RIGHT");
		IMAGE_HUNGARR_BEAM_UP = aMgr.GetImageThrow("IMAGE_HUNGARR_BEAM_UP");
		IMAGE_HUNGARR_HORIZ = aMgr.GetImageThrow("IMAGE_HUNGARR_HORIZ");
		IMAGE_HUNGARR_SMALL = aMgr.GetImageThrow("IMAGE_HUNGARR_SMALL");
		IMAGE_HUNGARR_VERT = aMgr.GetImageThrow("IMAGE_HUNGARR_VERT");
		IMAGE_PARTICLE_LIGHTNING = aMgr.GetImageThrow("IMAGE_PARTICLE_LIGHTNING");
		IMAGE_PLANETS = aMgr.GetImageThrow("IMAGE_PLANETS");
		IMAGE_SPARK = aMgr.GetImageThrow("IMAGE_SPARK");
		SOUND_BEAM_HIT = aMgr.GetSoundThrow("SOUND_BEAM_HIT");
		SOUND_BEAM_MOVING = aMgr.GetSoundThrow("SOUND_BEAM_MOVING");
		SOUND_BUTTON = aMgr.GetSoundThrow("SOUND_BUTTON");
		SOUND_EXPLOSION = aMgr.GetSoundThrow("SOUND_EXPLOSION");
		SOUND_GAME_OVER_CLICK = aMgr.GetSoundThrow("SOUND_GAME_OVER_CLICK");
		SOUND_GAME_OVER_RESTART = aMgr.GetSoundThrow("SOUND_GAME_OVER_RESTART");
		SOUND_GAME_OVER_STATS = aMgr.GetSoundThrow("SOUND_GAME_OVER_STATS");
		SOUND_GAME_OVER_TEXT = aMgr.GetSoundThrow("SOUND_GAME_OVER_TEXT");
		SOUND_LEVEL_UP1 = aMgr.GetSoundThrow("SOUND_LEVEL_UP1");
		SOUND_LEVEL_UP2 = aMgr.GetSoundThrow("SOUND_LEVEL_UP2");
		SOUND_LEVEL_UP3 = aMgr.GetSoundThrow("SOUND_LEVEL_UP3");
		SOUND_LEVEL_UP4 = aMgr.GetSoundThrow("SOUND_LEVEL_UP4");
		SOUND_MAGZAP = aMgr.GetSoundThrow("SOUND_MAGZAP");
		SOUND_PLANET = aMgr.GetSoundThrow("SOUND_PLANET");
		SOUND_PLANET_HIT = aMgr.GetSoundThrow("SOUND_PLANET_HIT");
		SOUND_REGION_FILLED = aMgr.GetSoundThrow("SOUND_REGION_FILLED");
	}
	catch (ResourceManagerException &)
	{
		return false;
	}
	return true;
}

// Init Resources
Font *PopWork::FONT_DEFAULT;
Font *PopWork::FONT_HUNGARR;
Image *PopWork::IMAGE_CUSTOM_DRAGGING;
Image *PopWork::IMAGE_CUSTOM_HAND;
Image *PopWork::IMAGE_CUSTOM_POINTER;
Image *PopWork::IMAGE_CUSTOM_TEXT;
Image *PopWork::IMAGE_HUNGARR_LOGO;

bool PopWork::ExtractInitResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_DEFAULT = aMgr.GetFontThrow("FONT_DEFAULT");
		FONT_HUNGARR = aMgr.GetFontThrow("FONT_HUNGARR");
		IMAGE_CUSTOM_DRAGGING = aMgr.GetImageThrow("IMAGE_CUSTOM_DRAGGING");
		IMAGE_CUSTOM_HAND = aMgr.GetImageThrow("IMAGE_CUSTOM_HAND");
		IMAGE_CUSTOM_POINTER = aMgr.GetImageThrow("IMAGE_CUSTOM_POINTER");
		IMAGE_CUSTOM_TEXT = aMgr.GetImageThrow("IMAGE_CUSTOM_TEXT");
		IMAGE_HUNGARR_LOGO = aMgr.GetImageThrow("IMAGE_HUNGARR_LOGO");
	}
	catch (ResourceManagerException &)
	{
		return false;
	}
	return true;
}

// TitleScreen Resources
Image *PopWork::IMAGE_LOADER_BAR;
Image *PopWork::IMAGE_LOADER_LOADINGTXT;
int PopWork::SOUND_CONTINUE;

bool PopWork::ExtractTitleScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_LOADER_BAR = aMgr.GetImageThrow("IMAGE_LOADER_BAR");
		IMAGE_LOADER_LOADINGTXT = aMgr.GetImageThrow("IMAGE_LOADER_LOADINGTXT");
		SOUND_CONTINUE = aMgr.GetSoundThrow("SOUND_CONTINUE");
	}
	catch (ResourceManagerException &)
	{
		return false;
	}
	return true;
}

static void *gResources[] = {&FONT_DEFAULT,
							 &FONT_HUNGARR,
							 &IMAGE_CUSTOM_POINTER,
							 &IMAGE_CUSTOM_HAND,
							 &IMAGE_CUSTOM_DRAGGING,
							 &IMAGE_CUSTOM_TEXT,
							 &IMAGE_HUNGARR_LOGO,
							 &IMAGE_LOADER_BAR,
							 &IMAGE_LOADER_LOADINGTXT,
							 &SOUND_CONTINUE,
							 &SOUND_MUTATOR,
							 &SOUND_TIMER,
							 &IMAGE_ROBOTROBOT,
							 &IMAGE_CHECKBOX,
							 &IMAGE_BG0,
							 &IMAGE_BG1,
							 &IMAGE_BG2,
							 &IMAGE_BUTTON_DOWN,
							 &IMAGE_BUTTON_OVER,
							 &IMAGE_BUTTON_NORMAL,
							 &IMAGE_DIALOG_BOX,
							 &IMAGE_DIALOG_BUTTON,
							 &IMAGE_SLIDER_TRACK,
							 &IMAGE_SLIDER_THUMB,
							 &IMAGE_HUNGARR_SMALL,
							 &IMAGE_HUNGARR_BEAM_UP,
							 &IMAGE_HUNGARR_BEAM_DOWN,
							 &IMAGE_HUNGARR_BEAM_LEFT,
							 &IMAGE_HUNGARR_BEAM_RIGHT,
							 &IMAGE_HUNGARR_HORIZ,
							 &IMAGE_HUNGARR_VERT,
							 &IMAGE_ATOMIC_EXPLOSION,
							 &IMAGE_BOMB_RADIAL_DEATH,
							 &IMAGE_PLANETS,
							 &IMAGE_SPARK,
							 &IMAGE_PARTICLE_LIGHTNING,
							 &SOUND_MAGZAP,
							 &SOUND_BUTTON,
							 &SOUND_PLANET,
							 &SOUND_LEVEL_UP1,
							 &SOUND_LEVEL_UP2,
							 &SOUND_EXPLOSION,
							 &SOUND_BEAM_HIT,
							 &SOUND_PLANET_HIT,
							 &SOUND_BEAM_MOVING,
							 &SOUND_LEVEL_UP4,
							 &SOUND_LEVEL_UP3,
							 &SOUND_GAME_OVER_CLICK,
							 &SOUND_GAME_OVER_STATS,
							 &SOUND_GAME_OVER_RESTART,
							 &SOUND_GAME_OVER_TEXT,
							 &SOUND_REGION_FILLED,
							 IMAGE_TESTPIXEL,
							 NULL};

Image *PopWork::LoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image **)gResources[theId]) = theManager->LoadImage(GetStringIdById(theId)));
}

Image *PopWork::GetImageById(int theId)
{
	return *(Image **)gResources[theId];
}

Font *PopWork::GetFontById(int theId)
{
	return *(Font **)gResources[theId];
}

int PopWork::GetSoundById(int theId)
{
	return *(int *)gResources[theId];
}

static PopWork::ResourceId GetIdByVariable(const void *theVariable)
{
	typedef std::map<int, int> MyMap;
	static MyMap aMap;
	if (gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for (int i = 0; i < RESOURCE_ID_MAX; i++)
			aMap[*(int *)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((uintptr_t)theVariable);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId)anItr->second;
}

PopWork::ResourceId PopWork::GetIdByImage(Image *theImage)
{
	return GetIdByVariable(theImage);
}

PopWork::ResourceId PopWork::GetIdByFont(Font *theFont)
{
	return GetIdByVariable(theFont);
}

PopWork::ResourceId PopWork::GetIdBySound(int theSound)
{
	return GetIdByVariable((void *)theSound);
}

const char *PopWork::GetStringIdById(int theId)
{
	switch (theId)
	{
	case FONT_DEFAULT_ID:
		return "FONT_DEFAULT";
	case FONT_HUNGARR_ID:
		return "FONT_HUNGARR";
	case IMAGE_CUSTOM_POINTER_ID:
		return "IMAGE_CUSTOM_POINTER";
	case IMAGE_CUSTOM_HAND_ID:
		return "IMAGE_CUSTOM_HAND";
	case IMAGE_CUSTOM_DRAGGING_ID:
		return "IMAGE_CUSTOM_DRAGGING";
	case IMAGE_CUSTOM_TEXT_ID:
		return "IMAGE_CUSTOM_TEXT";
	case IMAGE_HUNGARR_LOGO_ID:
		return "IMAGE_HUNGARR_LOGO";
	case IMAGE_LOADER_BAR_ID:
		return "IMAGE_LOADER_BAR";
	case IMAGE_LOADER_LOADINGTXT_ID:
		return "IMAGE_LOADER_LOADINGTXT";
	case SOUND_CONTINUE_ID:
		return "SOUND_CONTINUE";
	case SOUND_MUTATOR_ID:
		return "SOUND_MUTATOR";
	case SOUND_TIMER_ID:
		return "SOUND_TIMER";
	case IMAGE_ROBOTROBOT_ID:
		return "IMAGE_ROBOTROBOT";
	case IMAGE_CHECKBOX_ID:
		return "IMAGE_CHECKBOX";
	case IMAGE_BG0_ID:
		return "IMAGE_BG0";
	case IMAGE_BG1_ID:
		return "IMAGE_BG1";
	case IMAGE_BG2_ID:
		return "IMAGE_BG2";
	case IMAGE_BUTTON_DOWN_ID:
		return "IMAGE_BUTTON_DOWN";
	case IMAGE_BUTTON_OVER_ID:
		return "IMAGE_BUTTON_OVER";
	case IMAGE_BUTTON_NORMAL_ID:
		return "IMAGE_BUTTON_NORMAL";
	case IMAGE_DIALOG_BOX_ID:
		return "IMAGE_DIALOG_BOX";
	case IMAGE_DIALOG_BUTTON_ID:
		return "IMAGE_DIALOG_BUTTON";
	case IMAGE_SLIDER_TRACK_ID:
		return "IMAGE_SLIDER_TRACK";
	case IMAGE_TESTPIXEL_ID:
		return "IMAGE_TESTPIXEL";
	case IMAGE_SLIDER_THUMB_ID:
		return "IMAGE_SLIDER_THUMB";
	case IMAGE_HUNGARR_SMALL_ID:
		return "IMAGE_HUNGARR_SMALL";
	case IMAGE_HUNGARR_BEAM_UP_ID:
		return "IMAGE_HUNGARR_BEAM_UP";
	case IMAGE_HUNGARR_BEAM_DOWN_ID:
		return "IMAGE_HUNGARR_BEAM_DOWN";
	case IMAGE_HUNGARR_BEAM_LEFT_ID:
		return "IMAGE_HUNGARR_BEAM_LEFT";
	case IMAGE_HUNGARR_BEAM_RIGHT_ID:
		return "IMAGE_HUNGARR_BEAM_RIGHT";
	case IMAGE_HUNGARR_HORIZ_ID:
		return "IMAGE_HUNGARR_HORIZ";
	case IMAGE_HUNGARR_VERT_ID:
		return "IMAGE_HUNGARR_VERT";
	case IMAGE_ATOMIC_EXPLOSION_ID:
		return "IMAGE_ATOMIC_EXPLOSION";
	case IMAGE_BOMB_RADIAL_DEATH_ID:
		return "IMAGE_BOMB_RADIAL_DEATH";
	case IMAGE_PLANETS_ID:
		return "IMAGE_PLANETS";
	case IMAGE_SPARK_ID:
		return "IMAGE_SPARK";
	case IMAGE_PARTICLE_LIGHTNING_ID:
		return "IMAGE_PARTICLE_LIGHTNING";
	case SOUND_MAGZAP_ID:
		return "SOUND_MAGZAP";
	case SOUND_BUTTON_ID:
		return "SOUND_BUTTON";
	case SOUND_PLANET_ID:
		return "SOUND_PLANET";
	case SOUND_LEVEL_UP1_ID:
		return "SOUND_LEVEL_UP1";
	case SOUND_LEVEL_UP2_ID:
		return "SOUND_LEVEL_UP2";
	case SOUND_EXPLOSION_ID:
		return "SOUND_EXPLOSION";
	case SOUND_BEAM_HIT_ID:
		return "SOUND_BEAM_HIT";
	case SOUND_PLANET_HIT_ID:
		return "SOUND_PLANET_HIT";
	case SOUND_BEAM_MOVING_ID:
		return "SOUND_BEAM_MOVING";
	case SOUND_LEVEL_UP4_ID:
		return "SOUND_LEVEL_UP4";
	case SOUND_LEVEL_UP3_ID:
		return "SOUND_LEVEL_UP3";
	case SOUND_GAME_OVER_CLICK_ID:
		return "SOUND_GAME_OVER_CLICK";
	case SOUND_GAME_OVER_STATS_ID:
		return "SOUND_GAME_OVER_STATS";
	case SOUND_GAME_OVER_RESTART_ID:
		return "SOUND_GAME_OVER_RESTART";
	case SOUND_GAME_OVER_TEXT_ID:
		return "SOUND_GAME_OVER_TEXT";
	case SOUND_REGION_FILLED_ID:
		return "SOUND_REGION_FILLED";
	default:
		return "";
	}
}
