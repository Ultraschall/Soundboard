#pragma once

#include "JuceHeader.h"
#include "Identifier.h"

struct ClipModel
{
	ClipModel(ValueTree v)
            : state(v)
    {
        jassert(v.hasType(IDs::CLIP));

        uuid.referTo(state, IDs::uuid, nullptr);
        index.referTo(state, IDs::index, nullptr);
        playerUuid.referTo(state, IDs::player_uuid, nullptr);
    }

    ValueTree state;
    CachedValue<String> uuid;
    CachedValue<int> index;
    CachedValue<String> playerUuid;
};