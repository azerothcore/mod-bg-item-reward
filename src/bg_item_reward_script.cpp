/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Tokenize.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

class BgItemRewardScript : public BGScript
{
public:
    BgItemRewardScript() : BGScript("mod_bg_item_reward_bg_script", {
        ALLBATTLEGROUNDHOOK_ON_BATTLEGROUND_END_REWARD
    }) { }

    void OnBattlegroundEndReward(Battleground* bg, Player* player, TeamId winnerTeamId) override
    {
        std::string status;

        if (winnerTeamId == TEAM_NEUTRAL)
        {
            status = "Tie";
        }
        else {
            status = winnerTeamId == player->GetBgTeamId() ? "Win" : "Defeat";
        }

        switch (bg->GetMapId())
        {
            case 30:  // AV
            {
                AddItems(player, "ModBGItemReward.AV" + status + "Items");
                break;
            }
            case 489: // WSG
            {
                AddItems(player, "ModBGItemReward.WSG" + status + "Items");
                break;
            }
            case 529: // AB
                AddItems(player, "ModBGItemReward.AB" + status + "Items");
                break;
            case 566: // EOTS
                AddItems(player, "ModBGItemReward.EOTS" + status + "Items");
                break;
            case 607: // SOTA
                AddItems(player, "ModBGItemReward.SOTA" + status + "Items");
                break;
            case 628: // IC
                AddItems(player, "ModBGItemReward.WSG" + status + "Items");
                break;
        }
    }

    void AddItems(Player* player, std::string config)
    {
        std::string items = sConfigMgr->GetOption<std::string>(config, "");

        std::vector<std::string_view> tokens = Acore::Tokenize(items, ' ', false);

        for (auto token : tokens)
        {
            if (token.empty())
            {
                continue;
            }

            std::vector<std::string_view> itemData = Acore::Tokenize(token, ':', false);

            player->AddItem(*Acore::StringTo<uint32>(itemData.at(0)), *Acore::StringTo<uint32>(itemData.at(1)));
        }
    }
};

void Addmod_bg_item_reward_bgScripts()
{
    new BgItemRewardScript();
}
