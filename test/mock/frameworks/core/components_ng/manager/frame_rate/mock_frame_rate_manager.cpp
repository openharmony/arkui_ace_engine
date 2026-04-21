/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/frame_rate/frame_rate_manager.h"

namespace OHOS::Ace::NG {
bool FrameRateManager::IsRateChanged()
{
    return isRateChanged_;
}

void FrameRateManager::SetIsRateChanged(bool isChanged)
{
    isRateChanged_ = isChanged;
}

void FrameRateManager::AddNodeRate(int32_t nodeId, const std::string& scene, int32_t rate)
{
    nodeRateMap_[nodeId] = { scene, rate };
    isRateChanged_ = true;
}

void FrameRateManager::RemoveNodeRate(int32_t nodeId)
{
    nodeRateMap_.erase(nodeId);
    isRateChanged_ = true;
}

void FrameRateManager::UpdateNodeRate(int32_t nodeId, int32_t rate)
{
    auto iter = nodeRateMap_.find(nodeId);
    if (iter != nodeRateMap_.end()) {
        iter->second.second = rate;
    }
    isRateChanged_ = true;
}

void FrameRateManager::SetAnimateRate(int32_t rate, bool hasFirstFrameAnimation)
{
    animateRate_ = rate;
    hasFirstFrameAnimation_ = hasFirstFrameAnimation;
    isRateChanged_ = true;
}

void FrameRateManager::SetDisplaySyncRate(int32_t displaySyncRate, uint32_t displaySyncType)
{
    displaySyncRate_ = displaySyncRate;
    displaySyncType_ = displaySyncType;
    isRateChanged_ = true;
}

int32_t FrameRateManager::GetDisplaySyncRate() const
{
    return displaySyncRate_;
}

std::pair<int32_t, int32_t> FrameRateManager::GetExpectedRate()
{
    return { displaySyncRate_, animateRate_ };
}
} // namespace OHOS::Ace::NG
