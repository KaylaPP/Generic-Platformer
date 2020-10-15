//
//  EntityVars.cpp
//  Hello PGE
//
//  Created by Kevin Puig on 9/23/20.
//  Copyright © 2020 Kevin Puig. All rights reserved.
//

#include "EntityVars.hpp"

namespace kpg
{
    bool start = false;
    bool bJumped = false;
    bool bMovingLeft = false;
    bool bMovingRight = false;

    std::unordered_map<uint32_t, std::pair<std::string, kpg::LoopingEntity*>> Entities;
    std::unordered_set<uint32_t> KnownIDs;
    std::queue<uint32_t> DeadIDs;
}
