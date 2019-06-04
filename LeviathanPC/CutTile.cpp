#include "stdafx.h"
#include "CutTile.h"


CutTile::CutTile (char *filename, float scale)
{
	this->sprite = _new Sprite (filename);
	this->sprite->setFilter (GPU_FILTER_LINEAR);

	this->scale = scale;
}


CutTile::~CutTile () 
{
	delete this->sprite;
}


float CutTile::getFadeIn ()
{
	return this->timing.fade_in;
}


float CutTile::getStayTime () 
{
	return this->timing.stay_time;
}


float CutTile::getFadeOut () 
{
	return this->timing.fade_out;
}


void CutTile::setFadeIn (float value) 
{
	this->timing.fade_in = value;

	return;
}


void CutTile::setStayTime (float value)
{
	this->timing.stay_time = value;

	return;
}


void CutTile::setFadeOut (float value) 
{
	this->timing.fade_out = value;

	return;
}


void CutTile::render (GPU_Target * screen) 
{
	this->sprite->render (screen, 0.0f, 0.0f, this->scale, NULL);

	return;
}


void CutTile::setAlpha (Uint8 alpha)
{
	this->sprite->setAlpha (alpha);

	return;
}
