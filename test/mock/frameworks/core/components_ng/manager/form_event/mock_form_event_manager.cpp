/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/form_event/form_event_manager.h"

namespace OHOS::Ace::NG {
void FormEventManager::AddEtsCardTouchEventCallback(int32_t pointId, EtsCardTouchEventCallback&& callback)
{
    if (pointId < 0 || !callback) {
        return;
    }
    etsCardTouchEventCallback_[pointId] = std::move(callback);
}

void FormEventManager::AddEtsCardAxisEventCallback(int32_t pointId, EtsCardAxisEventCallback&& callback)
{
    if (pointId < 0 || !callback) {
        return;
    }
    etsCardAxisEventCallback_[pointId] = std::move(callback);
}

void FormEventManager::HandleEtsCardTouchEvent(const TouchEvent& point, SerializedGesture& serializedGesture)
{
    auto iter = etsCardTouchEventCallback_.find(point.id);
    if (iter != etsCardTouchEventCallback_.end() && iter->second) {
        iter->second(point, serializedGesture);
    }
}

void FormEventManager::HandleEtsCardAxisEvent(const AxisEvent& point, SerializedGesture& serializedGesture)
{
    auto iter = etsCardAxisEventCallback_.find(point.id);
    if (iter != etsCardAxisEventCallback_.end() && iter->second) {
        iter->second(point, serializedGesture);
    }
}

void FormEventManager::RemoveEtsCardTouchEventCallback(int32_t pointId)
{
    etsCardTouchEventCallback_.erase(pointId);
}

void FormEventManager::RemoveEtsCardAxisEventCallback(int32_t pointId)
{
    etsCardAxisEventCallback_.erase(pointId);
}

void FormEventManager::ClearEtsCardTouchEventCallback()
{
    etsCardTouchEventCallback_.clear();
}

void FormEventManager::ClearEtsCardAxisEventCallback()
{
    etsCardAxisEventCallback_.clear();
}
} // namespace OHOS::Ace::NG
