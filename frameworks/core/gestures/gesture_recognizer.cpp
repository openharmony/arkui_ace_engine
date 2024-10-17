/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/gestures/gesture_recognizer.h"

#include "core/common/container.h"

namespace OHOS::Ace {
namespace {

RefPtr<GestureReferee> GetCurrentGestureReferee()
{
    auto container = Container::Current();
    if (!container) {
        return nullptr;
    }
    auto pipelineBase = container->GetPipelineContext();
    if (!pipelineBase) {
        return nullptr;
    }
    auto eventManager = pipelineBase->GetEventManager();
    if (!eventManager) {
        return nullptr;
    }
    return eventManager->GetGestureReferee();
}

}

bool GestureRecognizer::HandleEvent(const TouchEvent& point)
{
    switch (point.type) {
        case TouchType::MOVE:
            HandleTouchMoveEvent(point);
            break;
        case TouchType::DOWN:
            deviceId_ = point.deviceId;
            deviceType_ = point.sourceType;
            HandleTouchDownEvent(point);
            break;
        case TouchType::UP:
            HandleTouchUpEvent(point);
            break;
        case TouchType::CANCEL:
            HandleTouchCancelEvent(point);
            break;
        default:
            LOGW("unknown touch type");
            break;
    }
    return true;
}

bool GestureRecognizer::HandleEvent(const AxisEvent& event)
{
    switch (event.action) {
        case AxisAction::BEGIN:
            deviceId_ = event.deviceId;
            deviceType_ = event.sourceType;
            HandleTouchDownEvent(event);
        case AxisAction::UPDATE:
            HandleTouchMoveEvent(event);
            break;
        case AxisAction::END:
            HandleTouchUpEvent(event);
            break;
        default:
            HandleTouchCancelEvent(event);
            LOGW("unknown touch type");
            break;
    }
    return true;
}

void GestureRecognizer::AddToReferee(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    auto gestureGroup = gestureGroup_.Upgrade();
    if (gestureGroup) {
        gestureGroup->AddToReferee(touchId, recognizer);
        return;
    }
    auto referee = GetCurrentGestureReferee();
    if (referee) {
        referee->AddGestureRecognizer(touchId, recognizer);
    }
}

void GestureRecognizer::DelFromReferee(size_t touchId, const RefPtr<GestureRecognizer>& recognizer)
{
    auto gestureGroup = gestureGroup_.Upgrade();
    if (gestureGroup) {
        gestureGroup->DelFromReferee(touchId, recognizer);
        return;
    }
    auto referee = GetCurrentGestureReferee();
    if (referee) {
        referee->DelGestureRecognizer(touchId, recognizer);
    }
}

void GestureRecognizer::BatchAdjudicate(
    const std::set<size_t>& touchIds, const RefPtr<GestureRecognizer>& recognizer, GestureDisposal disposal)
{
    auto gestureGroup = gestureGroup_.Upgrade();
    if (gestureGroup) {
        gestureGroup->BatchAdjudicate(touchIds, recognizer, disposal);
        return;
    }

    std::set<size_t> copyIds = touchIds;
    auto referee = GetCurrentGestureReferee();
    if (!referee) {
        LOGW("No GestureReferee in GestureRecoginer.");
        return;
    }
    for (auto pointerId : copyIds) {
        referee->Adjudicate(pointerId, recognizer, disposal);
    }
}
} // namespace OHOS::Ace
