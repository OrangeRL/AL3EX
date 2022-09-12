#pragma once
#include "Utill.h"
#include "Audio.h"

class SoundDataManager
{
public:

	void Initialize();

	SoundDataHandle shotSE = 0;
	SoundDataHandle jumpSE = 0;
	SoundDataHandle damageSE = 0;
	SoundDataHandle healSE = 0;
	SoundDataHandle enemyPopSE = 0;
	SoundDataHandle hitSE = 0;
	SoundDataHandle deadEnemySE = 0;
	SoundDataHandle jumpEventSE = 0;
	SoundDataHandle curserSE = 0;
	SoundDataHandle eventclearSE = 0;
	SoundDataHandle vibrationSE = 0;
	SoundDataHandle vibrationEndSE = 0;
	SoundDataHandle bossboomSE = 0;
	SoundDataHandle bossendboomSE = 0;
	SoundDataHandle checkpointSE = 0;
	SoundDataHandle pushSE = 0;
	SoundDataHandle jumpEndSE = 0;
	SoundDataHandle dashSE = 0;
	SoundDataHandle bossJumpEndSE = 0;
	SoundDataHandle criticalSE = 0;

	SoundDataHandle titleBGM = 0;
private:
	Audio* audio = Audio::GetInstance();

};

