#include "il2cpp-appdata.h"
#include "_rpc.h"
#include "utility.h"

RpcPlayAnimation::RpcPlayAnimation(uint8_t animId)
{
	this->animId = animId;
}

void RpcPlayAnimation::Process()
{
	PlayerControl_RpcPlayAnimation(*Game::pLocalPlayer, animId, NULL);
}