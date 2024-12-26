/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/manager/form_event/form_event_manager.h"

namespace OHOS::Ace::NG {

void FormEventManager::AddEtsCardTouchEventCallback(int32_t pointId, EtsCardTouchEventCallback&& callback)
{
    if (!callback || pointId < 0) {
        return;
    }

    etsCardTouchEventCallback_[pointId] = std::move(callback);
}

void FormEventManager::AddEtsCardAxisEventCallback(int32_t pointId, EtsCardAxisEventCallback&& callback)
{
    if (!callback || pointId < 0) {
        return;
    }

    etsCardAxisEventCallback_[pointId] = std::move(callback);
}

void FormEventManager::HandleEtsCardTouchEvent(const TouchEvent& point, SerializedGesture& serializedGesture)
{
    if (point.id < 0) {
        return;
    }

    auto iter = etsCardTouchEventCallback_.find(point.id);
    if (iter == etsCardTouchEventCallback_.end()) {
        return;
    }
    if (iter->second) {
        iter->second(point, serializedGesture);
    }
}

void FormEventManager::HandleEtsCardAxisEvent(const AxisEvent& point, SerializedGesture& serializedGesture)
{
    if (point.id < 0) {
        return;
    }

    auto iter = etsCardAxisEventCallback_.find(point.id);
    if (iter == etsCardAxisEventCallback_.end()) {
        return;
    }
    if (iter->second) {
        iter->second(point, serializedGesture);
    }
}

void FormEventManager::RemoveEtsCardTouchEventCallback(int32_t pointId)
{
    if (pointId < 0) {
        return;
    }

    auto iter = etsCardTouchEventCallback_.find(pointId);
    if (iter == etsCardTouchEventCallback_.end()) {
        return;
    }

    etsCardTouchEventCallback_.erase(iter);
}

void FormEventManager::RemoveEtsCardAxisEventCallback(int32_t pointId)
{
    if (pointId < 0) {
        return;
    }

    auto iter = etsCardAxisEventCallback_.find(pointId);
    if (iter == etsCardAxisEventCallback_.end()) {
        return;
    }

    etsCardAxisEventCallback_.erase(iter);
}

void FormEventManager::ClearEtsCardTouchEventCallback()
{
    etsCardTouchEventCallback_.clear();
}


void FormEventManager::ClearEtsCardAxisEventCallback()
{
    etsCardAxisEventCallback_.clear();
}

} //OHOS::Ace::NG
