#ifndef EntityVars_hpp
#define EntityVars_hpp

#include "LoopingEntity.hpp"

#include <unordered_map>
#include <unordered_set>

namespace kpg
{
    const int nWindowWidth = 1280;
    const int nWindowHeight = 720;

    const int nPlayerWidth = 64;
    const int nPlayerHeight = 64;

    extern bool start;
    extern bool bJumped;
    extern bool bMovingLeft;
    extern bool bMovingRight;

    extern std::unordered_map<uint32_t, std::pair<std::string, kpg::LoopingEntity*>> Entities;
    extern std::unordered_set<uint32_t> KnownIDs;
    extern std::queue<uint32_t> DeadIDs;
}

#endif /* EntityVars_h */
