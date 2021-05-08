#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "game.h"
#include "state.hpp"

void dChatController_AddChat(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method) {
	//Modify chat text here for markup
	if (State.ReadGhostMessages) {
		bool wasDead = false;
		GameData_PlayerInfo* player = GetPlayerData(sourcePlayer);
		GameData_PlayerInfo* local = GetPlayerData(*Game::pLocalPlayer);
		if (player->fields.IsDead && !local->fields.IsDead) {
			local->fields.IsDead = true;
			wasDead = true;
		}
		ChatController_AddChat(__this, sourcePlayer, chatText, method);
		if (wasDead) {
			local->fields.IsDead = false;
		}
	}
	else
		ChatController_AddChat(__this, sourcePlayer, chatText, method);
}

void dChatController_SetVisible(ChatController* __this, bool visible, MethodInfo* method) {
	State.ChatActiveOriginalState = visible;
	if (State.ChatAlwaysActive)
		ChatController_SetVisible(__this, true, method);
	else
		ChatController_SetVisible(__this, visible, method);
}

void dChatBubble_SetName(ChatBubble* __this, String* playerName, bool isDead, bool voted, Color color, MethodInfo* method) {
	if (IsInGame()) {
		for (auto playerData : GetAllPlayerData()) {
			if (playerName == playerData->fields.PlayerName) {
				auto localData = GetPlayerData(*Game::pLocalPlayer);
				if (!localData)
					continue;

				if (State.RevealImpostors || localData->fields.IsImpostor)
					color = playerData->fields.IsImpostor
					? Palette__TypeInfo->static_fields->ImpostorRed
					: Palette__TypeInfo->static_fields->White;
				else
					color = Palette__TypeInfo->static_fields->White;
			}
		}
	}
	ChatBubble_SetName(__this, playerName, isDead, voted, color, method);
}

void dChatController_Update(ChatController* __this, MethodInfo* method)
{
	SaveManager__TypeInfo->static_fields->chatModeType = 1;
	SaveManager__TypeInfo->static_fields->isGuest = false;
	__this->fields.TextArea->fields.characterLimit = 500;
	ChatController_Update(__this, method);
}

//This should apply to all text fields, not just chat
bool dTextBoxTMP_IsCharAllowed(TextBoxTMP* __this, uint16_t unicode_char, MethodInfo* method)
{
	return true; //We don't care what we put in here
}